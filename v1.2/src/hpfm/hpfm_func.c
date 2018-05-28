#include <stdio.h>
#include "f90.h"
#include "psi.h"
#include "ops.h"
#include "op.h"
#include "sys.h"

#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
#include "moa_func.e"

/* note:  the dim variable for the omegas was calculated assuming that
   scalars are stored as constant arrays and the dimension of an
   identifier is a scalar and is stored in ident->array.dim->value */

extern parser_t *vect2parser(vect_t *v);
extern char f90func[20];

parser_t *non_psi (parser_t *arg1, parser_t *arg2)
{
  parser_t *parser;
  expr_t *array;

  array=copy_expr(arg2->psi);
  array->op=EXT_OP;
  array->shp=arg2->psi->shp;
  array->left=arg1->psi;
  array->right=arg2->psi;

  array->ext_str=(char *) get_mem (strlen (arg1->psi->ext_str)+
    strlen (arg2->psi->ext_str)+strlen (f90func)+3);
  sprintf (array->ext_str,"%s%s%s",arg1->psi->ext_str,f90func,arg2->psi->ext_str);

  array->ext_op=UNRECOGNIZED;

  parser=(parser_t *) get_mem (sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;

  return(parser);
}

parser_t *unon_psi (parser_t *arg1)
{
  parser_t *parser;
  expr_t *array,*temp;
  char *f90str;
  int f90len=0;

  array=copy_expr(arg1->psi);
  array->op=EXT_OP;
  array->shp=arg1->psi->shp;
  array->left=arg1->psi;
  array->right=NULL;

  if (arg1->psi->ext_op != FUNC) {
    array->ext_str=(char *) get_mem (strlen (arg1->psi->ext_str)+
      strlen (f90func)+3);
    sprintf (array->ext_str,"%s%s",f90func,arg1->psi->ext_str);
  } else {
    if (arg1!=NULL) {
      temp=arg1->psi;
      f90len=strlen(temp->left->ext_str)+2;
      while (temp->right!=NULL) {
        temp=temp->right;
        f90len=strlen(temp->left->ext_str)+2;
      }
    }
    array->ext_str=(char *)get_mem(strlen(f90func)+f90len+3);
    sprintf (array->ext_str,"%s",f90func);
    if (arg1!=NULL) {
      temp=arg1->psi;
      strcat (array->ext_str, " (");
      strcat (array->ext_str, temp->left->ext_str);
      while (temp->right!=NULL) {
        temp=temp->right;
        strcat (array->ext_str, ", ");
        strcat (array->ext_str, temp->left->ext_str);
      }
      strcat (array->ext_str, ")");
    }
  }
   
  array->ext_op=UNRECOGNIZED;

  parser=(parser_t *) get_mem (sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;
 
  return(parser);
}


/* made another one becase some times it is called with the actual array
arguments and other times is called with function style list of arguments
in function_reference. */

parser_t *unon2_psi (parser_t *arg1)
{
  parser_t *parser;
  expr_t *array,*temp;
  char *f90str;
  int f90len=0;

  array=copy_expr(arg1->psi->left);
  array->op=EXT_OP;
  array->shp=arg1->psi->left->shp;
  array->left=arg1->psi->left;
  array->right=NULL;

  if (arg1->psi->ext_op != FUNC) {
    array->ext_str=(char *) get_mem (strlen (arg1->psi->ext_str)+
      strlen (f90func)+3);
    sprintf (array->ext_str,"%s%s",f90func,arg1->psi->ext_str);
  } else {
    temp=arg1->psi;
    f90len=strlen(temp->left->ext_str)+2;
    while (temp->right!=NULL) {
      temp=temp->right;
      f90len=strlen(temp->left->ext_str)+2;
    }
    array->ext_str=(char *)get_mem(strlen(f90func)+f90len+3);
    sprintf (array->ext_str,"%s",f90func);
    temp=arg1->psi;
    strcat (array->ext_str, " (");
    strcat (array->ext_str, temp->left->ext_str);
    while (temp->right!=NULL) {
      temp=temp->right;
      strcat (array->ext_str, ", ");
      strcat (array->ext_str, temp->left->ext_str);
    }
    strcat (array->ext_str, ")");
  }
   
  array->ext_op=UNRECOGNIZED;

  parser=(parser_t *) get_mem (sizeof(parser_t));
  parser->ident=NULL;
  parser->psi=array;
 
  return(parser);
}

vect_t *int2vect (int num)
{
  ident_t *tident;
  vect_t *tvect;

  tident=get_ident();
  tident->type=CONSTANT;
  tident->value=num;
  tident->array.dim=&const1;
  tident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  tident->array.shp[0]=&const1;
  tvect=get_vect();
  tvect->ident=tident;
  tvect->op=NOP;
  tvect->loc=&s_const0;
  tvect->index=&s_const0;
  tvect->shp=&s_const1;
  return (tvect);
}

/* force_order is used by instrinsic functions (like matmul and cshift)
   that are translated into omega expressions.  this function makes sure
   that if the arguments to the functions are non_psi operations, they
   are evaluated in the reduction phase before the instrinsic ones.  */

parser_t *force_order (parser_t *arg1, parser_t *arg2, parser_t *last)
{
  parser_t *new_arg;
  expr_t *temp;

  if (last->psi->right!=NULL)
    fatal("Internal error: force_order. can't use right tree of node");
  temp=last->psi;
  temp->ext_op=PREORDER;
  if (arg1!=NULL) {
    if (arg1->psi->ext_op!=NOP) {
      temp->right=get_expr_mem(1);
      temp=temp->right;
      temp->op=EXT_OP;
      temp->ext_op=SPLIT;
      temp->left=arg1->psi;
    }
  }
  if (arg2!=NULL) {
    if (arg2->psi->ext_op!=NOP) {
      temp->right=get_expr_mem (1);
      temp=temp->right;
      temp->op=EXT_OP;
      temp->ext_op=SPLIT;
      temp->left=arg2->psi;
    }
  }
  temp->right=NULL; 
  return (last);
}

/* omega_ize_binary is used to turn expressions of the form
   (?) func omega <dim1 dim2> (?) into their appropriate internal
   representation used by the MOA compiler */
op_t *omega_ize_binary (int dim1, int dim2, psiop_t func)
{
  op_t *oop;

  oop=(op_t *) get_mem(sizeof(op_t));
  oop->omega=FALSE;
  oop->func=func.func;
  oop->part=vect2parser(vect_cat(int2vect(dim1),int2vect(dim2))); 
  oop->next=NULL;
  return (oop);
}
  
/* omega_ize_unary is used to turn expressions of the form
   func omega <dim1> (?) into their appropriate internal
   representation used by the MOA compiler */
op_t *omega_ize_unary (int dim1, psiop_t func)
{
  op_t *oop;

  oop=(op_t *) get_mem(sizeof(op_t));
  oop->omega=FALSE;
  oop->func=func.func;
  oop->part=vect2parser(int2vect(dim1));
  oop->next=NULL;
  return (oop);
}
  
parser_t *hpfm_concat (parser_t *arglist)
{
  parser_t *arg1, *arg2;
  vect_t *tvect;
  expr_t *temp;
  op_t *cop;
  psiop_t func;
  int dim;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  arg2=(parser_t *) get_mem(sizeof(parser_t));
  arg2->psi=arglist->psi->right->left;
  arg2->ident=arglist->psi->right->ident;

  if (arglist->psi->right->right != NULL) {
    temp=arglist->psi->right->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0))
      error ("third argument to function CONCAT not constant integer");
    else {
      dim=(int)(arg1->ident->array.dim->value-(temp->ident->array.cnst[0]-1));
      func.func=psi_cat;
      cop=omega_ize_binary(dim,dim,func);
      return(force_order (arg1,arg2,psi_omega2(arg1,arg2,cop)));
    }
  } else return(psi_cat(arg1,arg2));
}

