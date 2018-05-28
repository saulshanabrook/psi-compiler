/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* sys.e - exported functions from sys.c */

extern int ntab;
extern dotab(int adj);
extern expr_t *get_expr_mem(int);
extern vect_t *get_vect();
extern ident_t *get_ident();
extern s_expr_t *get_s_expr();
extern void *get_mem(int);
extern void error(char *);
extern void fatal(char *);
extern expr_t *copy_expr(expr_t *);
extern stats();
extern collect_mem(parser_t *[],int);
extern FILE *cfile;
extern FILE *tfile;
extern FILE *vfile;
extern FILE *afile;
