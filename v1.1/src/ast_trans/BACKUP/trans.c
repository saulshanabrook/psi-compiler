#include <stdio.h>
#include "psi.h"
#include "trans.h"
#include "PGI_PSI.h"

extern ast_stack psi_ast_stack;
statement_t *assn;
extern FILE *cfile, *rfile, *tfile, *vfile;
extern int prove, generic;
expr_t *lhs, *rhs;

void PGI_PSI_INIT() {
  psi_ast_stack = NULL;
  mem_init();
  psi_init();
/*  lex_init(); */
  cfile = stdout;
  rfile = stdout;
  tfile = stdout;
  vfile = stdout;
  prove = FALSE;
  generic = FALSE;


}

void PGI_PSI_ASGN() {
  assn = get_statement(ASSIGN);
  assn->d.assign->expr = (rhs = (pop_ast())->psi);
  assn->d.assign->result = (lhs = (pop_ast())->psi);

}

void PGI_PSI_REDUCE(int curst) {
  ident_t *tmp;

  reduction_init();
  lhs->bound=rhs->shp;
  psi_reduce(assn, TRUE);
  assn->str = "FISH!";
/*  PSI_PGI_AST(assn, curst, partition(assn)); */
  code_c_rec(assn, partition(assn)); 
  printf("CODE GENERATION COMPLETE\n"); fflush(stdout);
}

void PSI_PGI_BOOT() {}

void PSI_PGI_FREEMEM() {}
