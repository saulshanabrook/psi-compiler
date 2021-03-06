#header <<#include "charbuf.h" 
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
>>

<<
vect_t *new_vect()

{
  vect_t *vect;

  vect=get_vect();
  vect->index=&s_const0;
  vect->loc=&s_const0;
	
  return(vect);
}

parser_t *vect2parser(vect_t *v)

{
  parser_t *p;
  expr_t *e;

  v=purify_vect(v);

  e=get_expr_mem(1);
  e->op=NOP;
  if ((v->ident->type==VARIABLE)||(v->ident->type==CONSTANT)) {
    e->dim=&s_const1;
    e->shp=&one_vec;
  } else if ((v->ident->array.dim->type==CONSTANT)&&
      (v->ident->array.dim->value==0.0)) {
    e->dim=&s_const1;
    e->shp=&one_vec;
  } else {
    e->dim=get_s_expr();
    e->dim->op=NOP;
    e->dim->ident=v->ident->array.dim;
    e->shp=new_vect();
    e->shp->shp=&s_const1;
    e->shp->ident=make_ident(v->shp);
  }
  e->ident=v->ident;

  p=(parser_t *) get_mem(sizeof(parser_t));
  p->ident=e->ident;
  p->psi=e;
 
  return(p);
}


vect_t *shp2vect(ident_t *ident)

{
  int i;
  vect_t *vect;

  vect=get_vect();
  vect->shp=get_s_expr();
  vect->shp->ident=ident->array.dim;
  vect->ident=get_ident();
  vect->ident->type=RAV;
  vect->ident->array.dim=&const1;
  vect->ident->array.rav=(s_expr_t **) 
    get_mem(ident->array.dim->value*sizeof(s_expr_t *));
  for (i=0; i<ident->array.dim->value; i++) {
    vect->ident->array.rav[i]=get_s_expr();
    vect->ident->array.rav[i]->ident=ident->array.shp[i];
  }
  vect->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  vect->ident->array.shp[0]=ident->array.dim;
  vect->index=&s_const0;
  vect->loc=&s_const0;

  return(vect);
}


programx() {
  ANTLR(executable_program(),infile)
}

parse_init() {
} >>

