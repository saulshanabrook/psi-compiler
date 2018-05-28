/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.20
 */
#include <stdio.h>
#define ANTLR_VERSION	120
#include "charbuf.h" 
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
#define LL_K 4
#define zzEOF_TOKEN 1
#define zzSET_SIZE 44
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"
ANTLR_INFO

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
}   

void
#ifdef __STDC__
executable_program(void)
#else
executable_program()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==330) ) {
			directive_origin();
			processor_directive();
		}
		zzEXIT(zztasp2);
		}
	}
	{
		zzBLOCK(zztasp2);
		int zzcnt=1;
		zzMake0;
		{
		do {
			program_unit();
			zzLOOP(zztasp2);
		} while ( (setwd1[LA(1)]&0x1) );
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x2);
	}
}

void
#ifdef __STDC__
program_unit(void)
#else
program_unit()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	external_subprogram();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x4);
	}
}

void
#ifdef __STDC__
external_subprogram(void)
#else
external_subprogram()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	subroutine_subprogram();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x8);
	}
}

void
#ifdef __STDC__
subroutine_subprogram(void)
#else
subroutine_subprogram()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	char buf[1024]; statement_t *body=NULL;
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
	}   
	subroutine_stmt();
	if (host) {
		fprintf(hostfile,"USE %s\n",arch_module);
		fprintf(hostfile,"USE MOALIB\n");
	}
	if (n_procs>1) fprintf(cfile,"USE %s\n",arch_module);
	fprintf(cfile,"USE MOALIB\n");   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd1[LA(1)]&0x10) ) {
			specification_part();
		}
		zzEXIT(zztasp2);
		}
	}
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd1[LA(1)]&0x20) ) {
			 body  = execution_part();

		}
		zzEXIT(zztasp2);
		}
	}
	declare_utils();
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
	end_subroutine_stmt();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x40);
	}
}

 statement_t * 
#ifdef __STDC__
execution_part(void)
#else
 statement_t * 
execution_part()
#endif
{
	 statement_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	statement_t *node;
	
           curtempf90=0;
	 _retv  = executable_construct();

	node=_retv;
	if (node != NULL) { 
		while (node->next != NULL) node=node->next;
		node->next = NULL;
		code_c(_retv,partition(_retv));
	}
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd1[LA(1)]&0x80)
 ) {
			 _retv  = execution_part_construct();

			node=_retv; 
			if (node != NULL) { 
				while (node->next != NULL) node=node->next;
				node->next = NULL;
				code_c(_retv,partition(_retv));
			}
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	if (node != NULL) node->next=NULL;   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x1);
	return _retv;
	}
}

 statement_t * 
#ifdef __STDC__
execution_part_construct(void)
#else
 statement_t * 
execution_part_construct()
#endif
{
	 statement_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	 _retv  = executable_construct();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x2);
	return _retv;
	}
}

 statement_t * 
#ifdef __STDC__
executable_construct(void)
#else
 statement_t * 
executable_construct()
#endif
{
	 statement_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (setwd2[LA(1)]&0x4) && (setwd2[LA(2)]&0x8) && (setwd2[LA(3)]&0x10) && (setwd2[LA(4)]&0x20) ) {
		 _retv  = action_stmt();

	}
	else {
		if ( (setwd2[LA(1)]&0x40) && (setwd2[LA(2)]&0x80) && 
(setwd3[LA(3)]&0x1) && (setwd3[LA(4)]&0x2) ) {
			do_construct();
			_retv = NULL;   
		}
		else {
			if ( (setwd3[LA(1)]&0x4) && (setwd3[LA(2)]&0x8) && (setwd3[LA(3)]&0x10) && (setwd3[LA(4)]&0x20) ) {
				if_construct();
				_retv = NULL;   
			}
			else {zzFAIL(4,zzerr1,zzerr2,zzerr3,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x40);
	return _retv;
	}
}

 statement_t * 
#ifdef __STDC__
action_stmt(void)
#else
 statement_t * 
action_stmt()
#endif
{
	 statement_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==NAME1)
 ) {
		 _retv  = assignment_stmt();

	}
	else {
		if ( (LA(1)==IF1) ) {
			if_stmt();
			_retv = NULL;   
		}
		else {zzFAIL(1,zzerr5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x80);
	return _retv;
	}
}

 parser_t * 
#ifdef __STDC__
array_constructor(void)
#else
 parser_t * 
array_constructor()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tvect; s_expr_t *acv1;   
	zzmatch(LEFTCONS1); zzCONSUME;
	 acv1  = s_expr();

	tvect=s_vect(acv1);   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1) ) {
			zzmatch(COMMA1); zzCONSUME;
			 acv1  = s_expr();

			tvect=vect_cat(tvect,s_vect(acv1));   
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=vect2parser(tvect);   
	zzmatch(RIGHTCONS1); zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x1);
	return _retv;
	}
}

void
#ifdef __STDC__
variable(void)
#else
variable()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(NAME1);
	sprintf(line+strlen(line),"%s ",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x2);
	}
}

 parser_t * 
#ifdef __STDC__
array_variable(void)
#else
 parser_t * 
array_variable()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tk, *dr; int indexed; parser_t *tkp,*drp;  
	zzmatch(NAME1);
	_retv=psi_access(find_sym(name_id(zzaArg(zztasp1,1 ).text),TRUE));
	_retv->psi->ext_str=(char *) get_mem(strlen(zzaArg(zztasp1,1 ).text));
	sprintf (_retv->psi->ext_str,"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==LEFTPAREN1) ) {
			zzmatch(LEFTPAREN1); zzCONSUME;
			section_subscript_list( &tk,&dr,&indexed );
			tkp=vect2parser(tk);
			drp=vect2parser(dr);
			if (indexed) {
				_retv=psi_psi(drp,_retv);
			} else {
				_retv=psi_pdrop(drp,_retv);
				_retv=psi_ptake(tkp,_retv);
			}
			zzmatch(RIGHTPAREN1); zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x4);
	return _retv;
	}
}

 vect_t * 
#ifdef __STDC__
subscript(void)
#else
 vect_t * 
subscript()
#endif
{
	 vect_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *p;   
	 p  = array_expr();

	_retv=make_vect(p->psi);   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x8);
	return _retv;
	}
}

void
#ifdef __STDC__
section_subscript( vect_t **tk, vect_t **dr, int *indexed )
#else
section_subscript(tk,dr,indexed)
 vect_t **tk;
vect_t **dr;
int *indexed ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	*indexed=TRUE;   
	 *dr  = subscript();

	*tk=*dr; *dr=vect_op(MINUS,*dr,&one_vec);   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==COLON1) ) {
			zzmatch(COLON1); zzCONSUME;
			 *tk  = subscript();

			*indexed=FALSE;   
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x10);
	}
}

void
#ifdef __STDC__
section_subscript_list( vect_t **tk, vect_t **dr, int *indexed )
#else
section_subscript_list(tk,dr,indexed)
 vect_t **tk;
vect_t **dr;
int *indexed ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tk1, *dr1;   
	section_subscript( tk,dr,indexed );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1)
 ) {
			zzmatch(COMMA1); zzCONSUME;
			section_subscript( &tk1,&dr1,indexed );
			*tk=vect_cat(*tk,tk1); *dr=vect_cat(*dr,dr1);   
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	*tk=vect_op(MINUS,*tk,*dr);   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x20);
	}
}

 parser_t * 
#ifdef __STDC__
array_result(void)
#else
 parser_t * 
array_result()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tk,*dr; int psi;   
	zzmatch(NAME1);
	_retv=psi_access(find_sym(name_id(zzaArg(zztasp1,1 ).text),TRUE));
	_retv->psi->ext_str=(char *) get_mem(strlen(zzaArg(zztasp1,1 ).text));
	sprintf (_retv->psi->ext_str,"%s",zzaArg(zztasp1,1 ).text);
	_retv->psi->loc=NULL;   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==LEFTPAREN1) ) {
			zzmatch(LEFTPAREN1); zzCONSUME;
			section_subscript_list( &tk,&dr,&psi );
			_retv->psi->loc=dr;   
			zzmatch(RIGHTPAREN1); zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x40);
	return _retv;
	}
}

