%{
/* This is inserted in resulting .C file */
#include <stdio.h>
#include <stdlib.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"
#include "ops.h"
 
#include "code.e"
#include "part.e"
#include "dist.e"
#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
#include "moa_func.e"
#include "_psi.sem.h"

extern int line_num;
extern op_t *op;
FILE *cfile;
%}
%union {
  unsigned int wval;
  signed int swval;
  double fval;
  char *cval;

  ident_t *ident;
  statement_t *statement;
  reduced_t *reduced;
  parser_t *parser;
  vect_t *loc;
  op_t *op;
  s_expr_t *s_expr;
}

/* token definitions */
%token <wval> FOR1
%token <cval> NAME1
%token <fval> NUMBER1
%token <wval> ARRAY1
%token <wval> GLOBAL1
%token <wval> INT1
%token <wval> FLOAT1
%token <wval> PSI1
%token <wval> TAKE1
%token <wval> DROP1
%token <wval> CAT1
%token <wval> PDROP1
%token <wval> PTAKE1
%token <wval> CONST1
%token <wval> IOTA1
%token <wval> DIM1
%token <wval> SHP1
%token <wval> TAU1
%token <wval> RAV1
%token <cval> LTE1
%token <wval> RED1
%token <wval> OMEGA1
%token <wval> TRACE1
%token <wval> PROCS1
%token <wval> ARCH1
%token <wval> HOSTNAME1
%token <wval> PICL1

%left PSI1 TAKE1 DROP1 CAT1 PDROP1 PTAKE1 '+' '-' '*' '/'
%right UNEG IOTA1 DIM1 SHP1 TAU1 RAV1 RED1 

%type <ident> arg_dec
%type <ident> arg_list_opt
%type <ident> arg_list_cont
%type <ident> var_dec
/*
%type <ident> const_dec 
*/
%type <swval> anynumber
%type <ident> global_dec 
%type <ident> var_dec_statement_cont
%type <ident> var_dec_statement_mand
%type <ident> var_dec_statement_opt
%type <statement> statement_base_opt
%type <statement> statement_base_mand
%type <statement> assignment
%type <statement> for_statement
%type <statement> procedure_call
%type <ident> vector_const_ident_base
%type <wval> vector_const2_base
%type <wval> vector_const2_mand
%type <wval> vector_const2_opt
%type <parser> expression
%%

executable_program : /* replaces programx(); */
	{ executable_header(); }
	directives_opt
	{ executable_post_declaration(); }
	procedure_list
	{ executable_footer(); }
	;

directives_opt:
	| '$' TRACE1 {directive_trace(); }
	| '$' PROCS1 NUMBER1 { directive_procs($3);}
	| '$' ARCH1 NAME1 {directive_arch($3);}
	| '$' HOSTNAME1 NAME1 {directive_hostname($3);}
	| '$' PICL1 NAME1 {directive_picl($3);}
	;

procedure_mand:
				{procedure_header();}
	declaration
	'{' 		
	var_dec_statement_opt
	{ procedure_post_declaration(); }
	statement_base_opt 
	'}' 			
				{ procedure_footer($6); } 
	;

procedure_opt:
	| procedure_mand procedure_opt
	;

procedure_list :
	procedure_mand procedure_opt
	;

arg_dec: /* from param_def() and array_def*/
	INT1 NAME1 { arg_dec_int($2); }  
	| ARRAY1 NAME1 '^' NUMBER1 { $<ident>$ = arg_dec_array($2,$4); 
	 $$ = arg_dec_array_3($<ident>5); }
	| ARRAY1 NAME1 '^' NUMBER1 { $<ident>$ = arg_dec_array($2,$4); }
	'<' vector_const_ident_base '>' { $$ = arg_dec_array_2($2,$7,$4,$<ident>5); }

var_dec:
	ARRAY1 NAME1 '^' NUMBER1 { $$ = var_dec_array($2,$4); }
	'<' vector_const_ident_base '>' { $$ = var_dec_array_2($2,$7,$4,$<ident>5); }
	| ARRAY1 NAME1 '^' NUMBER1 { $<ident>$ = var_dec_array($2,$4); 
	 $$ = var_dec_array_3($2,$<ident>5); }
/*	;

const_dec:  */
	| CONST1 ARRAY1 NAME1 '^' NUMBER1 
	'<' vector_const_ident_base '>' 
	'=' '<'vector_const_ident_base '>' 
{ $$=const_dec_array_3(const_dec_array_2($7,$5,const_dec_array($3,$5))); }
	| CONST1 ARRAY1 NAME1 '^' NUMBER1 
	'<' vector_const_ident_base '>' 
	'=' anynumber 
{ $$=const_dec_array_4($3,const_dec_array_2($7,$5,const_dec_array($3,$5)),$10); }
	;

anynumber:
	NUMBER1 { $$ = $1 }
	| '+' NUMBER1 { $$ = $2 }
	| '-' NUMBER1 { $$ = 0 - $2 }

global_dec:
	GLOBAL1 NAME1 { $$ = global_dec($2); }
	;

var_dec_statement_cont : { $$ = NULL; }
	|	var_dec ';' var_dec_statement_cont 
	/*|	const_dec ';' var_dec_statement_cont */
	|	global_dec ';' var_dec_statement_cont
	;

var_dec_statement_mand :
	var_dec ';' var_dec_statement_cont
	/*const_dec ';' var_dec_statement_cont*/
	;