#token NOT1 ".NOT."
#token AND1 ".AND."
#token OR1 ".OR."
#token EQV1 ".EQV."
#token NEQV1 ".NEQV."
#token TRUE1 "TRUE"
#token FALSE1 "FALSE"
#token EQ1 ".EQ.|=="
#token NE1 ".NE.|/="
#token LT1 ".LT.|<"
#token LE1 ".LE.|<="
#token GT1 ".GT.|>"
#token GE1 ".GE.|>="
#token LEFTCONS1 "\(/"
#token RIGHTCONS1 "/\)"
#token LEFTPAREN1 "\("
#token RIGHTPAREN1 "\)"
#token POWER1 "\*\*"
#token TIMES1 "\*"
#token DSLASH1 "//"
#token SLASH1 "/"
#token PLUS1 "\+"
#token MINUS1 "\-"
#token EQUAL1 "\="
#token COMMA1 ","
#token DCOLON1 "::"
#token COLON1 ":"
#token PERCENT1 "%"
#token SEMI1 ";"
#token KIND1 "KIND"
#token MASK1 "MASK"
#token LEN1 "LEN"
#token PUBLIC1 "PUBLIC"
#token PERIOD1 "."
#token IN1 "IN"
#token OUT1 "OUT"
#token INOUT1 "INOUT"
#token OPTIONAL1 "OPTIONAL"
#token IMPLICIT1 "IMPLICIT"
#token EQUIVALENCE1 "EQUIVALENCE"
#token NULLIFY1 "NULLIFY"
#token IF1 "IF"
#token ELSE1 "ELSE"
#token DEFAULT1 "DEFAULT"
#token CYCLE1 "CYCLE"
#token ASSIGN1 "ASSIGN"
#token PRIVATE1 "PRIVATE"
#token SEQUENCE1 "SEQUENCE"
#token TYPE1 "TYPE"
#token END1 "END"
#token PARAMETER1 "PARAMETER"
#token ALLOCATABLE1 "ALLOCATABLE"
#token EXTERNAL1 "EXTERNAL"
#token INTENT1 "INTENT"
#token UNKNOWN1 "UNKNOWN"
#token TARGET1 "TARGET"
#token NONE1 "NONE"
#token COMMON1 "COMMON"
#token DEALLOCATE1 "DEALLOCATE"
#token THEN1 "THEN"
#token SELECT1 "SELECT"
#token DO1 "DO"
#token EXIT1 "EXIT"
#token CONTINUE1 "CONTINUE"
#token POINTER1 "POINTER"
#token DIMENSION1 "DIMENSION"
#token INTEGER1 "INTEGER"
#token REAL1 "REAL"
#token DOUBLE1 "DOUBLE"
#token PERCISION1 "PERCISION"
#token COMPLEX1 "COMPLEX"
#token CHARACTER1 "CHARACTER"
#token LOGICAL1 "LOGICAL"
#token INTRINSIC1 "INTRINSIC"
#token SAVE1 "SAVE"
#token DATA1 "DATA"
#token LIST1 "LIST"
#token STAT1 "STAT"
#token WHERE1 "WHERE"
#token ELSEWHERE1 "ELSEWHERE"
#token CASE1 "CASE"
#token WHILE1 "WHILE"
#token GO1 "GO"
#token TO1 "TO"
#token STOP1 "STOP"
#token PAUSE1 "PAUSE"
#token IOSTAT1 "IOSTAT"
#token STATUS1 "STATUS"
#token POISITION1 "POISITION"
#token ACTION1 "ACTION"
#token READ1 "READ"
#token PRINT1 "PRINT"
#token REC1 "REC"
#token EOR1 "EOR"
#token REWIND1 "REWIND"
#token OPENED1 "OPENED"
#token NAMED1 "NAMED"
#token READWRITE1 "READWRITE"
#token FORMAT1 "FORMAT"
#token ONLY1 "ONLY"
#token PROCEDURE1 "PROCEDURE"
#token CALL1 "CALL"
#token FUNCTION1 "FUNCTION"
#token CONTAINS1 "CONTAINS"
#token OPEN1 "OPEN"
#token ERR1 "ERR"
#token ACCESS1 "ACCESS"
#token BLANK1 "BLANK"
#token DELIM1 "DELIM"
#token WRITE1 "WRITE"
#token FMT1 "FMT"
#token ADVANCE1 "ADVANCE"
#token BACKSPACE1 "BACKSPACE"
#token INQUIRE1 "INQUIRE"
#token NUMBER1 "NUMBER"
#token SEQUENTIAL1 "SEQUENTIAL"
#token FORMATTED1 "FORMATTED"
#token NEXTREC1 "NEXTREC"
#token PROGRAM1 "PROGRAM"
#token INTERFACE1 "INTERFACE"
#token OPERATOR1 "OPERATOR"
#token RECURSIVE1 "RECURSIVE"
#token ENTRY1 "ENTRY"
#token UNIT1 "UNIT"
#token FILE1 "FILE"
#token FORM1 "FORM"
#token RECL1 "RECL"
#token PAD1 "PAD"
#token CLOSE1 "CLOSE"
#token NML1 "NML"
#token SIZE1 "SIZE"
#token ENDFILE1 "ENDFILE"
#token EXIST1 "EXIST"
#token DIRECT1 "DIRECT"
#token UNFORMATED1 "UNFORMATED"
#token MODULE1 "MODULE"
#token USE1 "USE"
#token BLOCK1 "BLOCK"
#token ASSIGNMENT1 "ASSIGNMENT"
#token RESULT1 "RESULT"
#token SUBROUTINE1 "SUBROUTINE"
#token DYNAMIC1 "DYNAMIC"
#token HPF1 "HPF"
#token INHERIT1 "INHERIT"
#token ONTO1 "ONTO"
#token REALLIGN1 "REALLIGN"
#token ALIGN1 "ALIGN"
#token EXTRINSIC1 "EXTRINSIC"
#token HPF_LOCAL1 "HPF_LOCAL"
#token NEW1 "NEW"
#token PROCESSORS1 "PROCESSORS"
#token TEMPLATE1 "TEMPLATE"
#token CYCLIC1 "CYCLIC"
#token DISTRIBUTE1 "DISTRIBUTE"
#token FORALL1 "FORALL"
#token INDEPENDENT1 "INDEPENDENT"
#token NO1 "NO"
#token PURE1 "PURE"
#token REDISTRIBUTE1 "REDISTRIBUTE"
#token WITH1 "WITH"
#token ABS1 "ABS"
#token AIMAG1 "AIMAG"
#token AINT1 "AINT"
#token ANINT1 "ANINT"
#token CEILING1 "CEILING"
#token CMPLX1 "CMPLX"
#token CONJG1 "CONJG"
#token DBLE1 "DBLE"
#token DIM1 "DIM"
#token DPROD1 "DPROD"
#token INT1 "INT"
#token FLOOR1 "FLOOR"
#token MAX1 "MAX"
#token MIN1 "MIN"
#token MOD1 "MOD"
#token MODULO1 "MODULO"
#token NINT1 "NINT"
#token SIGN1 "SIGN"
#token ACOS1 "ACOS"
#token ASIN1 "ASIN"
#token ATAN1 "ATAN"
#token ATAN21 "ATAN2"
#token COS1 "COS"
#token COSH1 "COSH"
#token EXP1 "EXP"
#token LOG1 "LOG"
#token LOG101 "LOG10"
#token SIN1 "SIN"
#token SINH1 "SINH"
#token SQRT1 "SQRT"
#token TAN1 "TAN"
#token TANH1 "TANH"
#token ACHAR1 "ACHAR"
#token ADJUSTL1 "ADJUSTL"
#token ADJUSTR1 "ADJUSTR"
#token CHAR1 "CHAR"
#token IACHAR1 "IACHAR"
#token ICHAR1 "ICHAR"
#token INDEX1 "INDEX"
#token LEN_TRIM1 "LEN_TRIM"
#token LGE1 "LGE"
#token LGT1 "LGT"
#token LLE1 "LLE"
#token LLT1 "LLT"
#token REPEAT1 "REPEAT"
#token SCAN1 "SCAN"
#token TRIM1 "TRIM"
#token VERIFY1 "VERIFY"
#token SELECTED_INT_KIND1 "SELECTED_INT_KIND"
#token SELECTED_REAL_KIND1 "SELECTED_REAL_KIND"
#token DIGITS1 "DIGITS"
#token EPSILON1 "EPSILON"
#token HUGE1 "HUGE"
#token MAXEXPONENT1 "MAXEXPONENT"
#token MINEXPONENT1 "MINEXPONENT"
#token PRECISION1 "PRECISION"
#token RADIX1 "RADIX"
#token RANGE1 "RANGE"
#token TINY1 "TINY"
#token EXPONENT1 "EXPONENT"
#token FRACTION1 "FRACTION"
#token NEAREST1 "NEAREST"
#token RRSPACING1 "RRSPACING"
#token SCALE1 "SCALE"
#token SET_EXPONENT1 "SET_EXPONENT"
#token SPACING1 "SPACING"
#token BIT_SIZE1 "BIT_SIZE"
#token BTEST1 "BTEST"
#token IAND1 "IAND"
#token IBCLR1 "IBCLR"
#token IBITS1 "IBITS"
#token IBSET1 "IBSET"
#token IEOR1 "IEOR"
#token IOR1 "IOR"
#token ISHFT1 "ISHFT"
#token ISHFTC1 "ISHFTC"
#token TRANSFER1 "TRANSFER"
#token DOT_PRODUCT1 "DOT_PRODUCT"
#token MATMUL1 "MATMUL"
#token ALL1 "ALL"
#token ANY1 "ANY"
#token COUNT1 "COUNT"
#token MAXVAL1 "MAXVAL"
#token MINVAL1 "MINVAL"
#token PRODUCT1 "PRODUCT"
#token SUM1 "SUM"
#token ALLOCATED1 "ALLOCATED"
#token LBOUND1 "LBOUND"
#token SHAPE1 "SHAPE"
#token UBOUND1 "UBOUND"
#token MERGE1 "MERGE"
#token PACK1 "PACK"
#token SPREAD1 "SPREAD"
#token UNPACK1 "UNPACK"
#token RESHAPE1 "RESHAPE"
#token CONCAT1 "CONCAT"
#token CSHIFT1 "CSHIFT"
#token EOSHIFT1 "EOSHIFT"
#token TRANSPOSE1 "TRANSPOSE"
#token MAXLOC1 "MAXLOC"
#token MINLOC1 "MINLOC"
#token ASSOCIATED1 "ASSOCIATED"
#token DATE_AND_TIME1 "DATE_AND_TIME"
#token SYSTEM_CLOCK1 "SYSTEM_CLOCK"
#token RANDOM_NUMBER1 "RANDOM_NUMBER"
#token RANDOM_SEED1 "RANDOM_SEED"
#token MVBITS1 "MVBITS"
#token ILEN1 "ILEN"
#token NUMBER_OF_PROCESSORS1 "NUMBER_OF_PROCESSORS"
#token PROCESSORS_SHAPE1 "PROCESSORS_SHAPE"
#token ALL_PREFIX1 "ALL_PREFIX"
#token ALL_SCATTER1 "ALL_SCATTER"
#token ALL_SUFFIX1 "ALL_SUFFIX"
#token ANY_PREFIX1 "ANY_PREFIX"
#token ANY_SCATTER1 "ANY_SCATTER"
#token ANY_SUFFIX1 "ANY_SUFFIX"
#token COPY_PREFIX1 "COPY_PREFIX"
#token COPY_SCATTER1 "COPY_SCATTER"
#token COPY_SUFFIX1 "COPY_SUFFIX"
#token COUNT_PREFIX1 "COUNT_PREFIX"
#token COUNT_SCATTER1 "COUNT_SCATTER"
#token COUNT_SUFFIX1 "COUNT_SUFFIX"
#token GRADE_DOWN1 "GRADE_DOWN"
#token GRADE_UP1 "GRADE_UP"
#token HPF_ALLIGNMENT1 "HPF_ALLIGNMENT"
#token HPF_TEMPLATE1 "HPF_TEMPLATE"
#token HPF_DISTRIBUTION1 "HPF_DISTRIBUTION"
#token IALL1 "IALL"
#token IALL_PREFIX1 "IALL_PREFIX"
#token IALL_SCATTER1 "IALL_SCATTER"
#token ICALL_SUFFIX1 "ICALL_SUFFIX"
#token IANY_PREFIX1 "IANY_PREFIX"
#token IANY_SCATTER1 "IANY_SCATTER"
#token IANY_SUFFIX1 "IANY_SUFFIX"
#token IPARITY_PREFIX1 "IPARITY_PREFIX"
#token IPARITY_SCATTER1 "IPARITY_SCATTER"
#token IPARITY_SUFFIX1 "IPARITY_SUFFIX"
#token LEADZ1 "LEADZ"
#token MAXVAL_PREFIX1 "MAXVAL_PREFIX"
#token MAXVAL_SCATTER1 "MAXVAL_SCATTER"
#token MAXVAL_SUFFIX1 "MAXVAL_SUFFIX"
#token PARITY1 "PARITY"
#token PARITY_PREFIX1 "PARITY_PREFIX"
#token PARITY_SCATTER1 "PARITY_SCATTER"
#token PARITY_SUFFIX1 "PARITY_SUFFIX"
#token POPCNT1 "POPCNT"
#token POPPAR1 "POPPAR"
#token PRODUCT_PREFIX1 "PRODUCT_PREFIX"
#token PRODUCT_SCATTER1 "PRODUCT_SCATTER"
#token PRODUCT_SUFFIX1 "PRODUCT_SUFFIX"
#token SUM_PREFIX1 "SUM_PREFIX"
#token SUM_SCATTER1 "SUM_SCATTER"
#token SUM_SUFFIX1 "SUM_SUFFIX"
#token RAV1 "RAV"
#token REVERSE1 "REVERSE"
#token IOTA1 "IOTA"
#token CAT_PARTS1 "CAT_PARTS"
#token REVERSE_PARTS1 "REVERSE_PARTS"
#token TRANSPOSE_PARTS1 "TRANSPOSE_PARTS"
#token INDEX_PARTS1 "INDEX_PARTS"
#token CSHIFT_PARTS1 "CSHIFT_PARTS"
#token PRODUCT_PARTS1 "PRODUCT_PARTS"
#token SUM_PARTS1 "SUM_PARTS"

