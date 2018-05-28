%{
#include "psi.h"
#include "dist.h"
#include "op.h"
#include "sys.h"
#include "f90.h"
 
#include "dist.e"
#include "vect.e"
#include "psi.e"
#include "ident.e"
#include "moa_func.e"
#include "sys.e"
#include "sym.e"
#include "part.e"
#include "compat.e"
#include "hpfm_func.e"
 
#define FNAMELEN 20
 
extern FILE *cfile,*infile,*vfile,*tfile;
extern int ntab;
 
vect_t const1_v;
ident_t const1_i;
char line[1024];
char f90line[1024];
int curtempf90;
char f90func [FNAMELEN];
char arch_module [20];
%}

%token IN1 
%token IF1 
%token DO1 
%token GO1 
%token TO1 
%token NO1 
%token REC1 
%token EOR1 
%token OUT1 
%token LEN1 
%token END1 
%token NEW1 
%token ABS1 
%token DIM1 
%token INT1 
%token MAX1 
%token MIN1 
%token MOD1 
%token COS1 
%token EXP1 
%token LOG1 
%token ERR1 
%token FMT1 
%token USE1 
%token PAD1 
%token HPF1 
%token NML1 
%token SIN1 
%token TAN1 
%token LGE1 
%token LGT1 
%token LLE1 
%token LLT1 
%token IOR1 
%token ALL1 
%token SUM1 
%token ANY1 
%token RAV1 
%token IOTA1 
%token IALL1 
%token IEOR1 
%token PACK1 
%token ILEN1 
%token SCAN1 
%token TRIM1 
%token TANH1 
%token SINH1 
%token SQRT1 
%token CHAR1 
%token HUGE1 
%token TINY1 
%token IAND1 
%token UNIT1 
%token FILE1 
%token FORM1 
%token RECL1 
%token SIZE1 
%token ONLY1 
%token CALL1 
%token OPEN1 
%token COSH1 
%token NINT1 
%token SIGN1 
%token ACOS1 
%token ASIN1 
%token ATAN1 
%token WITH1 
%token DBLE1 
%token AINT1 
%token PURE1 
%token ONTO1 
%token TYPE1 
%token TRUE1 
%token KIND1 
%token MASK1 
%token ELSE1 
%token READ1 
%token NONE1 
%token THEN1 
%token EXIT1 
%token REAL1 
%token SAVE1 
%token DATA1 
%token LIST1 
%token STAT1 
%token CASE1 
%token STOP1 
%token WHILE1 
%token PAUSE1 
%token WHERE1 
%token PRINT1 
%token NAMED1 
%token FALSE1 
%token INOUT1 
%token CYCLE1 
%token ALIGN1 
%token CMPLX1 
%token CONJG1 
%token AIMAG1 
%token ANINT1 
%token LOG101 
%token DPROD1 
%token FLOOR1 
%token ATAN21 
%token BLANK1 
%token DELIM1 
%token WRITE1 
%token ENTRY1 
%token BLOCK1 
%token CLOSE1 
%token EXIST1 
%token SCALE1 
%token BTEST1 
%token IBCLR1 
%token IBITS1 
%token RADIX1 
%token RANGE1 
%token ACHAR1 
%token ICHAR1 
%token INDEX1 
%token MERGE1
%token SHAPE1 
%token IBSET1 
%token ISHFT1 
%token COUNT1 
%token LEADZ1 
%token PARITY1 
%token POPCNT1 
%token POPPAR1 
%token MAXVAL1 
%token MINVAL1 
%token ISHFTC1 
%token MVBITS1 
%token MATMUL1 
%token SPREAD1 
%token UBOUND1
%token LBOUND1
%token UNPACK1 
%token CONCAT1 
%token CSHIFT1 
%token MAXLOC1 
%token MINLOC1 
%token IACHAR1 
%token REPEAT1 
%token VERIFY1 
%token DIGITS1 
%token DIRECT1 
%token MODULE1 
%token RESULT1 
%token ACCESS1 
%token NUMBER1 
%token MODULO1 
%token CYCLIC1 
%token FORALL1 
%token ASSIGN1 
%token PUBLIC1 
%token DCOLON1 
%token INTENT1 
%token FORMAT1 
%token IOSTAT1 
%token STATUS1 
%token ACTION1 
%token REWIND1 
%token OPENED1 
%token TARGET1 
%token COMMON1 
%token SELECT1 
%token DOUBLE1 
%token COMPLEX1 
%token POINTER1 
%token INTEGER1 
%token LOGICAL1 
%token DEFAULT1 
%token NULLIFY1 
%token UNKNOWN1 
%token PRIVATE1 
%token INHERIT1 
%token CEILING1 
%token ADVANCE1 
%token INQUIRE1 
%token NEXTREC1 
%token PROGRAM1 
%token ENDFILE1 
%token DYNAMIC1 
%token EPSILON1 
%token ADJUSTL1 
%token ADJUSTR1 
%token SPACING1 
%token NEAREST1 
%token REVERSE1 
%token RESHAPE1 
%token EOSHIFT1 
%token PRODUCT1 
%token GRADE_UP1 
%token TRANSFER1 
%token LEN_TRIM1 
%token EXPONENT1 
%token FRACTION1 
%token BIT_SIZE1 
%token FUNCTION1 
%token CONTAINS1 
%token OPERATOR1 
%token TEMPLATE1 
%token REALLIGN1 
%token EXTERNAL1 
%token SEQUENCE1 
%token IMPLICIT1 
%token OPTIONAL1 
%token LEFTCONS1 
%token CONTINUE1 
%token RIGHTCONS1 
%token PARAMETER1 
%token DIMENSION1 
%token INTRINSIC1 
%token PERCISION1 
%token CHARACTER1 
%token ELSEWHERE1 
%token POISITION1 
%token READWRITE1 
%token EXTRINSIC1 
%token HPF_LOCAL1 
%token PROCEDURE1 
%token BACKSPACE1 
%token FORMATTED1 
%token INTERFACE1 
%token RECURSIVE1 
%token PRECISION1 
%token RRSPACING1 
%token ALLOCATED1 
%token TRANSPOSE1 
%token CAT_PARTS1 
%token SUM_PARTS1 
%token SUM_PREFIX1 
%token SUM_SUFFIX1 
%token ASSOCIATED1 
%token ALL_PREFIX1 
%token ALL_SUFFIX1 
%token ANY_PREFIX1 
%token ANY_SUFFIX1 
%token GRADE_DOWN1 
%token SEQUENTIAL1 
%token UNFORMATED1 
%token ASSIGNMENT1 
%token SUBROUTINE1 
%token PROCESSORS1 
%token DISTRIBUTE1 
%token DEALLOCATE1 
%token EQUIVALENCE1 
%token ALLOCATABLE1 
%token INDEPENDENT1 
%token MAXEXPONENT1 
%token MINEXPONENT1 
%token IALL_PREFIX1
%token IANY_PREFIX1
%token IANY_SUFFIX1
%token SUM_SCATTER1
%token INDEX_PARTS1
%token ALL_SCATTER1 
%token ANY_SCATTER1 
%token COPY_PREFIX1 
%token COPY_SUFFIX1 
%token DOT_PRODUCT1 
%token RANDOM_SEED1 
%token REDISTRIBUTE1 
%token CSHIFT_PARTS1
%token IALL_SCATTER1
%token ICALL_SUFFIX1
%token IANY_SCATTER1
%token SYSTEM_CLOCK1 
%token HPF_TEMPLATE1 
%token COUNT_SUFFIX1 
%token COPY_SCATTER1 
%token COUNT_PREFIX1 
%token SET_EXPONENT1 
%token MAXVAL_PREFIX1 
%token MAXVAL_SUFFIX1 
%token PARITY_PREFIX1 
%token PARITY_SUFFIX1 
%token REVERSE_PARTS1 
%token PRODUCT_PARTS1 
%token COUNT_SCATTER1 
%token DATE_AND_TIME1 
%token RANDOM_NUMBER1 
%token HPF_ALLIGNMENT1 
%token PRODUCT_PREFIX1 
%token PRODUCT_SUFFIX1 
%token PARITY_SCATTER1 
%token IPARITY_PREFIX1 
%token IPARITY_SUFFIX1 
%token MAXVAL_SCATTER1 
%token IPARITY_SCATTER1 
%token TRANSPOSE_PARTS1 
%token PRODUCT_SCATTER1 
%token HPF_DISTRIBUTION1 
%token PROCESSORS_SHAPE1 
%token SELECTED_INT_KIND1 
%token SELECTED_REAL_KIND1 
%token NUMBER_OF_PROCESSORS1 