void
#ifdef __STDC__
primary(void)
#else
primary()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (setwd4[LA(1)]&0x80) ) {
		constant();
	}
	else {
		if ( (LA(1)==NAME1) ) {
			variable();
		}
		else {
			if ( (LA(1)==LEFTPAREN1) ) {
				zzmatch(LEFTPAREN1);
				sprintf(line+strlen(line),"(");   
 zzCONSUME;
				expr();
				zzmatch(RIGHTPAREN1);
				sprintf(line+strlen(line),")");   
 zzCONSUME;
			}
			else {zzFAIL(1,zzerr6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x1);
	}
}

 parser_t * 
#ifdef __STDC__
array_primary(void)
#else
 parser_t * 
array_primary()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tk, *dr; int indexed; parser_t *tkp,*drp; char *f90str;   
	if ( (LA(1)==NAME1)
 ) {
		 _retv  = array_variable();

	}
	else {
		if ( (setwd5[LA(1)]&0x2) ) {
			 _retv  = array_constant();

		}
		else {
			if ( (setwd5[LA(1)]&0x4) ) {
				 _retv  = function_reference();

			}
			else {
				if ( (LA(1)==LEFTCONS1) ) {
					 _retv  = array_constructor();

				}
				else {
					if ( (LA(1)==LEFTPAREN1) ) {
						zzmatch(LEFTPAREN1); zzCONSUME;
						 _retv  = array_expr();

						zzmatch(RIGHTPAREN1);
						if (_retv->psi->op==EXT_OP) {
							f90str=(char *) get_mem (strlen (_retv->psi->ext_str)+2);
							sprintf (f90str,"(%s)",_retv->psi->ext_str);
							free(_retv->psi->ext_str);
							_retv->psi->ext_str=f90str; }   
 zzCONSUME;
						{
							zzBLOCK(zztasp2);
							zzMake0;
							{
							if ( (LA(1)==LEFTPAREN1)
 ) {
								zzmatch(LEFTPAREN1); zzCONSUME;
								section_subscript_list( &tk,&dr,&indexed );
								tkp=vect2parser(tk);
								drp=vect2parser(dr);
								if (indexed) {
									_retv=psi_psi(drp,_retv);
								} else {
									_retv=psi_pdrop(drp,_retv);
									_retv=psi_ptake(tkp,_retv);
								}
								zzmatch(RIGHTPAREN1); zzCONSUME;
							}
							zzEXIT(zztasp2);
							}
						}
					}
					else {zzFAIL(1,zzerr7,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x8);
	return _retv;
	}
}

void
#ifdef __STDC__
level_1_expr(void)
#else
level_1_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==PERIOD1) ) {
			defined_unary_op();
		}
		zzEXIT(zztasp2);
		}
	}
	primary();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x10);
	}
}

 parser_t * 
#ifdef __STDC__
array_level_1_expr(void)
#else
 parser_t * 
array_level_1_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1; psiop_t func;
	char fname [FNAMELEN];   
	func.func=NULL;   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==PERIOD1) ) {
			 func  = array_defined_unary_op();

			strcpy (fname,f90func);   
		}
		zzEXIT(zztasp2);
		}
	}
	 arg1  = array_primary();

	if (func.func!=NULL) {
		arg1=make_compatable (arg1, func);
		strcpy (f90func,fname); 
		_retv=(func.func)(arg1);
	} else _retv=arg1;   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x20);
	return _retv;
	}
}

void
#ifdef __STDC__
defined_unary_op(void)
#else
defined_unary_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(PERIOD1); zzCONSUME;
	zzmatch(NAME1); zzCONSUME;
	zzmatch(PERIOD1);
	sprintf(line+strlen(line),".%s. ",zzaArg(zztasp1,2 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x40);
	}
}

 psiop_t  
#ifdef __STDC__
array_defined_unary_op(void)
#else
 psiop_t  
array_defined_unary_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(PERIOD1); zzCONSUME;
	zzmatch(NAME1); zzCONSUME;
	zzmatch(PERIOD1);
	sprintf (f90func, ".%s.", zzaArg(zztasp1,2 ).text);
	_retv.func=unon_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x80);
	return _retv;
	}
}

void
#ifdef __STDC__
mult_operand(void)
#else
mult_operand()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	level_1_expr();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==POWER1) ) {
			power_op();
			level_1_expr();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x1);
	}
}

 parser_t * 
#ifdef __STDC__
array_mult_operand(void)
#else
 parser_t * 
array_mult_operand()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_level_1_expr();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==POWER1) ) {
			 func  = array_power_op();

			strcpy (fname,f90func);   
			 arg2  = array_level_1_expr();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x2);
	return _retv;
	}
}

void
#ifdef __STDC__
add_operand(void)
#else
add_operand()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	mult_operand();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd6[LA(1)]&0x4)
 ) {
			mult_op();
			mult_operand();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x8);
	}
}

 parser_t * 
#ifdef __STDC__
array_add_operand(void)
#else
 parser_t * 
array_add_operand()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_mult_operand();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd6[LA(1)]&0x10) ) {
			 func  = array_mult_op();

			strcpy (fname,f90func);   
			 arg2  = array_mult_operand();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x20);
	return _retv;
	}
}

void
#ifdef __STDC__
level_2_expr(void)
#else
level_2_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd6[LA(1)]&0x40) ) {
			add_op();
		}
		zzEXIT(zztasp2);
		}
	}
	add_operand();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd6[LA(1)]&0x80) ) {
			add_op();
			add_operand();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x1);
	}
}

 parser_t * 
#ifdef __STDC__
array_level_2_expr(void)
#else
 parser_t * 
array_level_2_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_add_operand();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd7[LA(1)]&0x2) ) {
			 func  = array_add_op();

			strcpy (fname,f90func);   
			 arg2  = array_add_operand();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x4);
	return _retv;
	}
}

void
#ifdef __STDC__
power_op(void)
#else
power_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(POWER1);
	sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x8);
	}
}

 psiop_t  
#ifdef __STDC__
array_power_op(void)
#else
 psiop_t  
array_power_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(POWER1);
	sprintf (f90func, "%s", zzaArg(zztasp1,1)); 
	_retv.func=non_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x10);
	return _retv;
	}
}

void
#ifdef __STDC__
mult_op(void)
#else
mult_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==TIMES1)
 ) {
		zzmatch(TIMES1); zzCONSUME;
	}
	else {
		if ( (LA(1)==SLASH1) ) {
			zzmatch(SLASH1);
			sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr8,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x20);
	}
}

 psiop_t  
#ifdef __STDC__
array_mult_op(void)
#else
 psiop_t  
array_mult_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==TIMES1) ) {
		zzmatch(TIMES1);
		_retv.func=psi_times;   
 zzCONSUME;
	}
	else {
		if ( (LA(1)==SLASH1) ) {
			zzmatch(SLASH1);
			_retv.func=psi_div;   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr9,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x40);
	return _retv;
	}
}

void
#ifdef __STDC__
add_op(void)
#else
add_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==PLUS1) ) {
		zzmatch(PLUS1); zzCONSUME;
	}
	else {
		if ( (LA(1)==MINUS1)
 ) {
			zzmatch(MINUS1);
			sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr10,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x80);
	}
}

 psiop_t  
#ifdef __STDC__
array_add_op(void)
#else
 psiop_t  
array_add_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==PLUS1) ) {
		zzmatch(PLUS1);
		_retv.func=psi_plus;   
 zzCONSUME;
	}
	else {
		if ( (LA(1)==MINUS1) ) {
			zzmatch(MINUS1);
			_retv.func=psi_minus;   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr11,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x1);
	return _retv;
	}
}

void
#ifdef __STDC__
level_3_expr(void)
#else
level_3_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	level_2_expr();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==DSLASH1) ) {
			concat_op();
			level_2_expr();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x2);
	}
}

 parser_t * 
#ifdef __STDC__
array_level_3_expr(void)
#else
 parser_t * 
array_level_3_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_level_2_expr();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==DSLASH1) ) {
			 func  = array_concat_op();

			strcpy (fname,f90func);   
			 arg2  = array_level_2_expr();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x4);
	return _retv;
	}
}

void
#ifdef __STDC__
concat_op(void)
#else
concat_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(DSLASH1);
	sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x8);
	}
}

 psiop_t  
#ifdef __STDC__
array_concat_op(void)
#else
 psiop_t  
array_concat_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(DSLASH1);
	sprintf (f90func, "//");
	_retv.func=non_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x10);
	return _retv;
	}
}

void
#ifdef __STDC__
level_4_expr(void)
#else
level_4_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	level_3_expr();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd8[LA(1)]&0x20)
 ) {
			rel_op();
			level_3_expr();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x40);
	}
}

 parser_t * 
#ifdef __STDC__
array_level_4_expr(void)
#else
 parser_t * 
array_level_4_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_level_3_expr();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd8[LA(1)]&0x80) ) {
			 func  = array_rel_op();

			strcpy (fname,f90func);   
			 arg2  = array_level_3_expr();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x1);
	return _retv;
	}
}

void
#ifdef __STDC__
rel_op(void)
#else
rel_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==EQ1) ) {
		zzmatch(EQ1); zzCONSUME;
	}
	else {
		if ( (LA(1)==NE1) ) {
			zzmatch(NE1); zzCONSUME;
		}
		else {
			if ( (LA(1)==LT1) ) {
				zzmatch(LT1); zzCONSUME;
			}
			else {
				if ( (LA(1)==GT1)
 ) {
					zzmatch(GT1); zzCONSUME;
				}
				else {
					if ( (LA(1)==GE1) ) {
						zzmatch(GE1);
						sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
					}
					else {zzFAIL(1,zzerr12,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x2);
	}
}

 psiop_t  
#ifdef __STDC__
array_rel_op(void)
#else
 psiop_t  
array_rel_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==EQ1) ) {
		zzmatch(EQ1); zzCONSUME;
	}
	else {
		if ( (LA(1)==NE1) ) {
			zzmatch(NE1); zzCONSUME;
		}
		else {
			if ( (LA(1)==LT1) ) {
				zzmatch(LT1); zzCONSUME;
			}
			else {
				if ( (LA(1)==GT1)
 ) {
					zzmatch(GT1); zzCONSUME;
				}
				else {
					if ( (LA(1)==GE1) ) {
						zzmatch(GE1);
						sprintf (f90func,"%s", zzaArg(zztasp1,1 ).text);
						_retv.func=non_psi;   
 zzCONSUME;
					}
					else {zzFAIL(1,zzerr13,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x4);
	return _retv;
	}
}

void
#ifdef __STDC__
and_operand(void)
#else
and_operand()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NOT1) ) {
			not_op();
		}
		zzEXIT(zztasp2);
		}
	}
	level_4_expr();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x8);
	}
}

 parser_t * 
#ifdef __STDC__
array_and_operand(void)
#else
 parser_t * 
