/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   code.c - This module contains the procedures related to generating code
     for array operations on a uniprocessor.  In the case of multiprocessor
     code generation control is passed on to the dist.c module.
   
   v0.3 Scott Thibault - 8/93
               This code was scattered previous to v0.3.
        Scott Thibault - 10/93
	   - code_reduced was changed to reflect the fact that now NOP type
	   reduced objects are lists of assignments instead of just one.
	   - To do this code_expr was added to take the code out of the
	   switch in code_reduced and separate_reduced was added to
	   separated the list of assignments.
	   - do_location and do_gamma were changed so that offset and
	   shift include the base address now.

*/

#include <stdio.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"

#include "psi.e"
#include "dist.e"
#include "part.e"
#include "parse.e"
#include "ident.e"
#include "vect.e"
#include "sys.e"

#define NOTALLOCATED(a) ((!ISUSED(a->flags))&&(!ISPARAMETER(a->flags))&&(a->type!=RAV)&&(a->type!=CONST_ARRAY)&&(a->type!=FLOAT))


typedef struct step_node {
  int              num;
  s_expr_t         **steps;
  struct step_node *next;
} steps_t;

typedef struct names {
  char name[18];
  struct names *next;
} name_t;


int const_array_num=0;
int max_dim=0;
int max_combined=0;
name_t *allocs,*dynamics;
steps_t *step_list;


/* addto_allocs - adds expr to the list of arrays that need to be 
     allocated. */

addto_allocs(expr_t *expr)

{
  name_t *node;

  node=(name_t *) get_mem(sizeof(name_t));
  strncpy(node->name,expr->ident->string,17);
  node->next=allocs;
  allocs=node;
}


/* addto_dynamics - adds expr to the list of arrays that need to be allocated
     dynamically with get_mem. */

addto_dynamics(expr_t *expr)

{
  name_t *node;

  node=(name_t *) get_mem(sizeof(name_t));
  strncpy(node->name,expr->ident->string,17);
  node->next=dynamics;
  dynamics=node;
}


/* allocate_array - generate C code to declare an array of the appropriate
     size.  Arrays are allocated as one dimensional arrays to allow linear
     access. Output is to the variable file. */

allocate_array(ident_t *ident)

{
  int i,dynamic;

  SETUSED(ident->flags);

  if (ident->type!=VAR_FLOAT) {
    if (ident->array.dim->value>0) {
      dynamic=FALSE;
      for (i=0; i<ident->array.dim->value; i++) {
	if (ident->array.shp[i]->type!=FLOAT)
	  dynamic=TRUE;
      }

      if (dynamic) {
	fprintf(vfile,"  double *%s",ident->string);
	fprintf(vfile,"=(double *) get_mem(");
      } else {
	fprintf(vfile,"  double %s",ident->string);
	fprintf(vfile,"[");
      }
      for (i=0; i<ident->array.dim->value; i++) {
	if (i==0) {
	  if (ident->array.shp[i]->type==FLOAT)
	    fprintf(vfile,"%d",(int) ident->array.shp[i]->value);
	  else
	    fprintf(vfile,"%s",ident->array.shp[i]->string);
	} else {
	  if (ident->array.shp[i]->type==FLOAT)
	    fprintf(vfile,"*%d",(int) ident->array.shp[i]->value);
	  else
	    fprintf(vfile,"*%s",ident->array.shp[i]->string);
	}	
      }
      if (ident->array.dim->value==0)
	fprintf(vfile,"1");
      if (dynamic)
	fprintf(vfile,"*sizeof(double));\n");
      else
	fprintf(vfile,"];\n");
    } else fprintf(vfile,"  double %s[1];\n",ident->string);
  }     
} 


/* do_shapes - if expr and result's shapes have not been scanned then they
     are scanned.  Scanning results in storing *SCAN(shape) in the shape
     field for calculating loop steps.  */

do_shapes(expr_t *expr, expr_t *result)

