/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include "psi.h"
#include "ops.h"

#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

int forall_num=0;
int red_num=0;


parser_t *psi_access(ident_t *ident)

{
  int i;
  expr_t *array;
  parser_t *parser;

  array=get_expr_mem(1);
  array->dim=get_s_expr();
  array->dim->ident=ident->array.dim;
  if (ident->array.shp!=NULL) {
    array->shp=get_vect();
    array->shp->shp=get_s_expr();
    array->shp->shp->ident=ident->array.dim;
    array->shp->ident=get_ident();
    array->shp->ident->type=RAV;
    array->shp->ident->array.dim=&const1;
    array->shp->ident->array.rav=(s_expr_t **) 
      get_mem(ident->array.dim->value*sizeof(s_expr_t *));
    for (i=0; i<ident->array.dim->value; i++) {
      array->shp->ident->array.rav[i]=get_s_expr();
      array->shp->ident->array.rav[i]->ident=ident->array.shp[i];
    }
    array->shp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    array->shp->ident->array.shp[0]=ident->array.dim;
    array->shp->index=&s_const0;
    array->shp->loc=&s_const0;
  } else array->shp=&empty_vec;
  array->ident=ident;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=ident;
  parser->psi=array;

  return(parser);
}


parser_t *psi_iota(parser_t *arg1)

{
  parser_t *iota;
  
  if (arg1->psi!=NULL) {
    iota=(parser_t *) get_mem(sizeof(parser_t));
    iota->psi=get_expr_mem(1);
    iota->psi->dim=s_op(PLUS,make_s_expr(arg1->psi->shp),&s_const1);
    if (arg1->psi->dim->ident->value!=0) {
      iota->psi->shp=vect_cat(make_vect(arg1->psi),arg1->psi->shp);
    } else {
      iota->psi->shp=make_vect(arg1->psi);
    }
      
    iota->psi->ident=get_ident();
    iota->psi->ident->type=IOTA;

    return(iota);
  } else {
    return(NULL);
  }
}


parser_t *psi_dim(parser_t *arg1)

{
  parser_t *dim;
  
  dim=(parser_t *) get_mem(sizeof(parser_t));
  dim->ident=NULL;
  dim->psi=get_expr_mem(1);
  dim->psi->dim=&s_const0;
  dim->psi->shp=&empty_vec;
  dim->psi->ident=make_ident(arg1->psi->dim);
  return(dim);
}


parser_t *psi_tau(parser_t *arg1)

