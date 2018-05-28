/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include "psi.h"

#include "ident.e"
#include "vect.e"
#include "moa_func.e"
#include "sys.e"

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

int temp_used,clean;
int temp_array_num=0;
int expr_num=0;
int const_array_num=0;
int max_dim=0;
ident_t const0,const1;
s_expr_t s_const0,s_const1;
vect_t zero_vec,one_vec,empty_vec;
                              /* recursive block_rav needs these values */
expr_t *block_result,*block_expr; 
char *block_op;               /* they're put here to avoid having to push */
int block_top,block_inright;  /* them for each recursive call */
vect_t *block_loc;


expr_t *assign(expr_t *, expr_t *, int, char *, int);


int empty(vect_t *vect)

{
  int i,ret;
  ret=FALSE;
  if (vect->ident->type==CONST_ARRAY) {
    for (i=0; i<vect->ident->array.shp[0]->value; i++)
      if (vect->ident->array.cnst[i]==0) ret=TRUE;
  }
  if (vect->ident->type==RAV) {
    for (i=0; i<vect->ident->array.shp[0]->value; i++) {
      if (SCALAR(vect->ident->array.rav[i]))
	if (vect->ident->array.rav[i]->ident->value==0)
	  ret=TRUE;
    }
  }

  return(ret);
}


expr_t *dup_expr(expr_t *expr)

{
  expr_t *ret;

  if (expr==NULL) return(NULL);
  else {
    ret=get_expr_mem(1);
    *ret=*expr;
    ret->left=dup_expr(expr->left);
    ret->right=dup_expr(expr->right);
    
    return(ret);
  }
}


block_rav(s_expr_t *i, s_expr_t *b, vect_t *s, vect_t *bound, vect_t *index,
	  s_expr_t *loc)

{
  int j;
  s_expr_t *p,*e;
  s_expr_t *to,*ti,*ts,*tl;
  s_expr_t *bs,*bo,*bl;
  s_expr_t *ho,*hi,*hs,*hl;
  vect_t *pad0,*g_bound,*g_index;
  expr_t *gen;

  if (SCALAR(s->shp)) {
    if ((!SCALAR(b))||(b->ident->value>0)) {
      p=&s_const1;
      for (j=0; j<s->shp->ident->value; j++) {
	p=s_op(TIMES,p,red_rav(s,j));
      }
      
      e=s_op(PLUS,b,i);
      to=s_op(DIVIDE,e,p);
      ti=&s_const0;
      ts=s_op(MINUS,e,s_op(TIMES,to,p));
      bs=s_op(DIVIDE,s_op(MINUS,b,ts),p);
      ho=s_op(DIVIDE,i,p);
      hi=s_op(MINUS,i,s_op(TIMES,ho,p));
      hs=s_op(MINUS,b,s_op(PLUS,ts,s_op(TIMES,bs,p)));
      bo=s_op(DIVIDE,s_op(PLUS,i,hs),p);
      hl=loc;
      bl=s_op(PLUS,hl,hs);
      tl=s_op(PLUS,bl,s_op(TIMES,bs,p));

      g_bound=vect_cat(vect_cat(bound,s_vect(bs)),s);
      if (!empty(g_bound)) {
	gen=dup_expr(block_expr);
	pad0=get_vect();
	pad0->shp=s->shp;
	pad0->loc=&s_const0;
	pad0->index=&s_const0;
	pad0->ident=&const0;
	gen->index=vect_cat(vect_cat(index,s_vect(bo)),pad0);
	gen->bound=g_bound;
	gen->loc=vect_cat(block_loc,s_vect(bl));
	assign(gen,block_result,block_top,block_op,block_inright);
      }

      s=vect_drop(&one_vec,s);
      bound=vect_cat(bound,&one_vec);
      block_rav(hi,hs,s,bound,vect_cat(index,s_vect(ho)),hl);
      block_rav(ti,ts,s,bound,vect_cat(index,s_vect(to)),tl);
    }
  } else {
    fatal("non-scalar shape caught in block_rav");
  }
}


assign_rav(expr_t *rav, expr_t *expr, expr_t *result, 
	  int top, char *op, int inright)