{
  if (!ISSCANNED(expr->flags)) {
    expr->shp=vect_unop(RSCAN,expr->shp);
    expr->shp=purify_vect(expr->shp);
    SETSCANNED(expr->flags);
  }
  if (!ISSCANNED(result->flags)) {
    result->shp=vect_unop(RSCAN,result->shp);
    result->shp=purify_vect(result->shp);
    SETSCANNED(result->flags);
  }
}


/* my_gamma - generates C code to calculate Gamma(index,shp) and assign
     it to name.  dim is the length of index, and shp.  The resulting
     C code is output to file out. */

int my_gamma(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim)

{
  int ret;
  int i,j;

  index=vect_drop(s_vect(s_op(MINUS,index->shp,dim)),index);
  if (SCALAR(dim)) {
    if (dim->ident->value>0) {
      dotabf(out,0);
      fprintf(out,"%s",name);
      for (i=0; i<dim->ident->value-1; i++) {
	if (i>0) fprintf(out,"+");
	print_rav(out,index,i);
	fprintf(out,"*(int) ");
	print_rav(out,shp,i+1);
      }
      if (i>0) fprintf(out,"+");
      print_rav(out,index,dim->ident->value-1);
      fprintf(out,";\n");
      ret=TRUE;
    } else {
      dotabf(out,0);
      fprintf(out,"%s0;\n",name);
      ret=TRUE;
    }
  } else {
    ret=TRUE;
    shp=vect2array("gamma_shp",shp);
    index=vect2array("gamma_index",index);
    dotabf(out,0);
    fprintf(out,"for (i=0; i<");
    print_s_expr(out,dim);
    fprintf(out,"; i++)\n");
    dotabf(out,0);
    fprintf(out,"%s+=%s[i",name,index->ident->string);
    if (index->index!=NULL) {
      fprintf(out,"+");
      print_s_expr(out,index->index);
    }
    fprintf(out,"]*%s[i];\n",shp->ident->string);
  }
 
  return(ret);
}


/* do_location - generates C code that assigns the location of the assignment
     in the shift variable for the assignment of expr to result.  Output is
     to the temporary code file.  */

int do_location(expr_t *expr, expr_t *result)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->loc==NULL) {
    dotab(0);
    fprintf(tfile,"shift=%s;\n",result->ident->string);
  } else {
    sprintf(buf,"shift=%s+",result->ident->string);
    return(my_gamma(tfile,buf,expr->loc,result->shp,result->dim));
  }
}


/* do_gamma - generates C code that assigns the index of the assignment
     in the offset variable for the assignment of expr to result.  Output is
     to the temporary code file.  */

do_gamma(expr_t *expr, expr_t *result, int num)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->index==NULL) {
    dotab(0);
    fprintf(tfile,"offset%d=%s;\n",num,expr->ident->string);
  } else {
    sprintf(buf,"offset%d=%s+",num,expr->ident->string);
    return(my_gamma(tfile,buf,expr->index,expr->shp,expr->dim));
  }
}


/* add_steps - calculates the step for each loop in an assigment, eliminating
     a step if possible.  */

add_steps(vect_t *bound, vect_t *shp1, s_expr_t *dim , int num, int scalar)

