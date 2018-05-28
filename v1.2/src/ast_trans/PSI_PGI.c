#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../psi.h"
#include "../dist.h"
#include "../sys.h"
#include "trans.h"
#include "../psi.e"
#include "../dist.e"
#include "../part.e"
#include "../parse.e"
#include "../ident.e"
#include "../vect.e"
#include "../sys.e"

#define NOTALLOCATED(a) ((!ISUSED(a->flags))&&(!ISPARAMETER(a->flags))&&(a->type!=RAV)&&(a->type!=CONST_ARRAY)&&(a->type!=CONSTANT)&&(a->type!=IOTA))

/* WARNING -- THE FOLLOWING ARE PGI MACROS!!! */

#define OP_ADD 1
#define OP_SUB 2
#define OP_MUL 3
#define OP_DIV 4

reduced_t *separate_reduced(reduced_t *list);
int cur_stmnt;  /* used to memorize point of insertion -- PGI!!! */
int pgi_start_stride = 1;  /* 1 when stride is next to be computed in psi omega */
int pgi_start[7];
int pgi_stride[7];
int pgi_bound[7];
int pgi_dossb = 0;
int pgi_psiass = 0;  /* used when hpf subscript node was converted */


void pgi_ident2array(ident_t *id, int dim) {
  int i, index;
  int *ip;

  printf("In pgi_ident2array dim = %d\n", dim);

  if (pgi_start_stride == 0) {
    ip = pgi_start;
    pgi_start_stride = 1;
  }
  else {
    ip = pgi_stride;
    pgi_start_stride = 0;
  }

  index=id->value;

  if (id->type == CONST_ARRAY) {
    for (i=0;i<dim;i++)
      ip[i]=id->array.cnst[index+i];    
  }
  else     /* RAV */ {
    for (i=0;i<dim;i++)
      ip[i]= (simplify_s_expr(id->array.rav[index+i]))->ident->value;
  }
}

void pgi_vect2array(int dest[], vect_t *source, int dim) {
  int i, index, simple_index;
  s_expr_t *s;      
  short int pgi_switch;  /* used for start vs. stride */

  if (pgi_dossb) {
    if (pgi_dossb == 1) {
      printf("COPYING PGI_BOUND\n");
      for (i=0;i<dim;i++) dest[i] = pgi_bound[i];
      pgi_dossb = 2;
    }
    else {
      printf("COPYING PGI_STRIDE\n");
      for (i=0;i<dim;i++) {
	dest[i] = pgi_stride[i];}
      pgi_dossb = 0;
    }
    return;
  }

  if (source->op != NOP) {
    printf("Unexpected op in vect2array PSI_PGI.c\n\n"); exit(1);
  }

  if (SCALAR(source->index)) {
    simple_index=1;
    index=source->index->ident->value;
  }
  else simple_index=0;

/*  index=source->index->ident->value; */

  printf("pgi_vect2array with ident type %d and dim %d\n",
	 source->ident->type, dim);

  switch(source->ident->type) {
  case CONSTANT:
    for (i=0;i<dim;i++) {
      dest[i]=source->ident->value;
    }
    break;
  case CONST_ARRAY:
    if (simple_index)
      for (i=0;i<dim;i++) {
	dest[i]=source->ident->array.cnst[index+i];
      }
    else {
      printf("I think i found a forall!\n\n"); exit(1);
    }
    break;
  case RAV:
    if (simple_index)
      for (i=0;i<dim;i++) {
	s = source->ident->array.rav[index+i];
	/* this is NOT where tmp_vect is found! */
	if (((s->op==NOP)||ISCODED(s->flags)) && (s->ident->type == VARIABLE))
	  dest[i]=-1;
	else {
	  s = simplify_s_expr(s);
	  dest[i]=s->ident->value;
	}
      }
    else {
      printf("I think i found a forall!\n\n"); exit(1);
    }
    break;
  case ARRAY:
    for (i=0;i<dim;i++)
      if (strncmp("tmp_vect",source->ident->string,8) == 0) {
	printf("COPYING PGI_START %d\n", pgi_start[i]);
	pgi_dossb = 1;
	dest[i] = pgi_start[i];
      }
      else dest[i]=-1;

    break;
  default:
    printf("Unexpected vect type %d in vect2array PSI_PGI.c\n\n",
	   source->ident->type);
    exit(1);
  }
}