{
  s_expr_t *i,*b;
  vect_t *s,*adj;

  if (SCALAR(expr->dim)) {
    block_expr=expr;
    block_result=result;
    adj=s_vect(s_op(MINUS,result->dim,&s_const1));
    block_loc=vect_take(adj,rav->loc);
    block_top=top;
    block_op=op;
    block_inright=inright;
    i=make_s_expr(rav->index);
    b=make_s_expr(rav->bound);
    s=vect_drop(&one_vec,expr->shp);
    block_rav(i,b,s,&empty_vec,&empty_vec,
	      make_s_expr(vect_drop(adj,rav->loc)));
  } else {
    fatal("Red rav does'nt know the dimension");
  }
}


expr_t *red_scalar_extend(expr_t *expr)

{
  vect_t *vtmp;
  s_expr_t *stmp;

  vtmp=make_vect(expr->left);
  stmp=make_s_expr(vtmp);
  expr->ident=make_ident(stmp);
  expr->op=NOP;
  expr->left=NULL;
 
  return(expr);
}


red_take(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(TIMES,vect_op(PLUS,v,vect_take(arg1->shp,arg2->shp)),
		vect_unop(IF_NEG,v));
  index=vect_op(PLUS,index,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
    
}


red_pdrop(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(PLUS,v,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
    
}


red_ptake(expr_t *arg1, expr_t *arg2)

{

}


red_drop(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(TIMES,v,vect_unop(IF_POS,v));
  index=vect_op(PLUS,index,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
    
}


expr_t *red_psi(expr_t *arg1, expr_t *arg2, s_expr_t *r_dim)

{
  vect_t *index,*pad1,*len,*size;
  
  pad1=get_vect();
  pad1->index=&s_const0;
  pad1->loc=&s_const0;
  pad1->shp=make_s_expr(arg1->shp);
  pad1->ident=&const1;
  size=s_vect(s_op(MINUS,s_op(PLUS,arg2->index->shp,arg2->dim),r_dim));
  arg2->bound=vect_take(size,vect_cat(pad1,arg2->bound));
  arg2->index=vect_take(size,vect_cat(make_vect(arg1),arg2->index));

  return(arg2);
}


red_cat(expr_t *arg1, expr_t *arg2)

{
  vect_t *tmp,*tmp2,*adj;
  vect_t *index,*bound,*shp,*index2;

  index=vect_take(&one_vec,arg1->index);
  bound=vect_take(&one_vec,arg1->bound);
  shp=vect_take(&one_vec,arg1->shp);

  index=vect_op(MIN,index,shp);
  arg1->index=vect_cat(index,vect_drop(&one_vec,arg1->index));

  bound=vect_op(MIN,bound,vect_op(MINUS,shp,index));
  arg1->bound=vect_cat(bound,vect_drop(&one_vec,arg1->bound));

  index2=vect_take(&one_vec,arg2->index);
  index2=vect_op(MINUS,index2,index);
  arg2->index=vect_cat(index2,vect_drop(&one_vec,arg2->index));

  tmp=vect_op(MINUS,vect_take(&one_vec,arg2->bound),
	      vect_take(&one_vec,arg1->bound));
  arg2->bound=vect_cat(tmp,vect_drop(&one_vec,arg2->bound));
  
  tmp=s_vect(s_op(MIN,arg2->dim,arg2->loc->shp));
  adj=vect_op(MINUS,vect_len(arg2->loc),tmp);
  tmp2=vect_drop(adj,arg2->loc);
  tmp=vect_op(PLUS,vect_take(&one_vec,tmp2),vect_take(&one_vec,arg1->bound));
  tmp=vect_cat(vect_take(adj,arg2->loc),tmp);
  arg2->loc=vect_cat(tmp,vect_drop(&one_vec,tmp2));
}


do_shapes(expr_t *expr, expr_t *result)

{
  if (!expr->scanned) {
    expr->shp=vect_unop(RSCAN,expr->shp);
    expr->shp=purify_vect(expr->shp);
    expr->scanned=TRUE;
  }
  if (!result->scanned) {
    result->shp=vect_unop(RSCAN,result->shp);
    result->shp=purify_vect(result->shp);
    result->scanned=TRUE;
  }
}


my_gamma(char *name, vect_t *index, vect_t *shp, s_expr_t *dim)

{
  int i,j;

  index=vect_drop(s_vect(s_op(MINUS,index->shp,dim)),index);
  if (SCALAR(dim)) {
    dotab(0);
    fprintf(tfile,"%s=",name);
    for (i=0; i<dim->ident->value-1; i++) {
      if (i>0) fprintf(tfile,"+");
      print_rav(index,i);
      fprintf(tfile,"*");
      print_rav(shp,i+1);
    }
    if (i>0) fprintf(tfile,"+");
    print_rav(index,dim->ident->value-1);
    fprintf(tfile,";\n");
  } else {
    shp=vect2array("gamma_shp",shp);
    index=vect2array("gamma_index",index);
    dotab(0);
    fprintf(tfile,"for (i=0; i<");
    print_s_expr(tfile,dim);
    fprintf(tfile,"; i++)\n");
    dotab(1);
    fprintf(tfile,"%s+=%s[i",name,index->ident->string);
    if (index->index!=NULL) {
      fprintf(tfile,"+");
      print_s_expr(tfile,index->index);
    }
    fprintf(tfile,"]*%s[i];\n",shp->ident->string);
  }
}


int do_location(expr_t *expr, expr_t *result)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->loc==NULL) {
    dotab(0);
    fprintf(tfile,"shift=0;\n",expr->ident->string);
    return(FALSE);
  } else {
    sprintf(buf,"shift",expr->ident->string);
    my_gamma(buf,expr->loc,result->shp,result->dim);
    return(TRUE);
  }
}


int do_gamma(expr_t *expr, expr_t *result)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->index==NULL) {
    dotab(0);
    fprintf(tfile,"offset=0;\n",expr->ident->string);
    return(FALSE);
  } else {
    sprintf(buf,"offset",expr->ident->string);
    my_gamma(buf,expr->index,expr->shp,expr->dim);
    return(TRUE);
  }
}


