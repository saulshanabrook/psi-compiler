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

extern int line_num;
FILE *cfile;
%}
%union {
  unsigned int wval;
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

%left PSI1 TAKE1 DROP1 CAT1 PDROP1 PTAKE1 '+' '-' '*' '/'
%right UNEG IOTA1 DIM1 SHP1 TAU1 RAV1 RED1 

%%

executable_program : /* replaces programx(); */
	{ executable_header(); }
	directives_opt
	{ executable_post_declaration(); }
	procedure_mand
	{ executable_footer(); }
	;

directives_opt:
	| '$' NAME1 {directive_trace($2); }
	| '$' NAME1 NUMBER1 { directive_procs($2,$3);}
	| '$' NAME1 NAME1 {directive_other($2,$3);}
	;

procedure_mand:
				{procedure_header();}
	declaration
	'{' 		
	var_dec_statement
	{ procedure_post_declaration(); }
	statement_base 
	'}' 			
				{ procedure_footer(); } 
	procedure_opt
	;

procedure_opt:
	| procedure_mand
	;

var_dec:
	INT1 NAME1  
	| ARRAY1 NAME1 '^' NUMBER1 '<' vector_const2_base '>'

const_dec: 
	CONST1 ARRAY1 NAME1 '^' NUMBER1 '<' vector_const2_base '>'
	'=' '<'vector_const2_base '>'
	| CONST1 ARRAY1 NAME1 '^' NUMBER1 '<' vector_const2_base '>'
	'=' vector_const2_mand
	;

var_dec_statement:
	| var_dec ';' var_dec_statement
	| var_dec
	| const_dec ';' var_dec_statement
	| const_dec
	;

	
arg_list_opt:
	| var_dec arg_list_cont
	;

arg_list_cont:
	| ',' {dual_fprintf(","); } var_dec arg_list_cont
	;

declaration:
	NAME1 '(' { declaration_name($1);} 
	arg_list_opt 
	')' {  dual_fprintf(")"); } 
	;

statement_base:
	statement_base_opt
	{ collect_garbage(NULL,save_list,NULL) }
	;

statement_base_opt:
	| statement_base_mand statement_base_opt
	;

statement_base_mand:
	assignment
	| for_statement
	| procedure_call
	;

assignment:
	NAME1 '=' expression ';'
	| expression PDROP1 expression '=' expression ';'
	| expression PSI1 expression '=' expression ';'
	;

for_statement:
	FOR1 '(' expression LTE1 expression '<' expression ')' 
	'{'
	statement_base
	'}'
	;

procedure_call:
	NAME1 '(' expression ')' ';'
	;

(* const_vars and const_numbers and curr_const_num are all global
   variables within semantic.c *)

vector_const2_base:
	(* set curr_const_num to 0 after '<' and before call to this *)
	vector_const2_opt
	{ /* put it all into a ident_t */ }
	;

vector_const2_mand:
	NUMBER1		{ $$ = (* function to add to const_numbers *) 1 }
	| NAME1		{ $$ = (* function to add to const_vars *) 1 }
	| '+' NUMBER1	{ $$ = (* function to add to const_numbers *) 1 }
	| '-' NUMBER1	{ $$ = (* function to add to const_numbers *) 1 }
	;

vector_const2_opt: { $$ = 0; }
	| vector_const2_mand vector_const2_opt { $$ = $1 + $2; }
	;

expression:
	NAME1
	| NUMBER1
	| FLOAT1
	| '+' expression %prec UNEG
	| '-' expression %prec UNEG
	| '(' expression ')'
	| expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| '<' vector_const2_base '>' 
	| expression PSI1 expression
	| expression TAKE1 expression
	| expression DROP1 expression
	| expression CAT1 expression
	| expression PDROP1 expression
	| expression PTAKE1 expression
	| IOTA1 expression
	| DIM1 expression
	| SHP1 expression
	| TAU1 expression
	| RAV1 expression
	| '+' RED1 expression
	| '-' RED1 expression
	| '*' RED1 expression
	| '/' RED1 expression
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