%token NUMBER1
%token FLOAT1
%token NAME1
%token FNAME1

%right NEQV1 EQV1
%right OR1
%right AND1
%right EQ1 NE1 '>' '<' GE1 LE1
%right DSLASH1
%right '+' '-'
%right '*' '/'
%right POWER1
%right UNARYOP
%right NOT1

%%

/* R201 */
executable_program :
		program_unit
		;

/* R202 incomplete */
program_unit :
		external_subprogram
		;

/* R203 incomplete */
external_subprogram :
		subroutine_subprogram
		;

/* R1219 incomplete */
subroutine_subprogram :
		{ subroutine_subprogram_s1 (); }
		subroutine_stmt
		{ subroutine_subprogram_s2 (); }
		specification_part_opt1
		execution_part_opt1
		{ subroutine_subprogram_s3 (); }
		end_subroutine_stmt
		;

/* R204 incomplete */
specification_part :
		declaration_construct
		;
specification_part_opt1 :
	|	specification_part
		;

/* R207 incomplete */
declaration_construct :
		type_declaration_stmt
/*	|	hpf_directive_line */
		;
/*
declaration_construct_opt :
	|	declaration_construct declaration_construct_opt
		;
*/
		
/* R208 */
execution_part :
		executable_construct
		{ $<stval>$ = execution_part_s1 ($1); }
		execution_part_construct_opt
		;