int *do_steps(char *name, vect_t *bound, vect_t *shp1, vect_t *shp2, 
	     s_expr_t *dim, s_expr_t *r_dim)

{
  int i,j,constant,d,d2,*step_mask;
  int pos,last;
  float value1,value2,value3;
  vect_t *step;
  expr_t *tmp_expr;

  step_mask=NULL;
  if (SCALAR(dim)) {
    d=dim->ident->value;
    d2=r_dim->ident->value;
    if (d>0) {
      step_mask=(int *) get_mem(d*sizeof(int));
/*
      value1=rav_value(bound,(int) d-1,&constant);
      if ((!constant)||(value1>1)) {
	dotab(0);
	fprintf(tfile,"step1[%d]=1;\n",(int) d-1);
      }
      step_mask[d-1]=TRUE;
*/
      value1=rav_value(bound,d-1,&constant);
      step_mask[d-1]=((!constant)||(value1>1));
      last=d-1;
    }
    for (i=d-2; i>=0; i--) {
      value1=rav_value(bound,i,&constant);
      if ((!constant)||(value1>1)) {
	j=i+1;
	value1=1;
	while ((constant)&&(j<=last)) {
	  value1*=rav_value(bound,j,&constant);
	  j++;
	}
	if (constant)
	  value2=rav_value(shp1,i+1,&constant);
	if (constant)
	  value3=(last<d-1) ? rav_value(shp1,last+1,&constant):step_mask[d-1];
	if (constant) {
	  if (value2-value3*value1>0) {
	    last=i;
	    dotab(0);
	    fprintf(tfile,"step1[%d]=%d;\n",i,(int) (value2-value3*value1));
	    step_mask[i]=TRUE;
	  } else step_mask[i]=FALSE;
	}
      } else if (constant) {
	step_mask[i]=FALSE;
      } else {
	dotab(0);
	fprintf(tfile,"step1[%d]=",i);
	print_rav(shp1,i+1);
	fprintf(tfile,"-");
	if (i<d-1) {
	  print_rav(shp1,last+1);
	  fprintf(tfile,"*");
	  print_rav(bound,last);
	} else fprintf(tfile,"%d",step_mask[d-1]);
	fprintf(tfile,";\n");
	last=i;
	step_mask[i]=TRUE;
      }
    }
/*
    last=d-1;
    pos=d2-2;
    for (i=d-1; i>=0; i--) {
      if (step_mask[i]) {
	value1=rav_value(bound,last,&constant);
	if (constant)
	  value2=rav_value(shp2,pos+1,&constant);
	if (constant)
	  value3=(last<d-1) ? rav_value(shp2,pos+2,&constant) :step_mask[d-1];
	if (constant) {
	  if (value2-value3*value1>0) {
	    last=i;
	    dotab(0);
	    fprintf(tfile,"step2[%d]=%d;\n",i,(int) (value2-value3*value1));
	  }
	} else {
	  dotab(0);
	  fprintf(tfile,"step2[%d]=",i);
	  print_rav(shp2,pos+1);
	  fprintf(tfile,"-");
	  if (last<d-1) {
	    print_rav(shp2,pos+2);
	    fprintf(tfile,"*");
	    print_rav(bound,last);
	  } else fprintf(tfile,"%d",step_mask[d-1]);
	  fprintf(tfile,";\n");
	  last=i;
	}
	pos--;
	}
       }
*/
  }
  
  return(step_mask);
}