array_and_operand()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1; psiop_t func;
	char fname [FNAMELEN];   
	if ( (setwd9[LA(1)]&0x10) ) {
		 _retv  = array_level_4_expr();

	}
	else {
		if ( (LA(1)==NOT1) ) {
			 func  = array_not_op();

			strcpy (fname,f90func);   
			 arg1  = array_level_4_expr();

			arg1=make_compatable (arg1,func);
			strcpy (f90func,fname); 
			_retv=(func.func)(arg1);  
		}
		else {zzFAIL(1,zzerr14,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x20);
	return _retv;
	}
}

void
#ifdef __STDC__
or_operand(void)
#else
or_operand()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	and_operand();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==AND1)
 ) {
			and_op();
			and_operand();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x40);
	}
}

 parser_t * 
#ifdef __STDC__
array_or_operand(void)
#else
 parser_t * 
array_or_operand()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_and_operand();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==AND1) ) {
			 func  = array_and_op();

			strcpy (fname,f90func);   
			 arg2  = array_and_operand();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd9, 0x80);
	return _retv;
	}
}

void
#ifdef __STDC__
equiv_operand(void)
#else
equiv_operand()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	or_operand();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==OR1) ) {
			or_op();
			or_operand();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x1);
	}
}

 parser_t * 
#ifdef __STDC__
array_equiv_operand(void)
#else
 parser_t * 
array_equiv_operand()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_or_operand();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==OR1) ) {
			 func  = array_or_op();

			strcpy (fname,f90func);   
			 arg2  = array_or_operand();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x2);
	return _retv;
	}
}

void
#ifdef __STDC__
level_5_expr(void)
#else
level_5_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	equiv_operand();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd10[LA(1)]&0x4) ) {
			equiv_op();
			equiv_operand();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x8);
	}
}

 parser_t * 
#ifdef __STDC__
array_level_5_expr(void)
#else
 parser_t * 
array_level_5_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_equiv_operand();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd10[LA(1)]&0x10)
 ) {
			 func  = array_equiv_op();

			strcpy (fname,f90func);   
			 arg2  = array_equiv_operand();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x20);
	return _retv;
	}
}

void
#ifdef __STDC__
not_op(void)
#else
not_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(NOT1);
	sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x40);
	}
}

 psiop_t  
#ifdef __STDC__
array_not_op(void)
#else
 psiop_t  
array_not_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(NOT1);
	sprintf (f90func,"%s",zzaArg(zztasp1,1 ).text);
	_retv.func=unon_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd10, 0x80);
	return _retv;
	}
}

void
#ifdef __STDC__
and_op(void)
#else
and_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(AND1);
	sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x1);
	}
}

 psiop_t  
#ifdef __STDC__
array_and_op(void)
#else
 psiop_t  
array_and_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(AND1);
	sprintf (f90func,"%s",zzaArg(zztasp1,1 ).text);
	_retv.func=non_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x2);
	return _retv;
	}
}

void
#ifdef __STDC__
or_op(void)
#else
or_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(OR1);
	sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x4);
	}
}

 psiop_t  
#ifdef __STDC__
array_or_op(void)
#else
 psiop_t  
array_or_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(OR1);
	sprintf (f90func,"%s",zzaArg(zztasp1,1 ).text);
	_retv.func=non_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x8);
	return _retv;
	}
}

void
#ifdef __STDC__
equiv_op(void)
#else
equiv_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==EQV1) ) {
		zzmatch(EQV1); zzCONSUME;
	}
	else {
		if ( (LA(1)==NEQV1) ) {
			zzmatch(NEQV1);
			sprintf(line+strlen(line),"%s",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr15,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x10);
	}
}

 psiop_t  
#ifdef __STDC__
array_equiv_op(void)
#else
 psiop_t  
array_equiv_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==EQV1) ) {
		zzmatch(EQV1); zzCONSUME;
	}
	else {
		if ( (LA(1)==NEQV1) ) {
			zzmatch(NEQV1);
			sprintf (f90func,"%s",zzaArg(zztasp1,1 ).text);
			_retv.func=non_psi;   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr16,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x20);
	return _retv;
	}
}

void
#ifdef __STDC__
expr(void)
#else
expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	level_5_expr();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==PERIOD1)
 ) {
			defined_binary_op();
			level_5_expr();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x40);
	}
}

 parser_t * 
#ifdef __STDC__
array_expr(void)
#else
 parser_t * 
array_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; psiop_t func;
	char fname [FNAMELEN];   
	 arg1  = array_level_5_expr();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==PERIOD1) ) {
			 func  = array_defined_binary_op();

			strcpy (fname,f90func);   
			 arg2  = array_level_5_expr();

			arg1=make_compatable (arg1,func);
			arg2=make_compatable (arg2,func);
			strcpy (f90func,fname); 
			arg1=(func.func)(arg1,arg2);  
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	_retv=arg1;  
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd11, 0x80);
	return _retv;
	}
}

void
#ifdef __STDC__
defined_binary_op(void)
#else
defined_binary_op()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(PERIOD1); zzCONSUME;
	zzmatch(NAME1); zzCONSUME;
	zzmatch(PERIOD1);
	sprintf(line+strlen(line),".%s. ",zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x1);
	}
}

void
#ifdef __STDC__
logical_expr(void)
#else
logical_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	expr();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x2);
	}
}

 parser_t * 
#ifdef __STDC__
array_logical_expr(void)
#else
 parser_t * 
array_logical_expr()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	 _retv  = array_expr();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x4);
	return _retv;
	}
}

void
#ifdef __STDC__
numeric_expr(void)
#else
numeric_expr()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	expr();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x8);
	}
}

void
#ifdef __STDC__
array_numeric_expr( parser_t *e )
#else
array_numeric_expr(e)
 parser_t *e ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	  e  = array_expr();

	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x10);
	}
}

 psiop_t  
#ifdef __STDC__
array_defined_binary_op(void)
#else
 psiop_t  
array_defined_binary_op()
#endif
{
	 psiop_t  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(PERIOD1); zzCONSUME;
	zzmatch(NAME1); zzCONSUME;
	zzmatch(PERIOD1);
	sprintf (f90func,".%s.",zzaArg(zztasp1,2 ).text);
	_retv.func=non_psi;   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x20);
	return _retv;
	}
}

 statement_t * 
#ifdef __STDC__
assignment_stmt(void)
#else
 statement_t * 
assignment_stmt()
#endif
{
	 statement_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *result,*e; statement_t *assign;  
	reduction_init(); assign=get_statement(ASSIGN);  
	 result  = array_result();

	zzmatch(EQUAL1); zzCONSUME;
	 e  = array_expr();

	assign->str="array assignment";
	result->psi->bound=e->psi->shp;
	assign->d.assign->expr=e->psi;
	assign->d.assign->result=result->psi;
	psi_reduce(assign,TRUE);
	_retv=assign;   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd12, 0x40);
	return _retv;
	}
}

void
#ifdef __STDC__
block(void)
#else
block()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	statement_t *body=NULL;   
	{
		zzBLOCK(zztasp2);
		int zzcnt=1;
		zzMake0;
		{
		do {
			 body  = execution_part_construct();

			if (body != NULL) { 
				body->next = NULL;
				code_c(body,partition(body));
			}
			zzLOOP(zztasp2);
		} while ( (setwd12[LA(1)]&0x80) );
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd13, 0x1);
	}
}

void
#ifdef __STDC__
if_construct(void)
#else
if_construct()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if_then_statement();
	dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; ntab++;   
	block();
	{
		zzBLOCK(zztasp2);
		int zzcnt=1;
		zzMake0;
		{
		do {
			else_if_statement();
			dotab (0); fprintf(tfile,"%s\n",line); line[0]=0;   
			block();
			zzLOOP(zztasp2);
		} while ( (LA(1)==ELSE1) && (LA(2)==IF1) && (LA(3)==LEFTPAREN1) && 
(setwd13[LA(4)]&0x2) );
		zzEXIT(zztasp2);
		}
	}
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==ELSE1) ) {
			else_statement();
			dotab (0); fprintf(tfile,"%s\n",line); line[0]=0;   
			block();
		}
		zzEXIT(zztasp2);
		}
	}
	end_if_statement();
	ntab--; dotab (0); fprintf(tfile,"%s\n",line); line[0]=0;   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd13, 0x4);
	}
}

void
#ifdef __STDC__
if_then_statement(void)
#else
if_then_statement()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) ) {
			if_construct_name();
			zzmatch(COLON1);
			sprintf(line+strlen(line)," : ");   
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(IF1); zzCONSUME;
	zzmatch(LEFTPAREN1);
	sprintf(line+strlen(line),"IF (");   
 zzCONSUME;
	logical_expr();
	zzmatch(RIGHTPAREN1); zzCONSUME;
	zzmatch(THEN1);
	sprintf(line+strlen(line),") THEN");   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd13, 0x8);
	}
}

void
#ifdef __STDC__
else_if_statement(void)
#else
else_if_statement()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(ELSE1); zzCONSUME;
	zzmatch(IF1); zzCONSUME;
	zzmatch(LEFTPAREN1);
	sprintf(line+strlen(line),"ELSE IF (");   
 zzCONSUME;
	logical_expr();
	zzmatch(RIGHTPAREN1); zzCONSUME;
	zzmatch(THEN1);
	sprintf(line+strlen(line),") THEN ");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) && (setwd13[LA(2)]&0x10) && (setwd13[LA(3)]&0x20) && 
(setwd13[LA(4)]&0x40) ) {
			if_construct_name();
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd13, 0x80);
	}
}

