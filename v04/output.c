/* output.c - the module contains routines that print an array expression */

#include <stdio.h>
#include "psi.h"
#include "sys.h"

#include "code.e"
#include "ident.e"
#include "vect.e"
#include "psi.e"
#include "sys.e"

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
    fprintf(rfile,"<%d>",(int) ident->value);
    break;
  case VARIABLE:
  case ARRAY:
    fprintf(rfile,"%s[]",ident->string);
    break;
  case CONST_ARRAY:
    fprintf(rfile,"<");
    for (i=0; i<ident->array.shp[0]->value; i++) {
      fprintf(rfile,"%d ",(int) ident->array.cnst[i]);
    }
    fprintf(rfile,"\b>");
    break;
  case IOTA:
    fprintf(rfile,"<");
    for (i=0; i<ident->array.shp[0]->value; i++) {
      fprintf(rfile,"%d ",i);
    }
    fprintf(rfile,"\b>");
    break;
  case RAV:
    fprintf(rfile,"<");
    for (i=0; i<ident->array.shp[0]->value; i++) {
      print_s(rfile,ident->array.rav[i]);
      fprintf(rfile," ");
    }
    fprintf(rfile,"\b>");
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
    fprintf(rfile,"(");

  switch (vect->op) {
  case NOP:
    if (static_shps(vect)) {
      if (vect->shp->ident->value>0) {
	fprintf(rfile,"<");
	for (i=0; i<vect->shp->ident->value-1; i++) {
	  print_rav(rfile,vect,i);
	  fprintf(rfile," ");
	}
	print_rav(rfile,vect,vect->shp->ident->value-1);
	fprintf(rfile,">");
      } else fprintf(rfile,"<>");
    } else {
      if (!SCALAR(vect->index)||(vect->index->ident->value>0)) {
	fprintf(rfile,"(");
	print_s(rfile,vect->index);
	fprintf(rfile," Tk ");
	print_gen_ident(vect->ident);
	fprintf(rfile,")");
      } else print_gen_ident(vect->ident);
    }
    break;
  case ABS:
    fprintf(rfile,"abs(");
    print_vector(vect->left);
    fprintf(rfile,")");
    break;
  case IF_NEG:
    fprintf(rfile,"0>");
    print_vector(vect->left);
    break;
  case IF_POS:
    fprintf(rfile,"0<");
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
    fprintf(rfile,"min(");
    print_vector(vect->left);
    fprintf(rfile,",");
    print_vector(vect->right);
    fprintf(rfile,")");
    break;
  case MAX:
    fprintf(rfile,"max(");
    print_vector(vect->left);
    fprintf(rfile,",");
    print_vector(vect->right);
    fprintf(rfile,")");
    break;
  case CAT:
    print_vector(vect->left);
    fprintf(rfile,"++");
    print_vector(vect->right);
    break;
  default:
    fatal("Internal error: print_vector -- unknown operator");
  }
    
  if ((vect->op!=NOP)&&(vect->op!=ABS)&&(vect->op!=SKIP)&&
      (vect->op!=MIN)&&(vect->op!=MAX))
    fprintf(rfile,")");
}


/* print an array expression */

rec_print_expr(expr_t *expr)
{
  if (expr==NULL) {
    fprintf(rfile,"NULL");
    return;
  }
  switch (expr->op) {
  case NOP:
    print_gen_ident(expr->ident);
    break;
  case PLUS:
  case MINUS:
  case TIMES:
  case DIVIDE:
    fprintf(rfile,"(");
    rec_print_expr(expr->left);
    print_op(rfile,expr->op);
    rec_print_expr(expr->right);
    fprintf(rfile,")");
    break;
  case SCALAR_EXTEND:
    rec_print_expr(expr->left);
    break;
  case FORALL:
    fprintf(rfile,"\n");
    do_ptab(1);
    fprintf(rfile,"forall (%s in ",expr->forall->fa->string);
    print_vector(expr->forall->bound);
    fprintf(rfile,") {\n");
    do_ptab(2);
    rec_print_expr(expr->left);
    fprintf(rfile,"\n");
    do_ptab(1);
    fprintf(rfile,"}");
    break;
  case PTAKE:
  case TAKE:
    fprintf(rfile,"(");
    rec_print_expr(expr->left);
    fprintf(rfile," Tk ");
    rec_print_expr(expr->right);
    fprintf(rfile,")");
    break;
  case DROP:
  case PDROP:
    fprintf(rfile,"(");
    rec_print_expr(expr->left);
    fprintf(rfile," Dr ");
    rec_print_expr(expr->right);
    fprintf(rfile,")");
    break;
  case TIMES_RED:
    fprintf(rfile,"*red(");
    rec_print_expr(expr->left);
    fprintf(rfile,")");
    break;
  case DIVIDE_RED:
    fprintf(rfile,"/red(");
    rec_print_expr(expr->left);
    fprintf(rfile,")");
    break;
  case MINUS_RED:
    fprintf(rfile,"-red(");
    rec_print_expr(expr->left);
    fprintf(rfile,")");
    break;
  case PLUS_RED:
    fprintf(rfile,"+red(");
    rec_print_expr(expr->left);
    fprintf(rfile,")");
    break;
  case RAVEL:
    fprintf(rfile,"rav(");
    rec_print_expr(expr->left);
    fprintf(rfile,")");
    break;
  case PSI:
    fprintf(rfile,"(");
    rec_print_expr(expr->left);
    fprintf(rfile," Psi ");
    rec_print_expr(expr->right);
    fprintf(rfile,")");
    break;
  case CAT:
    fprintf(rfile,"(");
    rec_print_expr(expr->left);
    fprintf(rfile,"++");
    rec_print_expr(expr->right);
    fprintf(rfile,")");
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
      fprintf(rfile,"#");
    }
    do_ptab(0);

    old_int_state=int_expr;
    int_expr=FALSE;
    if ((expr->bound->op==NOP)&&(empty(expr->bound))) {
      fprintf(rfile,"empty expression\n");
    } else {
      if (!SCALAR(result->dim)||!SCALAR(expr->bound->shp)) {
	fatal("Internal error in print_expr");
      }

      /* adjust bound to fit the dimension of the result */
      d=result->dim->ident->value;
      s=expr->bound->shp->ident->value;
      if (d>s) {
	pad1=get_vect();
	*pad1=one_vec;
	pad1->shp=s_op(MINUS,result->dim,expr->bound->shp);
	r_bound=vect_cat(pad1,expr->bound);
      } else if (d<s) {
	r_bound=vect_drop(s_vect(s_op(MINUS,expr->bound->shp,result->dim)),
			  expr->bound);
      } else r_bound=expr->bound;
      
      print_vector(r_bound);
      fprintf(rfile," take (");
      print_vector(expr->loc);
      fprintf(rfile," drop ");
      rec_print_expr(result);
      fprintf(rfile,")");
      
      fprintf(rfile,op);
      print_vector(expr->bound);
      fprintf(rfile," take (");
      print_vector(expr->index);
      fprintf(rfile," drop ");
      rec_print_expr(expr);
      fprintf(rfile,") stride=");
      print_vector(expr->stride);
      fprintf(rfile,"\n");
    }
    int_expr=old_int_state;
  }
}