do_loop_open(char *name, vect_t *bound, s_expr_t *dim)

{
  int i,j,constant;
  float value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=0",i);
	fprintf(tfile,"; i%d<",i);
	print_rav(bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
	ntab++;
      }
    }
  } else {
    dotab(0);
    fprintf(tfile,"for (i=0; i<");
    print_s_expr(tfile,dim);
    fprintf(tfile,"; i++)  {\n");
    dotab(1);
    fprintf(tfile,"offset_save[i]=%s_offset;\n",name);
    dotab(1);
    fprintf(tfile,"shift_save[i]=%s_shift;\n",name);
    dotab(1);
    fprintf(tfile,"cnt[i]=%s_bound[i];\n",name);
    dotab(0);
    fprintf(tfile,"}\n");
    dotab(0);
    fprintf(tfile,"while (cnt[0]>0) {\n");
    ntab++;
  }
}


do_loop_close(char *name, s_expr_t *dim, vect_t *bound,
	      int *mask, int do_offset)

{
  int i,j,constant;
  float value;

  if (SCALAR(dim)) {
    if (dim->ident->value>0) {
      i=0;
      while ((!mask[i])&&(i<dim->ident->value)) i++;
      if (i<dim->ident->value) {
	dotab(0);
	fprintf(tfile,"shift++;\n");
      }
      value=rav_value(bound,dim->ident->value-1,&constant);
      if ((!constant)||(value>1)) {
	if (do_offset) {
	  dotab(0);
	  fprintf(tfile,"offset++;\n");
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      }
    }
    for (i=dim->ident->value-2; i>=0; i--) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	if (mask[i]&&do_offset) {
	  dotab(0);
	  fprintf(tfile,"offset+=step1[%d];\n",i);
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      }
    }
  } else {
    dotab(0);
    fprintf(tfile,"cnt[");
    print_s_expr(tfile,dim);
    fprintf(tfile,"-1]--;\n");
    dotab(0);
    fprintf(tfile,"offset+=step1[");
    print_s_expr(tfile,dim);
    fprintf(tfile,"-1];\n");
    dotab(0);
    fprintf(tfile,"shift+=step2[");
    print_s_expr(tfile,dim);
    fprintf(tfile,"-1];\n");
    dotab(0);
    fprintf(tfile,"for (i=");
    print_s_expr(tfile,dim);
    fprintf(tfile,"-1; i>0 i--)\n");
    dotab(1);
    fprintf(tfile,"if (cnt[i]==0) {\n");
    dotab(2);
    fprintf(tfile,"offset=offset_save[i]\n"); 
    dotab(2);
    fprintf(tfile,"offset=offset_save[i]\n");
    dotab(2);
    fprintf(tfile,"offset+=step1[i-1];\n");
    dotab(2);
    fprintf(tfile,"shift+=step2[i-1];\n");
    dotab(2);
    fprintf(tfile,"cnt[i]=bound[i]\n");
    dotab(2);
    fprintf(tfile,"cnt[i-1]--;\n");
    dotab(1);
    fprintf(tfile,"} else break;\n");
    ntab--;
    dotab(0);
    fprintf(tfile,"}\n");
  }
}


iota_loop_open(vect_t *index, vect_t *bound, s_expr_t *dim)

{
  int i,constant;
  float value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value-1; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=",i);
	print_rav(index,i);
	fprintf(tfile,"; i%d<",i);
	print_rav(index,i);
	fprintf(tfile,"+");
	print_rav(bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
	ntab++;
      }
    }
  } else {
    fatal("Help, I don't know the dimension");
  }
}


