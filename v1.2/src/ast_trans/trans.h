typedef struct stacknode {
  parser_t *expr;
  struct stacknode *next;
} pasnode, *ast_stack;

void init_psi();
void push_ast(parser_t *);
parser_t *pop_ast(void);
int conv_pgi_intr(int);
void psi_binop(int);
void psi_unop(int);
void process_intr(int, int);
ident_t *make_id_cnst(double);

parser_t *psi_op(int, parser_t *, parser_t *);
ident_t *get_ident(void);
statement_t *get_statement(int);