{
  int i;
  parser_t *parser;
  expr_t *array;
  s_expr_t *tmp;
  ident_t *ident;

  if (arg1->psi->dim->ident->value==0) {
    ident=&const0;
  } else {
    tmp=simplify_s_expr(red_rav(arg1->psi->shp,0));
    for (i=1; i<arg1->psi->dim->ident->value; i++) {
      tmp=s_op(TIMES,tmp,red_rav(arg1->psi->shp,i));
    }
    ident=make_ident(tmp);
  }
  
  array=get_expr_mem(1);
  array->dim=&s_const0;
  array->shp=&empty_vec;
  array->ident=ident;
  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_shp(parser_t *arg1)

{
  parser_t *shp;
  vect_t *vect;

  shp=(parser_t *) get_mem(sizeof(parser_t));
  shp->ident=NULL;
  shp->psi=get_expr_mem(1);
  shp->psi->dim=&s_const1;
  shp->psi->shp=s_vect(arg1->psi->dim);
  vect=purify_vect(arg1->psi->shp);
  shp->psi->ident=vect->ident;
  
  return(shp);
}


parser_t *psi_rav(parser_t *arg1)

{
  int i;
  parser_t *parser;
  expr_t *array;
  vect_t *vect;
  ident_t *ident;
  s_expr_t *tmp;

  if (arg1->psi->dim->ident->value==0) {
    ident=&const1;
  } else {
    tmp=simplify_s_expr(red_rav(arg1->psi->shp,0));
    for (i=1; i<arg1->psi->dim->ident->value; i++) {
      tmp=s_op(TIMES,tmp,red_rav(arg1->psi->shp,i));
    }
    ident=make_ident(tmp);
  }
  vect=get_vect();
  vect->loc=&s_const0;
  vect->index=&s_const0;
  vect->shp=&s_const1;
  vect->ident=ident;

  array=get_expr_mem(1);
  array->op=RAVEL;
  array->dim=&s_const1;
  array->shp=vect;
  array->left=arg1->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}
  



/*
parser_t *psi_tr(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=copy_expr(arg2->psi);
  parser->psi->rot=arg1->psi;
  parser->psi->shp->rot=arg1->psi;

  return(parser);
}
*/


parser_t *psi_take(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *shp,*array;

  array=copy_expr(arg2->psi);
  array->op=TAKE;
  if (arg1->psi->shp==NULL) arg1->psi->shp=&one_vec;
  array->shp=vect_cat(vect_unop(ABS,make_vect(arg1->psi)),
		      vect_drop(arg1->psi->shp,arg2->psi->shp));
  
  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_drop(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *shp,*array,*tmp,*tmp_shp;

  array=copy_expr(arg2->psi);
  array->op=DROP;
  if (arg1->psi->shp==NULL) arg1->psi->shp=&one_vec;
  array->shp=vect_op(MINUS,vect_take(arg1->psi->shp,arg2->psi->shp),
		     vect_unop(ABS,make_vect(arg1->psi)));
  array->shp=vect_cat(array->shp,vect_drop(arg1->psi->shp,arg2->psi->shp));
  
  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_ptake(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *shp,*array;

  array=copy_expr(arg2->psi);
  array->op=PTAKE;
  if (arg1->psi->shp==NULL) arg1->psi->shp=&one_vec;
  array->shp=vect_cat(make_vect(arg1->psi),
		      vect_drop(arg1->psi->shp,arg2->psi->shp));
  
  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_pdrop(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *shp,*array,*tmp,*tmp_shp;

  array=copy_expr(arg2->psi);
  array->op=PDROP;
  if (arg1->psi->shp==NULL) arg1->psi->shp=&one_vec;
  array->shp=vect_op(MINUS,vect_take(arg1->psi->shp,arg2->psi->shp),
		     make_vect(arg1->psi));
  array->shp=vect_cat(array->shp,vect_drop(arg1->psi->shp,arg2->psi->shp));
  
  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


expr_t *scalar_extend(expr_t *scalar, vect_t *shp)

{
  expr_t *ret;

  ret=get_expr_mem(1);
  ret->op=SCALAR_EXTEND;
  ret->dim=shp->shp;
  ret->shp=shp;
  ret->left=scalar;

  return(ret);
}  


parser_t *psi_op(int op, parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *array;

  array=get_expr_mem(1);
  if ((SCALAR(arg1->psi->dim)&&(SCALAR(arg2->psi->dim)))&&
      (arg1->psi->dim->ident->value==arg2->psi->dim->ident->value)) {
    array->dim=arg2->psi->dim;
    array->shp=arg2->psi->shp;    
    array->left=arg1->psi;
    array->right=arg2->psi;
  } else if (SCALAR(arg1->psi->dim)&&(arg1->psi->dim->ident->value==0)) {
    array->dim=arg2->psi->dim;
    array->shp=arg2->psi->shp;    
    array->left=scalar_extend(arg1->psi,array->shp);
    array->right=arg2->psi;
  } else if (SCALAR(arg2->psi->dim)&&(arg2->psi->dim->ident->value==0)) {
    array->dim=arg1->psi->dim;
    array->shp=arg1->psi->shp;    
    array->left=arg1->psi;
    array->right=scalar_extend(arg2->psi,array->shp);
  } else {
    report("Incompatibale shapes with algebraic operator");
  }

  array->op=op;

  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;
  
  return(parser);
}


parser_t *psi_plus(parser_t *left, parser_t *right)

{
  return(psi_op(PLUS,left,right));
}

parser_t *psi_minus(parser_t *left, parser_t *right)

{
  return(psi_op(MINUS,left,right));
}

parser_t *psi_times(parser_t *left, parser_t *right)

{
  return(psi_op(TIMES,left,right));
}

parser_t *psi_div(parser_t *left, parser_t *right)

{
  return(psi_op(DIVIDE,left,right));
}


parser_t *psi_psi(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *array,*tmp;

  array=get_expr_mem(1);
  array->op=PSI;
  array->dim=s_op(MINUS,arg2->psi->dim,make_s_expr(arg1->psi->shp));
  array->shp=vect_drop(arg1->psi->shp,arg2->psi->shp);
  
  array->left=arg1->psi;
  array->right=arg2->psi;
  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;
  
  return(parser);
}
      

parser_t *psi_cat(parser_t *arg1, parser_t *arg2)

{
  parser_t *parser;
  expr_t *array,*shp,*tmp,*left,*right;

  left=arg1->psi;
  if (SCALAR(left->dim)&&(left->dim->ident->value==0)) {
    left=get_expr_mem(1);
    *left=*(arg1->psi);
    left->dim=&s_const1;
    left->shp=&one_vec;
  } 
  right=arg2->psi;
  if (SCALAR(right->dim)&&(right->dim->ident->value==0)) {
    right=get_expr_mem(1);
    *right=*(arg2->psi);
    right->dim=&s_const1;
    right->shp=&one_vec;
  } 

  array=get_expr_mem(1);
  array->op=CAT;
  array->dim=left->dim;
  array->shp=vect_op(PLUS,vect_take(&one_vec,left->shp),
		     vect_take(&one_vec,right->shp));
  array->shp=vect_cat(array->shp,vect_drop(&one_vec,left->shp));
  
  array->left=left;
  array->right=right;
  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_omega2(parser_t *arg1, parser_t *arg2, op_t *op)

{
  vect_t *sig_l,*sig_r,*u,*u_x,*v_x,*m;
  vect_t *fa_bound,*dim_v;
  expr_t *array,*fa_i1,*fa_i2;
  parser_t *parser,*tmp1,*tmp2,*tmp3;
  parser_t *new_left,*new_right;
  ident_t *fa;
  float size;
  int constant;

  sig_l=vect_take(&one_vec,make_vect(op->part->psi));
  sig_r=vect_drop(&one_vec,make_vect(op->part->psi));

  fa_i1=get_expr_mem(1);
  fa_i1->dim=&s_const1;
  fa_i1->shp=vect_op(MINUS,s_vect(arg1->psi->dim),sig_l);
  fa_i2=get_expr_mem(1);
  fa_i2->dim=&s_const1;
  fa_i2->shp=vect_op(MINUS,s_vect(arg2->psi->dim),sig_r);

  m=vect_op(MIN,fa_i1->shp,fa_i2->shp);
  u_x=vect_take(fa_i1->shp,arg1->psi->shp);
  u=vect_take(vect_op(MINUS,fa_i1->shp,m),u_x);
  v_x=vect_take(fa_i2->shp,arg2->psi->shp);
  fa_bound=vect_cat(u,v_x);

  fa=get_ident();
  fa->type=ARRAY;
  fa->array.dim=&const1;
  fa->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  fa->array.shp[0]=make_ident(fa_bound->shp);
  sprintf(fa->string,"forall_i%d",forall_num);
  fprintf(vfile,"  int forall_i%d[%d];\n",forall_num,
	  (int) fa_bound->shp->ident->value);
  fa_i1->ident=fa_i2->ident=fa;
  forall_num++;

  size=rav_value(fa_i1->shp,0,&constant);
  if (constant&&(size==0)) tmp1=NULL;
  else {
    tmp1=(parser_t *) get_mem(sizeof(parser_t));
    tmp1->ident=NULL;
    tmp1->psi=fa_i1;
  }
  size=rav_value(fa_i2->shp,0,&constant);
  if (constant&&(size==0)) tmp2=NULL;
  else {
    tmp2=(parser_t *) get_mem(sizeof(parser_t));
    tmp2->ident=NULL;
    tmp2->psi=fa_i2;
  }

  if ((tmp1!=NULL)&&(tmp2!=NULL)) {
    new_left=psi_psi(tmp1,arg1);
    new_right=psi_psi(tmp2,arg2);
  }
  else if (tmp1!=NULL) {
    new_left=psi_psi(tmp1,arg1);
    new_right=arg2;
  }
  else if (tmp2!=NULL) {
    new_left=arg1;
    new_right=psi_psi(tmp2,arg2);
  } else {
    new_left=arg1;
    new_right=arg2;
  }
  
  if (op->next!=NULL) {
    tmp3=psi_omega2(new_left,new_right,op->next);
  } else {
    tmp3=(*(op->func))(new_left,new_right);
  }

  array=get_expr_mem(1);
  array->op=FORALL;
  dim_v=vect_op(MINUS,vect_op(PLUS,fa_i1->shp,fa_i2->shp),m);
  array->dim=s_op(PLUS,make_s_expr(dim_v),tmp3->psi->dim);
  array->shp=vect_cat(fa_bound,tmp3->psi->shp);
  array->left=tmp3->psi;
  array->forall=(forall_t *) get_mem(sizeof(forall_t));
  array->forall->bound=fa_bound;
  array->forall->fa=fa;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  free(op);
  return(parser);
}


parser_t *psi_red_op(int op, parser_t *arg)

{
  parser_t *tmp,*parser;
  expr_t *i_expr,*array;
  ident_t *i;

  i=get_ident();
  i->type=ARRAY;
  i->array.dim=&const1;
  i->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  i->array.shp[0]=&const1;
  sprintf(i->string,"red_i%d",red_num);
  fprintf(vfile,"  int red_i%d;\n",red_num);
  red_num++;

  i_expr=get_expr_mem(1);
  i_expr->dim=&s_const1;
  i_expr->shp=&one_vec;
  i_expr->ident=i;
  
  tmp=(parser_t *) get_mem(sizeof(parser_t));
  tmp->ident=NULL;
  tmp->psi=i_expr;

  tmp=psi_psi(tmp,arg);

  array=get_expr_mem(1);
  array->op=op;
  array->dim=tmp->psi->dim;
  array->shp=tmp->psi->shp;
  array->left=tmp->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}


parser_t *psi_red_plus(parser_t *arg)

{
  return(psi_red_op(PLUS_RED,arg));
}

parser_t *psi_red_minus(parser_t *arg)

{
  return(psi_red_op(MINUS_RED,arg));
}

parser_t *psi_red_times(parser_t *arg)

{
  return(psi_red_op(TIMES_RED,arg));
}

parser_t *psi_red_div(parser_t *arg)

{
  return(psi_red_op(DIVIDE_RED,arg));
}
