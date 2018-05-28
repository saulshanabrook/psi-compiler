#include <stdio.h>
#include "../src/psi.h"
#include "trans.h"
#include "PGI_PSI.h"
#include "../src/ops.h"
#include "../src/hpfm/op.h"
#include "../src/sys.h"
#include "../src/moa_func.e"


extern ast_stack psi_ast_stack;
parser_t *vect2parser(vect_t *v);
vect_t *int2vect (int num);
op_t *omega_ize_binary (int dim1, int dim2, psiop_t func);
parser_t *force_order (parser_t *arg1, parser_t *arg2, parser_t *last);
parser_t *psi_access(ident_t *);
expr_t *get_expr_mem(int);
extern vect_t one_vec;
extern ident_t const1;
op_t *omega_ize_unary (int dim1, psiop_t func);


void PGI_PSI_CONCAT(int dim) {
  parser_t *arg1, *arg2;
  op_t *cop;
  psiop_t func;

  arg1 = pop_ast();
  arg2 = pop_ast();
  if (dim == 1)
    push_ast(psi_cat(arg1, arg2));
  else {
    func.func = psi_cat;
    dim = (arg1->ident->array.dim->value - (dim - 1));
    cop = omega_ize_binary(dim, dim, func);
    push_ast(force_order(arg1, arg2, psi_omega2(arg1, arg2, cop)));
  }
}

void PGI_PSI_CSHIFT(int shift_amt, int dim) {
  parser_t *arg1, *arg2;
  op_t *cop, *dop, *top;
  expr_t *boge;
  psiop_t func;
  ident_t *bogi;

  arg1 = pop_ast();
  arg2 = vect2parser(int2vect(shift_amt));
/*  bogi = make_id_cnst(shift_amt);
  arg2 = psi_access(bogi);
*/
  if (dim != 1) {
    dim = (arg1->ident->array.dim->value - (dim - 1));
    func.func=psi_drop;
    dop = omega_ize_binary(1, dim, func);
    dop->omega=FALSE;
    func.func = psi_cat;
    cop = omega_ize_binary(dim, dim, func);
    cop->omega=FALSE;
    func.func = psi_take;
    top = omega_ize_binary(1, dim, func);
    top->omega=FALSE;
    arg2->psi->shp = &one_vec;
    push_ast(force_order (arg1, arg2, psi_omega2(psi_omega2(arg2, arg1, dop),
	    psi_omega2(arg2, arg1, top), cop)));
  }
  else {
    arg2->psi->shp = &one_vec;
    push_ast(psi_cat(psi_drop(arg2,arg1), psi_take(arg2, arg1)));
  }
}

void PGI_PSI_CSHIFT2(int shift_amt, int dim) {
  parser_t *arg1, *arg2;
  op_t *cop, *dop, *top;
  expr_t *boge;
  psiop_t func;
  ident_t *bogi;

  arg1 = pop_ast();
  bogi = make_id_cnst(shift_amt);
  arg2 = psi_access(bogi);
  if (dim != 1) {
    dim = (arg1->ident->array.dim->value - (dim - 1));
    func.func=psi_drop;
    dop = omega_ize_binary(1, dim, func);
    dop->omega=FALSE;
    func.func = psi_cat;
    cop = omega_ize_binary(dim, dim, func);
    cop->omega=FALSE;
    func.func = psi_take;
    top = omega_ize_binary(1, dim, func);
    top->omega=FALSE;
    arg2->psi->shp = &one_vec;
    push_ast(force_order (arg1, arg2, psi_omega2(psi_omega2(arg2, arg1, dop),
	    psi_omega2(arg2, arg1, top), cop)));
  }
  else {
    arg2->psi->shp = &one_vec;
    push_ast(psi_cat(psi_drop(arg2,arg1), psi_take(arg2, arg1)));
  }
}


void PGI_PSI_TRANSPOSE() {
  parser_t *arg1, *arg2;

  arg1 = pop_ast();
  arg2 = NULL;
  push_ast(psi_transpose(arg1,arg2));
}

void PGI_PSI_DOTPROD() {
  parser_t *arg1, *arg2;

  arg1 = pop_ast();
  arg2 = pop_ast();
  push_ast(psi_red_plus(psi_times(arg1, arg2)));
}

void PGI_PSI_MATMUL() {

  /* NOTE -- NEED TO ADD MULTI-DIMENSIONAL ARRAYS BEFORE I CAN TEST THIS! */

  parser_t *arg1, *arg2;
  op_t *mop, *rop;
  psiop_t func;

  arg1 = pop_ast();
  arg2 = pop_ast();
  func.func=NULL;
  mop=omega_ize_binary(1,2,func);
  mop->omega=TRUE;
  func.func=psi_times;
  mop->next=omega_ize_binary(0,1,func);
  mop->next->omega=FALSE;
  
  func.func=psi_red_plus;
  rop=omega_ize_unary (2,func);

  push_ast(force_order(arg1,arg2,psi_omega1(psi_omega2(arg1,arg2,mop),rop)));
}

void PGI_PSI_PRODUCT(int dim) {
  parser_t *arg1;
  psiop_t func;

  arg1=pop_ast();
  func.func=psi_red_times;
  if (dim==1)
    push_ast(psi_red_times(arg1));
  else
    push_ast(
      force_order(arg1,NULL,psi_omega1(arg1,omega_ize_unary(dim,func))));
}

void PGI_PSI_SPREAD(int dim, int nc) {
  parser_t *arg1, *result;
  vect_t *fake;
  int i;

  result=(arg1=pop_ast());
  printf("PSI -- ready to spread along dim %d with %d copies", dim, nc);
  if (dim == 1)
    if (nc > 1) {
      result = psi_cat(arg1, arg1);
      for (i=2; i<nc; i++) {
	result = psi_cat(arg1, result);
      }
    }
  rec_print_expr(result->psi);

/* FAKE -- change shape of 
  fake = vect_cat(int2vect(nc),int2vect(30));
  result->psi->shp = fake;
*/
  push_ast(result);
}