psi_global_assign(reduced_t *global, expr_t *result)

{
  int scalar_num_save;
  double value;
  int tau,i,constant;
  int num,last_num;
  s_expr_t **mask;
  reduced_t *node;
  vect_t *pgi_bound;
  int pgi_i1, pgi_i2;
  int pgi_optype;
  int pgi_doassign;
  int pgi_dont_pop;
  int pgi_no_expr = 0;
  int start[7], stop[7], stride[7];
  int pgi_dim;

  pgi_bound = global->d.frag->bound;

  /* skip all the temporary assignments */
  node=global;

  while ((node!=NULL)&&
         (strncmp(node->d.frag->left->ident->string,"temp",4)==0)) {
    node=node->next;
  }
  if (strncmp(result->ident->string, "tmp_vect", 8) == 0)
    pgi_no_expr = 1;
  else {
    if (node!=NULL) {
      /* use the location of the first non-temporary assignments */
      if ((strncmp("temp",node->d.frag->ident->string,4)!=0)) {
	pgi_dim = node->d.frag->left->ident->array.dim->value;
	pgi_vect2array(start, node->d.frag->loc, pgi_dim);
	pgi_vect2array(stop, node->d.frag->bound, pgi_dim);
	pgi_vect2array(stride, node->d.frag->stride, pgi_dim);
	PSI_PGI_SUBSCR(result->ident->string, start, stop, stride);
      }
    }
    else {
      /* must be all temporary so used first one */
      if (global->d.frag->left->ident->type!=VARIABLE) {
	pgi_dim = global->d.frag->ident->array.dim->value;
	pgi_vect2array(start, global->d.frag->loc, pgi_dim);
	pgi_vect2array(stop, global->d.frag->bound, pgi_dim);
	pgi_vect2array(stride, global->d.frag->stride, pgi_dim);
	PSI_PGI_SUBSCR(result->ident->string, start, stop, stride);
      }
    }
  }
  printf("global_assign breakpoint 1\n");
  num=0;
  node=global;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV: {
      vect_t *pgi_ss;   /* find either start or stride for psi omega */
      printf("g_a C_A & RAV\n");
      printf("Cannot handle C_A or RAV in PSI_PGI.c\n\n");
      tau=1;
      for (i=0; i<node->d.frag->ident->array.dim->value; i++) {
        tau*=node->d.frag->ident->array.shp[i]->value;
      }
      pgi_no_expr = 1;
      /* deleted for now */
      pgi_ident2array(node->d.frag->ident, tau);
    }
      /* continue to the ARRAY case */
    case EMBEDED_ARRAY:
    case ARRAY:
      printf("g_a ARRAY case\n");
      do_shapes(node->d.frag,result);
      do_gamma(node->d.frag,result,num);
      add_steps(node->d.frag->bound,node->d.frag->shp,
                node->d.frag->stride,node->d.frag->dim,num,FALSE);
      num++;
      break;
    case IOTA:
      printf("g_a IOTA\n");
      pgi_no_expr = 1;
      do_shapes(node->d.frag,result);
      break;
    case CONSTANT:
    case VARIABLE:
      printf("g_a CONST & VAR\n");
      do_shapes(node->d.frag,result);
      add_steps(node->d.frag->bound,node->d.frag->shp,
                node->d.frag->stride,node->d.frag->dim,num,TRUE);
      num++;
      break;
    }
    node=node->next;
  }

  last_num=num-1;

  printf("global_assign Breakpoint 2\n");
  node=global;
  num=0;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
    case EMBEDED_ARRAY:
    case ARRAY:
      printf("ARRAYS...\n");
      if (pgi_no_expr) {
	printf("CONSTA NODE\n");
      }
      else {
	if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
	    (node->d.frag->left->ident->type==VARIABLE))
	  pgi_i1 = atoi(node->d.frag->left->ident->string+4);
	else
	  pgi_i1 = 0;
	pgi_doassign = 0;
	switch (node->d.frag->func[0]) {
	case '+': pgi_optype = OP_ADD; break;
	case '-': pgi_optype = OP_SUB; break;
	case '*': pgi_optype = OP_MUL; break;
	case '/': pgi_optype = OP_DIV; break;
	case '=': pgi_optype = 0; pgi_doassign = 1; break;
	}
	/* need to do subscript of offset# num and push on stack */
	if (strncmp("temp",node->d.frag->ident->string,4)!=0) {
	  pgi_dim = node->d.frag->ident->array.dim->value;
	  pgi_vect2array(start, node->d.frag->index, pgi_dim);
	  pgi_vect2array(stop, node->d.frag->bound, pgi_dim);
	  pgi_vect2array(stride, node->d.frag->stride, pgi_dim);
	  PSI_PGI_SUBSCR(node->d.frag->ident->string, start, stop, stride);
	  PSI_PGI_EXPR(pgi_i1, pgi_optype, pgi_doassign, 0, 0);
	}
	else {
	  if (strncmp("temp",node->d.frag->left->ident->string,4)==0) {
	    pgi_i2 = atoi(node->d.frag->ident->string+4);
	    pgi_dont_pop = 1;
	    if (pgi_no_expr == 0) 
	      PSI_PGI_EXPR(pgi_i1,pgi_optype,pgi_doassign,pgi_dont_pop,pgi_i2);
	  }
	  else {
	    PSI_PGI_NEWST(node->d.frag->left->ident->string,
			  node->d.frag->ident->string,
			  pgi_optype, cur_stmnt);
	  }
	}
      }
      num++;
      break;
      
    case IOTA:
      printf("IOTA...\n");