{
  int i,j,constant,d,d2,k;
  s_expr_t **step_mask;
  int pos,last;
  double value1,value2,value3;
  vect_t *step,*pad1;
  expr_t *tmp_expr;
  steps_t *node;

  step_mask=NULL;
  if (SCALAR(dim)) {
    d=dim->ident->value;

    if (SCALAR(bound->shp)) {
      if ((int) bound->shp->ident->value<d) {
	pad1=get_vect();
	*pad1=one_vec;
	pad1->shp=get_s_expr();
	pad1->shp->ident=get_ident();
	pad1->shp->ident->type=FLOAT;
	pad1->shp->ident->value=d-(int) bound->shp->ident->value;
	bound=vect_cat(pad1,bound);
      }
    }
    
    if (scalar) {
      i=0;
      if (d>0)
	step_mask=(s_expr_t **) get_mem(d*sizeof(s_expr_t *));
      while (i<d) {
	step_mask[i]=NULL;
	i++;
      }
    } else {
      if (d>0) {
	step_mask=(s_expr_t **) get_mem(d*sizeof(s_expr_t *));
	value1=rav_value(bound,d-1,&constant);
	if ((!constant)||(value1>1)) step_mask[d-1]=&s_const1;
	else step_mask[d-1]=&s_const0;
	last=d-1;
      }       
      for (i=d-2; i>=0; i--) {
	value1=rav_value(bound,i,&constant);
	if ((constant)&&(value1>1)) {
	  j=i+1;
	  value1=1;
	  while ((constant)&&(j<=last)) {
 	    value1*=rav_value(bound,j,&constant);
	    j++;
	  }
	  if (constant)
	    value2=rav_value(shp1,i+1,&constant);
	  if (constant)
	    value3=(last<d-1) ? rav_value(shp1,last+1,&constant) : 
	      (step_mask[d-1])->ident->value;
	  if (constant) {
	    if (value2-value3*value1>0) {
	      last=i;
	      step_mask[i]=get_s_expr();
	      step_mask[i]->ident=get_ident();
	      step_mask[i]->ident->type=FLOAT;
	      step_mask[i]->ident->value=value2-value3*value1;
	    } else step_mask[i]=NULL;
	  }
	} else if (constant) {
	  step_mask[i]=NULL;
	} else {
	  if (last<d-1) {
	    step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
			      s_op(TIMES,red_rav(shp1,last+1),
				   red_rav(bound,last)));
	  } else {
	    step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
			      s_op(TIMES,step_mask[d-1],red_rav(bound,last)));
	  }
	  last=i;
	}
	step_mask[i]=red_s_expr(step_mask[i]);
      }
    }
  } else {
    fatal("Unknown dimension in add_steps");
  }
  
  node=(steps_t *) get_tmp_mem(sizeof(steps_t));
  node->num=num;
  node->steps=step_mask;
  node->next=step_list;
  step_list=node;
  
}


/* do_loop_open - generates the C for loops for an assigment with bound and
     dimension dim. */

do_loop_open(vect_t *bound, s_expr_t *dim)

{
  int i,j,constant;
  double value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=0",i);
	fprintf(tfile,"; i%d<",i);
	print_rav(tfile,bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
	ntab++;
      }
    }
  } else {
    fatal("Unknown dimension in do_loop_open");
  }
}


/* do_loop_close - generates C code to calculate the step for each loop
     as well as close it with a {.  mask indicates which loops require
     a step.  name is unused. */

do_loop_close(s_expr_t *dim, vect_t *bound, s_expr_t *rdim)

{
  int i,j,constant,d,rd,k;
  double value;
  steps_t *node;
  
  if (SCALAR(rdim)) {
    rd=rdim->ident->value;
  } else {
    fatal("Unknown dimension: do_loop_close");
  }

  if (SCALAR(dim)) {
    d=dim->ident->value;
    if (d>0) {
      value=rav_value(bound,dim->ident->value-1,&constant);
      if ((!constant)||(value>1)) {
	node=step_list->next;
	while (node!=NULL) {
	  if ((node->steps[d-1]!=NULL)&&(node->steps[d-1]!=&s_const0)) {
	    dotab(0);
	    fprintf(tfile,"offset%d+=",node->num);
	    print_s_expr(tfile,node->steps[d-1]);
	    fprintf(tfile,";\n");
	  }
	  node=node->next;
	}
	if ((step_list->steps[rd-1]!=NULL)&&
	    (step_list->steps[rd-1]!=&s_const0)) {
	  dotab(0);
	  fprintf(tfile,"shift++;\n");
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      }
    }
    k=rd-2;
    for (i=dim->ident->value-2; i>=0; i--) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	node=step_list->next;
	while (node!=NULL) {
	  if (node->steps[i]!=NULL) {
	    dotab(0);
	    fprintf(tfile,"offset%d+=",node->num);
	    print_s(tfile,node->steps[i]);
	    fprintf(tfile,";\n");
	  }
	  node=node->next;
	}
	if (step_list->steps[k]!=NULL) {
	  dotab(0);
	  fprintf(tfile,"shift+=");
	  print_s(tfile,step_list->steps[k]);
	  fprintf(tfile,";\n");
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
	k--;
      }
    }
  } else {
    fatal("Unknown dimension in do_loop_close");
  }
}