void
#ifdef __STDC__
else_statement(void)
#else
else_statement()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(ELSE1);
	sprintf(line+strlen(line),"ELSE ");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) && (setwd14[LA(2)]&0x1) && (setwd14[LA(3)]&0x2) && (setwd14[LA(4)]&0x4) ) {
			if_construct_name();
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd14, 0x8);
	}
}

void
#ifdef __STDC__
end_if_statement(void)
#else
end_if_statement()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(END1); zzCONSUME;
	zzmatch(IF1);
	sprintf(line+strlen(line),"END IF ");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) && (setwd14[LA(2)]&0x10) && 
(setwd14[LA(3)]&0x20) && (setwd14[LA(4)]&0x40) ) {
			if_construct_name();
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd14, 0x80);
	}
}

void
#ifdef __STDC__
if_stmt(void)
#else
if_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	statement_t *body=NULL;   
	zzmatch(IF1); zzCONSUME;
	zzmatch(LEFTPAREN1);
	sprintf(line+strlen(line),"IF (");   
 zzCONSUME;
	logical_expr();
	zzmatch(RIGHTPAREN1);
	sprintf(line+strlen(line),")");   
 zzCONSUME;
	 body  = action_stmt();

	if (body != NULL) { 
		body->next = NULL;
		code_c(body,partition(body));
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x1);
	}
}

void
#ifdef __STDC__
if_construct_name(void)
#else
if_construct_name()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	variable();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x2);
	}
}

void
#ifdef __STDC__
do_construct(void)
#else
do_construct()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	block_do_construct();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x4);
	}
}

void
#ifdef __STDC__
block_do_construct(void)
#else
block_do_construct()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	do_stmt();
	dotab (0); fprintf(tfile,"%s\n",line); line[0]=0; ntab++;   
	do_block();
	end_do();
	ntab--; dotab (0); fprintf(tfile,"%s\n",line); line[0]=0;   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x8);
	}
}

void
#ifdef __STDC__
do_stmt(void)
#else
do_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	nonlabel_do_stmt();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x10);
	}
}

void
#ifdef __STDC__
nonlabel_do_stmt(void)
#else
nonlabel_do_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) ) {
			do_construct_name();
			zzmatch(COLON1);
			sprintf (line + strlen(line), " : ");   
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(DO1);
	sprintf (line+strlen(line),"DO ");   
 zzCONSUME;
	loop_control();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd15, 0x20);
	}
}

void
#ifdef __STDC__
loop_control(void)
#else
loop_control()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (setwd15[LA(1)]&0x40) && (setwd15[LA(2)]&0x80) ) {
		{
			zzBLOCK(zztasp2);
			zzMake0;
			{
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==COMMA1)
 ) {
					zzmatch(COMMA1);
					sprintf (line+strlen(line), ", ");   
 zzCONSUME;
				}
				zzEXIT(zztasp3);
				}
			}
			do_variable();
			zzmatch(EQUAL1);
			sprintf (line+strlen(line), "= ");   
 zzCONSUME;
			numeric_expr();
			zzmatch(COMMA1);
			sprintf (line+strlen(line), ", ");   
 zzCONSUME;
			numeric_expr();
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==COMMA1) ) {
					zzmatch(COMMA1);
					sprintf (line+strlen(line), ", ");   
 zzCONSUME;
					numeric_expr();
				}
				zzEXIT(zztasp3);
				}
			}
			zzEXIT(zztasp2);
			}
		}
	}
	else {
		if ( (setwd16[LA(1)]&0x1) && (setwd16[LA(2)]&0x2) ) {
			{
				zzBLOCK(zztasp2);
				zzMake0;
				{
				{
					zzBLOCK(zztasp3);
					zzMake0;
					{
					if ( (LA(1)==COMMA1) ) {
						zzmatch(COMMA1);
						sprintf (line+strlen(line), ", ");   
 zzCONSUME;
					}
					zzEXIT(zztasp3);
					}
				}
				zzmatch(WHILE1); zzCONSUME;
				zzmatch(LEFTPAREN1);
				sprintf (line+strlen(line), "WHILE ( ");   
 zzCONSUME;
				logical_expr();
				zzmatch(RIGHTPAREN1);
				sprintf (line+strlen(line), ")");   
 zzCONSUME;
				zzEXIT(zztasp2);
				}
			}
		}
		else {zzFAIL(2,zzerr17,zzerr18,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd16, 0x4);
	}
}

void
#ifdef __STDC__
do_variable(void)
#else
do_variable()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	variable();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd16, 0x8);
	}
}

void
#ifdef __STDC__
do_block(void)
#else
do_block()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	block();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd16, 0x10);
	}
}

void
#ifdef __STDC__
end_do(void)
#else
end_do()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	end_do_stmt();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd16, 0x20);
	}
}

void
#ifdef __STDC__
end_do_stmt(void)
#else
end_do_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(END1); zzCONSUME;
	zzmatch(DO1);
	sprintf(line+strlen(line), "END DO ");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) && 
(setwd16[LA(2)]&0x40) && (setwd16[LA(3)]&0x80) && (setwd17[LA(4)]&0x1) ) {
			do_construct_name();
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd17, 0x2);
	}
}

void
#ifdef __STDC__
do_construct_name(void)
#else
do_construct_name()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	variable();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd17, 0x4);
	}
}

 parser_t * 
#ifdef __STDC__
function_reference(void)
#else
 parser_t * 
function_reference()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	parser_t *arg1,*arg2; 
	expr_t *arg_expr, *temp;
	psiop_t func;
	char msg[60], fname[FNAMELEN];
	/* na = minimum number of arguments allowed to function, xa = maximum
	ca = current argument */
	int na, xa, ca=0;  
	{ struct _rv88 _trv; _trv = function_name();

	func = _trv.func; na = _trv.na; xa  = _trv.xa; }
	arg1=NULL;
	strcpy (fname,f90func);   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==LEFTPAREN1) ) {
			zzmatch(LEFTPAREN1); zzCONSUME;
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (setwd17[LA(1)]&0x8) ) {
					 arg1  = actual_arg_spec( func );

					ca++;
					arg1=make_compatable (arg1,func);
					arg_expr=get_expr_mem (1);
					arg_expr->left=arg1->psi;
					arg_expr->right=NULL;
					arg_expr->op=EXT_OP;
					arg_expr->ext_op=FUNC;
					arg_expr->ident=arg1->ident;
					arg1->psi=arg_expr;
					temp=arg1->psi;   
					{
						zzBLOCK(zztasp4);
						zzMake0;
						{
						while ( (LA(1)==COMMA1)
 ) {
							zzmatch(COMMA1); zzCONSUME;
							 arg2  = actual_arg_spec( func );

							ca++;
							arg2=make_compatable (arg2,func);
							temp->right=get_expr_mem (1);
							temp=temp->right;
							temp->left=arg2->psi;
							temp->right=NULL;
							temp->op=EXT_OP;
							temp->ext_op=SPLIT;
							temp->ident=arg2->ident;   
							zzLOOP(zztasp4);
						}
						zzEXIT(zztasp4);
						}
					}
				}
				zzEXIT(zztasp3);
				}
			}
			zzmatch(RIGHTPAREN1); zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	if (xa&&(ca>xa)) {
		sprintf (msg,"too many args to %s.  additional args disregarded.",
		fname);
		error (msg);
	}
	if (na&&(ca<na)) {
		sprintf (msg,"too few args to %s",fname);
		error (msg);
	}
	strcpy (f90func,fname);
	_retv=(func.func)(arg1);   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd17, 0x10);
	return _retv;
	}
}

 parser_t * 
#ifdef __STDC__
actual_arg_spec( psiop_t func )
#else
 parser_t * 
actual_arg_spec(func)
 psiop_t func ;
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int dummy_assign=0; char *f90str;   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) && (LA(2)==EQUAL1) ) {
			zzmatch(NAME1); zzCONSUME;
			zzmatch(EQUAL1);
			dummy_assign = 1;   
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	 _retv  = actual_arg();

	_retv=make_compatable (_retv, func); 
	if (dummy_assign) {
		f90str=(char *) get_mem (strlen(_retv->psi->ext_str)+
		strlen(zzaArg(zztasp1,1 ).text)+3);
		sprintf(f90str,"%s = %s",zzaArg(zztasp1,1 ).text,_retv->psi->ext_str);
		free(_retv->psi->ext_str);
		_retv->psi->ext_str=f90str;
	}   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd17, 0x20);
	return _retv;
	}
}

 parser_t * 
#ifdef __STDC__
actual_arg(void)
#else
 parser_t * 
actual_arg()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	 _retv  = array_expr();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd17, 0x40);
	return _retv;
	}
}

struct _rv88
#ifdef __STDC__
function_name(void)
#else
struct _rv88
function_name()
#endif
{
	struct _rv88 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (setwd17[LA(1)]&0x80) ) {
		{ struct _rv89 _trv; _trv = function_name1();

		_retv.func = _trv.func; _retv.na = _trv.na; _retv.xa  = _trv.xa; }
	}
	else {
		if ( (setwd18[LA(1)]&0x1) ) {
			{ struct _rv90 _trv; _trv = function_name2();

			_retv.func = _trv.func; _retv.na = _trv.na; _retv.xa  = _trv.xa; }
		}
		else {zzFAIL(1,zzerr19,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x2);
	return _retv;
	}
}

