%{
#include "parser.h"
#include "types.h"
#include "semantic.e"
#include "code.e"

extern int line_num;               /* current line number */

word vartype;                      /* TYPEINT or TYPEFLOAT */
word cttos;                        /* compile time top of stack */
word defsize;                      /* size of info for current obj def */
word sti;                          /* global variable to make things easier */
word test_global;                  /* global variable to make things easier */
word jump_global;                  /* global variable to make things easier */
passinfo *global_step;             /* global variable to make things easier */
passinfo *at_global;               /* global variable to make things easier */
char errmsg [80];                  /* used to store error messages */
%}

%union {
  word wval;
  flt fval;
  char *cval;
  passinfo *pval;
}

%token <wval> TRANSLATE1
%token <wval> SCALE1
%token <wval> ROTATE1
%token <wval> COLOR1
%token <wval> QUADRIC1
%token <wval> ENDQUADRIC1
%token <wval> OBJECT1
%token <wval> ENDOBJECT1 
%token <wval> TEXTURE1
%token <wval> ENDTEXTURE1
%token <wval> SPECULAR1
%token <wval> RED1
%token <wval> GREEN1
%token <wval> BLUE1
%token <wval> LOCATION1
%token <wval> DIRECTION1
%token <wval> UP1
%token <wval> RIGHT1
%token <wval> SPHERE1
%token <wval> ENDSPHERE1
%token <wval> PLANE1
%token <wval> ENDPLANE1
%token <wval> TRIANGLE1
%token <wval> ENDTRIANGLE1
%token <wval> VIEWPOINT1
%token <wval> ENDVIEWPOINT1
%token <wval> AMBIENT1
%token <wval> DIFFUSE1
%token <wval> LIGHTSOURCE1
%token <wval> REFLECTION1
%token <wval> REFRACTION1
%token <wval> INCLUDE1
%token <wval> COLORMAP1
%token <wval> ENDCOLORMAP1
%token <wval> DECLARE1
%token <wval> BRILLIANCE1
%token <wval> ALPHA1
%token <wval> PHONG1
%token <wval> PHONGSIZE1
%token <wval> ROUGHNESS1
%token <wval> METALLIC1
%token <wval> IOR1
%token <wval> TURBULENCE1
%token <wval> SKY1
%token <wval> LOOKAT1
%token <wval> FOG1
%token <wval> ENDFOG1
%token <wval> SMOOTHTRIANGLE1
%token <wval> ENDSMOOTHTRIANGLE1
%token <wval> QUARTIC1
%token <wval> ENDQUARTIC1
%token <wval> BOUNDEDBY1
%token <wval> ENDBOUND1
%token <wval> UNION1
%token <wval> ENDUNION1
%token <wval> DIFFERENCE1
%token <wval> ENDDIFFERENCE1
%token <wval> INTERSECTION1
%token <wval> ENDINTERSECTION1
%token <wval> INVERSE1
%token <wval> ENDINVERSE1
%token <wval> BOZO1
%token <wval> WOOD1
%token <wval> MARBLE1
%token <wval> CHECKER1
%token <wval> GRANITE1
%token <wval> SPOTTED1
%token <wval> AGATE1
%token <wval> WAVES1
%token <wval> RIPPLES1
%token <wval> PHASE1
%token <wval> FREQUENCY1
%token <wval> DENTS1
%token <wval> BUMPS1
%token <wval> WRINKLES1
%token <wval> CHECKERTEXTURE1
%token <wval> ENDCHECKERTEXTURE1
%token <wval> TILE21
%token <wval> GRADIENT1
%token <wval> IMAGEMAP1
%token <wval> DUMP1
%token <wval> IFF1
%token <wval> GIF1
%token <wval> ONCE1
%token <wval> ALL1
%token <wval> COMPOSITE1
%token <wval> ENDCOMPOSITE1