execution_part_opt1 :
	|	execution_part
		;

/* R209 incomplete */
execution_part_construct :
		executable_construct
		{ execution_part_s1 ($1); }
		;
execution_part_construct_opt :
	|	execution_part_construct execution_part_construct_opt
		;

/* R215 incomplete */
executable_construct :
		action_stmt { $$ = $1; }
	|	do_construct { $$ = NULL; }
	|	if_construct { $$ = NULL; }
		;

/* R216 incomplete */
action_stmt :
		assignment_stmt { $$ = $1; }
	|	if_stmt { $$ = NULL; }
		;

/* R304 */
name :
		NAME1 { $$ = $1; }
		;

/* R305 incomplete */
constant :
		NUMBER1 { constant_s1 ($1); }
	|	FLOAT1  { constant_s2 ($1); }
		;
s_constant :
		'-' NUMBER1 { $$ = s_constant_s1 (TRUE, $2); }
	|	NUMBER1 { $$ = s_constant_s1 (FALSE, $1); }
		;
	
s_expr :
		s_constant { $$ = $1; }
		;
s_expr_opt1 :	{ $$ = NULL; }
	|	s_expr { $$ = $1; }
		;

/* R431 */
array_constructor :
		LEFTCONS1 ac_value_list RIGHTCONS1 
		{ $$ = vect2parser ($2); }
		;

/* R432 incomplete and changed */
ac_value :
		s_expr { $$ = $1; }
		;
ac_value_list :
		ac_value ac_value_list_cont
		{ $$ = vect_cat (s_vect($1), $2); }
		;
ac_value_list_cont : { $$ = NULL; }
	|	',' ac_value ac_value_list_cont
		{ $$ = vect_cat (s_vect($1), $2); } 
		;

/* R501 incomplete */
type_declaration_stmt :
		type_spec attr_spec_cont DCOLON1 entity_decl_list
		;
entity_decl_list :
		entity_decl entity_decl_cont
		;
