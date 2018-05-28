extern parser_t *make_compatable (parser_t *arg, psiop_t func);
extern parser_t *non_psi (parser_t *arg1, parser_t *arg2);
extern parser_t *unon_psi (parser_t *arg1);
extern parser_t *unon2_psi (parser_t *arg1);
statement_t *hpfm_reduce(parser_t *result, parser_t *expr, statement_t *statement);