struct _rv89
#ifdef __STDC__
function_name1(void)
#else
struct _rv89
function_name1()
#endif
{
	struct _rv89 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==CONCAT1)
 ) {
			zzmatch(CONCAT1);
			_retv.func.func=hpfm_concat; _retv.na=2; _retv.xa=3;   
 zzCONSUME;
		}
		else {
			if ( (LA(1)==CSHIFT1) ) {
				zzmatch(CSHIFT1);
				_retv.func.func=hpfm_cshift; _retv.na=2; _retv.xa=3;   
 zzCONSUME;
			}
			else {
				if ( (LA(1)==DOT_PRODUCT1) ) {
					zzmatch(DOT_PRODUCT1);
					_retv.func.func=hpfm_dot_product; _retv.na=2; _retv.xa=2;   
 zzCONSUME;
				}
				else {
					if ( (LA(1)==EOSHIFT1) ) {
						zzmatch(EOSHIFT1);
						_retv.func.func=hpfm_eoshift; _retv.na=2; _retv.xa=4;   
 zzCONSUME;
					}
					else {
						if ( (LA(1)==MATMUL1) ) {
							zzmatch(MATMUL1);
							_retv.func.func=hpfm_matmul; _retv.na=2; _retv.xa=2;   
 zzCONSUME;
						}
						else {
							if ( (LA(1)==PRODUCT1)
 ) {
								zzmatch(PRODUCT1);
								_retv.func.func=hpfm_product; _retv.na=1; _retv.xa=2;   
 zzCONSUME;
							}
							else {
								if ( (LA(1)==SHAPE1) ) {
									zzmatch(SHAPE1);
									_retv.func.func=hpfm_shape; _retv.na=1; _retv.xa=1;   
 zzCONSUME;
								}
								else {
									if ( (LA(1)==SUM1) ) {
										zzmatch(SUM1);
										_retv.func.func=hpfm_sum; _retv.na=1; _retv.xa=2;   
 zzCONSUME;
									}
									else {
										if ( (LA(1)==TRANSPOSE1) ) {
											zzmatch(TRANSPOSE1);
											_retv.func.func=hpfm_transpose; _retv.na=1; _retv.xa=2;   
 zzCONSUME;
										}
										else {zzFAIL(1,zzerr20,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
									}
								}
							}
						}
					}
				}
			}
		}
		zzEXIT(zztasp2);
		}
	}
	sprintf (f90func,"%s",zzaArg(zztasp1,2 ).text);   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x4);
	return _retv;
	}
}