iota_loop_close(s_expr_t *dim, vect_t *bound)

{
  int i,constant;
  float value;

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


int purify(expr_t *expr, expr_t *result)

{
  vect_t *tmp;

  expr->dim=red_s_expr(expr->dim);
  result->dim=red_s_expr(result->dim);
  expr->index=purify_vect(expr->index);
  expr->loc=purify_vect(expr->loc);
  expr->bound=purify_vect(expr->bound);
  expr->shp=purify_vect(expr->shp);
  result->shp=purify_vect(result->shp);
}


do_assign(expr_t *expr, expr_t *result, char *op)

{
  float value;
  int tau,i,*mask,constant;

  switch (expr->ident->type) {
  case CONST_ARRAY:
  case RAV:
    tau=1;
    for (i=0; i<expr->ident->array.dim->value; i++) {
      tau*=expr->ident->array.shp[i]->value;
    }
    fprintf(vfile,"  float consta%d[%d];\n",const_array_num,tau);
    for (i=0; i<tau; i++) {
      dotab(0);
      fprintf(tfile,"consta%d[%d]=",const_array_num,i);
      if (expr->ident->type==CONST_ARRAY) {
	fprintf(tfile,"%f",expr->ident->array.cnst[i]);
      } else {
	print_s_expr(tfile,expr->ident->array.rav[i]);
      }
      fprintf(tfile,";\n");
    }
    sprintf(expr->ident->string,"consta%d",const_array_num);
    expr->ident->type=EMBEDED_ARRAY;
    const_array_num++;
    /* continue to the ARRAY case */

  case EMBEDED_ARRAY:
  case ARRAY:
    do_shapes(expr,result);
    do_location(expr,result);
    do_gamma(expr,result);
    mask=do_steps(expr->ident->string,expr->bound,
		  expr->shp,result->shp,expr->dim,result->dim);
    do_loop_open(expr->ident->string,expr->bound,expr->dim);
    dotab(0);
    fprintf(tfile,"*(%s+shift)%s*(%s+offset);\n",result->ident->string,op,
	   expr->ident->string);

    do_loop_close(expr->ident->string,expr->dim,expr->bound,mask,TRUE);
    break;
        
  case IOTA:
    do_shapes(expr,result);
    do_location(expr,result);
/*    do_gamma(expr,result);
    mask=do_steps(expr->ident->string,expr->bound,
		  expr->shp,result->shp,expr->dim,result->dim); */
    iota_loop_open(expr->index,expr->bound,expr->dim);
    for (i=0; i<expr->dim->ident->value-1; i++) {
      value=rav_value(expr->bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"*(%s+shift)%si%d;\n",result->ident->string,op,i);
      } else {
	dotab(0);
	fprintf(tfile,"*(%s+shift)%s",result->ident->string,op);
	print_rav(expr->index,i);
	fprintf(tfile,";\n");
      }
      dotab(0);
      fprintf(tfile,"shift++;\n");
    }
    iota_loop_close(expr->dim,expr->bound);
    break;
        
  case FLOAT:
  case VAR_FLOAT:
    do_shapes(expr,result);
    do_location(expr,result);
    mask=do_steps(expr->ident->string,expr->bound,
		  expr->shp,result->shp,expr->dim,result->dim);
    do_loop_open(expr->ident->string,expr->bound,expr->dim);
    dotab(0);
    if (expr->ident->type==VAR_FLOAT) {
      fprintf(tfile,"*(%s+shift)%s%s;\n",result->ident->string,op,
	      expr->ident->string);
    } else {
      fprintf(tfile,"*(%s+shift)%s%f;\n",result->ident->string,op,
	      expr->ident->value);
    }

    do_loop_close(expr->ident->string,expr->dim,expr->bound,mask,FALSE);
    break;
  }
  fprintf(tfile,"\n");
}


red_loop(expr_t *expr)

{
  dotab(0);
  fprintf(tfile,"for (%s=0",expr->left->ident->string);
  fprintf(tfile,"; %s<",expr->left->ident->string);
  print_rav(expr->right->shp,0);
  fprintf(tfile,"; %s++) {\n",expr->left->ident->string);
  ntab++;
}
  