/* iota_loop_open - generates special loop code required for an assigment
     of iota.  */

iota_loop_open(vect_t *index, vect_t *bound, s_expr_t *dim)

{
  int i,constant;
  double value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value-1; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=",i);
	print_rav(tfile,index,i);
	fprintf(tfile,"; i%d<",i);
	print_rav(tfile,index,i);
	fprintf(tfile,"+");
	print_rav(tfile,bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
	ntab++;
      }
    }
  } else {
    fatal("Help, I don't know the dimension");
  }
}


/* iota_loop_close - generates code to close special loops require for 
     assigments involving iota. */

iota_loop_close(s_expr_t *dim, vect_t *bound)

{
  int i,constant;
  double value;

  if (SCALAR(dim)) {
    for (i=0; i<dim->ident->value-1; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      }
    }
  } else {
    fatal("Help! I don't know the dimension");
  }
}


/* global_assign - generates C code to implement a single array assigment of
     expr to result. */

global_assign(reduced_t *global, expr_t *result)

{
  int scalar_num_save;
  double value;
  int tau,i,constant;
  int num,last_num;
  s_expr_t **mask;
  reduced_t *node;

  /* any scalars  used during the assign can be reused */
  scalar_num_save=scalar_num;

  step_list=NULL;

  /* skip all the temporary assignments */
  node=global;
  while ((node!=NULL)&&
	 (strncmp(node->d.frag->left->ident->string,"temp",4)==0)) {
    node=node->next;
  }
  if (node!=NULL)
    /* use the location of the first non-temporary assignments */
    do_location(node->d.frag,result);
  else {
    /* must be all temporary so used first one */
    if (global->d.frag->left->ident->type!=VAR_FLOAT)
      do_location(global->d.frag,result);
  }

  num=0;
  node=global;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
      tau=1;
      for (i=0; i<node->d.frag->ident->array.dim->value; i++) {
	tau*=node->d.frag->ident->array.shp[i]->value;
      }
      fprintf(vfile,"  double consta%d[%d];\n",const_array_num,tau);
      for (i=0; i<tau; i++) {
	dotab(0);
	fprintf(tfile,"consta%d[%d]=",const_array_num,i);
	if (node->d.frag->ident->type==CONST_ARRAY) {
	  fprintf(tfile,"%f",node->d.frag->ident->array.cnst[i]);
	} else {
	  print_s_expr(tfile,node->d.frag->ident->array.rav[i]);
	}
	fprintf(tfile,";\n");
      }
      sprintf(node->d.frag->ident->string,"consta%d",const_array_num);
      node->d.frag->ident->type=EMBEDED_ARRAY;
      const_array_num++;
      /* continue to the ARRAY case */

    case EMBEDED_ARRAY:
    case ARRAY:
      do_shapes(node->d.frag,result);
      do_gamma(node->d.frag,result,num);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->dim,num,FALSE);
      num++;
      break;
    case IOTA:
      do_shapes(node->d.frag,result);
      break;
    case FLOAT:
    case VAR_FLOAT:
      do_shapes(node->d.frag,result);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->dim,num,TRUE);
      num++;
      break;
    }
    node=node->next;
  }

  last_num=num-1;

  if (num>max_combined) max_combined=num;

  if (global->d.frag->ident->type==IOTA) 
    iota_loop_open(node->d.frag->index,node->d.frag->bound,
		     node->d.frag->dim);
  else {
    add_steps(result->bound,result->shp,result->dim,num,FALSE);
    do_loop_open(global->d.frag->bound,global->d.frag->dim);
  }

  node=global;
  num=0;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
    case EMBEDED_ARRAY:
    case ARRAY:
      dotab(0);
      if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
	  (node->d.frag->left->ident->type==VAR_FLOAT)) {
	fprintf(tfile,node->d.frag->left->ident->string);
      } else {
	fprintf(tfile,"*(shift)");
      }
      fprintf(tfile,"%s *(offset%d);\n",node->d.frag->func,num);
      num++;
      break;
      
    case IOTA:
      for (i=0; i<node->d.frag->dim->ident->value-1; i++) {
	value=rav_value(node->d.frag->bound,i,&constant);
	if ((!constant)||(value>1)) {
	  dotab(0);
	  fprintf(tfile,"*(shift)%s i%d;\n",node->d.frag->func,i);
	} else {
	  dotab(0);
	  fprintf(tfile,"*(shift)%s ",node->d.frag->func);
	  print_rav(tfile,node->d.frag->index,i);
	  fprintf(tfile,";\n");
	}
	dotab(0);
	fprintf(tfile,"shift++;\n");
      }
      break;
      
    case FLOAT:
    case VAR_FLOAT:
      dotab(0);
      if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
	  (node->d.frag->left->ident->type==VAR_FLOAT)) {
	fprintf(tfile,node->d.frag->left->ident->string);
      } else {
	fprintf(tfile,"*(shift)");
      }
      if (node->d.frag->ident->type==VAR_FLOAT) {
	fprintf(tfile,"%s %s;\n",node->d.frag->func,
		node->d.frag->ident->string);
      } else {
	fprintf(tfile,"%s %f;\n",node->d.frag->func,
		node->d.frag->ident->value);
      }
      num++;
      break;
    }

    node=node->next;
  }

  if (global->d.frag->ident->type==IOTA) 
    iota_loop_close(global->d.frag->dim,global->d.frag->bound);
  else {
    do_loop_close(global->d.frag->dim,global->d.frag->bound,result->dim);
  }

  /* any scalars used during the assign can be reused */
  scalar_num=scalar_num_save;
}


