#define uchar unsigned char
typedef struct symbol {
  uchar         isname;
  char          *name;
  int           index;
  struct symbol *next;
} symbol_t;


ident_t *find_sym(int index,int talk);
void insert_sym(ident_t *ident, int index);
symbol_t *insert(uchar isname, char *name, int index, int key);
void search(char *name, uchar *isname, int *index);
int find_index(char *name);
ident_t *global_dec();
void arg_dec_int(char *name);
ident_t *var_dec_array(char *name,int number);
ident_t *var_dec_array_2(char *name,int tauvec, int tau, ident_t *ident);
ident_t *var_dec_array_3(char *name,ident_t *ident);
ident_t *const_dec_array(char *name,int number);
ident_t *const_dec_array_2(int tauvec, int tau, ident_t *ident);
ident_t *const_dec_array_3(char *name,ident_t *ident);
ident_t *const_dec_array_4(char *name,ident_t *ident,float number);
ident_t *arg_dec_array(char *name,int number);
ident_t *arg_dec_array_2(char *name,int tauvec, int tau, ident_t *ident);
ident_t *arg_dec_array_3(char *name,ident_t *ident);
statement_t *assignment_psi(ident_t *ident, char *name,parser_t *expr);
statement_t *assignment_pdrop(ident_t *ident, char *name,parser_t *expr);
statement_t *assignment_pdrop(ident_t *ident, char *name,parser_t *expr);
statement_t *assignment_normal(char *name,parser_t *expr);
void declaration_footer();
void dual_fprintf(char *msg);
void executable_header();
void exectutable_post_declaration();
void executable_footer();
parser_t *expression_unary_operator(char *name, parser_t *expr2,
        parser_t *(*func)());
parser_t *expression_binary_operator(parser_t *expr1,char *name, parser_t *expr2,
        parser_t *(*func)());
parser_t *expression_name(char *name);
statement_t *for_statement(parser_t *expr1,parser_t *expr2,
        parser_t *expr3,statement_t *state1);
void procedure_header();
void procedure_post_declaration();
void procedure_footer(statement_t *body);
statement_t *do_procedure_call (char *name, parser_t *expr);
int vector_const2_number(float num);
void vector_const2_init();
void vector_const2_footer();
ident_t *vector_const2_ident();
int vector_const2_name(char *name);
void directive_trace();
void directive_procs(int number);
void directive_arch(char *option);
void directive_hostname(char *option);
void directive_picl(char *option);
void declaration_name(char *name);