%token <wval> SCENEDEF1
%token <wval> ENDSCENEDEF1
%token <wval> STARTTIME1
%token <wval> ENDTIME1
%token <wval> STEPTIME1
%token <wval> HRES1
%token <wval> VRES1
%token <wval> RAYDEPTH1
%token <wval> ASPECTRATIO1
%token <wval> ANTIALIASING1
%token <wval> VERBOSEMODE1
%token <wval> ZDIST1
%token <wval> CAMZOOM1
%token <wval> INTEGER1
%token <wval> REAL1
%token <wval> DO1
%token <wval> WHILE1
%token <wval> IF1
%token <wval> THEN1
%token <wval> ELSE1
%token <wval> END1

%token <wval> SIN1
%token <wval> COS1
%token <wval> TAN1
%token <wval> ASIN1
%token <wval> ACOS1
%token <wval> ATAN1
%token <wval> ABS1

%token <wval> OVECT1
%token <wval> CVECT1

%token <cval> NAME1
%token <wval> NUMBER1
%token <fval> FLOAT1

%left <cval> OR1
%left <cval> AND1
%left <cval> EQU1 NEQ1
%left <cval> '<' LTE1 '>' GTE1
%left <cval> '+' '-'
%left <cval> '*' '/' '%'
%right UNEG
%right <cval> '!'
%right <cval> '^'

%type <wval> executable_program
%type <pval> expression
%type <wval> vector3 
%type <wval> var_decl_base
%type <wval> var_type
%type <wval> var_list
%type <wval> var_list_cont
%type <wval> var_name
%type <wval> assignment_base
%type <wval> assignment_base_opt
%type <wval> assignment_base_mand
%type <wval> statement_base
%type <wval> statement_base_mand
%type <wval> statement_base_opt
%type <wval> while_construct_base_mand
%type <wval> if_construct_base_mand
%type <wval> else_part
%type <wval> object_def_base_mand
%type <wval> object_body_base
%type <wval> what_it_is
%type <wval> sphere_def
%type <wval> plane_def
%type <wval> color_def_base
%type <wval> light_source_def_opt
%type <wval> texture_def_opt
%type <wval> texture_def_base_mand
%type <wval> texture_def_base2
%type <wval> texture_def_base2_mand
%type <wval> texture_def_base2_opt
%type <wval> scene_def
%type <wval> time_scene_opt
%type <wval> time_scene_mand
%type <wval> view_point_def

%%

executable_program :
		{ $<wval>$ = new_program (); }
		var_decl_base 
		assignment_base
		scene_def
		assignment_base
		view_point_def
		statement_base
		{ $$ = end_program ($<wval>1); }
		;

expression :
		NAME1      { $$ = expr_name ($1); }
	|	NUMBER1    { $$ = expr_number ($1); }
	|	FLOAT1     { $$ = expr_float ($1); }
	|	'!' expression { $$ = expr_unop (NOT, $2); }
	|	'+' expression %prec '!' { $$ = expr_unop (ADD, $2); }
	|	'-' expression %prec UNEG { $$ = expr_unop (NEG, $2); }
	|	SIN1 '(' expression ')' { $$ = expr_trig (SIN, $3); }
	|	COS1 '(' expression ')' { $$ = expr_trig (COS, $3); }
	|	TAN1 '(' expression ')' { $$ = expr_trig (TAN, $3); }
	|	ASIN1 '(' expression ')' { $$ = expr_trig (ATAN, $3); }
	|	ACOS1 '(' expression ')' { $$ = expr_trig (ACOS, $3); }
	|	ATAN1 '(' expression ')' { $$ = expr_trig (ATAN, $3); }
	|	'(' expression ')' { $$ = $2; }
	|	expression OR1 expression  { $$ = expr_binop ($1, OR,  $3); }
	|	expression AND1 expression { $$ = expr_binop ($1, AND, $3); }
	|	expression EQU1 expression { $$ = expr_binop ($1, EQ,  $3); }
	|	expression NEQ1 expression { $$ = expr_binop ($1, NEQ, $3); }
	|	expression '<' expression  { $$ = expr_binop ($1, LT,  $3); }
	|	expression LTE1 expression { $$ = expr_binop ($1, LTE, $3); }
	|	expression '>' expression  { $$ = expr_binop ($1, GT,  $3); }
	|	expression GTE1 expression { $$ = expr_binop ($1, GTE, $3); }
	|	expression '+' expression  { $$ = expr_binop ($1, ADD, $3); }
	|	expression '-' expression  { $$ = expr_binop ($1, SUB, $3); }
	|	expression '*' expression  { $$ = expr_binop ($1, MUL, $3); }
	|	expression '/' expression  { $$ = expr_binop ($1, DIV, $3); }
	|	expression '^' expression  { $$ = expr_binop ($1, POW, $3); }
		;

