/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   vect.e - exported functions from vect.c 

*/

extern vect_t *make_vect(expr_t *expr);
extern vect_t *vect_op(int op, vect_t *left, vect_t *right);
extern vect_t *vect_take(vect_t *left, vect_t *right);
extern vect_t *vect_drop(vect_t *left, vect_t *right);
extern vect_t *vect_cat(vect_t *left, vect_t *right);
extern vect_t *vect_unop(int op, vect_t *vect);
extern s_expr_t *red_rav(vect_t *vect, int i);
extern print_scalar(vect_t *expr);
extern vect_assign(vect_t *vect, vect_t *res, char *op);
extern int vect_setup(vect_t *expr);
extern vect_t *purify_vect(vect_t *vect);
extern vect_t *vect2array(char *name,vect_t *vect);
extern double rav_value(vect_t *vect, int i, int *simple);
extern vect_t *vect_len(vect_t *vect);
extern vect_t *simplify_vect(vect_t *vect);
extern int vect_tmp_num;
extern int cond_tmp_num;
extern tau(FILE *fd, expr_t *expr);
extern vect_t *force_vect(vect_t *vect);
extern int static_shps(vect_t *vect);