do_assign(expr_t *expr, expr_t *result)

{
  reduced_t reduced;

  reduced.type=NOP;
  reduced.d.frag=expr;
  reduced.next=NULL;
  expr->left=result;
  
  global_assign(&reduced,result);
}
    

/* start_loop - generates C code for the forall statement.  var is the looping
     variable and left and right are its bounds. */

int start_loop(expr_t *var, expr_t *left, expr_t *right)

{
  int i,len,simple;
  vect_t *l_bound,*r_bound;

  if (NOTALLOCATED(var->ident))
    allocate_array(var->ident);
  l_bound=make_vect(left);
  r_bound=make_vect(right);

  len=rav_value(var->shp,0,&simple);
  if (simple) {
    for (i=0; i<len; i++) {
      dotab(0);
      fprintf(tfile,"for (%s[%d]=",var->ident->string,i);
      print_rav(tfile,l_bound,i);
      fprintf(tfile,"; %s[%d]<",var->ident->string,i);
      print_rav(tfile,r_bound,i);
      fprintf(tfile,"; %s[%d]++) {\n",var->ident->string,i);
      ntab++;
    }
  } else {
    report("forall vector must have a static shape.");
  }

  return(len);
}


/* end_loop - generates end }s for a forall statement of depth dimension. */

end_loop(int depth)

{
  int i,simple,len;

  for (i=0; i<depth; i++) {
    ntab--;
    dotab(0);
    fprintf(tfile,"}\n");
  }
}


