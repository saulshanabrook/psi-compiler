/* output.c - the module contains routines that print an array expression */

#include <stdio.h>
#include "psi.h"
#include "sys.h"

#include "code.e"
#include "ident.e"
#include "vect.e"
#include "psi.e"
#include "sys.e"
#define DEBUG DEBUG
#include "rambam.h"

extern int prove, generic;

/* print an identifer */

print_gen_ident(ident_t *ident)
{
  int i,type;

  if (ident->type==EMBEDED_ARRAY) {
    type=(ident->array.cnst==NULL) ? RAV : CONST_ARRAY;
  } else type=ident->type;

  switch (ident->type) {
  case CONSTANT:
  q1("case CONSTANT:");
    fprintf(rfile,"<%d>",(int) ident->value); fflush(rfile);
    break;
  case VARIABLE:
  q1("case VARIABLE:");
  case ARRAY:
  q1("case ARRAY:");
    fprintf(rfile,"%s[]",ident->string); fflush(rfile);
    break;
  case CONST_ARRAY:
  q1("case CONST_ARRAY:");
    fprintf(rfile,"<"); fflush(rfile);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      fprintf(rfile,"%d ",(int) ident->array.cnst[i]); fflush(rfile);
    }
    fprintf(rfile,"\b>"); fflush(rfile);
    break;
  case IOTA:
  q1("case IOTA:");
    fprintf(rfile,"<"); fflush(rfile);
q2("ident = x%lx",ident);
qident("ident",ident);
q2("ident->array = x%lx",ident->array);
q2("ident->array.shp = x%lx",ident->array.shp);
q2("ident->array.shp[0] = x%lx",ident->array.shp[0]);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      fprintf(rfile,"%d ",i); fflush(rfile);
    }
q1(" ");
    fprintf(rfile,"\b>"); fflush(rfile);
    break;
  case RAV:
  q1("case RAV:");
    fprintf(rfile,"<"); fflush(rfile);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      print_s(rfile,ident->array.rav[i]);
      fprintf(rfile," "); fflush(rfile);
    }
    fprintf(rfile,"\b>"); fflush(rfile);
    break;
  }
}