entity_decl_cont :
	|	',' entity_decl entity_decl_cont
		;

/* R502 incomplete */
type_spec :
		INTEGER1 { $$ = type_spec_s1 (FALSE); }
	|	REAL1 { $$ = type_spec_s1 (TRUE); }
		;

/* R503 */
attr_spec :
		DIMENSION1 '(' array_spec ')'
		;
attr_spec_cont :
	|	',' attr_spec attr_spec_cont
		;

/* R504 */
entity_decl :
		name
		;

/* R512 incomplete */
array_spec :
		explicit_shape_spec_list
		;
explicit_shape_spec_list :
		explicit_shape_spec explicit_shape_spec_cont
		;
explicit_shape_spec_cont :
	|	',' explicit_shape_spec explicit_shape_spec_cont
		;

/* R513 */
explicit_shape_spec :
		lower_bound
	|	lower_bound ':' upper_bound
		;

/* R514 changed */
lower_bound :
		NUMBER1
	|	name
		;

/* R515 changed */
upper_bound :
		NUMBER1
	| 	name
		;

/* R601 incomplete */
variable :
		NAME1
		;
/* R611 */
substring_range :
		s_expr_opt1 ':' s_expr_opt1
		;
substring_range_paren_opt1 :
		'(' substring_range ')'
		;

/* R615,616 */
array_variable :
		NAME1
		substring_range_paren_opt1
		;

/* R617 */
subscript :
		s_expr
		;
subscript_opt1 :
	|	subscript
		;

/* R618 incomplete */
section_subscript :
		subscript
	|	subscript_triplet
		;

/* R619 incomplete */
subscript_triplet :
		subscript_opt1 ':' subscript_opt1
		;

/* added to get subscripting on LHS */
array_result :
		NAME1 substring_range_paren_opt1 
		;

/* R701 incomplete */
primary :
		constant
	|	variable
	|	'(' expr ')'
		;
array_primary :
		array_variable
	|	array_constructor
	|	function_reference
	|	'(' array_expr ')'  substring_range_paren_opt1 
		;

/* R705, R707, R711, R713, R716, R718, R723 combined and split */
expr :
		primary
	|	NOT1 expr
	|	'+' expr %prec UNARYOP
	|	'-' expr %prec UNARYOP
	|	expr POWER1 expr
	|	expr '*' expr
	|	expr '/' expr
	|	expr '+' expr
	|	expr '-' expr
	|	expr DSLASH1 expr
	|	expr EQV1 expr
	|	expr NEQV1 expr
	|	expr AND1 expr
	|	expr OR1 expr
	|	expr EQ1 expr
	|	expr NE1 expr
	|	expr '>' expr
	|	expr '<' expr
	|	expr GE1 expr
	|	expr LE1 expr
		;
array_expr :
		array_primary
	|	NOT1 array_expr
	|	'+' array_expr %prec UNARYOP
	|	'-' array_expr %prec UNARYOP
	|	array_expr POWER1 array_expr
	|	array_expr '*' array_expr
	|	array_expr '/' array_expr
	|	array_expr '+' array_expr
	|	array_expr '-' array_expr
	|	array_expr DSLASH1 array_expr
	|	array_expr EQV1 array_expr
	|	array_expr NEQV1 array_expr
	|	array_expr AND1 array_expr
	|	array_expr OR1 array_expr
	|	array_expr EQ1 array_expr
	|	array_expr NE1 array_expr
	|	array_expr '>' array_expr
	|	array_expr '<' array_expr
	|	array_expr GE1 array_expr
	|	array_expr LE1 array_expr
		;

/* R725 */
logical_expr :
		expr
		;
	
/* R725 */
numeric_expr :
		expr
		;

/* R735 */
assignment_stmt :
		array_result '=' array_expr
		;

/* R801 */
block :
		execution_part_construct_opt
		;

/* R802 */
if_construct :
		if_then_statement
		block
		else_if_statement_block_opt
		else_statement_block_opt1
		end_if_statement
		;