vector3 :
		OVECT1
		expression ','
		expression ','
		expression
		CVECT1
		{ $$ = vector3_s ($2, $4, $6); }
		;

var_decl_base :	{ $$ = 0; }
	|	var_type var_list var_decl_base
		;

var_type :
		INTEGER1 { $$ = vartype = TYPEINT; }
	|	REAL1    { $$ = vartype = TYPEFLOAT; }
		;

var_list :
		var_name var_list_cont
		;

var_list_cont :	{ $$ = 0; }
	|	',' var_name var_list_cont { $$ = $3; }
		;

var_name :
		NAME1 { $$ = var_decl_s ($1, vartype); }
		;

assignment_base :
		assignment_base_opt
		;

assignment_base_opt :	{ $$ = 0; }
	|	assignment_base_mand assignment_base_opt
		;

assignment_base_mand :
		NAME1 '=' expression { $$ = assignment_s ($1, $3); }
		;

statement_base :
		statement_base_mand statement_base_opt
		;

statement_base_mand :
		while_construct_base_mand { $$ = $1; }
	|	if_construct_base_mand    { $$ = $1; }
	|	object_def_base_mand      { $$ = $1; }
	|	assignment_base_mand      { $$ = $1; }
		;

statement_base_opt :	{ $$ = 0; }
	|	statement_base_mand statement_base_opt { $$ = $2; }
		;

while_construct_base_mand :
		WHILE1 { $<wval>$ = get_curr_code (); }
		'(' expression ')' { $<wval>$ = enter_while ($4); } 
		statement_base
		END1 WHILE1 { $$ = exit_while ($<wval>2, $<wval>6); }
		;

if_construct_base_mand :
		IF1 '(' expression ')' THEN1 { $<wval>$ = enter_if ($3); }
		statement_base 
		else_part END1 IF1 { $$ = exit_if ($8); }
		;

else_part :	{ $$ = $<wval>-2; }
	|	ELSE1 { $$ = enter_else ($<wval>-3); } statement_base
		;

object_def_base_mand :
		OBJECT1
		object_body_base
		ENDOBJECT1
		{ $$ = $2; }
		;

object_body_base :
		what_it_is
		light_source_def_opt 
		texture_def_opt
		{ $$ = end_out ($1 + $2, cttos-defsize, defsize); }
		;

what_it_is :
		sphere_def { $$ = SPHRDEF; defsize = SPHRDEFSIZE; }
	|	plane_def  { $$ = PLANEDEF; defsize = PLANEDEFSIZE; }
		;

sphere_def :
		SPHERE1 { $<wval>$ = begin_out (SPHRDEFSIZE); }
		vector3 { $<wval>$ = back_vector ($3, BP, $<wval>2 + CENTER); }
		expression { out_expression ($5, $<wval>2+RADIUS, TYPEFLOAT); }
		transformation_base
		ENDSPHERE1
		{ $$ = SPHRDEF; } 
		;

