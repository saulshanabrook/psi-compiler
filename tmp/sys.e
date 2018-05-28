/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   sys.e - exported functions from sys.c

*/

extern int ntab;
extern int ntabf;
extern int ptabs;
extern dotab(int adj);
extern dotabf(FILE *fd, int adj);
extern do_ptab(int adj);
extern expr_t *get_expr_mem(int);
extern vect_t *get_vect();
extern ident_t *get_ident();
extern s_expr_t *get_s_expr();
extern statement_t *get_statement(int kind);
extern void *get_mem(int);
extern void *get_tmp_mem(int);
extern void free_tmp_mem();
extern void error(char *);
extern expr_t *copy_expr(expr_t *);
extern stats();
extern FILE *cfile;
extern FILE *tfile;
extern FILE *vfile;
extern FILE *hostfile;
extern FILE *hfile;
extern FILE *rfile;
extern save_t *save_list;
#define get_reduced() (reduced_t *) get_tmp_mem(sizeof(reduced_t))
#define get_dist() (dist_t *) get_tmp_mem(sizeof(dist_t))
#define get_rule() (rule_t *) get_tmp_mem(sizeof(rule_t))
#define free_mem(junk) free(junk)