struct _rv90
#ifdef __STDC__
function_name2(void)
#else
struct _rv90
function_name2()
#endif
{
	struct _rv90 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	_retv.func.func=unon2_psi;   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==ABS1) ) {
			zzmatch(ABS1); zzCONSUME;
		}
		else {
			if ( (LA(1)==AIMAG1)
 ) {
				zzmatch(AIMAG1); zzCONSUME;
			}
			else {
				if ( (LA(1)==AINT1) ) {
					zzmatch(AINT1); zzCONSUME;
				}
				else {
					if ( (LA(1)==ANINT1) ) {
						zzmatch(ANINT1); zzCONSUME;
					}
					else {
						if ( (LA(1)==CEILING1) ) {
							zzmatch(CEILING1); zzCONSUME;
						}
						else {
							if ( (LA(1)==CMPLX1) ) {
								zzmatch(CMPLX1); zzCONSUME;
							}
							else {
								if ( (LA(1)==CONJG1)
 ) {
									zzmatch(CONJG1); zzCONSUME;
								}
								else {
									if ( (LA(1)==DBLE1) ) {
										zzmatch(DBLE1); zzCONSUME;
									}
									else {
										if ( (LA(1)==DIM1) ) {
											zzmatch(DIM1); zzCONSUME;
										}
										else {
											if ( (LA(1)==DPROD1) ) {
												zzmatch(DPROD1); zzCONSUME;
											}
											else {
												if ( (LA(1)==INT1) ) {
													zzmatch(INT1); zzCONSUME;
												}
												else {
													if ( (LA(1)==FLOOR1)
 ) {
														zzmatch(FLOOR1); zzCONSUME;
													}
													else {
														if ( (LA(1)==MAX1) ) {
															zzmatch(MAX1); zzCONSUME;
														}
														else {
															if ( (LA(1)==MIN1) ) {
																zzmatch(MIN1); zzCONSUME;
															}
															else {
																if ( (LA(1)==MOD1) ) {
																	zzmatch(MOD1); zzCONSUME;
																}
																else {
																	if ( (LA(1)==MODULO1) ) {
																		zzmatch(MODULO1); zzCONSUME;
																	}
																	else {
																		if ( (LA(1)==NINT1)
 ) {
																			zzmatch(NINT1); zzCONSUME;
																		}
																		else {
																			if ( (LA(1)==SIGN1) ) {
																				zzmatch(SIGN1); zzCONSUME;
																			}
																			else {
																				if ( (LA(1)==ACOS1) ) {
																					zzmatch(ACOS1); zzCONSUME;
																				}
																				else {
																					if ( (LA(1)==ASIN1) ) {
																						zzmatch(ASIN1); zzCONSUME;
																					}
																					else {
																						if ( (LA(1)==ATAN1) ) {
																							zzmatch(ATAN1); zzCONSUME;
																						}
																						else {
																							if ( (LA(1)==ATAN21)
 ) {
																								zzmatch(ATAN21); zzCONSUME;
																							}
																							else {
																								if ( (LA(1)==COS1) ) {
																									zzmatch(COS1); zzCONSUME;
																								}
																								else {
																									if ( (LA(1)==COSH1) ) {
																										zzmatch(COSH1); zzCONSUME;
																									}
																									else {
																										if ( (LA(1)==EXP1) ) {
																											zzmatch(EXP1); zzCONSUME;
																										}
																										else {
																											if ( (LA(1)==LOG1) ) {
																												zzmatch(LOG1); zzCONSUME;
																											}
																											else {
																												if ( (LA(1)==LOG101)
 ) {
																													zzmatch(LOG101); zzCONSUME;
																												}
																												else {
																													if ( (LA(1)==SIN1) ) {
																														zzmatch(SIN1); zzCONSUME;
																													}
																													else {
																														if ( (LA(1)==SINH1) ) {
																															zzmatch(SINH1); zzCONSUME;
																														}
																														else {
																															if ( (LA(1)==SQRT1) ) {
																																zzmatch(SQRT1); zzCONSUME;
																															}
																															else {
																																if ( (LA(1)==TAN1) ) {
																																	zzmatch(TAN1); zzCONSUME;
																																}
																																else {
																																	if ( (LA(1)==TANH1)
 ) {
																																		zzmatch(TANH1); zzCONSUME;
																																	}
																																	else {
																																		if ( (LA(1)==ACHAR1) ) {
																																			zzmatch(ACHAR1); zzCONSUME;
																																		}
																																		else {
																																			if ( (LA(1)==ADJUSTL1) ) {
																																				zzmatch(ADJUSTL1); zzCONSUME;
																																			}
																																			else {
																																				if ( (LA(1)==ADJUSTR1) ) {
																																					zzmatch(ADJUSTR1); zzCONSUME;
																																				}
																																				else {
																																					if ( (LA(1)==CHAR1) ) {
																																						zzmatch(CHAR1); zzCONSUME;
																																					}
																																					else {
																																						if ( (LA(1)==IACHAR1)
 ) {
																																							zzmatch(IACHAR1); zzCONSUME;
																																						}
																																						else {
																																							if ( (LA(1)==ICHAR1) ) {
																																								zzmatch(ICHAR1); zzCONSUME;
																																							}
																																							else {
																																								if ( (LA(1)==INDEX1) ) {
																																									zzmatch(INDEX1); zzCONSUME;
																																								}
																																								else {
																																									if ( (LA(1)==LEN_TRIM1) ) {
																																										zzmatch(LEN_TRIM1); zzCONSUME;
																																									}
																																									else {
																																										if ( (LA(1)==LGE1) ) {
																																											zzmatch(LGE1); zzCONSUME;
																																										}
																																										else {
																																											if ( (LA(1)==LGT1)
 ) {
																																												zzmatch(LGT1); zzCONSUME;
																																											}
																																											else {
																																												if ( (LA(1)==LLE1) ) {
																																													zzmatch(LLE1); zzCONSUME;
																																												}
																																												else {
																																													if ( (LA(1)==LLT1) ) {
																																														zzmatch(LLT1); zzCONSUME;
																																													}
																																													else {
																																														if ( (LA(1)==REPEAT1) ) {
																																															zzmatch(REPEAT1); zzCONSUME;
																																														}
																																														else {
																																															if ( (LA(1)==SCAN1) ) {
																																																zzmatch(SCAN1); zzCONSUME;
																																															}
																																															else {
																																																if ( (LA(1)==TRIM1)
 ) {
																																																	zzmatch(TRIM1); zzCONSUME;
																																																}
																																																else {
																																																	if ( (LA(1)==VERIFY1) ) {
																																																		zzmatch(VERIFY1); zzCONSUME;
																																																	}
																																																	else {
																																																		if ( (LA(1)==SELECTED_INT_KIND1) ) {
																																																			zzmatch(SELECTED_INT_KIND1); zzCONSUME;
																																																		}
																																																		else {
																																																			if ( (LA(1)==SELECTED_REAL_KIND1) ) {
																																																				zzmatch(SELECTED_REAL_KIND1); zzCONSUME;
																																																			}
																																																			else {
																																																				if ( (LA(1)==DIGITS1) ) {
																																																					zzmatch(DIGITS1); zzCONSUME;
																																																				}
																																																				else {
																																																					if ( (LA(1)==EPSILON1)
 ) {
																																																						zzmatch(EPSILON1); zzCONSUME;
																																																					}
																																																					else {
																																																						if ( (LA(1)==HUGE1) ) {
																																																							zzmatch(HUGE1); zzCONSUME;
																																																						}
																																																						else {
																																																							if ( (LA(1)==MAXEXPONENT1) ) {
																																																								zzmatch(MAXEXPONENT1); zzCONSUME;
																																																							}
																																																							else {
																																																								if ( (LA(1)==MINEXPONENT1) ) {
																																																									zzmatch(MINEXPONENT1); zzCONSUME;
																																																								}
																																																								else {
																																																									if ( (LA(1)==PRECISION1) ) {
																																																										zzmatch(PRECISION1); zzCONSUME;
																																																									}
																																																									else {
																																																										if ( (LA(1)==RADIX1)
 ) {
																																																											zzmatch(RADIX1); zzCONSUME;
																																																										}
																																																										else {
																																																											if ( (LA(1)==RANGE1) ) {
																																																												zzmatch(RANGE1); zzCONSUME;
																																																											}
																																																											else {
																																																												if ( (LA(1)==TINY1) ) {
																																																													zzmatch(TINY1); zzCONSUME;
																																																												}
																																																												else {
																																																													if ( (LA(1)==EXPONENT1) ) {
																																																														zzmatch(EXPONENT1); zzCONSUME;
																																																													}
																																																													else {
																																																														if ( (LA(1)==FRACTION1) ) {
																																																															zzmatch(FRACTION1); zzCONSUME;
																																																														}
																																																														else {
																																																															if ( (LA(1)==NEAREST1)
 ) {
																																																																zzmatch(NEAREST1); zzCONSUME;
																																																															}
																																																															else {
																																																																if ( (LA(1)==RRSPACING1) ) {
																																																																	zzmatch(RRSPACING1); zzCONSUME;
																																																																}
																																																																else {
																																																																	if ( (LA(1)==SCALE1) ) {
																																																																		zzmatch(SCALE1); zzCONSUME;
																																																																	}
																																																																	else {
																																																																		if ( (LA(1)==SET_EXPONENT1) ) {
																																																																			zzmatch(SET_EXPONENT1); zzCONSUME;
																																																																		}
																																																																		else {
																																																																			if ( (LA(1)==SPACING1) ) {
																																																																				zzmatch(SPACING1); zzCONSUME;
																																																																			}
																																																																			else {
																																																																				if ( (LA(1)==BIT_SIZE1)
 ) {
																																																																					zzmatch(BIT_SIZE1); zzCONSUME;
																																																																				}
																																																																				else {
																																																																					if ( (LA(1)==BTEST1) ) {
																																																																						zzmatch(BTEST1); zzCONSUME;
																																																																					}
																																																																					else {
																																																																						if ( (LA(1)==IAND1) ) {
																																																																							zzmatch(IAND1); zzCONSUME;
																																																																						}
																																																																						else {
																																																																							if ( (LA(1)==IBCLR1) ) {
																																																																								zzmatch(IBCLR1); zzCONSUME;
																																																																							}
																																																																							else {
																																																																								if ( (LA(1)==IBITS1) ) {
																																																																									zzmatch(IBITS1); zzCONSUME;
																																																																								}
																																																																								else {
																																																																									if ( (LA(1)==IBSET1)
 ) {
																																																																										zzmatch(IBSET1); zzCONSUME;
																																																																									}
																																																																									else {
																																																																										if ( (LA(1)==IEOR1) ) {
																																																																											zzmatch(IEOR1); zzCONSUME;
																																																																										}
																																																																										else {
																																																																											if ( (LA(1)==IOR1) ) {
																																																																												zzmatch(IOR1); zzCONSUME;
																																																																											}
																																																																											else {
																																																																												if ( (LA(1)==ISHFT1) ) {
																																																																													zzmatch(ISHFT1); zzCONSUME;
																																																																												}
																																																																												else {
																																																																													if ( (LA(1)==ISHFTC1) ) {
																																																																														zzmatch(ISHFTC1); zzCONSUME;
																																																																													}
																																																																													else {
																																																																														if ( (LA(1)==TRANSFER1)
 ) {
																																																																															zzmatch(TRANSFER1); zzCONSUME;
																																																																														}
																																																																														else {
																																																																															if ( (LA(1)==ALL1) ) {
																																																																																zzmatch(ALL1); zzCONSUME;
																																																																															}
																																																																															else {
																																																																																if ( (LA(1)==ANY1) ) {
																																																																																	zzmatch(ANY1); zzCONSUME;
																																																																																}
																																																																																else {
																																																																																	if ( (LA(1)==COUNT1) ) {
																																																																																		zzmatch(COUNT1); zzCONSUME;
																																																																																	}
																																																																																	else {
																																																																																		if ( (LA(1)==MAXVAL1) ) {
																																																																																			zzmatch(MAXVAL1); zzCONSUME;
																																																																																		}
																																																																																		else {
																																																																																			if ( (LA(1)==MINVAL1)
 ) {
																																																																																				zzmatch(MINVAL1); zzCONSUME;
																																																																																			}
																																																																																			else {
																																																																																				if ( (LA(1)==ALLOCATED1) ) {
																																																																																					zzmatch(ALLOCATED1); zzCONSUME;
																																																																																				}
																																																																																				else {
																																																																																					if ( (LA(1)==LBOUND1) ) {
																																																																																						zzmatch(LBOUND1); zzCONSUME;
																																																																																					}
																																																																																					else {
																																																																																						if ( (LA(1)==UBOUND1) ) {
																																																																																							zzmatch(UBOUND1); zzCONSUME;
																																																																																						}
																																																																																						else {
																																																																																							if ( (LA(1)==MERGE1) ) {
																																																																																								zzmatch(MERGE1); zzCONSUME;
																																																																																							}
																																																																																							else {
																																																																																								if ( (LA(1)==PACK1)
 ) {
																																																																																									zzmatch(PACK1); zzCONSUME;
																																																																																								}
																																																																																								else {
																																																																																									if ( (LA(1)==SPREAD1) ) {
																																																																																										zzmatch(SPREAD1); zzCONSUME;
																																																																																									}
																																																																																									else {
																																																																																										if ( (LA(1)==UNPACK1) ) {
																																																																																											zzmatch(UNPACK1); zzCONSUME;
																																																																																										}
																																																																																										else {
																																																																																											if ( (LA(1)==RESHAPE1) ) {
																																																																																												zzmatch(RESHAPE1); zzCONSUME;
																																																																																											}
																																																																																											else {
																																																																																												if ( (LA(1)==MAXLOC1) ) {
																																																																																													zzmatch(MAXLOC1); zzCONSUME;
																																																																																												}
																																																																																												else {
																																																																																													if ( (LA(1)==MINLOC1)
 ) {
																																																																																														zzmatch(MINLOC1); zzCONSUME;
																																																																																													}
																																																																																													else {
																																																																																														if ( (LA(1)==ASSOCIATED1) ) {
																																																																																															zzmatch(ASSOCIATED1); zzCONSUME;
																																																																																														}
																																																																																														else {
																																																																																															if ( (LA(1)==DATE_AND_TIME1) ) {
																																																																																																zzmatch(DATE_AND_TIME1); zzCONSUME;
																																																																																															}
																																																																																															else {
																																																																																																if ( (LA(1)==SYSTEM_CLOCK1) ) {
																																																																																																	zzmatch(SYSTEM_CLOCK1); zzCONSUME;
																																																																																																}
																																																																																																else {
																																																																																																	if ( (LA(1)==RANDOM_NUMBER1) ) {
																																																																																																		zzmatch(RANDOM_NUMBER1); zzCONSUME;
																																																																																																	}
																																																																																																	else {
																																																																																																		if ( (LA(1)==RANDOM_SEED1)
 ) {
																																																																																																			zzmatch(RANDOM_SEED1); zzCONSUME;
																																																																																																		}
																																																																																																		else {
																																																																																																			if ( (LA(1)==MVBITS1) ) {
																																																																																																				zzmatch(MVBITS1); zzCONSUME;
																																																																																																			}
																																																																																																			else {zzFAIL(1,zzerr21,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
																																																																																																		}
																																																																																																	}
																																																																																																}
																																																																																															}
																																																																																														}
																																																																																													}
																																																																																												}
																																																																																											}
																																																																																										}
																																																																																									}
																																																																																								}
																																																																																							}
																																																																																						}
																																																																																					}
																																																																																				}
																																																																																			}
																																																																																		}
																																																																																	}
																																																																																}
																																																																															}
																																																																														}
																																																																													}
																																																																												}
																																																																											}
																																																																										}
																																																																									}
																																																																								}
																																																																							}
																																																																						}
																																																																					}
																																																																				}
																																																																			}
																																																																		}
																																																																	}
																																																																}
																																																															}
																																																														}
																																																													}
																																																												}
																																																											}
																																																										}
																																																									}
																																																								}
																																																							}
																																																						}
																																																					}
																																																				}
																																																			}
																																																		}
																																																	}
																																																}
																																															}
																																														}
																																													}
																																												}
																																											}
																																										}
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		zzEXIT(zztasp2);
		}
	}
	_retv.na=0; _retv.xa=0;
	sprintf (f90func,"%s",zzaArg(zztasp1,2 ).text);   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x8);
	return _retv;
	}
}

void
#ifdef __STDC__
subroutine_stmt(void)
#else
subroutine_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index;   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==RECURSIVE1) ) {
			zzmatch(RECURSIVE1);
			sprintf(line+strlen(line),"RECURSIVE ");
			if (host) fprintf(hostfile,"RECURSIVE");   
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(SUBROUTINE1);
	sprintf(line+strlen(line),"SUBROUTINE ");
	if (host) fprintf(hostfile,"SUBROUTINE ");   
 zzCONSUME;
	 index  = name();

	if (host) fprintf(hostfile,id_text(index));   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==LEFTPAREN1) ) {
			subroutine_args();
		}
		zzEXIT(zztasp2);
		}
	}
	fprintf(cfile,line); line[0]=0;   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x10);
	}
}

void
#ifdef __STDC__
subroutine_args(void)
#else
subroutine_args()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(LEFTPAREN1);
	sprintf(line+strlen(line),"( ");
	if (host) fprintf(hostfile,"( ");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NAME1) ) {
			dummy_arg_list();
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(RIGHTPAREN1);
	sprintf(line+strlen(line),")\n"); if (host) fprintf(hostfile,")\n");   
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x20);
	}
}

void
#ifdef __STDC__
dummy_arg_list(void)
#else
dummy_arg_list()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	dummy_arg();
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1)
 ) {
			zzmatch(COMMA1);
			sprintf(line+strlen(line),", "); if (host) fprintf(hostfile,", ");   
 zzCONSUME;
			dummy_arg();
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x40);
	}
}

void
#ifdef __STDC__
dummy_arg(void)
#else
dummy_arg()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index; ident_t *ident;  
	 index  = name();

	ident=get_ident();
	SETPARAMETER(ident->flags);
	insert_sym(ident,index);
	if (host) fprintf(hostfile,id_text(index)); 
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd18, 0x80);
	}
}

void
#ifdef __STDC__
end_subroutine_stmt(void)
#else
end_subroutine_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index;   
	zzmatch(END1);
	sprintf(line+strlen(line),"END "); if (host) fprintf(hostfile,"END\n");   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==SUBROUTINE1) && (setwd19[LA(2)]&0x1) && (setwd19[LA(3)]&0x2) && (setwd19[LA(4)]&0x4) && !((LA(1)==1&&((LA(2)==1&&
((LA(3)==1&&(LA(4)==1))))))||((LA(1)==SUBROUTINE1&&((LA(2)==NAME1&&((LA(3)==NAME1&&
(LA(4)==LEFTPAREN1)))))))) ) {
			zzmatch(SUBROUTINE1);
			sprintf(line+strlen(line),"SUBROUTINE ");  
 zzCONSUME;
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==NAME1) ) {
					 index  = name();

				}
				zzEXIT(zztasp3);
				}
			}
		}
		zzEXIT(zztasp2);
		}
	}
	sprintf(line+strlen(line),"\n");
	fprintf(cfile,line);
	line[0]=0;   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd19, 0x8);
	}
}

void
#ifdef __STDC__
specification_part(void)
#else
specification_part()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	{
		zzBLOCK(zztasp2);
		int zzcnt=1;
		zzMake0;
		{
		do {
			declaration_construct();
			zzLOOP(zztasp2);
		} while ( (setwd19[LA(1)]&0x10) );
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd19, 0x20);
	}
}

void
#ifdef __STDC__
declaration_construct(void)
#else
declaration_construct()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (setwd19[LA(1)]&0x40) ) {
		type_declaration_stmt();
	}
	else {
		if ( (LA(1)==330) ) {
			hpf_directive_line();
		}
		else {zzFAIL(1,zzerr22,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd19, 0x80);
	}
}

void
#ifdef __STDC__
type_declaration_stmt(void)
#else
type_declaration_stmt()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident_t *new=get_ident();
	int display;
	new->type=VARIABLE;   
	type_spec( new );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd20[LA(1)]&0x1)
 ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				while ( (LA(1)==COMMA1) ) {
					zzmatch(COMMA1);
					sprintf(line+strlen(line),", ");  
 zzCONSUME;
					attr_spec( new );
					zzLOOP(zztasp3);
				}
				zzEXIT(zztasp3);
				}
			}
			zzmatch(DCOLON1);
			sprintf(line+strlen(line)," :: ");  
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	entity_decl_list( new );
	sprintf(line+strlen(line),"\n");
	if (new->type!=ARRAY) fprintf(cfile,line);
	line[0]=0;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x2);
	}
}