plane_def :
		PLANE1 { $<wval>$ = begin_out (PLANEDEFSIZE); }
		vector3 { $<wval>$ = back_vector ($3, BP, $<wval>2 + CENTER); }
		vector3 { $<wval>$ = back_vector ($5, BP, $<wval>2 + NORMAL); }
		transformation_base
		ENDPLANE1
		{ $$ = PLANEDEF; }
		;

transformation_base :
		;

color_def_base :
		COLOR1
		RED1 expression
		GREEN1 expression
		BLUE1 expression
		{ $$ = color_def_s ($3, $5, $7); }
		;

light_source_def_opt :  { $$ = 0 }
	|	LIGHTSOURCE1 { $$ = 30; }
		;

texture_def_opt :	{ $$ = 0; }
	|	texture_def_base_mand 
		;

texture_def_base_mand :
		TEXTURE1
		{ sti = begin_out (TEXDEFSIZE); }
		texture_def_base2
		ENDTEXTURE1
		{ $$ = end_out (TEXDEF, sti, TEXDEFSIZE); }
		;

texture_def_base2 :
		texture_def_base2_mand texture_def_base2_opt
		;

texture_def_base2_mand :
		AMBIENT1 expression
		{ out_expression ($2, sti+AMBIENT, TYPEFLOAT); }
	|	DIFFUSE1 expression
		{ out_expression ($2, sti+DIFFUSE, TYPEFLOAT); }
	|	SPECULAR1 expression
		{ out_expression ($2, sti+SPECULAR, TYPEFLOAT); }
	|	color_def_base { $$ = back_vector ($1, BP, sti + COLOR); }
		;

texture_def_base2_opt :	{ $$ = 0; }
	|	texture_def_base2_mand texture_def_base2_opt
		;

scene_def :	SCENEDEF1
		{ $<wval>$ = begin_out (SCENEDEFSIZE); }
		time_scene_opt
		HRES1 expression
		{ out_expression ($5, $<wval>2+HRES, TYPEFLOAT); }
		VRES1 expression
		{ out_expression ($8, $<wval>2+VRES, TYPEFLOAT); }
		RAYDEPTH1 expression
		{ out_expression ($11, $<wval>2+RAYDEPTH, TYPEFLOAT); }
		ASPECTRATIO1 expression
		{ out_expression ($14, $<wval>2+ASPECTRATIO, TYPEFLOAT); }
		ANTIALIASING1 expression
		{ out_expression ($17, $<wval>2+ANTIALIASING, TYPEFLOAT); }
		VERBOSEMODE1 expression
		{ out_expression ($20, $<wval>2+VERBOSEMODE, TYPEFLOAT); }
		ENDSCENEDEF1
		{ $$ = end_out (SCENEDEF, $<wval>2, SCENEDEFSIZE); }
		;

time_scene_opt :	{ $$ = no_time_scene (); }
	|	time_scene_mand { $$ = $1; }
		;

time_scene_mand :
		STARTTIME1 expression
		ENDTIME1 expression
		STEPTIME1 expression
		{ $$ = time_scene_s ($2, $4, $6); }
		;

view_point_def :
		VIEWPOINT1 { $<wval>$ = begin_out (VPTDEFSIZE); }
		LOCATION1 vector3
		{ $<wval>$ = back_vector ($4, BP, $<wval>2 + LOCATION); }
		DIRECTION1 vector3
		{ $<wval>$ = back_vector ($7, BP, $<wval>2 + DIRECTION); }
		UP1 vector3
		{ $<wval>$ = back_vector ($10, BP, $<wval>2 + UP); }
		RIGHT1 vector3
		{ $<wval>$ = back_vector ($13, BP, $<wval>2 + RIGHT); }
		ZDIST1 expression
		{ out_expression ($16, $<wval>2+ZDIST, TYPEFLOAT); }
		CAMZOOM1 expression
		{ out_expression ($19, $<wval>2+CAMZOOM, TYPEFLOAT); }
		ENDVIEWPOINT1
		{ $$ = end_out (VPTDEF, $<wval>2, VPTDEFSIZE); }
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