/* print a vector */
print_vector(vect_t *vect)
{
  int i;
  if (vect==NULL) return;

  if ((vect->op!=NOP)&&(vect->op!=ABS)&&(vect->op!=SKIP)&&
      (vect->op!=MIN)&&(vect->op!=MAX))
    fprintf(rfile,"("); fflush(rfile);

  switch (vect->op) {
  case NOP:
    if (static_shps(vect)) {
      if (vect->shp->ident->value>0) {
	fprintf(rfile,"<"); fflush(rfile);
	for (i=0; i<vect->shp->ident->value-1; i++) {
	  print_rav(rfile,vect,i);
	  fprintf(rfile," "); fflush(rfile);
	}
	print_rav(rfile,vect,vect->shp->ident->value-1);
	fprintf(rfile,">"); fflush(rfile);
      } else fprintf(rfile,"<>"); fflush(rfile);
    } else {
      if (!SCALAR(vect->index)||(vect->index->ident->value>0)) {
	fprintf(rfile,"("); fflush(rfile);
	print_s(rfile,vect->index);
	fprintf(rfile," Tk "); fflush(rfile);
	print_gen_ident(vect->ident);
	fprintf(rfile,")"); fflush(rfile);
      } else print_gen_ident(vect->ident);
    }
    break;
  case ABS:
    fprintf(rfile,"abs("); fflush(rfile);
    print_vector(vect->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case IF_NEG:
    fprintf(rfile,"0>"); fflush(rfile);
    print_vector(vect->left);
    break;
  case IF_POS:
    fprintf(rfile,"0<"); fflush(rfile);
    print_vector(vect->left);
    break;
  case DIVIDE:
  case TIMES:
  case MINUS:
  case PLUS:
    print_vector(vect->left);
    print_op(rfile,vect->op);
    print_vector(vect->right);
    break;
  case SKIP:
    print_vector(vect->left);
    print_vector(vect->right);
    break;
  case MIN:
    fprintf(rfile,"min("); fflush(rfile);
    print_vector(vect->left);
    fprintf(rfile,","); fflush(rfile);
    print_vector(vect->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case MAX:
    fprintf(rfile,"max("); fflush(rfile);
    print_vector(vect->left);
    fprintf(rfile,","); fflush(rfile);
    print_vector(vect->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case CAT:
    print_vector(vect->left);
    fprintf(rfile,"++"); fflush(rfile);
    print_vector(vect->right);
    break;
  default:
    fatal("Internal error: print_vector -- unknown operator");
  }
    
  if ((vect->op!=NOP)&&(vect->op!=ABS)&&(vect->op!=SKIP)&&
      (vect->op!=MIN)&&(vect->op!=MAX))
    fprintf(rfile,")"); fflush(rfile);
}


/* print an array expression */

rec_print_expr(expr_t *expr)
{
  if (expr==NULL) {
    fprintf(rfile,"NULL"); fflush(rfile);
    return;
  }
  switch (expr->op) {
  case NOP:
  q1("case NOP:");
    if (expr->ident == NULL)		{
    q1("expr->ident == NULL)");
					}
    else				{
    print_gen_ident(expr->ident);
					}
    break;
  case PLUS:
  q1("case PLUS:");
  case MINUS:
  q1("case MINUS:");
  case TIMES:
  q1("case TIMES:");
  case DIVIDE:
  q1("case DIVIDE");
    fprintf(rfile,"("); fflush(rfile);
    rec_print_expr(expr->left);
    print_op(rfile,expr->op);
    rec_print_expr(expr->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case SCALAR_EXTEND:
  q1("case SCALAR_EXTEND");
    rec_print_expr(expr->left);
    break;
  case FORALL:
  q1("case FORALL");
    fprintf(rfile,"\n"); fflush(rfile);
    do_ptab(1);
    fprintf(rfile,"forall (%s in ",expr->forall->fa->string); fflush(rfile);
    print_vector(expr->forall->bound);
    fprintf(rfile,") {\n"); fflush(rfile);
    do_ptab(2);
    rec_print_expr(expr->left);
    fprintf(rfile,"\n"); fflush(rfile);
    do_ptab(1);
    fprintf(rfile,"}"); fflush(rfile);
    break;
  case PTAKE:
  q1("case PTAKE");
  case TAKE:
  q1("case TAKE");
    fprintf(rfile,"("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile," Tk "); fflush(rfile);
    rec_print_expr(expr->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case DROP:
  q1("case DROP");
  case PDROP:
  q1("case DROP");
  q1("case PDROP");
    fprintf(rfile,"("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile," Dr "); fflush(rfile);
    rec_print_expr(expr->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case TIMES_RED:
  q1("case TIMES_RED");
    fprintf(rfile,"*red("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case DIVIDE_RED:
  q1("case DIVIDE_RED");
    fprintf(rfile,"/red("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case MINUS_RED:
  q1("case MINUS_RED");
    fprintf(rfile,"-red("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case PLUS_RED:
  q1("case PLUS_RED");
    fprintf(rfile,"+red("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case RAVEL:
  q1("case RAVEL");
    fprintf(rfile,"rav("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case PSI:
  q1("case PSI");
    fprintf(rfile,"("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile," Psi "); fflush(rfile);
    rec_print_expr(expr->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  case CAT:
  q1("case CAT");
    fprintf(rfile,"("); fflush(rfile);
    rec_print_expr(expr->left);
    fprintf(rfile,"++"); fflush(rfile);
    rec_print_expr(expr->right);
    fprintf(rfile,")"); fflush(rfile);
    break;
  default:
    fatal("Internal error: rec_print_expr");
  }
}


/* print the left and right side of an assigment */

print_expr(int bottom,expr_t *expr, expr_t *result, char *op)
{
  int d,s,old_int_state;
  vect_t *pad1,*r_bound;

  if (prove||(generic&&bottom)) {
    if (prove) {
      fprintf(rfile,"#"); fflush(rfile);
      q1("#");
    }
    q1("About to do do_ptab(0)");
    do_ptab(0);
    q1("After do_ptab(0)");

    old_int_state=int_expr;
	q1(" ");
    int_expr=FALSE;
	q1(" ");
    if (expr == NULL)                        {
      q1("expr is NULL\n");
      fprintf(rfile,"expr is NULL\n"); fflush(rfile);
					     }
    else                                                  {
	q1(" ");
    if ((expr->bound) == NULL)                        {
      q1("expr->bound is NULL\n");
      fprintf(rfile,"expr->bound is NULL\n"); fflush(rfile);
						      }
    else						{
    if ((expr->bound->op==NOP)&&(empty(expr->bound))) {
	q1(" ");
      fprintf(rfile,"empty expression\n"); fflush(rfile);
    } else {
	q1(" ");
      if (!SCALAR(result->dim)||!SCALAR(expr->bound->shp)) {
	q1(" ");
	fatal("Internal error in print_expr");
      }

      /* adjust bound to fit the dimension of the result */
	q1(" ");
      d=result->dim->ident->value;
	q1(" ");
      s=expr->bound->shp->ident->value;
	q1(" ");
      if (d>s) {
	q1(" ");
	pad1=get_vect();
	q1(" ");
	*pad1=one_vec;
	q1(" ");
	pad1->shp=s_op(MINUS,result->dim,expr->bound->shp);
	q1(" ");
	r_bound=vect_cat(pad1,expr->bound);
	q1(" ");
      } else if (d<s) {
	q1(" ");
	r_bound=vect_drop(s_vect(s_op(MINUS,expr->bound->shp,result->dim)),
			  expr->bound);
	q1(" ");
      } else r_bound=expr->bound;
      
	q1(" ");
      print_vector(r_bound);
	q1(" ");
      if (expr == NULL)				{
	q1("expr is NULL");
						}
q1(" ");
      fprintf(rfile," take ("); fflush(rfile);
q1(" ");
      print_vector(expr->loc);
q1(" ");
      fprintf(rfile," drop "); fflush(rfile);
q1(" ");
      rec_print_expr(result);
q1(" ");
      fprintf(rfile,")"); fflush(rfile);
q1(" ");
      
q1(" ");
      fprintf(rfile,op); fflush(rfile);
q1(" ");
      print_vector(expr->bound);
q1(" ");
      fprintf(rfile," take ("); fflush(rfile);
q1(" ");
      print_vector(expr->index);
q1(" ");
      fprintf(rfile," drop "); fflush(rfile);
q2("expr = x%lx",expr);
      rec_print_expr(expr);
q1(" ");
      fprintf(rfile,") stride="); fflush(rfile);
q1(" ");
      print_vector(expr->stride);
q1(" ");
      fprintf(rfile,"\n"); fflush(rfile);
q1(" ");
    }
                  }       }
    int_expr=old_int_state;
  }
}