#token "[\t\ ]" <<zzskip();>>
#token "[!]~[\n]" <<zzskip();>>
#token "[\n]" <<zzskip(); zzline++;>>

#token NUMBER1 "[0-9]+"
#token FLOAT1 "[0-9]+\.[0-9]+"
#token NAME1 "[a-zA-Z][_a-zA-Z0-9]*" <<{int index; search(zzlextext,&index);}>>

/* R201 */
executable_program : {directive_origin processor_directive} (program_unit)+
	;

/* R202 incomplete */
program_unit : external_subprogram
	;

/* R203 incomplete */
external_subprogram : subroutine_subprogram
	;

/* R1219 incomplete */
subroutine_subprogram : 
	<< char buf[1024]; statement_t *body=NULL;
	  line[0]=0;

	  if ((tfile=fopen("temp$$$$.moa","wt"))==NULL) {
	    fatal("Couldn't create temporary file.");
	  }
	  if ((vfile=fopen("vtemp$$$$.moa","wt"))==NULL) {
	    fatal("Couldn't create temporary file.");
	  }

	  if (host) {
	    if ((hfile=fopen("htemp$$$$.moa","wt"))==NULL)
	      fatal("Couldn't create temporary file.");
	  } >>


	subroutine_stmt 

	<< if (host) {
	     fprintf(hostfile,"USE %s\n",arch_module);
	     fprintf(hostfile,"USE MOALIB\n");
	   }
	   if (n_procs>1) fprintf(cfile,"USE %s\n",arch_module);
	   fprintf(cfile,"USE MOALIB\n"); >>

	{specification_part}
	{execution_part > [body]}

	<<declare_utils();
	  fclose(tfile);
	  fclose(vfile);
	  if (host)  fclose(hfile);

	  fprintf(cfile,"\n! MOA\n! Variable declarations\n!\n");
	  if ((vfile=fopen("vtemp$$$$.moa","r"))==NULL) {
	    fatal("Couldn't open temporary file.");
	  }
	  fgets(buf,1024,vfile);
	  while (!feof(vfile)) {
	    fputs(buf,cfile);
	    fgets(buf,1024,vfile);
	  }
	  fclose(vfile);
	  fputs("\n",cfile);

	  if (n_procs>1) fprintf(cfile,"  call NODE_INIT()\n\n");

	  if (host) {
	    fprintf(hostfile,"\n  call HOST_INIT()\n\n");
	  }

	  if (host) {
	    if ((hfile=fopen("htemp$$$$.moa","r"))==NULL) {
	      fatal("Couldn't open temporary file.");
	    }
	    fgets(buf,1024,hfile);
	    while (!feof(hfile)) {
	      fputs(buf,hostfile);
	      fgets(buf,1024,hfile);
	    }
	    fclose(hfile);
	  }

	  if ((tfile=fopen("temp$$$$.moa","r"))==NULL) {
	    fatal("Couldn't open temporary file.");
	  }
	  fgets(buf,1024,tfile);
	  while (!feof(tfile)) {
	    fputs(buf,cfile);
	    fgets(buf,1024,tfile);
	  }
	  fclose(tfile);

	  free_tmp_mem();    /* free any temporary memory used */
	>>
	end_subroutine_stmt
	;

/* R208 */
execution_part > [statement_t *body] :
	<< statement_t *node;

           curtempf90=0;
        >>
	executable_construct > [$body] 
	<< node=$body;
	   if (node != NULL) { 
	     while (node->next != NULL) node=node->next;
	     node->next = NULL;
	     code_c($body,partition($body));
	   }
        >>
	( execution_part_construct > [$body] 
	<< node=$body; 
	   if (node != NULL) { 
	     while (node->next != NULL) node=node->next;
	     node->next = NULL;
	     code_c($body,partition($body));
	   }
        >>
	)*
	<< if (node != NULL) node->next=NULL; >>
	;