forall(expr_t *fa_expr, expr_t *result, int top, char *op, int inright)

{
  int i,tmp_num;
  char *newop;
  expr_t *expr,*tmp;
  vect_t *fa_vect,*tmp_vec,*loc,*pad1;

  expr=fa_expr->left;

  fa_vect=get_vect();
  fa_vect->shp=fa_expr->forall->bound->shp;
  fa_vect->loc=&s_const0;
  fa_vect->index=&s_const0;
  fa_vect->ident=fa_expr->forall->fa;

  fa_expr->index=purify_vect(fa_expr->index);
  fa_expr->bound=purify_vect(fa_expr->bound);
  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      dotab(0);
      fprintf(tfile,"for (%s[%d]=",fa_expr->forall->fa->string,i);
      print_rav(fa_expr->index,i);
      fprintf(tfile,"; %s[%d]<",fa_expr->forall->fa->string,i);
      print_rav(fa_expr->index,i);
      fprintf(tfile,"+");
      print_rav(fa_expr->bound,i);
      fprintf(tfile,"; %s[%d]++) {\n",fa_expr->forall->fa->string,i);
      ntab++;
    }
  }

  tmp_vec=vect_len(fa_vect);
  loc=vect_op(MINUS,fa_vect,vect_take(tmp_vec,fa_expr->index));
  loc=vect_cat(vect_op(PLUS,vect_take(tmp_vec,fa_expr->loc),loc),
	       vect_drop(tmp_vec,fa_expr->loc));
  expr->loc=loc;
  pad1=get_vect();
  pad1->loc=&s_const0;
  pad1->index=&s_const0;
  pad1->shp=s_op(MINUS,fa_vect->shp,s_op(MINUS,fa_expr->dim,expr->dim));
  pad1->ident=&const1;
  expr->bound=vect_cat(pad1,vect_drop(tmp_vec,fa_expr->bound));
  expr->index=vect_cat(pad1,vect_drop(tmp_vec,fa_expr->index));

  tmp_num=temp_array_num;
  if (inright) {
    if (temp_used) temp_array_num++;
    else temp_used=TRUE;
    tmp=get_expr_mem(1);
    tmp->dim=result->dim;
    tmp->shp=result->shp;
    tmp->loc=fa_expr->loc;
    expr->loc=result->loc;
    tmp->bound=fa_expr->bound;
    tmp->ident=get_ident();
    sprintf(tmp->ident->string,"temp%d",temp_array_num);
    tmp->ident->type=ARRAY;
    newop="=";
    fprintf(vfile,"  float *temp%d;\n",temp_array_num);
    dotab(0);
    fprintf(tfile,"  temp%d=(float *) malloc((",temp_array_num);
    tau(tfile,result);
    fprintf(tfile,")*sizeof(float));\n");
  } else {
    tmp=result;
    newop=op;
  }

  assign(expr,tmp,TRUE,newop,inright);

  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      ntab--;
      dotab(0);
      fprintf(tfile,"}\n");
    }
  }
  
  if (inright)
    assign(tmp,result,top,op,inright);
  temp_array_num=tmp_num;

  free(fa_expr->forall);
}


expr_t *assign(expr_t *expr, expr_t *result, int top, char *op, int inright)

