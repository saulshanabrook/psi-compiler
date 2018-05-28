#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "psi.h"
#include "trans.h"
#include "../ops.h"
#include "../hpfm/op.h"
#include "../vect.e"
#include "../moa_func.e"

parser_t *vect2parser(vect_t *v);
op_t *omega_ize_binary (int dim1, int dim2, psiop_t func);
vect_t *int2vect (int num);
extern ident_t const1;
ast_stack psi_ast_stack;

void init_psi() {
  psi_ast_stack = NULL;
}

void push_ast(parser_t *cur_expr) {
  ast_stack curnode;

  curnode = (ast_stack)malloc(sizeof(pasnode));
  curnode->next = psi_ast_stack;
  curnode->expr = cur_expr;
  psi_ast_stack = curnode;
}

parser_t *pop_ast() {
  ast_stack curnode;
  parser_t *curexpr;

  curnode = psi_ast_stack;
  if (curnode == NULL) {printf("\nCANNOT POP EMPTY STACK!\n"); exit(1);} 

  psi_ast_stack = psi_ast_stack->next;
  curexpr = curnode->expr;
  free(curnode);
  return(curexpr);
}

void PGI_PSI_FLUSHS() {
  ast_stack t;

  while(psi_ast_stack) {
    t = psi_ast_stack->next; free(psi_ast_stack); psi_ast_stack = t;
  }
}

void psi_binop(int opcode) {
  parser_t *l_ast, *r_ast;

  l_ast = pop_ast();
  r_ast = pop_ast();
  push_ast(psi_op(opcode, l_ast, r_ast));
}
  

void psi_unop(int opcode) {
  parser_t *l_ast, *new_expr;

  push_ast(psi_op(opcode, pop_ast(), NULL));
}

void PGI_PSI_PLUS() {
  psi_binop(PLUS);
}

void PGI_PSI_MINUS() {
  psi_binop(MINUS);
}

void PGI_PSI_TIMES() {
  psi_binop(TIMES);
}

void PGI_PSI_DIVIDE() {
  psi_binop(DIVIDE);
}

void PGI_PSI_NEGATE() {
  /* make a parser for -1 */
  /* push on stack */
  psi_binop(TIMES);
}

void PGI_PSI_NOP() {
  psi_unop(NOP);
}

void PGI_PSI_ABS() {
  psi_unop(ABS);
}

void PGI_PSI_NULL() {
  parser_t *p;
  /* I think this is whack -- I think I need to set fields in psi to NULL */
  printf("Processing PGI NULL node\n");
  p = (parser_t *)get_mem(sizeof(parser_t));
  p->ident = NULL;
  p->psi = NULL;
  push_ast(p);
}

void PGI_PSI_CONS(char *name, double psi_val, int is_real) {
  ident_t *i;
  int bogus_i;
  unsigned char bogus_c = 1;

  i = get_ident();
  strcpy(i->string, name);
  i->real = is_real;
  i->value = psi_val;
  i->type = CONSTANT;
  search(name, &bogus_c, &bogus_i);
  i->index = bogus_i;
  push_ast((parser_t *)psi_access(i));
}



void PGI_PSI_SCALAR(char *name){
  ident_t *i;
  int bogus_i;
  unsigned char bogus_c = 1;

  i = get_ident();
  strcpy(i->string, name);
  i->type = VARIABLE;
  search(name, &bogus_c, &bogus_i);
  i->index = bogus_i;
  push_ast((parser_t *)psi_access(i));
}

ident_t *make_id_cnst(double psi_val) {
  ident_t *i;
  i = get_ident();
  i->type = CONSTANT;
  i->value = psi_val;
  i->real = 0;
  i->array.dim = get_ident();
  i->array.dim->value=1.0;
  i->array.shp=NULL;
  return(i);
}
  
ident_t *cnst2parse(int psi_val) {
  ident_t *i;
  int j = 0;
  i = get_ident();
  i->type = ARRAY;
  i->array.dim=&const1;
  i->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  i->array.shp[0]->type=CONSTANT;
  i->array.shp[0]->real=FALSE;
  i->array.shp[0]->value=psi_val;
  return i;
}

void PGI_PSI_ARRAY(char *name, int dim, int shps[]){
  ident_t *i, **temp;
  ident_t *j;
  int k;
  int bogus_i;
  unsigned char bogus_c = 1;

  i = get_ident();
  strcpy(i->string, name);
  i->type = ARRAY;
  search(name, &bogus_c, &bogus_i);
  i->index = bogus_i;
  i->array.dim = make_id_cnst(dim);
  i->array.shp = (ident_t **) get_mem(sizeof(ident_t *) * dim);
  for (k=0;k<dim;k++) {
    i->array.shp[k] = make_id_cnst(shps[k]);
  }
  push_ast((parser_t *)psi_access(i));
}

void PGI_PSI_INDEX(int dim, int starts[], int stops[], int strides[]) {
  int i;
  op_t *mop, *aop, *psop;
  vect_t *tempv, *striv, *startv;
  psiop_t func;
  int *components = stops;
  parser_t *argh;

 printf("IN PGI_PSI_INDEX!!!\n"); printf("dim = %d\n", dim); 

  for (i=0; i<dim; i++) {
    printf
      ("Start: %d  Stop: %d  Stride:  %d\n", starts[i], stops[i], strides[i]);
    fflush(stdout);
  }

  for (i=0; i<dim; i++) 
    components[i] = floor((stops[i] - starts[i]) / strides[i]) + 1;

  tempv=int2vect(components[0]);
  for (i=1;i<dim;i++) tempv=vect_cat(tempv, int2vect(components[i]));

  printf("COMPONENTS: "); print_vector(tempv); 
  
  striv=int2vect(strides[0]); startv=int2vect(starts[0]);
  for (i=1;i<dim;i++) {
    striv=vect_cat(striv,int2vect(strides[i]));
    startv=vect_cat(startv,int2vect(starts[i]));
  }

  printf("STARTS: "); print_vector(startv);
  printf("STRIDES: "); print_vector(striv); 
  
  
  func.func = psi_times;
  mop = omega_ize_binary(1,1,func);
  func.func = psi_plus;
  aop = omega_ize_binary(1,1,func);
  func.func = psi_psi;
  psop = omega_ize_binary(1,dim,func);

  argh=vect2parser(tempv);

  push_ast(psi_omega2(psi_omega2(psi_omega2(psi_iota(vect2parser(tempv)),
					    vect2parser(striv), mop),
				 vect2parser(startv), aop),
		      pop_ast(), psop));    
}

void psi_spread_binop(int opcode) {
  parser_t *l_ast, *r_ast;

/*  l_ast = pop_ast();
  r_ast = pop_ast();
  push_ast(psi_op(opcode, l_ast, r_ast));
*/

   printf("WUDDUP? spread binop for opcode %d\n", opcode);
}

void PGI_PSI_SPLUS() {
  psi_spread_binop(PLUS);
}

void PGI_PSI_SMINUS() {
  psi_spread_binop(MINUS);
}

void PGI_PSI_STIMES() {
  psi_spread_binop(TIMES);
}

void PGI_PSI_SDIVIDE() {
  psi_spread_binop(DIVIDE);
}

