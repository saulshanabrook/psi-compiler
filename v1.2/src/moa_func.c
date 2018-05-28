/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   moa_func.c - procedures to preform shape analysis.

   5/93 - v0.0 Scott Thibault
   6/93 - v0.1 Scott Thibault
   7/93 - v0.2 Scott Thibault

*/

#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include "psi.h"
#include "ops.h"
#include "sys.h"

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

/* count of utility variables used */
int forall_num=0;  
int red_num=0;

/* psi_access:  converts an ident_t type to a parser_t type */
parser_t *psi_access(ident_t *ident)
{
  int i;
  expr_t *array;
  parser_t *parser;

  array=get_expr_mem(1);
  /*
   * if identifier is a variable, or it's dimenwion is 0 (i.e. a scalar),
   * then set dimension of array to 0;  else copy dimension from ident 
   */
  if ((ident->type==VARIABLE)||(ident->array.dim->value==0.0)) {
    array->dim = &s_const0;
  } else {
    array->dim = get_s_expr();
    array->dim->ident = ident->array.dim;
  }
  if (ident->array.shp!=NULL) {
    /* get memory for array->shp, and set shp->shp (dimension) of array */
    array->shp=get_vect();
    array->shp->shp=get_s_expr();
    array->shp->shp->ident=ident->array.dim;
    /* 
     * get memory for array->shp->ident, type is RAV, dimension of shape
     * vector is one, then set value of shape, component by component
     */
    array->shp->ident=get_ident();
    array->shp->ident->type=RAV;
    array->shp->ident->array.dim=&const1;
    array->shp->ident->array.rav=(s_expr_t **) 
      get_mem(ident->array.dim->value*sizeof(s_expr_t *));
    for (i=0; i<ident->array.dim->value; i++) {
      array->shp->ident->array.rav[i]=get_s_expr();
      array->shp->ident->array.rav[i]->ident=ident->array.shp[i];
    }
    /*
     * set shape of the ident_t that holds the shape to the value of
     * the dimension.  index and loc are 0
     */
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

/*
 * psi_iota:  creates a parser_t type for the operator iota.  arg1 is
 * the vector (contained in an expr_t) to take iota of.
 */
parser_t *psi_iota(parser_t *arg1)

{
  parser_t *iota;
  
  if (arg1->psi!=NULL) {
    /* get memory to store everything */
    iota=(parser_t *) get_mem(sizeof(parser_t));
    iota->psi=get_expr_mem(1);
    /* dim (iota (arg1)) = shape (arg1) + 1.  */
    iota->psi->dim=s_op(PLUS,make_s_expr(arg1->psi->shp),&s_const1);
    /*
     * shape (iota (arg1)) = arg1 cat shape (arg1). (if arg1 is vector) 
     * shape (iota (arg1)) = arg1.                  (if arg1 is scalar)
     */
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

/* psi_dim:  creates a parser_t type for the dimension of arg1 */
parser_t *psi_dim(parser_t *arg1)
{
  parser_t *dim;
 
  /*
   * set up the parser_t type to hold dim (arg1).  
   */
  dim=(parser_t *) get_mem(sizeof(parser_t));
  dim->ident=NULL;
  dim->psi=get_expr_mem(1);
  /*  dim=0, shape=<>, convert arg1->psi->dim to an ident_t type. */
  dim->psi->dim=&s_const0;
  dim->psi->shp=&empty_vec;
  dim->psi->ident=make_ident(arg1->psi->dim);
  return(dim);
}

/* psi_tau:  creates a parser_t type for the tau of arg1 */
parser_t *psi_tau(parser_t *arg1)
{
  int i;
  parser_t *parser;
  expr_t *array;
  s_expr_t *tmp;
  ident_t *ident;

  /* 
   * if the dimension of arg1 is 0, then it's a scalar, and tau of a
   * scalar is 0. 
   */
  if (arg1->psi->dim->ident->value==0) {
    ident=&const0;
  } else {
    /*
     * simplify the scalar expression shape as much as possible, and
     * then do pi (shape (arg1)).
     */
    tmp=simplify_s_expr(red_rav(arg1->psi->shp,0));
    for (i=1; i<arg1->psi->dim->ident->value; i++) {
      tmp=s_op(TIMES,tmp,red_rav(arg1->psi->shp,i));
    }
    ident=make_ident(tmp);
  }
 
  /* set up the expr_t that holds tau (arg1).  dim=0; shp=<> */ 
  array=get_expr_mem(1);
  array->dim=&s_const0;
  array->shp=&empty_vec;
  array->ident=ident;
  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

/* psi_shp:  creates a parser_t type for the shp of arg1 */
parser_t *psi_shp(parser_t *arg1)
{
  parser_t *shp;
  vect_t *vect;

  /*
   * set up everything for the parser_t type that holds shape (arg1).
   */
  shp=(parser_t *) get_mem(sizeof(parser_t));
  shp->ident=NULL;
  shp->psi=get_expr_mem(1);
  /* dim (shape (arg1)) = 1;  shape (shape (arg1)) = dim (arg1) */
  shp->psi->dim=&s_const1;
  shp->psi->shp=s_vect(arg1->psi->dim);
  vect=purify_vect(arg1->psi->shp);
  shp->psi->ident=vect->ident;
  
  return(shp);
}

/* psi_rav:  creates a parser_t type for the rav of arg1 */
parser_t *psi_rav(parser_t *arg1)
{
  int i;
  parser_t *parser;
  expr_t *array;
  vect_t *vect;
  ident_t *ident;
  s_expr_t *tmp;

  /* 
   * compute shape (rav (arg1)).  if arg1's dimension is 0 (a scalar),
   * then the shape (rav (arg1)) is 1.  else compute pi (shape (arg1)).
   */
  if (arg1->psi->dim->ident->value==0) {
    ident=&const1;
  } else {
    tmp=simplify_s_expr(red_rav(arg1->psi->shp,0));
    for (i=1; i<arg1->psi->dim->ident->value; i++) {
      tmp=s_op(TIMES,tmp,red_rav(arg1->psi->shp,i));
    }
    ident=make_ident(tmp);
  }
  /*
   * set up everything for the vect_t type that holds shape (rav (arg1)).
   * loc=0; index=0; shp=<1>;
   */
  vect=get_vect();
  vect->loc=&s_const0;
  vect->index=&s_const0;
  vect->shp=&s_const1;
  vect->ident=ident;

  /* set up the expr_t that holds rav (arg1) */
  array=get_expr_mem(1);
  array->op=RAVEL;
  array->dim=&s_const1;
  array->shp=vect;
  /* array->right should not be used for unary operators */
  array->left=arg1->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}
  
/* psi_take:  creates a parser_t type for arg1 take arg2 */
parser_t *psi_take(parser_t *arg1, parser_t *arg2)
{
  parser_t *parser;
  expr_t *shp,*array;

  printf("\nin psi_take...");
  /* set up the expr_t that holds arg1 take arg2.  since arg2 holds the
     actual data for our operation (taking 2 rows, taking 3 rows from the
     end, etc...)  */
  array=copy_expr(arg2->psi);
  array->op=TAKE;
/*  if (arg1->psi->shp==NULL) */ arg1->psi->shp=&one_vec;
  array->shp=vect_cat(vect_unop(ABS,make_vect(arg1->psi)),
		      vect_drop(arg1->psi->shp,arg2->psi->shp));
  
  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

/* psi_take: creates a parser_t type for arg1 drop arg2 */
parser_t *psi_drop(parser_t *arg1, parser_t *arg2)
{
  parser_t *parser;
  expr_t *shp,*array,*tmp,*tmp_shp;

  printf("\nin psi_drop...");
  array=copy_expr(arg2->psi);
  array->op=DROP;
/*  if (arg1->psi->shp==NULL) */
  arg1->psi->shp=&one_vec;
  print_vector(&one_vec);
  print_vector(arg1->psi->shp); print_vector(arg2->psi->shp);
  array->shp=vect_op(MINUS,vect_take(arg1->psi->shp,arg2->psi->shp),
		     vect_unop(ABS,make_vect(arg1->psi)));
  array->shp=vect_cat(array->shp,vect_drop(arg1->psi->shp,arg2->psi->shp));
/*  printf("CHECK  "); fflush(stdout); */
  array->left=arg1->psi;
/*  printf("CHECK  "); fflush(stdout); */
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

/* psi_take: creates a parser_t type for arg1 ptake arg2, i.e. positive
   take  */
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

/* psi_take: creates a parser_t type for arg1 pdrop arg2, i.e. positive
   drop  */
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

/* psi_take: creates a parser_t type for reverse arg2 */
parser_t *psi_reverse(parser_t *arg1)
{
  parser_t *parser;
  expr_t *shp,*array,*tmp,*tmp_shp;

  array=copy_expr(arg1->psi);
  array->op=REVERSE;
  array->right=arg1->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

/* psi_take: creates a parser_t type for reverse arg2 */
parser_t *psi_transpose(parser_t *arg1, parser_t *arg2)
{
  /* nothing is here yet.  when time flows like the river nile, 
     something will be put here */
}

parser_t *psi_reshape(parser_t *arg1, parser_t *arg2)
{
  /* guess what!  nothing's here either.  reshape is difficult to
     implement since the compiler represents EVERY expression in
     terms of (b take i drop array).  reshaping one array is simple
     enough, but reshaping a complicated expression requires a little
     more doing */
}

/* psi_rotate: creates a parser_t type for arg1 rotate arg2 */
/* (this probably doesn't work) */
parser_t *psi_rotate(parser_t *arg1, parser_t *arg2)
{
  parser_t *parser;
  expr_t *shp,*array,*tmp,*tmp_shp;

  array=copy_expr(arg2->psi);
  array->op=ROTATE;
  if (arg1->psi->shp==NULL) arg1->psi->shp=&one_vec;

  array->left=arg1->psi;
  array->right=arg2->psi;

  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

/* scalar_extend: create an expr_t type for a scalar extension */
expr_t *scalar_extend(expr_t *scalar, vect_t *shp)
{
  expr_t *ret;

  scalar->shp=&one_vec;
  ret=get_expr_mem(1);
  ret->op=SCALAR_EXTEND;
  ret->dim=shp->shp;
  ret->shp=shp;
  ret->left=scalar;

  return(ret);
}  

/* psi_op: creates a parser_t type for arg1 op arg2 */
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
    psi_error("Incompatibale shapes with algebraic operator");
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

/* psi_psi: creates a parser_t type represting arg1 psi arg2 */
parser_t *psi_psi(parser_t *arg1, parser_t *arg2)
{
  parser_t *parser;
  expr_t *array,*tmp,*left;

  left=arg1->psi;
  if (SCALAR(left->dim)&&(left->dim->ident->value==0)) {
    left=get_expr_mem(1);
    *left=*(arg1->psi);
    left->dim=&s_const1;
    left->shp=&one_vec;
  } 
  array=get_expr_mem(1);
  array->op=PSI;
  array->dim=s_op(MINUS,arg2->psi->dim,make_s_expr(left->shp));
  array->shp=vect_drop(left->shp,arg2->psi->shp);
  
  array->left=left;
  array->right=arg2->psi;
  
  parser=(parser_t *) get_mem(sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;
  
  return(parser);
}
  
/* psi_cat: creates a parser_t type for arg1 cat arg2 */    
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

/* psi_omega1: creates a parser_t type for an unary omega expression */
parser_t *psi_omega1(parser_t *arg2, op_t *op)
{
  s_expr_t *fa_s;
  vect_t *sig_r,*u;
  vect_t *c_sig_r,*fa_i2_vect;
  vect_t *fa_bound,*dim_v, *fa_vect;
  expr_t *array,*fa_i2;
  parser_t *parser,*tmp2,*tmp3;
  parser_t *new_right;
  ident_t *fa;
  double size;
  int constant;

  sig_r=make_vect(op->part->psi);

  c_sig_r=vect_op(MINUS,s_vect(arg2->psi->dim),sig_r);

  u=vect_take(c_sig_r,arg2->psi->shp);
  fa_bound=u;

  fa=get_ident();
  fa->type=ARRAY;
  fa->real=FALSE;
  fa->array.dim=&const1;
  fa->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  fa->array.shp[0]=make_ident(fa_bound->shp);
  sprintf(fa->string,"forall_i%d",forall_num);
  declare_var (TRUE, fa->string, (int) fa_bound->shp->ident->value);
  fa_vect=get_vect();
  fa_vect->index=&s_const0;
  fa_vect->loc=&s_const0;
  fa_vect->shp=fa_bound->shp;
  fa_vect->ident=fa;
  SETUSED(fa->flags);
  forall_num++;

  fa_i2=(psi_access(fa_vect->ident))->psi;
  size=rav_value(fa_i2->shp,0,&constant);

  if (constant&&(size==0)) tmp2=NULL;
  else {
    tmp2=(parser_t *) get_mem(sizeof(parser_t));
    tmp2->ident=NULL;
    tmp2->psi=fa_i2;
  }

  if (tmp2!=NULL) {
    new_right=psi_psi(tmp2,arg2);
  } else {
    new_right=arg2;
  }
  
  if (op->next!=NULL) {
    tmp3=psi_omega1(new_right,op->next);
  } else {
    tmp3=(*(op->func))(new_right);
  }

  array=get_expr_mem(1);
  array->op=FORALL;
  dim_v=fa_i2->shp;
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

/* psi_omega: creates a parser_t type for a binary omega expression */
parser_t *psi_omega2(parser_t *arg1, parser_t *arg2, op_t *op)
{
  s_expr_t *fa_s;
  vect_t *sig_l,*sig_r,*u,*u_x,*v_x,*m;
  vect_t *c_sig_l,*c_sig_r,*v,*fa_i1_vect,*fa_i2_vect;
  vect_t *fa_bound,*dim_v, *fa_vect;
  expr_t *array,*fa_i1,*fa_i2;
  parser_t *parser,*tmp1,*tmp2,*tmp3;
  parser_t *new_left,*new_right;
  ident_t *fa;
  double size;
  int constant;

  printf("\nIN PSI_OMEGA\n"); 
  /* pick out the elements of the vector argument to omega */
  sig_l=vect_take(&one_vec,make_vect(op->part->psi));
  print_vector(sig_l); fflush(stdout);
  sig_r=vect_drop(&one_vec,make_vect(op->part->psi));
  print_vector(sig_r);fflush(stdout);
  /* find the dimensions of the partitions of the left and right arguments */
  c_sig_l=vect_op(MINUS,s_vect(arg1->psi->dim),sig_l);

/* THIS IS WHERE THINGS ARE BREAKING DOWN... I SHOULD GET 0 BUT INSTEAD I
   AM GETTING -1.  SINCE I KNOW SIG_L IS CORRECT, THAT CAN ONLY MEAN ONE
   THING: ARG1 IS COMING IN AS 0-DIMENSTION AS OPPOSED TO 1-DIMENSIONAL!
*/

  print_vector(c_sig_l);fflush(stdout);
  c_sig_r=vect_op(MINUS,s_vect(arg2->psi->dim),sig_r);
  print_vector(c_sig_r);fflush(stdout);
  /* this follows pretty much directly from Dr. Mullin's thesis */
  m=vect_op(MIN,c_sig_l,c_sig_r);
  print_vector(m);fflush(stdout);
  u_x=vect_take(c_sig_l,arg1->psi->shp);
  print_vector(u_x);  
  u=vect_take(vect_op(MINUS,c_sig_l,m),u_x);
  print_vector(u);
  v_x=vect_take(c_sig_r,arg2->psi->shp);
  print_vector(v_x);
  v=vect_take(vect_op(MINUS,c_sig_r,m),v_x);
  print_vector(v);
  fa_bound=vect_cat(u,v_x);
  print_vector(fa_bound);  
  /* set up the forall expression */
  fa=get_ident();
  fa->type=ARRAY;
  fa->real=FALSE;
  fa->array.dim=&const1;
  fa->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  fa->array.shp[0]=make_ident(fa_bound->shp);
  sprintf(fa->string,"forall_i%d",forall_num);
  declare_var (TRUE, fa->string, (int) fa_bound->shp->ident->value);
  fa_vect=get_vect();
  fa_vect->index=&s_const0;
  fa_vect->loc=&s_const0;
  fa_vect->shp=fa_bound->shp;
  fa_vect->ident=fa;
  SETUSED(fa->flags);
  forall_num++;
  fa_i1_vect=purify_vect(vect_drop(s_vect(v->shp),fa_vect));
  fa_i1=(psi_access(fa_i1_vect->ident))->psi;
  size=rav_value(fa_i1->shp,0,&constant);

  if (constant&&(size==0)) tmp1=NULL;
  else {
    tmp1=(parser_t *) get_mem(sizeof(parser_t));
    tmp1->ident=NULL;
    tmp1->psi=fa_i1;
  }

  fa_i2_vect=purify_vect(vect_drop(s_vect(u->shp),fa_vect));
  fa_i2=(psi_access(fa_i2_vect->ident))->psi;
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
    printf("CHECK IF "); fflush(stdout);
    tmp3=psi_omega2(new_left,new_right,op->next);
  } else {
    printf("CHECK ELSE "); fflush(stdout);
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
  printf("I'M OUTTA HERE!\n");fflush(stdout);
  return(parser);
}

/* psi_red_op: creates a parser_t type for (op red arg) */
parser_t *psi_red_op(int op, parser_t *arg)
{
  s_expr_t *fa_s;
  vect_t *u;
  vect_t *fa_bound, *fa_vect;
  expr_t *array,*fa_i2;
  parser_t *parser,*tmp2,*tmp3;
  parser_t *new_right;
  ident_t *fa;
  double size;
  int constant;

  /* reduction is implemented with a forall expression */
  u=vect_take(&one_vec,arg->psi->shp);
  fa_bound=u;

  fa=get_ident();
  fa->type=ARRAY;
  fa->real=FALSE;
  fa->array.dim=&const1;
  fa->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  fa->array.shp[0]=make_ident(fa_bound->shp);
  sprintf(fa->string,"forall_i%d",forall_num);
  declare_var (TRUE, fa->string, (int) fa_bound->shp->ident->value);
  fa_vect=get_vect();
  fa_vect->index=&s_const0;
  fa_vect->loc=&s_const0;
  fa_vect->shp=fa_bound->shp;
  fa_vect->ident=fa;
  SETUSED(fa->flags);
  forall_num++;

  fa_i2=(psi_access(fa_vect->ident))->psi;
  size=rav_value(fa_i2->shp,0,&constant);

  if (constant&&(size==0)) tmp2=NULL;
  else {
    tmp2=(parser_t *) get_mem(sizeof(parser_t));
    tmp2->ident=NULL;
    tmp2->psi=fa_i2;
  }

  if (tmp2!=NULL) {
    new_right=psi_psi(tmp2,arg);
  } else {
    new_right=arg;
  }
  
  array=get_expr_mem(1);
  switch (op) {
  case PLUS_RED:
    array->op=PLUS;
    break;
  case MINUS_RED:
    array->op=MINUS;
    break;
  case TIMES_RED:
    array->op=TIMES;
    break;
  case DIVIDE_RED:
    array->op=DIVIDE;
    break;
  }

  if ((arg->psi->op!=PLUS)&&(arg->psi->op!=MINUS)) {
    /* this is a bad way to insure a temp gets created if needed */
    array->op=TIMES;
  }

  array->dim=new_right->psi->dim;
  array->shp=new_right->psi->shp;    
  array->left=new_right->psi;
  
  tmp3=(parser_t *) get_mem(sizeof(parser_t));
  tmp3->ident=NULL;
  tmp3->psi=array;

  array=get_expr_mem(1);
  array->op=op;
  array->dim=tmp3->psi->dim;
  array->shp=tmp3->psi->shp;
  array->left=tmp3->psi;
  array->forall=(forall_t *) get_mem(sizeof(forall_t));
  array->forall->bound=fa_bound;
  array->forall->fa=fa;

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