/* open_forall - generates C code for an internal forall generated by 
     and omega expression.  fa_expr describes the forall. */

open_forall(expr_t *fa_expr)

{
  int i;

  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      dotab(0);
      fprintf(tfile,"for (%s[%d]=",fa_expr->forall->fa->string,i);
      print_rav(tfile,fa_expr->index,i);
      fprintf(tfile,"; %s[%d]<",fa_expr->forall->fa->string,i);
      print_rav(tfile,fa_expr->index,i);
      fprintf(tfile,"+");
      print_rav(tfile,fa_expr->bound,i);
      fprintf(tfile,"; %s[%d]++) {\n",fa_expr->forall->fa->string,i);
      ntab++;
    }
  }
}


/* close_forall - generates code to close the loops resulting from an internal
     forall command.  */

close_forall(expr_t *fa_expr)

{
  int i;

  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      ntab--;
      dotab(0);
      fprintf(tfile,"}\n");
    }
  }

  free(fa_expr->forall);
  fa_expr->forall=NULL;
}


allocate_actuals(reduced_t *list)

{
  reduced_t *node;

  node=list;
  while (node!=NULL) {
    if (NOTALLOCATED(node->d.frag->ident)) {
      allocate_array(node->d.frag->ident);
      SETUSED(node->d.frag->ident->flags);
    }
    node=node->next;
  }
}


/* separate_reduced - separates a list of assignments into two lists,
     global if the right hand side is a global array or distributed if
     the right hand side is a distributed array. */

reduced_t *separate_reduced(reduced_t *list)

{
  dist_t *dist;
  reduced_t *ret,*new_list;
  reduced_t *last_node;

  if (list!=NULL) {
    ret=get_reduced();
    new_list=ret;
    new_list->type=NOP;
    new_list->d.list=list;
  } else ret=NULL;

  last_node=NULL;

  while (list!=NULL) {
    dist=find_dist(list->d.frag->ident);

    last_node=list;
    list=list->next;
    while ((list!=NULL)&&
	   ((find_dist(list->d.frag->ident)==NULL)==(dist==NULL))) {
      last_node=list;
      list=list->next;
    }
    last_node->next=NULL;

    if (list!=NULL) {
      new_list->next=get_reduced();
      new_list=new_list->next;
      new_list->type=NOP;
      new_list->d.list=list;
    }
  }
  
  if (new_list!=NULL)
    new_list->next=NULL;

  return(ret);
}


/* code_expr - generate code for a simple expression list */

code_expr(reduced_t *reduced)

{
  dist_t *l_dist;
  expr_t *result;
  reduced_t *node,*list;
  reduced_t *sep;

  /* find result */
  node=reduced;
  while ((node!=NULL)&&
	 (strncmp(node->d.frag->left->ident->string,"temp",4)==0))
    node=node->next;
  result=(node==NULL) ? reduced->d.frag->left : node->d.frag->left;

  l_dist=find_dist(result->ident);
  
  if ((l_dist==NULL)&&NOTALLOCATED(result->ident)) {
    allocate_array(result->ident);
    SETUSED(result->ident->flags);
  }
  
  sep=separate_reduced(reduced);
  
  /* allocate global variables */
  list=sep;
  while (list!=NULL) {
    node=list->d.list;
    if (find_dist(node->d.frag->ident)!=NULL)
      node=NULL;
    while (node!=NULL) {
      if (NOTALLOCATED(node->d.frag->ident)) {
	allocate_array(node->d.frag->ident);
	SETUSED(node->d.frag->ident->flags);
      }
      node=node->next;
    }
    list=list->next;
  }
  
  list=sep;
  while (list!=NULL) {
    node=list->d.list;
    if (l_dist==NULL) {
      if (find_dist(node->d.frag->ident)==NULL)
	global_assign(node,result);
      else
	code_dist(node,result,l_dist);
    } else {
      code_dist(node,result,l_dist);
    }
    list=list->next;
    collect_garbage(list,save_list,distribution);
  }
}