var_dec_statement_opt : { $$ = NULL; }
	|	var_dec_statement_mand
	
arg_list_opt: { $$ = NULL; }
	| arg_dec arg_list_cont
	;

arg_list_cont: { $$ = NULL; }
	| ',' {dual_fprintf(","); } arg_dec arg_list_cont { $$ = $3; }
	;

declaration:
	NAME1 '(' { declaration_name($1);} 
	arg_list_opt 
	')' {  declaration_footer(); } 
	;

statement_base_opt:
	{ $$=NULL}
	| statement_base_mand statement_base_opt 
	{ $$=$1; $1->next=$2; collect_garbage(NULL,save_list,NULL); }
	;

statement_base_mand:
	assignment { $$=$1 }
	| for_statement { $$=$1 }
	| procedure_call { $$=$1 }
	| '{' statement_base_opt '}' { $$=$2 }
	;

assignment: /* statement_t type */
	NAME1 '=' expression ';' 
		{ $$=assignment_normal($1,$3);}
	| '<' vector_const_ident_base '>' PDROP1 NAME1 '=' expression ';'
		{ $$=assignment_pdrop($2,$5,$7); }
	| '<' vector_const_ident_base '>' PSI1 NAME1 '=' expression ';'
		{ $$=assignment_psi($2,$5,$7); }
	;

for_statement:
	FOR1 '(' expression LTE1 expression '<' expression ')' 
	statement_base_mand { $$ = for_statement($3,$5,$7,$9); }
	;

procedure_call:
	NAME1 '(' expression ')' ';'
	/* The folloing function doesn't do anything yet -- thom */
	{ $$ = do_procedure_call ($1, $3); }
	;

vector_const_ident_base:
	vector_const2_base
	{ $$ = vector_const2_ident(); }
	;

vector_const2_base: /* must return an integer == to number of components in vector */
	{ vector_const2_init(); }
	vector_const2_opt
	{$$=vector_const2_num; vector_const2_footer(); }
	;

vector_const2_mand:
	NUMBER1  { $$ = vector_const2_number($1);}
	| NAME1  { $$ = vector_const2_name($1); }
	| '+' NUMBER1 { $$ = vector_const2_number($2); }
	| '-' NUMBER1 { $$ = vector_const2_number(-$2); }
	;

vector_const2_opt: { $$ = 0; }
	| vector_const2_mand vector_const2_opt { $$ = $1 + $2; }
	;

expression:
	NAME1   { $$=expression_name($1); }
/*	| NUMBER1
	| FLOAT1 */
	| '(' expression ')'
		{ strcat(expr_str,"("); $$=$2 strcat(expr_str,")");}
	| '<' vector_const_ident_base '>' 
		{ $$=psi_access($2); }
/* Binary operators */
	| expression '+' expression  
		{ $$=expression_binary_operator($1," + ",$3,psi_plus);} 
	| expression '-' expression  
		{ $$=expression_binary_operator($1," - ",$3,psi_minus);}
	| expression '*' expression   
		{ $$=expression_binary_operator($1," * ",$3,psi_times);}
	| expression '/' expression    
		{ $$=expression_binary_operator($1," / ",$3,psi_div);}
	| expression PSI1 expression  
		{ $$=expression_binary_operator($1," psi ",$3,psi_psi);}
	| expression TAKE1 expression
		{ $$=expression_binary_operator($1," take ",$3,psi_take);}
	| expression DROP1 expression
		{ $$=expression_binary_operator($1," drop ",$3,psi_drop);}
	| expression CAT1 expression
		{ $$=expression_binary_operator($1," cat ",$3,psi_cat);}
	| expression PDROP1 expression 
		{ $$=expression_binary_operator($1," pdrop ",$3,psi_pdrop);}
	| expression PTAKE1 expression 
		{ $$=expression_binary_operator($1," ptake ",$3,psi_ptake);}
/* unary operators */
	| '+' expression %prec UNEG 
		{ $$ = expression_unary_operator(" + ", $2,psi_plus); }
	| '-' expression %prec UNEG 
		{ $$ = expression_unary_operator(" - ", $2,psi_minus); }
	| IOTA1 expression      
		{ $$ = expression_unary_operator(" iota ", $2,psi_iota); }
	| DIM1 expression      
		{ $$ = expression_unary_operator(" dim ", $2,psi_dim); }
	| SHP1 expression     
		{ $$ = expression_unary_operator(" shp ", $2,psi_shp); }
	| TAU1 expression    
		{ $$ = expression_unary_operator(" tau ", $2,psi_tau); }
	| RAV1 expression   
		{ $$ = expression_unary_operator(" rav ", $2,psi_rav); }
	| '+' RED1 expression   
		{ $$ = expression_unary_operator(" +red ", $2,psi_red_plus); }
	| '-' RED1 expression   
		{ $$ = expression_unary_operator(" -red ", $2,psi_red_minus); }
	| '*' RED1 expression  
		 { $$ = expression_unary_operator(" *red ", $2,psi_red_times); }
	| '/' RED1 expression  
		{ $$ = expression_unary_operator(" /red ", $2,psi_red_div); }
	;

%%

yyerror (char *s)
{ 
	printf ("Error line %d:  %s\n", line_num, s);
	return (0);
}

void main()
{
	yyparse();
}
