/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* moa_func.e - exported functions from moa_func.c */
#include "ops.h"

extern parser_t *psi_access(ident_t *ident);
extern parser_t *psi_iota(parser_t *arg1);
extern parser_t *psi_tau(parser_t *arg1);
extern parser_t *psi_dim(parser_t *arg1);
extern parser_t *psi_shp(parser_t *arg1);
extern parser_t *psi_tr(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_take(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_drop(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_ptake(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_pdrop(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_op(int op, parser_t *arg1, parser_t *arg2);
extern parser_t *psi_psi(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_cat(parser_t *arg1, parser_t *arg2);
extern parser_t *psi_omega2(parser_t *arg1, parser_t *arg2, op_t *op);
extern parser_t *psi_plus(parser_t *left, parser_t *right);
extern parser_t *psi_minus(parser_t *left, parser_t *right);
extern parser_t *psi_div(parser_t *left, parser_t *right);
extern parser_t *psi_times(parser_t *left, parser_t *right);
extern parser_t *psi_red_plus(parser_t *arg);
extern parser_t *psi_red_minus(parser_t *arg);
extern parser_t *psi_red_times(parser_t *arg);
extern parser_t *psi_red_div(parser_t *arg);
extern parser_t *psi_rav(parser_t *arg1);
extern int forall_num;
extern int red_num;