/* R209 incomplete */
execution_part_construct > [statement_t *s] :
	executable_construct > [$s]
	;

/* R215 incomplete */
executable_construct > [statement_t *s] :
	action_stmt > [$s] |
	do_construct << $s = NULL; >> |
	if_construct << $s = NULL; >>
	;

/* R216 incomplete */
action_stmt > [statement_t *s] : 
	assignment_stmt > [$s] |
	if_stmt << $s = NULL; >>
	;

/* R431 */
array_constructor > [parser_t *e] :
	<< vect_t *tvect; s_expr_t *acv1; >>
	LEFTCONS1
	s_expr > [acv1]
	<< tvect=s_vect(acv1); >>
	( COMMA1 
	  s_expr > [acv1]
	  << tvect=vect_cat(tvect,s_vect(acv1)); >>
	)*
	<< $e=vect2parser(tvect); >>
	RIGHTCONS1
	;


/* R601 incomplete*/
variable : NAME1 << sprintf(line+strlen(line),"%s ",$1.text); >>
	;

/* merged with R615,R616 */
array_variable > [parser_t *e] : 
	<< vect_t *tk, *dr; int indexed; parser_t *tkp,*drp;>>
	NAME1 
	<<$e=psi_access(find_sym(name_id($1.text),TRUE));
	  $e->psi->ext_str=(char *) get_mem(strlen($1.text));
          sprintf ($e->psi->ext_str,"%s",$1.text); >>
	 { LEFTPAREN1 section_subscript_list[&tk,&dr,&indexed]
	  << tkp=vect2parser(tk);
	     drp=vect2parser(dr);
	     if (indexed) {
	       $e=psi_psi(drp,$e);
	     } else {
	       $e=psi_pdrop(drp,$e);
	       $e=psi_ptake(tkp,$e);
             }
	  >> RIGHTPAREN1 }
	;

/* R617 */
subscript > [vect_t *e] : 
	<< parser_t *p; >>
	array_expr > [p]
	<< $e=make_vect(p->psi); >>
	;

/* R619&R618 merged - incomplete */
section_subscript[vect_t **tk, vect_t **dr, int *indexed] :
	<< *indexed=TRUE; >>
	subscript > [*dr] << *tk=*dr; *dr=vect_op(MINUS,*dr,&one_vec); >>
	{ COLON1 subscript > [*tk] << *indexed=FALSE; >>}
	;

section_subscript_list[vect_t **tk, vect_t **dr, int *indexed] :
	<< vect_t *tk1, *dr1; >>
	section_subscript[tk,dr,indexed] 
	( COMMA1 section_subscript[&tk1,&dr1,indexed] 
	 << *tk=vect_cat(*tk,tk1); *dr=vect_cat(*dr,dr1); >> )*
	<< *tk=vect_op(MINUS,*tk,*dr); >>
	;


/* added this to get sections on LHS */
array_result > [parser_t *e] : << vect_t *tk,*dr; int psi; >>
	NAME1 
	<< $e=psi_access(find_sym(name_id($1.text),TRUE));
	   $e->psi->ext_str=(char *) get_mem(strlen($1.text));
           sprintf ($e->psi->ext_str,"%s",$1.text);
	   $e->psi->loc=NULL; >>
	{ LEFTPAREN1 
	  section_subscript_list[&tk,&dr,&psi] << $e->psi->loc=dr; >> 
	  RIGHTPAREN1 }
	;

/* R701 incomplete */
primary : constant | variable | 
	LEFTPAREN1 << sprintf(line+strlen(line),"("); >>
	expr
	RIGHTPAREN1 << sprintf(line+strlen(line),")"); >>
	;

array_primary > [parser_t *e] : 
	<< vect_t *tk, *dr; int indexed; parser_t *tkp,*drp; char *f90str; >>
	array_variable > [$e]
	| array_constant > [$e]
        | function_reference > [$e]
	| array_constructor > [$e]
	| LEFTPAREN1 array_expr > [$e] RIGHTPAREN1
	  << if ($e->psi->op==EXT_OP) {
	       f90str=(char *) get_mem (strlen ($e->psi->ext_str)+2);
	       sprintf (f90str,"(%s)",$e->psi->ext_str);
	       free($e->psi->ext_str);
	       $e->psi->ext_str=f90str; } >>
	 { LEFTPAREN1 section_subscript_list[&tk,&dr,&indexed]
	  << tkp=vect2parser(tk);
	     drp=vect2parser(dr);
	     if (indexed) {
	       $e=psi_psi(drp,$e);
	     } else {
	       $e=psi_pdrop(drp,$e);
	       $e=psi_ptake(tkp,$e);
             }
	  >> RIGHTPAREN1 }
	;

/* R703 */
level_1_expr : {defined_unary_op } primary
	;

array_level_1_expr > [parser_t *e] :
	<< parser_t *arg1; psiop_t func;
	   char fname [FNAMELEN]; >>
        << func.func=NULL; >>
	{ array_defined_unary_op > [func]
	  << strcpy (fname,f90func); >> }
	array_primary > [arg1]
	<< if (func.func!=NULL) {
	     arg1=make_compatable (arg1, func);
	     strcpy (f90func,fname); 
             $e=(func.func)(arg1);
	   } else $e=arg1; >>
	;

/* R704 */
defined_unary_op : PERIOD1 NAME1 PERIOD1
	<< sprintf(line+strlen(line),".%s. ",$2.text); >>
	;

array_defined_unary_op > [psiop_t func] : PERIOD1 NAME1 PERIOD1
	<< sprintf (f90func, ".%s.", $2.text);
           $func.func=unon_psi; >>
	;

/* R705 */
mult_operand : level_1_expr (power_op level_1_expr)*
	;

