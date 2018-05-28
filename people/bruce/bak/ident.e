/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   ident.e - exported functions from ident.c

*/

extern ident_t *make_ident(s_expr_t *s);
extern print_s_expr(FILE *outfile, s_expr_t *s);
extern s_expr_t *make_s_expr(vect_t *vect);
extern s_expr_t *red_s_expr(s_expr_t *s_expr);
extern s_expr_t *simplify_s_expr(s_expr_t *s);
extern s_expr_t *s_op(int op, s_expr_t *left, s_expr_t *right);
extern vect_t *s_vect(s_expr_t *s);
extern int scalar_num;
extern int int_expr;