else_if_statement_block_opt :
	|	else_if_statement block else_if_statement_block_opt
		;
else_statement_block_opt1 :
	|	else_statement block
		;

/* R803 */
if_then_statement :
/*
		if_construct_name_colon_opt1
*/
		IF1 '(' logical_expr ')' THEN1
		;
if_construct_name_colon_opt1 :
	|	if_construct_name ':'
		;

/* R804 */
else_if_statement :
		ELSE1 IF1 '(' logical_expr ')' THEN1
/*
		if_construct_name_opt1
*/
		;

/* R805 */
else_statement :
		ELSE1 /* if_construct_name_opt1 */
		;

/* R806 */
end_if_statement :
		END1 IF1 /* if_construct_name_opt1 */
		;

/* R807 */
if_stmt :
		IF1 '(' logical_expr ')' action_stmt
		;

if_construct_name :
		variable
		;
if_construct_name_opt1 :
	|	if_construct_name
		;

/* R816 incomplete */
do_construct :
		block_do_construct
		;

/* R817 */
block_do_construct :
		do_stmt do_block end_do
		;

/* R818 incomplete */
do_stmt :
		nonlabel_do_stmt
		;

/* R820 changed so loop_control is mandatory */
nonlabel_do_stmt :
/*
		do_construct_name_colon_opt1
*/
		DO1 loop_control_opt1
		;
do_construct_name_colon_opt1 :
	|	do_construct_name ':'
		;

/* R821 incomplete */
loop_control :
		loop_control1
	|	loop_control2
		;
loop_control1 :
		comma_opt1
		do_variable '=' numeric_expr ',' numeric_expr
		comma_numeric_expr_opt1
		;
comma_opt1 :
	|	','
		;
comma_numeric_expr_opt1 :
	|	',' numeric_expr
		;
loop_control2 :
		comma_opt1 WHILE1 '(' logical_expr ')'
		;
loop_control_opt1 :
	|	loop_control
		;

/* R822 */
do_variable :
		variable
		;

/* R823 */
do_block :
		block
		;

/* R824 incomplete */
end_do :
		end_do_stmt
		;

/* R825 */
end_do_stmt :
		END1 DO1 /* do_construct_name_opt1 */
		;

do_construct_name :
		variable
		;
do_construct_name_opt1 :
	|	do_construct_name
		;

/* R1209 */
function_reference :
		function_name '(' actual_arg_spec_list_opt1 ')'
		;
actual_arg_spec_list :
		actual_arg_spec actual_arg_spec_cont
		;
actual_arg_spec_cont :
	|	',' actual_arg_spec actual_arg_spec_cont
		;
actual_arg_spec_list_opt1 :
	|	actual_arg_spec_list
		;

/* R1211 changed */
actual_arg_spec :
		name_equal_opt1 actual_arg
		;
name_equal_opt1 :
	|	KIND1 '='
	|	DIM1 '='
		;

/* R1213 incomplete */
actual_arg :
		array_expr
		;

function_name :
		FNAME1
		;

/* R1220 */
/* NOTE: subroutine_name was replaced with name */
subroutine_stmt :
		SUBROUTINE1 name subroutine_args_opt1
	|	RECURSIVE1 SUBROUTINE1 name subroutine_args_opt1
		;

subroutine_args :
		'(' dummy_arg_list_opt1 ')'
		;
subroutine_args_opt1 :
	|	subroutine_args
		;

dummy_arg_list :
		dummy_arg dummy_arg_cont
		;
dummy_arg_cont :
	|	',' dummy_arg dummy_arg_cont
		;
dummy_arg_list_opt1 :
	|	dummy_arg_list
		;

/* R1221 incomplet */
/* NOTE: dummy_arg_name was replaced with name */
dummy_arg :
		name
		;

/* R1222 */
end_subroutine_stmt :
		END1
	|	END1 SUBROUTINE1
		;

%%
 
yyerror (char *s)
{
  printf ("Error line %d:  %s\n", line_num, s);
  return (0);
}
 
void main ()
{
  yyparse ();
}
