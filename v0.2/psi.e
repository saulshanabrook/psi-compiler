/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* psi.e - exported functions from psi.c */

extern int temp_used;
extern vect_t zero_vec,one_vec,empty_vec;
extern ident_t const0,const1;
extern s_expr_t s_const0,s_const1;
extern expr_t *assign(expr_t *expr, expr_t *result, int top, char *op, 
	int new_tmp);
extern int max_dim;
extern int temp_array_num;
extern int const_array_num;
extern int start_loop(expr_t *var, expr_t *left, expr_t *right);
extern end_loop(int depth);
extern psi_assign(parser_t *expr, parser_t *result);