/* code_reduced - generates code for an entire reduced expression. */

code_reduced(reduced_t *reduced)

{
  name_t  *alloc_list,*nnode,*junk;
  reduced_t *node,*sub_node;
  
  allocs=NULL;
  node=reduced;
  while (node!=NULL) {
    switch (node->type) {
    case SKIP:
      break;

    case NOP:
      code_expr(node->d.list);
      break;

    case ALLOCATE:
      fprintf(vfile,"  double *%s;\n",node->d.frag->ident->string);
      dotab(0);
      fprintf(tfile,"%s=(double *) get_mem((",node->d.frag->ident->string);
      tau(tfile,node->d.frag);
      fprintf(tfile,")*sizeof(double));\n");
      addto_allocs(node->d.frag);
      break;

    case FORALL:
      alloc_list=allocs;
      allocs=NULL;
      open_forall(node->d.list->d.frag);
      code_reduced(node->d.list->next);
      close_forall(node->d.list->d.frag);
      allocs=alloc_list;
      break;
    default:
      fatal("Unknown type encountered in code_reduced");
    }
    node=node->next;
  }

  nnode=allocs;
  while (nnode!=NULL) {
    junk=nnode;
    dotab(0);
    fprintf(tfile,"free(%s);\n",nnode->name);
    nnode=nnode->next;
    free(junk);
  }
}


/* code_c - initializes any distributed arrays and calls a recursive function
     to generate code for an entire procedure body.  */

code_c(statement_t *body, dist_t *dist)

{
  init_dist_arrays(dist);
  code_c_rec(body);
  if (n_procs>1) {
    allocate_utils();
  }
}


/* code_c_rec - generates code for an entire procedure body. */

code_c_rec(statement_t *body)

{
  dist_t *dist;
  statement_t *node;
  name_t *alloc,*dynamic_list,*junk;
  int depth,i;

  dynamics=NULL;
  node=body;
  while (node!=NULL) {
    switch (node->kind) {
    case REDUCED:
      fprintf(tfile,"/*******\n%s\n********/\n\n",node->str);
      code_reduced(node->d.reduced);
      fprintf(tfile,"\n\n");
      break;

    case DYNAMIC:
      dist=find_dist(node->d.dynamic->ident);
      fprintf(vfile,"  double *%s;\n",node->d.dynamic->ident->string);
      dotab(0);
      fprintf(tfile,"%s=(double *) get_mem((",
	      node->d.dynamic->ident->string);
      if (dist==NULL) {
	tau(tfile,node->d.dynamic);
      } else {
	if (dist->e->shp->ident->value>0) {
	  for (i=0; i<dist->e->shp->ident->value; i++) {
	    if (i>0) fprintf(tfile,"*");
	    print_rav(tfile,dist->e,i);
	  }
	} else fprintf(tfile,"1");
      }
      fprintf(tfile,")*sizeof(double));\n\n");
      addto_dynamics(node->d.dynamic);
      break;

    case LOOP:
      dynamic_list=dynamics;
      depth=start_loop(node->d.loop->var,node->d.loop->lower,
		       node->d.loop->upper);
      code_c_rec(node->d.loop->body);
      end_loop(depth);
      dynamics=dynamic_list;
      break;
    case CALL:
      dotab(0);
      allocate_actuals(node->d.reduced->next);
      fprintf(tfile,node->str);
      break;
    default:
      fatal("unknown kind in code_c");
    }
    collect_garbage(NULL,save_list,distribution);
    node=node->next;
  }

  alloc=dynamics;
  while (alloc!=NULL) {
    junk=alloc;
    dotab(0);
    fprintf(tfile,"free(%s);\n",alloc->name);
    alloc=alloc->next;
    free(junk);
  }
}