/*      for (i=0; i<(i==0 ? 1 : node->d.frag->dim->ident->value-1); i++) {
        value=rav_value(node->d.frag->bound,i,&constant);
        if ((!constant)||(value>1)) {
          fprintf(tfile,"*(shift)%s i%d;\n",node->d.frag->func,i);
        } else {
          fprintf(tfile,"*(shift)%s ",node->d.frag->func);
          print_rav(tfile,node->d.frag->index,i);
          fprintf(tfile,";\n");
        }
        fprintf(tfile,"shift++;\n");
      }
*/
      break;
      
    case CONSTANT:
    case VARIABLE:
      printf("CONST/VAR...\n");
      pgi_i2 = 0;
      if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
          (node->d.frag->left->ident->type==VARIABLE))
	pgi_i1 = atoi(node->d.frag->left->ident->string+4);
      else
	pgi_i1 = 0;
      
      if (node->d.frag->ident->type==VARIABLE) {
	if (strncmp("temp",node->d.frag->ident->string,4)==0) {
	  pgi_i2 = atoi(node->d.frag->ident->string+4);
	  pgi_dont_pop = 1;
	}
	else {
	  pgi_vect2array(start, node->d.frag->loc, pgi_dim);
	  pgi_vect2array(stop, node->d.frag->bound, pgi_dim);
	  pgi_vect2array(stride, node->d.frag->stride, pgi_dim);
	  PSI_PGI_SUBSCR(node->d.frag->ident->string, start, stop, stride);
	  pgi_dont_pop = 0;
	  /* need to process SCALAR and push onto stack */
	}
      }
      else {
	pgi_dont_pop = 0;
	/* need to process CONSTANT and push onto stack */
	/* value in node->d.frag->ident->value */
      }
      
      pgi_doassign = 0;
      switch (node->d.frag->func[0]) {
      case '+': pgi_optype = OP_ADD; break;
      case '-': pgi_optype = OP_SUB; break;
      case '*': pgi_optype = OP_MUL; break;
      case '/': pgi_optype = OP_DIV; break;
      case '=': pgi_optype = 0; pgi_doassign = 1; break;
      }      
      if (pgi_no_expr == 0) 
	PSI_PGI_EXPR(pgi_i1, pgi_optype, pgi_doassign, pgi_dont_pop, pgi_i2);

      num++;
      break;
    }

    node=node->next;
  }

  /* any scalars used during the assign can be reused */
  scalar_num=scalar_num_save;
  return(1);
}


