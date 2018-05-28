/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   psi.e - exported functions from psi.c

*/

extern int temp_used;
extern vect_t zero_vec,one_vec,empty_vec;
extern ident_t const0,const1;
extern s_expr_t s_const0,s_const1;
extern expr_t *assign(expr_t *expr, expr_t *result, int top, char *op, 
	int new_tmp);
extern int temp_array_num;
extern add_allocation(expr_t *expr);
extern psi_reduce(statement_t *statement);
extern int empty(vect_t *vect);