void
#ifdef __STDC__
entity_decl_list( ident_t *ident )
#else
entity_decl_list(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	entity_decl( ident );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1) ) {
			zzmatch(COMMA1);
			sprintf(line+strlen(line),",");  
 zzCONSUME;
			entity_decl( ident );
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x4);
	}
}

void
#ifdef __STDC__
type_spec( ident_t *ident )
#else
type_spec(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==INTEGER1) ) {
		zzmatch(INTEGER1);
		ident->real=FALSE; sprintf(line+strlen(line),"  INTEGER");  
 zzCONSUME;
	}
	else {
		if ( (LA(1)==REAL1) ) {
			zzmatch(REAL1);
			ident->real=TRUE; sprintf(line+strlen(line),"  REAL");  
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr23,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x8);
	}
}

void
#ifdef __STDC__
attr_spec( ident_t *ident )
#else
attr_spec(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident->type=ARRAY;  
	zzmatch(DIMENSION1); zzCONSUME;
	zzmatch(LEFTPAREN1);
	sprintf(line+strlen(line),"DIMENSION(");  
 zzCONSUME;
	array_spec( ident );
	zzmatch(RIGHTPAREN1);
	sprintf(line+strlen(line),")");  
 zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x10);
	}
}

void
#ifdef __STDC__
entity_decl( ident_t *ident )
#else
entity_decl(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index; ident_t *new;  
	 index  = name();

	new=find_sym(index,FALSE);
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
	strcpy(new->string,id_text(index));   
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x20);
	}
}

void
#ifdef __STDC__
array_spec( ident_t *ident )
#else
array_spec(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	explicit_shape_spec_list( ident );
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x40);
	}
}

void
#ifdef __STDC__
explicit_shape_spec_list( ident_t *ident )
#else
explicit_shape_spec_list(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident->array.dim=get_ident();
	ident->array.dim->type=CONSTANT;
	ident->array.dim->real=FALSE;
	ident->array.dim->value=0;   
	explicit_shape_spec( ident );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1)
 ) {
			zzmatch(COMMA1);
			sprintf(line+strlen(line),",");  
 zzCONSUME;
			explicit_shape_spec( ident );
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd20, 0x80);
	}
}

void
#ifdef __STDC__
explicit_shape_spec( ident_t *ident )
#else
explicit_shape_spec(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident_t **shp;
	ident->array.dim->value++;
	shp=(ident_t **) get_mem(ident->array.dim->value*sizeof(ident_t *));
	memcpy(shp,ident->array.shp,
	(ident->array.dim->value-1)*sizeof(ident_t *));
	free(ident->array.shp);
	ident->array.shp=shp;   
	 shp[(int) ident->array.dim->value-1]  = lower_bound();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==COLON1) ) {
			zzmatch(COLON1);
			sprintf(line+strlen(line),":");  
 zzCONSUME;
			upper_bound( shp[(int) ident->array.dim->value-1] );
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x1);
	}
}

 ident_t * 
#ifdef __STDC__
lower_bound(void)
#else
 ident_t * 
lower_bound()
#endif
{
	 ident_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index;   
	if ( (LA(1)==NUMBER1) ) {
		zzmatch(NUMBER1);
		sprintf(line+strlen(line),"%d",atoi(zzaArg(zztasp1,1 ).text));
		_retv=get_ident();
		_retv->type=CONSTANT;
		_retv->real=FALSE;
		_retv->value=atoi(zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	}
	else {
		if ( (LA(1)==NAME1) ) {
			 index  = name();

			_retv=find_sym(index,TRUE);   
		}
		else {zzFAIL(1,zzerr24,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x2);
	return _retv;
	}
}

void
#ifdef __STDC__
upper_bound( ident_t *ident )
#else
upper_bound(ident)
 ident_t *ident ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index;   
	if ( (LA(1)==NUMBER1) ) {
		zzmatch(NUMBER1);
		sprintf(line+strlen(line),"%d",atoi(zzaArg(zztasp1,1 ).text));
		ident->value=atoi(zzaArg(zztasp1,1 ).text)- ident->value+1;   
 zzCONSUME;
	}
	else {
		if ( (LA(1)==NAME1)
 ) {
			 index  = name();

		}
		else {zzFAIL(1,zzerr25,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x4);
	}
}

 int  
#ifdef __STDC__
name(void)
#else
 int  
name()
#endif
{
	 int  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(NAME1);
	_retv=name_id(zzaArg(zztasp1,1 ).text); sprintf(line+strlen(line),"%s ",zzaArg(zztasp1,1 ).text);  
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x8);
	return _retv;
	}
}

 int  
#ifdef __STDC__
quiet_variable(void)
#else
 int  
quiet_variable()
#endif
{
	 int  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(NAME1);
	_retv=name_id(zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x10);
	return _retv;
	}
}

void
#ifdef __STDC__
constant(void)
#else
constant()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==NUMBER1) ) {
		zzmatch(NUMBER1);
		sprintf(line+strlen(line),"%d",atoi(zzaArg(zztasp1,1 ).text));   
 zzCONSUME;
	}
	else {
		if ( (LA(1)==FLOAT1) ) {
			zzmatch(FLOAT1);
			sprintf(line+strlen(line),"%f",atof(zzaArg(zztasp1,1 ).text));   
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr26,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x20);
	}
}

 s_expr_t * 