parser_t *hpfm_cshift (parser_t *arglist)
{
  parser_t *arg1, *arg2;
  vect_t *tvect;
  expr_t *temp;
  op_t *dop, *cop, *top;
  psiop_t func;
  int dim;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  tvect=make_vect(arglist->psi->right->left);
  arg2=vect2parser(tvect);
  if (arglist->psi->right->right != NULL) {
    temp=arglist->psi->right->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0))
      error ("third argument to function CSHIFT not constant integer");
    else {
      dim=(int)(arg1->ident->array.dim->value-(temp->ident->array.cnst[0]-1));
      func.func=psi_drop;
      dop=omega_ize_binary(1,dim,func);
      func.func=psi_cat;
      cop=omega_ize_binary(dim,dim,func);
      func.func=psi_take;
      top=omega_ize_binary(1,dim,func);
      return (force_order (arg1,arg2,psi_omega2(psi_omega2(arg2,arg1,dop),
        psi_omega2(arg2,arg1,top),cop)));
    }
  } else return (psi_cat(psi_drop(arg2,arg1),psi_take(arg2,arg1))); 
}

parser_t *hpfm_dot_product (parser_t *arglist)
{
  parser_t *arg1;
  parser_t *arg2;
  
  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg2=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  arg2->psi=arglist->psi->right->left;
  arg2->ident=arglist->psi->right->ident;
  return (psi_red_plus(psi_times(arg1,arg2)));
}