{
  int copy,cnt;
  char *new_op[4],tmp_num;
  expr_t *left, *right, *tmp,*tmp2;
  vect_t *loc,*drop;

  if (expr==NULL) return(expr);

  left=expr->left;
  right=expr->right;

  cnt=0;
  switch (expr->op) {
  case NOP:
    if (!top) return(expr);
    purify(expr,result);

    if (!empty(expr->bound))
      do_assign(expr,result,op);
    break;

  case TIMES:
    new_op[cnt]="*=";
    cnt++;
  case DIVIDE:
    new_op[cnt]="/=";
    cnt++;
  case PLUS:
    new_op[cnt]="+=";
     cnt++;
  case MINUS:
    new_op[cnt]="-=";
    cnt++;

    tmp_num=temp_array_num++;
    if (((*new_op[0]=='-')||(*new_op[0]=='/'))&&(inright)) {
      temp_array_num++;
      tmp=get_expr_mem(1);
      tmp->dim=result->dim;
      tmp->shp=result->shp;
      drop=s_vect(s_op(MINUS,expr->dim,result->dim));
      drop=vect_op(TIMES,vect_unop(IF_POS,drop),drop);
      tmp->bound=vect_drop(drop,expr->bound);
      tmp->loc=vect_drop(drop,expr->loc);
      tmp->ident=get_ident();
      sprintf(tmp->ident->string,"temp%d",temp_array_num);
      tmp->ident->type=ARRAY;
      fprintf(vfile,"  float *temp%d;\n",temp_array_num);
      dotab(0);
      fprintf(tfile,"  temp%d=(float *) malloc((",temp_array_num);
      tau(tfile,result);
      fprintf(tfile,")*sizeof(float));\n");

      loc=get_vect();
      loc->shp=expr->loc->shp;
      loc->index=&s_const0;
      loc->loc=&s_const0;
      loc->ident=&const0;
  
      copy=TRUE;
    } else {
      tmp=result;
      copy=FALSE;
      loc=expr->loc;
    }

    left->index=expr->index;
    left->bound=expr->bound;
    left->loc=loc;
    if (copy) 
      assign(left,tmp,TRUE,"=",FALSE);
    else
      assign(left,tmp,TRUE,op,FALSE);
    
    if (right!=NULL) {
      right->index=expr->index;
      right->bound=expr->bound;
      right->loc=loc;
      assign(right,tmp,TRUE,*new_op,TRUE);
    }

    temp_array_num=tmp_num;
    if (copy) assign(tmp,result,TRUE,op,FALSE);
    break;

  case SCALAR_EXTEND:
    assign(red_scalar_extend(expr),result,top,op,inright);
    break;

  case FORALL:
    forall(expr,result,top,op,inright);
    break;

  case TAKE:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    red_take(left,right);
    assign(right,result,TRUE,op,inright);
    break;

  case DROP:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    red_drop(left,right);
    assign(right,result,TRUE,op,inright);
    break;

  case PTAKE:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    red_ptake(left,right);
    assign(right,result,TRUE,op,inright);
    break;

  case PDROP:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    red_pdrop(left,right);
    assign(right,result,TRUE,op,inright);
    break;

  case TIMES_RED:
    new_op[cnt]="*=";
    cnt++;
  case DIVIDE_RED:
    new_op[cnt]="/=";
    cnt++;
  case PLUS_RED:
    new_op[cnt]="+=";
     cnt++;
  case MINUS_RED:
    new_op[cnt]="-=";
    cnt++;
    
    tmp2=get_expr_mem(1);
    tmp2->dim=result->dim;
    tmp2->shp=result->shp;
    drop=s_vect(s_op(MINUS,expr->dim,result->dim));
    drop=vect_op(TIMES,vect_unop(IF_POS,drop),drop);
    tmp2->bound=vect_drop(drop,expr->bound);
    tmp2->loc=vect_drop(drop,expr->loc);
    if ((new_op[0][0]=='-')||(new_op[0][0]=='+')) 
      tmp2->ident=&const0;
    else tmp2->ident=&const1;

    tmp_num=temp_array_num++;
    if (inright) {
      tmp=get_expr_mem(1);
      *tmp=*tmp2;
      temp_array_num++;
      tmp->ident=get_ident();
      sprintf(tmp->ident->string,"temp%d",temp_array_num);
      tmp->ident->type=ARRAY;
      fprintf(vfile,"  float *temp%d;\n",temp_array_num);
      dotab(0);
      fprintf(tfile,"  temp%d=(float *) malloc((",temp_array_num);
      tau(tfile,result);
      fprintf(tfile,")*sizeof(float));\n");
      
      loc=get_vect();
      loc->shp=expr->loc->shp;
      loc->index=&s_const0;
      loc->loc=&s_const0;
      loc->ident=&const0;
      
      copy=TRUE;
    } else {
      tmp=result;
      copy=FALSE;
      loc=expr->loc;
    }

    assign(tmp2,tmp,TRUE,"=",FALSE);

    left->index=expr->index;
    left->bound=expr->bound;
    left->loc=loc;

    red_loop(left);

    assign(left,tmp,FALSE,*new_op,TRUE);

    ntab--;
    dotab(0);
    fprintf(tfile,"}\n");
    
    temp_array_num=tmp_num;
    if (copy) assign(tmp,result,TRUE,op,FALSE);
    break;

  case RAVEL:
    assign_rav(expr,left,result,top,op,inright);
    break;

  case PSI:
    right->loc=expr->loc;
    right->index=expr->index;
    right->bound=expr->bound;
    red_psi(left,right,expr->dim);
    assign(right,result,TRUE,op,inright);
    break;

  case CAT:
    left->bound=expr->bound;
    left->index=expr->index;
    left->loc=expr->loc;
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    red_cat(left,right);
    assign(left,result,TRUE,op,inright);
    assign(right,result,TRUE,op,inright);
    break;
  }

  return(expr);
}