#ifdef __STDC__
s_constant(void)
#else
 s_expr_t * 
s_constant()
#endif
{
	 s_expr_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int neg=FALSE;   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==MINUS1) ) {
			zzmatch(MINUS1);
			neg=TRUE;  
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(NUMBER1);
	_retv=get_s_expr();
	_retv->ident=get_ident();
	_retv->ident->real=FALSE;
	_retv->ident->type=CONSTANT;
	_retv->ident->value=atoi(zzaArg(zztasp1,2 ).text);
	if (neg) _retv->ident->value*=-1.0;
 zzCONSUME;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x40);
	return _retv;
	}
}

 parser_t * 
#ifdef __STDC__
array_constant(void)
#else
 parser_t * 
array_constant()
#endif
{
	 parser_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident_t *ident; vect_t *v;
	char temp[40];
	ident=get_ident();   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==NUMBER1) ) {
			zzmatch(NUMBER1);
			ident->array.cnst=(double *) get_mem(sizeof(double));
			ident->array.cnst[0]=atoi(zzaArg(zztasp2,1 ).text);
			sprintf (temp, "%s", zzaArg(zztasp2,1 ).text);   
 zzCONSUME;
		}
		else {
			if ( (LA(1)==FLOAT1)
 ) {
				zzmatch(FLOAT1);
				ident->array.cnst=(double *) get_mem(sizeof(double));
				ident->array.cnst[0]=atof(zzaArg(zztasp2,1 ).text);
				sprintf (temp, "%s", zzaArg(zztasp2,1 ).text);   
 zzCONSUME;
			}
			else {zzFAIL(1,zzerr27,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
		zzEXIT(zztasp2);
		}
	}
	ident->type=CONST_ARRAY;
	ident->array.dim=&const1;
	ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	ident->array.shp[0]=&const1;
	_retv=psi_access(ident);
	_retv->psi->ext_str=(char *) get_mem(strlen(temp));
	sprintf (_retv->psi->ext_str,"%s",temp);
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd21, 0x80);
	return _retv;
	}
}

 s_expr_t * 
#ifdef __STDC__
s_expr(void)
#else
 s_expr_t * 
s_expr()
#endif
{
	 s_expr_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	 _retv  = s_constant();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x1);
	return _retv;
	}
}

void
#ifdef __STDC__
hpf_directive_line(void)
#else
hpf_directive_line()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	directive_origin();
	hpf_directive();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x2);
	}
}

void
#ifdef __STDC__
directive_origin(void)
#else
directive_origin()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(330); zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x4);
	}
}

void
#ifdef __STDC__
hpf_directive(void)
#else
hpf_directive()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	specification_directive();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x8);
	}
}

void
#ifdef __STDC__
specification_directive(void)
#else
specification_directive()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==PROCESSORS1) ) {
		processor_directive();
	}
	else {
		if ( (LA(1)==DISTRIBUTE1) ) {
			distribute_directive();
		}
		else {zzFAIL(1,zzerr28,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x10);
	}
}

void
#ifdef __STDC__
distribute_directive(void)
#else
distribute_directive()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident_t *t;   
	zzmatch(DISTRIBUTE1); zzCONSUME;
	 t  = distributee();

	dist_directive_stuff( t );
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x20);
	}
}

void
#ifdef __STDC__
dist_directive_stuff( ident_t *t )
#else
dist_directive_stuff(t)
 ident_t *t ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int global;
	t->array.rule=get_rule(); 
	t->array.rule->ident=t;
	t->array.rule->shp=shp2vect(t);
	t->array.rule->part=NULL;
	t->array.rule->proc=NULL;
	dist_format_clause( &global, t->array.rule );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==ONTO1) ) {
			 t->array.rule->proc  = dist_onto_clause();

		}
		zzEXIT(zztasp2);
		}
	}
	if (global) {
		t->array.rule=NULL;
		SETGLOBAL(t->flags);
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x40);
	}
}

 ident_t * 
#ifdef __STDC__
distributee(void)
#else
 ident_t * 
distributee()
#endif
{
	 ident_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index;   
	 index  = quiet_variable();

	_retv=find_sym(index,TRUE);   
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd22, 0x80);
	return _retv;
	}
}

void
#ifdef __STDC__
dist_format_clause( int *global, rule_t *r )
#else
dist_format_clause(global,r)
 int *global;
rule_t *r ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *v; int cnt;
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
	v->ident->array.rav[0]=red_rav(r->shp,cnt);
	r->part=v;
	zzmatch(LEFTPAREN1); zzCONSUME;
	dist_format( global,r,r->part );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1) ) {
			zzmatch(COMMA1);
			v=new_vect();
			v->ident=get_ident();
			v->ident->type=RAV;
			v->ident->array.dim=&const1;
			v->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
			v->ident->array.shp[0]=&const1;
			v->ident->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
			cnt++;
			v->ident->array.rav[0]=red_rav(r->shp,cnt);
 zzCONSUME;
			dist_format( global,r,v );
			r->part=vect_cat(r->part,v);   
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(RIGHTPAREN1); zzCONSUME;
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x1);
	}
}

void
#ifdef __STDC__
dist_format( int *global, rule_t *r, vect_t *v )
#else
dist_format(global,r,v)
 int *global;
rule_t *r;
vect_t *v ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	if ( (LA(1)==BLOCK1)
 ) {
		zzmatch(BLOCK1); zzCONSUME;
		{
			zzBLOCK(zztasp2);
			zzMake0;
			{
			if ( (LA(1)==LEFTPAREN1) ) {
				zzmatch(LEFTPAREN1); zzCONSUME;
				 v->ident->array.rav[0]  = s_expr();

				zzmatch(RIGHTPAREN1); zzCONSUME;
			}
			zzEXIT(zztasp2);
			}
		}
		*global=FALSE;   
	}
	else {
		if ( (LA(1)==CYCLIC1) ) {
			zzmatch(CYCLIC1); zzCONSUME;
			{
				zzBLOCK(zztasp2);
				zzMake0;
				{
				if ( (LA(1)==LEFTPAREN1) ) {
					zzmatch(LEFTPAREN1); zzCONSUME;
					 v->ident->array.rav[0]  = s_expr();

					zzmatch(RIGHTPAREN1); zzCONSUME;
				}
				zzEXIT(zztasp2);
				}
			}
			r->type=CYCLIC; *global=FALSE;   
		}
		else {
			if ( (LA(1)==TIMES1) ) {
				zzmatch(TIMES1);
				r->type=DEFAULT_RULE; *global=FALSE;   
 zzCONSUME;
			}
			else {zzFAIL(1,zzerr29,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x2);
	}
}

 vect_t * 
#ifdef __STDC__
dist_onto_clause(void)
#else
 vect_t * 
dist_onto_clause()
#endif
{
	 vect_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(ONTO1); zzCONSUME;
	 _retv  = dist_target();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x4);
	return _retv;
	}
}

 vect_t * 
#ifdef __STDC__
dist_target(void)
#else
 vect_t * 
dist_target()
#endif
{
	 vect_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index; ident_t *p;  
	 index  = quiet_variable();

	p=find_sym(index,TRUE); 
	_retv=p->proc;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x8);
	return _retv;
	}
}

void
#ifdef __STDC__
processor_directive(void)
#else
processor_directive()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzmatch(PROCESSORS1); zzCONSUME;
	processor_decl();
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x10);
	}
}

void
#ifdef __STDC__
processor_decl(void)
#else
processor_decl()
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int index; ident_t *p;   
	 index  = processor_name();

	p=get_ident();
	p->type=PROCESSOR;
	p->proc=NULL;
	insert_sym(p,index);
	strcpy(p->string,id_text(index));
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==LEFTPAREN1)
 ) {
			zzmatch(LEFTPAREN1); zzCONSUME;
			 p->proc  = hpf_shape_spec_list();

			zzmatch(RIGHTPAREN1); zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	if (strcmp(p->string,"network")==0) {
		n_procs=p->proc->ident->array.rav[0]->ident->value; 
		sprintf(arch_module,"MPINET"); 
	}
	zzEXIT(zztasp1);
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x20);
	}
}

 int  
#ifdef __STDC__
processor_name(void)
#else
 int  
processor_name()
#endif
{
	 int  	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	 _retv  = quiet_variable();

	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x40);
	return _retv;
	}
}

 vect_t * 
#ifdef __STDC__
hpf_shape_spec(void)
#else
 vect_t * 
hpf_shape_spec()
#endif
{
	 vect_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	ident_t *i; s_expr_t *s;   
	 s  = s_expr();

	_retv=new_vect();
	_retv->shp = &s_const1;
	i=get_ident();
	_retv->ident=i;
	i->type=RAV;
	i->array.dim=&const1;
	i->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
	i->array.shp[0]=&const1;
	i->array.rav=(s_expr_t **) get_mem(sizeof(s_expr_t *));
	i->array.rav[0]=s;
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd23, 0x80);
	return _retv;
	}
}

 vect_t * 
#ifdef __STDC__
hpf_shape_spec_list(void)
#else
 vect_t * 
hpf_shape_spec_list()
#endif
{
	 vect_t * 	 _retv;
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	vect_t *tmp;   
	 _retv  = hpf_shape_spec();

	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==COMMA1) ) {
			zzmatch(COMMA1); zzCONSUME;
			 tmp  = hpf_shape_spec();

			_retv=vect_cat(_retv,tmp);   
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	return _retv;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd24, 0x1);
	return _retv;
	}
}