psi_code_expr(reduced_t *reduced)
{
  dist_t *l_dist;
  expr_t *result;
  reduced_t *node, *list, *sep;

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
  
  list=sep=separate_reduced(reduced);
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
      if (find_dist(node->d.frag->ident)==NULL) {
	printf("calling global_assign from within code_expr\n");
	psi_global_assign(node,result);
      }
      else {
	 printf("cannot do code_dist!!!\n\n\n"); exit(1);
       }
    }
    else{
      printf("cannot do code_dist!!!\n\n\n"); exit(1);
    }
    list=list->next;
    /* 
       collect_garbage(list,save_list,distribution);
    */
  }
}

psi_code_reduced(reduced_t *reduced)
{
  reduced_t *node;

  node = reduced;
  while (node!=NULL) {

    switch (node->type) {
    case SKIP:
      break;

    case NOP:
      psi_code_expr(node->d.list);
      PSI_PGI_ASS_EXPR(cur_stmnt);
      break;

    case ALLOCATE:
      printf("cannot handle ALLOCATE \n\n\n");
      /*
	 i think i can skip this, but i better check what tau does.
	 additionally, it is adding any allocated vars to allocs.
	 but does F77 deallocate?  if not, then just worry about being
	 added when i use them later.
	 */
      break;

    case FORALL: {
      int simple, i;
      expr_t *fa_expr = node->d.list->d.frag;
      printf("IN CASE FORALL\n");
      if (SCALAR(fa_expr->forall->bound->shp)) {
	printf("FORALL CHECK 1\n");
	for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
	  if (rav_value(fa_expr->bound, i, &simple) != 1) {
	    printf("FORALL CHECK 2\n");
	    pgi_vect2array(pgi_bound, fa_expr->bound,
			   fa_expr->forall->bound->shp->ident->value);
	    printf("PGI_BOUND DIM: %f   %d %d\n",
		 fa_expr->forall->bound->shp->ident->value,
		 pgi_bound[0], pgi_bound[1]);	
	  }
	}
      }
      psi_code_reduced(node->d.list->next);
      /* close_forall(node->d.list->d.frag); */
      break;
    }

    case EXT_OP:
      /* psi_code_extended (node); */
      /* if you look in extended.c, you will see that this hasn't been
         implemeneted yet. */
      fatal("Found unexepected EXT_OP in PSI_PGI.c\n");
      break; 

    default:
      fatal("Unknown type encountered in code_reduced");
    }
    node=node->next;
  }

  /* and yet again, more deallocation takes place. */
}

void PSI_PGI_AST(statement_t *cur, int cur_st)
{
  statement_t *node;


  cur_stmnt = cur_st;
/*  dynamics=NULL;    dynamics not found -- a prob?  */
  node = cur;
  while (node != NULL) {

     switch (node->kind) {
     case REDUCED:
       psi_code_reduced(node->d.reduced);
       break;

     case DYNAMIC:
       /* (node->d.dynamic->ident->real) */
       break;

     case LOOP:
       printf("\n\nCANNOT HANDLE LOOP in PSI_PGI.c\n\n\n");
       /* start_loop will give me depth of loop */
       /* d.loop->var, lower, and upper give me bouns */
       PSI_PGI_AST(node->d.loop->body,cur_st);
       /* pass depth to close loop */
       /* IS THIS CASE EVEN USED? */
       /* in addition, i use "dynamics" to memorize "dynamics list" */

       break;

     case CALL:
       printf("\n\nCANNOT HANDLE CASE in PSI_PGI.c\n\n\n");
       /* allocate_actuals(node->d.reduced->next); */
       /* node->str may have info as well */
       break;

     default:
       fatal("unknown kind in PSI_PGI_AST");
     }
     /*
       collect_garbage(NULL, save_list, distribution);
     */
     node=node->next;
   }
  PSI_PGI_ASS_EXPR(cur_stmnt);

  /* deallocate all variables in "alloc" list, via "alloc->name" */
}
