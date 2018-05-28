#define uchar unsigned char
typedef struct symbol {
  uchar         isname;
  char          *name;
  int           index;
  struct symbol *next;
} symbol_t;


extern ident_t *find_sym(int index,int talk);
extern void insert_sym(ident_t *ident, int index);
extern symbol_t *insert(uchar isname, char *name, int index, int key);
extern void search(char *name, uchar *isname, int *index);
extern int find_index(char *name);
extern ident_t *global_dec();
extern void arg_dec_int(char *name);
extern ident_t *var_dec_array(char *name,int number);
extern ident_t *var_dec_array_2(char *name,int tauvec, int tau, ident_t *ident);
extern ident_t *var_dec_array_3(char *name,ident_t *ident);
extern ident_t *const_dec_array(char *name,int number);
extern ident_t *const_dec_array_2(int tauvec, int tau, ident_t *ident);
extern ident_t *const_dec_array_3(char *name,ident_t *ident);
extern ident_t *const_dec_array_4(char *name,ident_t *ident,float number);
extern ident_t *arg_dec_array(char *name,int number);
extern ident_t *arg_dec_array_2(char *name,int tauvec, int tau, ident_t *ident);
extern ident_t *arg_dec_array_3(char *name,ident_t *ident);
extern statement_t *assignment_psi(ident_t *ident, char *name,parser_t *expr);
extern statement_t *assignment_pdrop(ident_t *ident, char *name,parser_t *expr);
extern statement_t *assignment_pdrop(ident_t *ident, char *name,parser_t *expr);
extern statement_t *assignment_normal(char *name, parser_t *expr);
extern void declaration_footer();
extern void dual_fprintf(char *msg);
extern void executable_header();
extern void exectutable_post_declaration();
extern void executable_footer();
extern parser_t *expression_unary_operator(char *name, parser_t *expr2,
        parser_t *(*func)());
extern parser_t *expression_binary_operator(parser_t *expr1,char *name, parser_t *expr2,
        parser_t *(*func)());
extern parser_t *expression_name(char *name);
extern op_t *set_opt (parser_t *(*func)(), char *blurb);
extern op_t *omega_no_bracket (op_t *op, ident_t *part);
extern op_t *omega_yes_bracket (op_t *op, ident_t *part);
extern parser_t *omega_unary (op_t *op, parser_t *right);
extern parser_t *omega_binary (parser_t *left, op_t *op, parser_t *right);
extern statement_t *for_statement(parser_t *expr1,parser_t *expr2,
        parser_t *expr3,statement_t *state1);
extern void procedure_header();
extern void procedure_post_declaration();
extern void procedure_footer(statement_t *body);
extern statement_t *do_procedure_call (char *name, statement_t *expr);
extern int vector_const2_number(float num);
extern void vector_const2_init();
extern void vector_const2_footer();
extern ident_t *vector_const2_ident();
extern int vector_const2_name(char *name);
extern void directive_trace();
extern void directive_procs(int number);
extern void directive_arch(char *option);
extern void directive_hostname(char *option);
extern void directive_picl(char *option);
extern void declaration_name(char *name);
extern void do_procedure_call_1 (char *name);
extern statement_t *do_procedure_call_2 (statement_t *ret);
extern statement_t *allocate_statement(char *name,parser_t *expr);
extern reduced_t *actual_list_4(reduced_t *node1,reduced_t *node2);
extern reduced_t *actual_list_3(char *name);
extern statement_t *actual_list_2(reduced_t *node1,reduced_t *node2);
extern reduced_t *actual_list_1(char *name);
extern expr_t *actual(char *name);