psi_assign(parser_t *expr, parser_t *result)

{
  parser_t *save[2];
  expr->psi->index=get_vect();
  expr->psi->index->index=&s_const0;
  expr->psi->index->loc=&s_const0;
  expr->psi->index->shp=expr->psi->shp->shp;
  expr->psi->index->ident=&const0;
  expr->psi->bound=expr->psi->shp;
  expr->psi->loc=get_vect();
  expr->psi->loc->index=&s_const0;
  expr->psi->loc->loc=&s_const0;
  expr->psi->loc->shp=result->psi->dim;
  expr->psi->loc->ident=&const0;
  result->psi->bound=expr->psi->shp;


#ifdef SHOWMEM
  puts("From shape analysis:");
  stats();
#endif

  save[0]=expr;
  save[1]=result;
  collect_mem(save,2);

#ifdef SHOWMEM
  puts("After collection:");
  stats();
#endif

  assign(expr->psi,result->psi,TRUE,"=",FALSE);

#ifdef SHOWMEM
  puts("From reductions:");
  stats();
#endif

  collect_mem(NULL,0);
}


int start_loop(expr_t *var, expr_t *left, expr_t *right)

{
  int i,len,simple;
  vect_t *l_bound,*r_bound;

  l_bound=make_vect(left);
  r_bound=make_vect(right);

  len=rav_value(var->shp,0,&simple);
  if (simple) {
    for (i=0; i<len; i++) {
      dotab(0);
      fprintf(tfile,"for (%s[%d]=",var->ident->string,i);
      print_rav(l_bound,i);
      fprintf(tfile,"; %s[%d]<",var->ident->string,i);
      print_rav(r_bound,i);
      fprintf(tfile,"; %s[%d]++) {\n",var->ident->string,i);
      ntab++;
    }
  } else {
    report("forall vector must have a static shape.");
  }

  return(len);
}


end_loop(int depth)

{
  int i,simple,len;

  for (i=0; i<depth; i++) {
    ntab--;
    dotab(0);
    fprintf(tfile,"}\n");
  }
}


psi_init()

{
  ident_t *ident;

  mem_init();
  s_const0.op=NOP;
  s_const0.left=NULL;
  s_const0.right=NULL;
  s_const0.ident=&const0;
  s_const1.op=NOP;
  s_const1.left=NULL;
  s_const1.right=NULL;
  s_const1.ident=&const1;

  const0.type=FLOAT;
  const0.value=0;
  sprintf(const0.string,"0");

  const1.type=FLOAT;
  const1.value=1;
  sprintf(const1.string,"1");

  ident=get_ident();
  sprintf(ident->string,"<0>");
  ident->type=RAV;
  ident->array.dim=&const1;
  ident->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
  ident->array.rav[0]=&s_const0;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const1;
  zero_vec.ident=ident;
  zero_vec.op=NOP;
  zero_vec.loc=&s_const0;
  zero_vec.index=&s_const0;
  zero_vec.shp=&s_const1;

  ident=get_ident();
  sprintf(ident->string,"1");
  ident->type=RAV;
  ident->array.dim=&const1;
  ident->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
  ident->array.rav[0]=&s_const1;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const1;
  one_vec.ident=ident;
  one_vec.op=NOP;
  one_vec.loc=&s_const0;
  one_vec.index=&s_const0;
  one_vec.shp=&s_const1;

  ident=get_ident();
  sprintf(ident->string,"empty");
  ident->type=CONST_ARRAY;
  ident->array.dim=&const0;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const0;
  empty_vec.ident=ident;
  empty_vec.op=NOP;
  empty_vec.loc=&s_const0;
  empty_vec.index=&s_const0;
  empty_vec.shp=&s_const0;
}
