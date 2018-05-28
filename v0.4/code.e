/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   code.e - exported functions from code.c

*/

extern print_ident(FILE *outfile, ident_t *ident);
extern print_s(FILE *outfile,s_expr_t *s);
extern allocate_vect(ident_t *ident);
extern embed_const_vect(ident_t *ident);
extern print_rav(FILE *outfile, vect_t *expr,int i);
extern code_vect(vect_t *vect, vect_t *res, char *op, char *pre ,char *post,
                 char *mid);
extern recursive_assign(vect_t *vect, vect_t *res, char *op);
extern void declare_utils ();
extern void declare_var (int integer, char *name, int len);
extern void code_idx_array (char *where, char *array, char *index);
extern int max_dim;
extern int max_combined;
extern int const_array_num;
extern my_gamma(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim);
extern my_gamma2(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim);
extern char *picl_file;