array_mult_operand > [parser_t *e] : 
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_level_1_expr > [arg1]
	( array_power_op > [func] 
	  << strcpy (fname,f90func); >>
	  array_level_1_expr > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R706 */
add_operand : mult_operand (mult_op mult_operand)*
	;

array_add_operand > [parser_t *e] : 
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_mult_operand > [arg1]
	 (array_mult_op > [func]
	  << strcpy (fname,f90func); >>
	  array_mult_operand > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
             arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R707 incomplete */
level_2_expr : {add_op} add_operand (add_op add_operand)*
	;

array_level_2_expr > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_add_operand > [arg1]
	( array_add_op > [func]
	  << strcpy (fname,f90func); >>
	  array_add_operand > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R708 */
power_op : POWER1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_power_op > [psiop_t func] : POWER1
	<< sprintf (f90func, "%s", $1); 
	   $func.func=non_psi; >>
	;

/* R709 */
mult_op : TIMES1 | SLASH1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_mult_op > [psiop_t func] : TIMES1 << $func.func=psi_times; >>
	| SLASH1 << $func.func=psi_div; >>
	;

/* R710 */
add_op :  PLUS1 | MINUS1 
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_add_op > [psiop_t func] : PLUS1 << $func.func=psi_plus; >>
	| MINUS1 << $func.func=psi_minus; >>
	;

/* R711 */
level_3_expr : level_2_expr (concat_op level_2_expr)*
	;

array_level_3_expr > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_level_2_expr > [arg1] 
	( array_concat_op > [func]
	  << strcpy (fname,f90func); >>
	  array_level_2_expr > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R712 */
concat_op : DSLASH1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_concat_op > [psiop_t func] : DSLASH1
	<< sprintf (f90func, "//");
	   $func.func=non_psi; >>
	;

/* R713 */
level_4_expr : level_3_expr (rel_op level_3_expr)*
	;

array_level_4_expr > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_level_3_expr > [arg1]
	( array_rel_op > [func]
	  << strcpy (fname,f90func); >>
	  array_level_3_expr > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R714 */
rel_op : EQ1 | NE1 | LT1 | GT1 | GE1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_rel_op > [psiop_t func] : EQ1 | NE1 | LT1 | GT1 | GE1
	<< sprintf (f90func,"%s", $1.text);
	   $func.func=non_psi; >>
	;

/* R715 */
and_operand : {not_op} level_4_expr
	;

array_and_operand > [parser_t *e] :
	<< parser_t *arg1; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_level_4_expr > [$e] |
	array_not_op > [func]
	<< strcpy (fname,f90func); >>
	array_level_4_expr > [arg1]
	<< arg1=make_compatable (arg1,func);
	   strcpy (f90func,fname); 
	   $e=(func.func)(arg1);>>
	;

/* R716 */
or_operand : and_operand (and_op and_operand)*
	;

array_or_operand > [parser_t *e] : 
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_and_operand > [arg1] 
	( array_and_op > [func]
	  << strcpy (fname,f90func); >>
	  array_and_operand > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R717 */
equiv_operand : or_operand (or_op or_operand)*
	;
	
array_equiv_operand > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_or_operand > [arg1] 
	( array_or_op > [func]
	  << strcpy (fname,f90func); >>
	  array_or_operand > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;
	
/* R718 */
level_5_expr : equiv_operand (equiv_op equiv_operand)*
	;

array_level_5_expr > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_equiv_operand > [arg1]
	( array_equiv_op > [func]
	  << strcpy (fname,f90func); >>
	  array_equiv_operand > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R719 */
not_op : NOT1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_not_op > [psiop_t func] : NOT1
	<< sprintf (f90func,"%s",$1.text);
	   $func.func=unon_psi; >>
	;

/* R720 */
and_op : AND1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_and_op > [psiop_t func] : AND1
	<< sprintf (f90func,"%s",$1.text);
	   $func.func=non_psi; >>
	;

/* R721 */
or_op : OR1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_or_op > [psiop_t func] : OR1
	<< sprintf (f90func,"%s",$1.text);
	   $func.func=non_psi; >>
	;

/* R722 */
equiv_op : EQV1 | NEQV1
	<< sprintf(line+strlen(line),"%s",$1.text); >>
	;

array_equiv_op > [psiop_t func] : EQV1 | NEQV1
	<< sprintf (f90func,"%s",$1.text);
	   $func.func=non_psi; >>
	;

/* R723 */
expr: level_5_expr (defined_binary_op level_5_expr)*
	;

array_expr > [parser_t *e] :
	<< parser_t *arg1,*arg2; psiop_t func;
	   char fname [FNAMELEN]; >>
	array_level_5_expr > [arg1]
	( array_defined_binary_op > [func]
	  << strcpy (fname,f90func); >>
	  array_level_5_expr > [arg2]
	  << arg1=make_compatable (arg1,func);
             arg2=make_compatable (arg2,func);
	     strcpy (f90func,fname); 
	     arg1=(func.func)(arg1,arg2);>> )*
	<<$e=arg1;>>
	;

/* R724 */
defined_binary_op : PERIOD1 NAME1 PERIOD1
	<< sprintf(line+strlen(line),".%s. ",$1.text); >>
	;

/* R725 */
logical_expr : expr
	;

array_logical_expr > [parser_t *e] : array_expr > [$e]
	;

/* R729 */
numeric_expr : expr 
	;

array_numeric_expr [parser_t *e] : array_expr > [$e]
	;

array_defined_binary_op > [psiop_t func] : PERIOD1 NAME1 PERIOD1
	<< sprintf (f90func,".%s.",$2.text);
	   $func.func=non_psi; >>
	;

/* R735 */
assignment_stmt > [statement_t *s] :
        <<parser_t *result,*e; statement_t *assign;>>
        << reduction_init(); assign=get_statement(ASSIGN);>>
        array_result > [result] EQUAL1 array_expr > [e]
        << assign->str="array assignment";
           result->psi->bound=e->psi->shp;
           assign->d.assign->expr=e->psi;
           assign->d.assign->result=result->psi;
           psi_reduce(assign,TRUE);
           $s=assign; >>
        ;

/* R801 */
block :
	<< statement_t *body=NULL; >>
	( execution_part_construct > [body]
	<< if (body != NULL) { 
	     body->next = NULL;
	     code_c(body,partition(body));
	   }
        >>
	)+
	;

/* R802 */
if_construct :
	if_then_statement
	<< dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; ntab++; >>
	block
	( else_if_statement 
	  << dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; >>
	  block )+
	{ else_statement
	  << dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; >>
	  block }
	end_if_statement
	<< ntab--; dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; >>
	;

/* R803 */
if_then_statement :
	{ if_construct_name COLON1 
	  << sprintf(line+strlen(line)," : "); >> }
	IF1 LEFTPAREN1 
	<< sprintf(line+strlen(line),"IF ("); >>
	logical_expr RIGHTPAREN1 THEN1 
	<< sprintf(line+strlen(line),") THEN"); >>
	;

/* R804 */
else_if_statement :
	ELSE1 IF1 LEFTPAREN1
	<< sprintf(line+strlen(line),"ELSE IF ("); >>
	logical_expr
	RIGHTPAREN1 THEN1 
	<< sprintf(line+strlen(line),") THEN "); >>
	{ if_construct_name }
	; 

/* R805 */
else_statement :
	ELSE1
	<< sprintf(line+strlen(line),"ELSE "); >>
	{ if_construct_name }
	;

/* R806 */
end_if_statement :
	END1 IF1
	<< sprintf(line+strlen(line),"END IF "); >>
	{ if_construct_name }
	;

/* R807 */
if_stmt :
	<< statement_t *body=NULL; >>
	IF1 LEFTPAREN1
	<< sprintf(line+strlen(line),"IF ("); >>
	logical_expr
	RIGHTPAREN1
	<< sprintf(line+strlen(line),")"); >>
	action_stmt > [body]
	<< if (body != NULL) { 
	     body->next = NULL;
	     code_c(body,partition(body));
	   }
        >>
	;

if_construct_name :
	variable
	;

/* R816 incomplete */
do_construct :
	block_do_construct
	;

/* R817 */
block_do_construct :
	do_stmt
	<< dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; ntab++; >>
	do_block
	end_do
	<< ntab--; dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; >>
	;

/* R818 incomplete */
do_stmt :
	nonlabel_do_stmt
	;

/* R820 changed so loop_control is mandatory to remove ambiguity */
nonlabel_do_stmt :
	{ do_construct_name COLON1
	<< sprintf (line + strlen(line), " : "); >> }
	DO1 
	<< sprintf (line+strlen(line),"DO "); >>
	loop_control 
	;

/* R821 incomplete */
loop_control :
	( { COMMA1 
	    << sprintf (line+strlen(line), ", "); >> }
	  do_variable EQUAL1
	  << sprintf (line+strlen(line), "= "); >> 
	  numeric_expr
	  COMMA1
	  << sprintf (line+strlen(line), ", "); >> 
	  numeric_expr
	  { COMMA1
	    << sprintf (line+strlen(line), ", "); >>
	    numeric_expr } ) |
	( { COMMA1 
	    << sprintf (line+strlen(line), ", "); >> }
	  WHILE1 LEFTPAREN1
	  << sprintf (line+strlen(line), "WHILE ( "); >>
	  logical_expr RIGHTPAREN1
	  << sprintf (line+strlen(line), ")"); >> )
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
	END1 DO1
	<< sprintf(line+strlen(line), "END DO "); >>
	{ do_construct_name }
	;

do_construct_name :
	variable
	;

/* R1209 */
function_reference > [parser_t *e] :
	<<parser_t *arg1,*arg2; 
	  expr_t *arg_expr, *temp;
	  psiop_t func;
          char msg[60], fname[FNAMELEN];
/* na = minimum number of arguments allowed to function, xa = maximum
   ca = current argument */
	  int na, xa, ca=0;>>
        function_name > [func,na,xa]
	<< arg1=NULL;
	   strcpy (fname,f90func); >>
	{ LEFTPAREN1 
	{ actual_arg_spec [func] > [arg1]
	  << ca++;
	     arg1=make_compatable (arg1,func);
	     arg_expr=get_expr_mem (1);
	     arg_expr->left=arg1->psi;
	     arg_expr->right=NULL;
             arg_expr->op=EXT_OP;
	     arg_expr->ext_op=FUNC;
	     arg_expr->ident=arg1->ident;
	     arg1->psi=arg_expr;
             temp=arg1->psi; >>
	  ( COMMA1 actual_arg_spec [func] > [arg2] 
            << ca++;
	       arg2=make_compatable (arg2,func);
	       temp->right=get_expr_mem (1);
               temp=temp->right;
	       temp->left=arg2->psi;
	       temp->right=NULL;
               temp->op=EXT_OP;
	       temp->ext_op=SPLIT;
	       temp->ident=arg2->ident; >>
	  )* }
	RIGHTPAREN1 }
	<< if (xa&&(ca>xa)) {
	     sprintf (msg,"too many args to %s.  additional args disregarded.",
	       fname);
             error (msg);
           }
	   if (na&&(ca<na)) {
	     sprintf (msg,"too few args to %s",fname);
             error (msg);
           }
	   strcpy (f90func,fname);
	   $e=(func.func)(arg1); >>
	;

/* R1211 changed */
actual_arg_spec [psiop_t func] > [parser_t *e] :
	<< int dummy_assign=0; char *f90str; >>
	{ NAME1 EQUAL1 << dummy_assign = 1; >> }
	actual_arg > [$e]
	<< $e=make_compatable ($e,$func); 
	   if (dummy_assign) {
	     f90str=(char *) get_mem (strlen($e->psi->ext_str)+
	       strlen($1.text)+3);
	     sprintf(f90str,"%s = %s",$1.text,$e->psi->ext_str);
	     free($e->psi->ext_str);
	     $e->psi->ext_str=f90str;
	   } >>
	;

/* R1213 incomplete */
actual_arg > [parser_t *e] :
	array_expr > [$e] 
	;
      
function_name > [psiop_t func, int na, int xa] :
	function_name1 > [$func, $na, $xa] |
	function_name2 > [$func, $na, $xa]
	;

function_name1 > [psiop_t func, int na, int xa] :
	( CONCAT1 << $func.func=hpfm_concat; $na=2; $xa=3; >> |
	CSHIFT1 << $func.func=hpfm_cshift; $na=2; $xa=3; >> |
	DOT_PRODUCT1 << $func.func=hpfm_dot_product; $na=2; $xa=2; >> |
	EOSHIFT1 << $func.func=hpfm_eoshift; $na=2; $xa=4; >> |
	MATMUL1 << $func.func=hpfm_matmul; $na=2; $xa=2; >> |
	PRODUCT1 << $func.func=hpfm_product; $na=1; $xa=2; >> |
	SHAPE1 << $func.func=hpfm_shape; $na=1; $xa=1; >> |
	SUM1 << $func.func=hpfm_sum; $na=1; $xa=2; >> |
	TRANSPOSE1 << $func.func=hpfm_transpose; $na=1; $xa=2; >> )
	<< sprintf (f90func,"%s",$2.text); >>
	;

function_name2 > [psiop_t func, int na, int xa] :
	<< $func.func=unon2_psi; >> 
	( ABS1 | AIMAG1 | AINT1 | ANINT1 | CEILING1 | CMPLX1 |
	CONJG1 | DBLE1 | DIM1 | DPROD1 | INT1 | FLOOR1 |
	MAX1 | MIN1 | MOD1 | MODULO1 | NINT1 | SIGN1 | ACOS1 |
	ASIN1 | ATAN1 | ATAN21 | COS1 | COSH1 | EXP1 | LOG1 |
	LOG101 | SIN1 | SINH1 | SQRT1 | TAN1 | TANH1 | ACHAR1 |
	ADJUSTL1 | ADJUSTR1 | CHAR1 | IACHAR1 | ICHAR1 | INDEX1 |
	LEN_TRIM1 | LGE1 | LGT1 | LLE1 | LLT1 | REPEAT1 | SCAN1 |
	TRIM1 | VERIFY1 | SELECTED_INT_KIND1 | SELECTED_REAL_KIND1 |
	DIGITS1 | EPSILON1 | HUGE1 | MAXEXPONENT1 | MINEXPONENT1 |
	PRECISION1 | RADIX1 | RANGE1 | TINY1 | EXPONENT1 | FRACTION1 |
	NEAREST1 | RRSPACING1 | SCALE1 | SET_EXPONENT1 | SPACING1 |
	BIT_SIZE1 | BTEST1 | IAND1 | IBCLR1 | IBITS1 | IBSET1 |
	IEOR1 | IOR1 | ISHFT1 | ISHFTC1 | TRANSFER1 | ALL1 | ANY1 |
	COUNT1 | MAXVAL1 | MINVAL1 | ALLOCATED1 | LBOUND1 | UBOUND1 |
	MERGE1 | PACK1 | SPREAD1 | UNPACK1 | RESHAPE1 | MAXLOC1 |
	MINLOC1 | ASSOCIATED1 | DATE_AND_TIME1 | SYSTEM_CLOCK1 |
	RANDOM_NUMBER1 | RANDOM_SEED1 | MVBITS1 )
	<< $na=0; $xa=0;
	   sprintf (f90func,"%s",$2.text); >>
	;

/* R1220 */
/* NOTE subroutine_name was replaced with name */
subroutine_stmt : << int index; >>
	{RECURSIVE1 
	 <<sprintf(line+strlen(line),"RECURSIVE ");
	   if (host) fprintf(hostfile,"RECURSIVE"); >> }
	SUBROUTINE1 
	 <<sprintf(line+strlen(line),"SUBROUTINE ");
	   if (host) fprintf(hostfile,"SUBROUTINE "); >>
	name > [index]
	 << if (host) fprintf(hostfile,id_text(index)); >>
	{subroutine_args}
	<< fprintf(cfile,line); line[0]=0; >>
	;

subroutine_args : LEFTPAREN1 
	<<sprintf(line+strlen(line),"( ");
	  if (host) fprintf(hostfile,"( "); >>
	{dummy_arg_list}
	RIGHTPAREN1 
	<<sprintf(line+strlen(line),")\n"); if (host) fprintf(hostfile,")\n"); >>
	;

dummy_arg_list : dummy_arg 
	(COMMA1
	 <<sprintf(line+strlen(line),", "); if (host) fprintf(hostfile,", "); >>
	 dummy_arg)*
	;

/* R1221 incomplete */
/* NOTE dummy_arg_name was replaced with name */
dummy_arg : << int index; ident_t *ident;>>
	name > [index] 
	<< ident=get_ident();
	   SETPARAMETER(ident->flags);
	   insert_sym(ident,index);
	   if (host) fprintf(hostfile,id_text(index)); 
	>>
	;

/* R1222 */
end_subroutine_stmt : 
	<< int index; >>
	END1 <<sprintf(line+strlen(line),"END "); if (host) fprintf(hostfile,"END\n"); >>
	{SUBROUTINE1 <<sprintf(line+strlen(line),"SUBROUTINE ");>>
	{name > [index] } }
	<<sprintf(line+strlen(line),"\n");
	  fprintf(cfile,line);
	  line[0]=0; >>
	;


/* R204 incomplete */
specification_part : (declaration_construct)+
	;

/* R207 incomplete */
declaration_construct : type_declaration_stmt | hpf_directive_line
	;

/* R501 incomplete */
type_declaration_stmt : 
	<< ident_t *new=get_ident();
	   int display;
	    new->type=VARIABLE; >>
	type_spec[new]
	{ ( COMMA1 <<sprintf(line+strlen(line),", ");>>
	    attr_spec[new])* 
	  DCOLON1 <<sprintf(line+strlen(line)," :: ");>>
	}
	entity_decl_list[new] 
	<<sprintf(line+strlen(line),"\n");
	  if (new->type!=ARRAY) fprintf(cfile,line);
	  line[0]=0;
	>>
	;

entity_decl_list [ident_t *ident] : 
	entity_decl[ident] 
	(COMMA1 <<sprintf(line+strlen(line),",");>> entity_decl[ident])*
	;

/* R502 incomplete */
type_spec [ident_t *ident] : INTEGER1 
	<<$ident->real=FALSE; sprintf(line+strlen(line),"  INTEGER");>> |
	REAL1 
	<<$ident->real=TRUE; sprintf(line+strlen(line),"  REAL");>>
	;

/* R503 incomplete */
attr_spec [ident_t *ident] : <<$ident->type=ARRAY;>> DIMENSION1 LEFTPAREN1 
	<<sprintf(line+strlen(line),"DIMENSION(");>>
	array_spec[ident]
	RIGHTPAREN1
	<<sprintf(line+strlen(line),")");>>
	;

/* R504 incomplete */
entity_decl [ident_t *ident] : <<int index; ident_t *new;>>
	name > [index] 
	<< new=find_sym(index,FALSE);
	   if ((new!=NULL)&&ISPARAMETER(new->flags)) {
	     *new=*ident;
	     new->index=index; 
	     SETPARAMETER(new->flags);
	   } else {
	     new=get_ident();
	     *new=*ident; 
	     new->index=index; 
	     insert_sym(new,index);
           }
	   strcpy(new->string,id_text(index)); >>
	;

/* R512 incomplete */
array_spec [ident_t *ident] : explicit_shape_spec_list[ident]
	;

explicit_shape_spec_list [ident_t *ident] : 
	<< ident->array.dim=get_ident();
	   ident->array.dim->type=CONSTANT;
	   ident->array.dim->real=FALSE;
	   ident->array.dim->value=0; >>
	explicit_shape_spec[ident] 
	( COMMA1 <<sprintf(line+strlen(line),",");>> explicit_shape_spec[ident] )*
	;

/* R513 incomplete */
explicit_shape_spec [ident_t *ident] : 
	<< ident_t **shp;
	   ident->array.dim->value++;
	   shp=(ident_t **) get_mem(ident->array.dim->value*sizeof(ident_t *));
	   memcpy(shp,ident->array.shp,
	          (ident->array.dim->value-1)*sizeof(ident_t *));
	   free(ident->array.shp);
	   ident->array.shp=shp; >>
	lower_bound > [shp[(int) ident->array.dim->value-1]]
	{ COLON1 <<sprintf(line+strlen(line),":");>>
	  upper_bound [shp[(int) ident->array.dim->value-1]] }
	;

/* R514 changed */
lower_bound > [ident_t *ident] :
	<< int index; >>
	NUMBER1 
	<< sprintf(line+strlen(line),"%d",atoi($1.text));
	   $ident=get_ident();
	   $ident->type=CONSTANT;
	   $ident->real=FALSE;
	   $ident->value=atoi($1.text); >>
	| name > [index] << $ident=find_sym(index,TRUE); >>
	;

/* R515 changed */
upper_bound [ident_t *ident] : 
	<< int index; >>
	NUMBER1 <<sprintf(line+strlen(line),"%d",atoi($1.text));
	          $ident->value=atoi($1.text)-$ident->value+1; >>  | 
	name > [index]
	;

/* R304 */
name > [int index] : NAME1 
	<< $index=name_id($1.text); sprintf(line+strlen(line),"%s ",$1.text);>>
	;

quiet_variable > [int index] : NAME1 
	<< $index=name_id($1.text); >>
	;

/* R305 incomplete */
constant :
	NUMBER1 << sprintf(line+strlen(line),"%d",atoi($1.text)); >> |
	FLOAT1 << sprintf(line+strlen(line),"%f",atof($1.text)); >>
	;

s_constant > [s_expr_t *s] : << int neg=FALSE; >>
	{ MINUS1 <<neg=TRUE;>> } NUMBER1 
	<< $s=get_s_expr();
	   $s->ident=get_ident();
	   $s->ident->real=FALSE;
	   $s->ident->type=CONSTANT;
	   $s->ident->value=atoi($2.text);
	   if (neg) $s->ident->value*=-1.0;
	>>
	;

array_constant > [parser_t *e] : 
	<< ident_t *ident; vect_t *v;
	   char temp[40];
	   ident=get_ident(); >>
	( NUMBER1
	  << ident->array.cnst=(double *) get_mem(sizeof(double));
	     ident->array.cnst[0]=atoi($1.text);
	     sprintf (temp, "%s", $1.text); >> |
	  FLOAT1 
	  << ident->array.cnst=(double *) get_mem(sizeof(double));
	     ident->array.cnst[0]=atof($1.text);
	     sprintf (temp, "%s", $1.text); >> 
	)
	<< ident->type=CONST_ARRAY;
	   ident->array.dim=&const1;
	   ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	   ident->array.shp[0]=&const1;
	   $e=psi_access(ident);
	   $e->psi->ext_str=(char *) get_mem(strlen(temp));
           sprintf ($e->psi->ext_str,"%s",temp);
	>>
	;

/* this should actually be the normal expr rule */
s_expr > [s_expr_t *s] : s_constant > [$s]
	;
	   
/* H201 */
hpf_directive_line : directive_origin hpf_directive
	;

/* H202 */
directive_origin : "!HPF$"
	;

/* H203 incomplete */
hpf_directive : specification_directive
	;

/* H204 incomplete */
specification_directive : processor_directive | distribute_directive
	;

/* H303 */
distribute_directive : << ident_t *t; >>
	DISTRIBUTE1 distributee > [t] dist_directive_stuff[t]
	;

/* H305 */
dist_directive_stuff[ident_t *t] : 
	<< int global;
	   t->array.rule=get_rule(); 
	   t->array.rule->ident=t;
	   t->array.rule->shp=shp2vect(t);
	   t->array.rule->part=NULL;
	   t->array.rule->proc=NULL;
	>>
	dist_format_clause[&global, t->array.rule]
	{ dist_onto_clause > [t->array.rule->proc]
/*
	  << for (i = 0,p = 0; i<t->array.rule->shp->shp->ident->value; i++) {
	       if (t->array.rule->part
*/
	       
	<< if (global) {
	     t->array.rule=NULL;
	     SETGLOBAL(t->flags);
           }
 	>>
	;

/* H307 incomplete */
distributee > [ident_t *t] : << int index; >>
	quiet_variable > [index]
	<< $t=find_sym(index,TRUE); >>
	;

/* H308 incomplete */
dist_format_clause[int *global, rule_t *r] : 
	<< vect_t *v; int cnt;
	   *global=TRUE;
	   r->type=BLOCK; 
	   v=new_vect();
	   v->ident=get_ident();
	   v->ident->type=RAV;
	   v->ident->array.dim=&const1;
	   v->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	   v->ident->array.shp[0]=&const1;
	   v->ident->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
	   cnt=0;
	   v->ident->array.rav[0]=-1; /* red_rav(r->shp,cnt); */
	   r->part=v;
	   >>
	LEFTPAREN1 dist_format[global,r,r->part] (COMMA1
	<< v=new_vect();
	   v->ident=get_ident();
	   v->ident->type=RAV;
	   v->ident->array.dim=&const1;
	   v->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	   v->ident->array.shp[0]=&const1;
	   v->ident->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
	   cnt++;
	   v->ident->array.rav[0]=-1; /* red_rav(r->shp,cnt); */
	   >>
	 dist_format[global,r,v] << r->part=vect_cat(r->part,v); >> )* 
	RIGHTPAREN1
	;

/* H309 */
dist_format[int *global, rule_t *r, vect_t *v] : 
	BLOCK1
	 { LEFTPAREN1 s_expr > [v->ident->array.rav[0]] RIGHTPAREN1 }
	 << *global=FALSE; >>
	| CYCLIC1 { LEFTPAREN1 s_expr > [v->ident->array.rav[0]] RIGHTPAREN1 } 
	  << r->type=CYCLIC; *global=FALSE; >>
	/* changed the meaning of star.  CHANGE BACK LATER */
	| TIMES1  << r->type=DEFAULT_RULE; *global=FALSE; >>
	;

/* H310 */
dist_onto_clause > [vect_t *v] : ONTO1 dist_target > [$v]
	;

/* H311 incomplete */
dist_target > [vect_t *v] : << int index; ident_t *p;>>
	quiet_variable > [index]
	<< p=find_sym(index,TRUE); 
	   $v=p->proc;
	>>
	;

/* H331 incomplete (only allows one processor declaration) */
processor_directive : PROCESSORS1 processor_decl
	;

/* H332 */
processor_decl : << int index; ident_t *p; >>
	processor_name > [index]
	<< p=get_ident();
	   p->type=PROCESSOR;
	   p->proc=NULL;
	   insert_sym(p,index);
	   strcpy(p->string,id_text(index));
	>>
	{ LEFTPAREN1 hpf_shape_spec_list > [p->proc] RIGHTPAREN1 }
	<< if (strcmp(p->string,"network")==0) {
	     n_procs=p->proc->ident->array.rav[0]->ident->value; 
	     sprintf(arch_module,"MPINET"); 
	   }
	>>
	;

/* H333 */
processor_name > [int index] : quiet_variable > [$index]
	;

hpf_shape_spec > [vect_t *v]:
	<< ident_t *i; s_expr_t *s; >>
	s_expr > [s]
	<< $v=new_vect();
	   $v->shp = &s_const1;
	   i=get_ident();
	   $v->ident=i;
	   i->type=RAV;
	   i->array.dim=&const1;
	   i->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	   i->array.shp[0]=&const1;
	   i->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
	   i->array.rav[0]=s;
	>>
	;

hpf_shape_spec_list > [vect_t *v] :
	<< vect_t *tmp; >>
	hpf_shape_spec > [$v]
	( COMMA1 hpf_shape_spec > [tmp] << $v=vect_cat($v,tmp); >> )*
	;