parser_t *hpfm_eoshift (parser_t *arglist)
{
  parser_t *arg1, *arg2, *arg3;
  vect_t *tvect,*shp;
  expr_t *temp;
  op_t *dop, *cop, *top;
  psiop_t func;
  int dim;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  tvect=make_vect(arglist->psi->right->left);
  arg2=vect2parser(tvect);
  if (arglist->psi->right->right!=NULL) {
    tvect=make_vect(arglist->psi->right->right->left);
    arg3=vect2parser(tvect);
    shp=vect_cat(tvect,vect_drop(&one_vec,arg1->psi->shp));
    arg3->psi=scalar_extend(arg3->psi,shp);
  } else arg3=vect2parser(&zero_vec);
  if ((arglist->psi->right->right!=NULL)&&
      (arglist->psi->right->right->right != NULL)) {
    temp=arglist->psi->right->right->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0))
      error ("fourth argument to function CSHIFT not constant integer");
    else {
      dim=(int)(arg1->ident->array.dim->value-(temp->ident->array.cnst[0]-1));
      func.func=psi_drop;
      dop=omega_ize_binary(1,dim,func);
      func.func=psi_cat;
      cop=omega_ize_binary(dim,dim,func);
      func.func=psi_take;
      top=omega_ize_binary(1,dim,func);
      return (force_order(arg1,arg2,psi_omega2(psi_omega2(arg2,arg1,dop),
        psi_omega2(arg2,arg1,top),cop)));
    }
  } else return (psi_cat(psi_drop(arg2,arg1),psi_take(arg2,arg3)));
}

parser_t *hpfm_matmul (parser_t *arglist)
{
  parser_t *arg1;
  parser_t *arg2;
  op_t *mop, *rop;
  psiop_t func;
  
  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg2=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  arg2->psi=arglist->psi->right->left;
  arg2->ident=arglist->psi->right->ident;

  func.func=NULL;
  mop=omega_ize_binary(1,2,func);
  mop->omega=TRUE;
  func.func=psi_times;
  mop->next=omega_ize_binary(0,1,func);
  mop->next->omega=FALSE;

  func.func=psi_red_plus;
  rop=omega_ize_unary (2,func);

  return (force_order(arg1,arg2,psi_omega1(psi_omega2(arg1,arg2,mop),rop)));
}


parser_t *hpfm_product (parser_t *arglist)
{
  parser_t *arg1;
  expr_t *temp;
  psiop_t func;
  int dim;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  func.func=psi_red_times;
  if (arglist->psi->right != NULL) {
    temp=arglist->psi->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0))
      error ("second argument to function CSHIFT not constant integer");
    else {
      dim=(int)(arg1->ident->array.dim->value-(temp->ident->array.cnst[0]-1));
      return (force_order(arg1,NULL,psi_omega1(arg1,omega_ize_unary(
        dim,func))));
    }
  } else return ((func.func)(arg1));
}

parser_t *hpfm_shape (parser_t *arglist)
{
  parser_t *arg1;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  return (psi_shp(arg1));
}

parser_t *hpfm_sum (parser_t *arglist)
{
  parser_t *arg1;
  expr_t *temp;
  psiop_t func;
  int dim;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  func.func=psi_red_plus;
  if (arglist->psi->right != NULL) {
    temp=arglist->psi->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0))
      error ("second argument to function CSHIFT not constant integer");
    else {
      dim=(int)(arg1->ident->array.dim->value-(temp->ident->array.cnst[0]-1));
      return (force_order(arg1,NULL,psi_omega1(arg1,omega_ize_unary(
        dim,func))));
    }
  } else return ((func.func)(arg1));
}

parser_t *hpfm_transpose (parser_t *arglist)
{
  parser_t *arg1,*arg2;
  expr_t *temp;

  arg1=(parser_t *) get_mem(sizeof(parser_t));
  arg1->psi=arglist->psi->left;
  arg1->ident=arglist->psi->ident;
  if (arglist->psi->right != NULL) {
    temp=arglist->psi->right->left;
    if ((temp->ident->type != CONST_ARRAY)||(temp->ident->real!=0)) {
      error ("second argument to function TRANSPOSE not constant array");
    } else {
      if ((int)(arg1->ident->array.dim->value)!=(int)(temp->shp->ident->value))
        error ("TRANSPOSE optional PERM incompatable with first argument");
      else {
        arg2=(parser_t *) get_mem(sizeof(parser_t));
        arg2->psi=temp->left;
        arg2->ident=temp->ident;
      }
    }
  } else arg2=NULL;
  return (psi_transpose(arg1,arg2));
}

