/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   v0.0 Scott Thibault - 5/93
   v0.1 Scott Thibault - 6/93
   v0.2 Scott Thibault - 7/93
   v0.3 Scott Thibault - 8/93
               Moved code generation to code.c
	       Restructured to return a list of assignments as the result of
	         the reduction.
	Scott Thibault - 10/93
	    The combine_reduced function was added and psi_reduce now
	    returns the result of combine_reduced.

*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h>
#include "psi.h"
#include "sys.h"

#include "ident.e"
#include "vect.e"
#include "moa_func.e"
#include "sys.e"

extern int prove,generic;  /* prove is true if a list of reductions should be
			      output.  generic is true if the reduced generic 
			      expressions should be output. */

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define NONASSOCIATIVE(op) ((*op=='/')||(*op=='-'))

/* prototypes */

extern void reduce_extended(expr_t *expr, expr_t *result, int top, char *op,
  int inright);
expr_t *assign(expr_t *, expr_t *, int, char *, int);

int clean;
int temp_array_num=0;
int expr_num=0;
ident_t const0,const1;        /* convient constants */
s_expr_t s_const0,s_const1;
vect_t zero_vec,one_vec,neg_one_vec,empty_vec;
vect_t pad_one,pad_zero;
                              /* recursive block_rav needs these values */
expr_t *block_result,*block_expr; 
expr_t buffer;
char *block_op;               /* they're put here to avoid having to push */
int block_top,block_inright;  /* them for each recursive call */
vect_t *block_loc;
reduced_t *reduced;        /* the resulting reduced expression */
                           /* this is used globally in order to add */
                           /* allocations required from shape analysis */


/* is_recursive - returns true if expr refers to the result */

int is_recursive(expr_t *expr, ident_t *result, int in_left)

{
  int next_in_left;
  int ret;

  if (expr==NULL) ret=FALSE;
  else {
    if (expr->op==NOP) {
      ret=(in_left) ? FALSE : (expr->ident==result);
    } else {
      next_in_left=!((expr->op==PLUS)||(expr->op==MINUS)||(expr->op==TIMES)||
		    (expr->op==DIVIDE));
      ret=is_recursive(expr->left,result,in_left)||
	is_recursive(expr->right,result,next_in_left);
    }
  }

  return(ret);
}
  

/* reverse_list - reverses a linked list of reduced_t type */

reduced_t *reverse_list(reduced_t *list)

{
  reduced_t *ret,*node;

  node=list;
  ret=NULL;
  while (node!=NULL) {
    if (node->type==FORALL) {
      node->d.list=reverse_list(node->d.list);
    }
    list=list->next;
    node->next=ret;
    ret=node;
    node=list;
  }

  return(ret);
}


/* add_allocation - a an allocation to the list of reduced expressions */

add_allocation(expr_t *expr)

{
  reduced_t *node;

  node=get_reduced();
  node->type=ALLOCATE;
  node->d.frag=copy_expr(expr);
  node->next=reduced;
  reduced=node;
}


/* add_reduced - a an assignment to the list of reduced expressions */

addto_reduced(expr_t *expr, expr_t *result, char *op)

{
  reduced_t *node;

  if (ISALLOC(expr->flags)) {
    add_allocation(expr);
    UNSETALLOC(expr->flags);
    SETUSED(expr->ident->flags);  /* so it does'nt get allocated in code.c */
  }
  if ((result!=NULL)&&ISALLOC(result->flags)) {
    add_allocation(result);
    SETUSED(result->ident->flags);  /* so it does'nt get allocated in code.c */
  }

  node=get_reduced();
  node->type=NOP;
  node->d.frag=copy_expr(expr);
  node->d.frag->op=NOP;
  node->d.frag->func=op;
  node->d.frag->left=result;
  node->next=reduced;
  reduced=node;
}


/* empty - return TRUE if the vector vect contains a zero element or no 
     elements.  This is used to detect empty assignments by checking if
     the shape of the assignment is empty. */

int empty(vect_t *vect)

{
  int i,ret;
  ret=FALSE;
  
  if (vect->op!=NOP)
    return(FALSE);

  if (vect->ident->type==CONST_ARRAY) {
    for (i=0; i<vect->ident->array.shp[0]->value; i++)
      if (vect->ident->array.cnst[i]==0) ret=TRUE;
  }
  if (vect->ident->type==RAV) {
    for (i=0; i<vect->ident->array.shp[0]->value; i++) {
      if (SCALAR(vect->ident->array.rav[i]))
	if (vect->ident->array.rav[i]->ident->value==0)
	  ret=TRUE;
    }
  }

  return(ret);
}


/* dup_expr - makes a copy of an entire expression */

expr_t *dup_expr(expr_t *expr)

{
  expr_t *ret;

  if (expr==NULL) return(NULL);
  else {
    ret=get_expr_mem(1);
    *ret=*expr;
    ret->left=dup_expr(expr->left);
    ret->right=dup_expr(expr->right);
    
    return(ret);
  }
}


/* block_rav - since rav can create access to a non-rectangular region of
     an array, block_rav breaks that region up into rectangular pieces. */

block_rav(s_expr_t *i, s_expr_t *b, vect_t *s, vect_t *bound, vect_t *index,
	  s_expr_t *loc)

{
  int j;
  s_expr_t *p,*e;
  s_expr_t *to,*ti,*ts,*tl;
  s_expr_t *bs,*bo,*bl;
  s_expr_t *ho,*hi,*hs,*hl;
  vect_t *pad0,*g_bound,*g_index;
  expr_t *gen;

  if (SCALAR(s->shp)) {
    if ((!SCALAR(b))||(b->ident->value>0)) {
      p=&s_const1;
      for (j=0; j<s->shp->ident->value; j++) {
	p=s_op(TIMES,p,red_rav(s,j));
      }
      
      e=s_op(PLUS,b,i);
      to=s_op(DIVIDE,e,p);
      ti=&s_const0;
      ts=s_op(MINUS,e,s_op(TIMES,to,p));
      bs=s_op(DIVIDE,s_op(MINUS,b,ts),p);
      ho=s_op(DIVIDE,i,p);
      hi=s_op(MINUS,i,s_op(TIMES,ho,p));
      hs=s_op(MINUS,b,s_op(PLUS,ts,s_op(TIMES,bs,p)));
      bo=s_op(DIVIDE,s_op(PLUS,i,hs),p);
      hl=loc;
      bl=s_op(PLUS,hl,hs);
      tl=s_op(PLUS,bl,s_op(TIMES,bs,p));

      g_bound=vect_cat(vect_cat(bound,s_vect(bs)),s);
      if (!empty(g_bound)) {
	gen=dup_expr(block_expr);
	pad0=get_vect();
	pad0->shp=s->shp;
	pad0->loc=&s_const0;
	pad0->index=&s_const0;
	pad0->ident=&const0;
	gen->index=vect_cat(vect_cat(index,s_vect(bo)),pad0);
	gen->bound=g_bound;
	gen->loc=vect_cat(block_loc,s_vect(bl));
	assign(gen,block_result,block_top,block_op,block_inright);
      }

      s=vect_drop(&one_vec,s);
      bound=vect_cat(bound,&one_vec);
      block_rav(hi,hs,s,bound,vect_cat(index,s_vect(ho)),hl);
      block_rav(ti,ts,s,bound,vect_cat(index,s_vect(to)),tl);
    }
  } else {
    fatal("non-scalar shape caught in block_rav");
  }
}


/* assign_rav - reduce a rav to a collection of rectangular operations.
     Calls block_rav above. */

assign_rav(expr_t *rav, expr_t *expr, expr_t *result, 
	  int top, char *op, int inright)

{
  s_expr_t *i,*b;
  vect_t *s,*adj;

  if (SCALAR(expr->dim)) {
    block_expr=expr;
    block_result=result;
    adj=s_vect(s_op(MINUS,result->dim,&s_const1));
    block_loc=vect_take(adj,rav->loc);
    block_top=top;
    block_op=op;
    block_inright=inright;
    i=make_s_expr(rav->index);
    b=make_s_expr(rav->bound);
    s=vect_drop(&one_vec,expr->shp);
    block_rav(i,b,s,&empty_vec,&empty_vec,
	      make_s_expr(vect_drop(adj,rav->loc)));
  } else {
    fatal("Red rav doesn't know the dimension");
  }
}


/* red_scalar_extend - the reduction rule for scalar extension (i.e. an
     operations between an array and scalar). */

expr_t *red_scalar_extend(expr_t *expr)

{
  vect_t *vtmp;
  s_expr_t *stmp;

  /* forcing the scalar expression to be assigned to a scalar identifier
     will cause code generation to use the scalar be with repeatition */
  vtmp=make_vect(expr->left);
  stmp=make_s_expr(vtmp);
  expr->ident=make_ident(stmp);
  expr->op=NOP;
  expr->left=NULL;
 
  return(expr);
}


/* red_take - the reduction rule for take */

red_take(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(TIMES,vect_op(PLUS,v,vect_take(arg1->shp,arg2->shp)),
		vect_unop(IF_NEG,v));
  index=vect_op(PLUS,index,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
    
}


/* red_pdrop - the reduction rule for pdrop */

red_pdrop(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(PLUS,v,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
    
}


/* red_ptake - the reduction rule for ptake */

red_ptake(expr_t *arg1, expr_t *arg2)

{
  /* this is not missing; there is nothing to do */
}


/* red_drop - the reduction rule for drop */

red_drop(expr_t *arg1, expr_t *arg2)

{
  vect_t *index,*v;

  v=make_vect(arg1);
  index=vect_op(TIMES,v,vect_unop(IF_POS,v));
  index=vect_op(PLUS,index,vect_take(arg1->shp,arg2->index));
  arg2->index=vect_cat(index,vect_drop(arg1->shp,arg2->index));
}


/* red_reverse - the reduction rule for reverse */

red_reverse(expr_t *arg2)

{
  vect_t *index,*stride;

  index=vect_op(MINUS,vect_take(&one_vec,arg2->shp),
    vect_op(PLUS,vect_take(&one_vec,arg2->index),&one_vec));
  arg2->index=vect_cat(index,vect_drop(&one_vec,arg2->index));
  stride=vect_op(TIMES,&neg_one_vec,vect_take(&one_vec,arg2->stride));
  arg2->stride=vect_cat(stride,vect_drop(&one_vec,arg2->stride));
}


/* red_psi - the reduction rule for psi */

expr_t *red_psi(expr_t *arg1, expr_t *arg2, s_expr_t *r_dim)

{
  vect_t *index,*pad1,*len,*size;
  
  /* make the bound 1 for all dimensions that have been indexed */
  pad1=get_vect();
  pad1->index=&s_const0;
  pad1->loc=&s_const0;
  pad1->shp=make_s_expr(arg1->shp);
  pad1->ident=&const1;
  size=s_vect(arg2->dim);
  arg2->bound=vect_take(size,vect_cat(pad1,arg2->bound));
  arg2->index=vect_take(size,vect_cat(make_vect(arg1),arg2->index));
  arg2->stride=vect_take(size,vect_cat(pad1,arg2->stride));

  return(arg2);
}


/* red_cat - the reduction rule for cat */

red_cat(expr_t *arg1, expr_t *arg2)

{
  vect_t *tmp,*tmp2,*adj;
  vect_t *index,*bound,*shp,*index2;

  index=vect_take(&one_vec,arg1->index);
  bound=vect_take(&one_vec,arg1->bound);
  shp=vect_take(&one_vec,arg1->shp);

  index=vect_op(MIN,index,shp);
  arg1->index=vect_cat(index,vect_drop(&one_vec,arg1->index));

  bound=vect_op(MIN,bound,vect_op(MINUS,shp,index));
  arg1->bound=vect_cat(bound,vect_drop(&one_vec,arg1->bound));

  index2=vect_take(&one_vec,arg2->index);
  index2=vect_op(MINUS,index2,index);
  arg2->index=vect_cat(index2,vect_drop(&one_vec,arg2->index));

  tmp=vect_op(MINUS,vect_take(&one_vec,arg2->bound),
	      vect_take(&one_vec,arg1->bound));
  arg2->bound=vect_cat(tmp,vect_drop(&one_vec,arg2->bound));
  
  tmp=s_vect(s_op(MIN,arg2->dim,arg2->loc->shp));
  adj=vect_op(MINUS,vect_len(arg2->loc),tmp);
  tmp2=vect_drop(adj,arg2->loc);
  tmp=vect_op(PLUS,vect_take(&one_vec,tmp2),vect_take(&one_vec,arg1->bound));
  tmp=vect_cat(vect_take(adj,arg2->loc),tmp);
  arg2->loc=vect_cat(tmp,vect_drop(&one_vec,tmp2));
}


/* purify - make sure all final vectors have been coded by calling
     purify_vect with them.  */

int purify(expr_t *expr, expr_t *result)

{
  vect_t *tmp;

  expr->dim=red_s_expr(expr->dim);
  result->dim=red_s_expr(result->dim);
  expr->index=purify_vect(expr->index);
  expr->loc=purify_vect(expr->loc);
  expr->bound=purify_vect(expr->bound);
  expr->stride=purify_vect(expr->stride);
  expr->shp=purify_vect(expr->shp);
  result->shp=purify_vect(result->shp);
  result->bound=purify_vect(result->bound);
  result->stride=purify_vect(result->stride);
}

  
/* redall - the reduction of a redall expression.  A redall is a forall
     loop that results from a reduction operator. */

redall(expr_t *fa_expr, expr_t *result, int top, char *op, int inright)

{
  int i,tmp_num;
  char *newop;
  expr_t *expr,*tmp;
  vect_t *tmp_vec,*loc,*pad1;
  reduced_t *fa_reduced;

  expr=fa_expr->left;

  fa_expr->index=purify_vect(fa_expr->index);
  fa_expr->bound=purify_vect(fa_expr->bound);
  fa_expr->stride=purify_vect(fa_expr->stride);

  /* expr is forall psi array so loc bound and index will be expanded
     when psi is reduced */
  expr->loc=fa_expr->loc;
  expr->bound=fa_expr->bound;
  expr->index=fa_expr->index;
  expr->stride=fa_expr->stride;

  fa_expr->index=vect_cat(&zero_vec,fa_expr->index);
  fa_expr->bound=fa_expr->forall->bound;

  if (generic) {
    fprintf(rfile,"\n");
    do_ptab(0);
    fprintf(rfile,"forall %s in ",fa_expr->forall->fa->string);
    print_vector(fa_expr->forall->bound);
    fprintf(rfile," {\n");
    ptabs++;
  }

  if (inright) {
    /* assign to a temporary first */

    temp_array_num++;
    tmp=get_expr_mem(1);
    tmp->dim=expr->dim;
    tmp->shp=expr->shp;
    tmp->index=get_vect();
    *tmp->index=zero_vec;
    tmp->index->shp=expr->index->shp;
    tmp->loc=expr->loc;
    expr->loc=get_vect();
    *expr->loc=zero_vec;
    expr->loc->shp=tmp->loc->shp;
    tmp->bound=fa_expr->bound;
    tmp->stride=fa_expr->stride;
    tmp->ident=get_ident();
    sprintf(tmp->ident->string,"temp%d",temp_array_num);
    tmp->ident->real=1;
    tmp->ident->type=ARRAY;
    newop="=";
    add_allocation(tmp);
    UNSETALLOC(tmp->flags);
    SETUSED(tmp->ident->flags);  /* so it does'nt get allocated in code.c */
  } 

  /* add a forall to the list of reduced expressions */
  fa_reduced=get_reduced();
  fa_reduced->type=FORALL;
  fa_reduced->next=reduced;

  /* start a new reduced list of the expressions that are in the scope of
     the forall */
  reduced=NULL;
  /* the first node is the forall node */
  addto_reduced(fa_expr,NULL,NULL);

  if (inright) {
    print_expr(FALSE,expr,tmp,newop);
    assign(expr,tmp,top,newop,inright);
    print_expr(FALSE,tmp,result,op);
    assign(tmp,result,FALSE,op,TRUE);
  } else {
    print_expr(FALSE,expr,result,op);
    assign(expr,result,FALSE,op,TRUE);
  }

  fa_reduced->d.list=reduced;  /* the resulting list of reduced expressions */
  reduced=fa_reduced;          /* restore the top level reduced */

  if (generic) {
    ptabs--;
    do_ptab(0);
    fprintf(rfile,"}\n");
  }
}


/* forall - reduce a forall expression.  This is a forall loop that results
     from omega operations. */

forall(expr_t *fa_expr, expr_t *result, int top, char *op, int inright)

{
  int i,tmp_num;
  char *newop;
  expr_t *expr,*tmp;
  vect_t *fa_vect,*tmp_vec,*loc,*pad1;
  reduced_t *fa_reduced;

  expr=fa_expr->left;

  fa_vect=get_vect();
  fa_vect->shp=fa_expr->forall->bound->shp;
  fa_vect->loc=&s_const0;
  fa_vect->index=&s_const0;
  fa_vect->ident=fa_expr->forall->fa;

  fa_expr->index=purify_vect(fa_expr->index);
  fa_expr->bound=purify_vect(fa_expr->bound);
  fa_expr->stride=purify_vect(fa_expr->stride);
  tmp_vec=vect_len(fa_vect);
  loc=vect_op(MINUS,fa_vect,vect_take(tmp_vec,fa_expr->index));
  loc=vect_cat(vect_op(PLUS,vect_take(tmp_vec,fa_expr->loc),loc),
	       vect_drop(tmp_vec,fa_expr->loc));
  expr->loc=loc;
  pad1=get_vect();
  pad1->loc=&s_const0;
  pad1->index=&s_const0;
  pad1->shp=s_op(MINUS,fa_vect->shp,s_op(MINUS,fa_expr->dim,expr->dim));
  pad1->ident=&const1;
  expr->bound=vect_cat(pad1,vect_drop(tmp_vec,fa_expr->bound));
  expr->stride=vect_cat(pad1,vect_drop(tmp_vec,fa_expr->stride));
  expr->index=vect_cat(pad1,vect_drop(tmp_vec,fa_expr->index));

  if (generic) {
    fprintf(rfile,"\n");
    do_ptab(0);
    fprintf(rfile,"forall %s in ",fa_expr->forall->fa->string);
    print_vector(fa_expr->forall->bound);
    fprintf(rfile," {\n");
    ptabs++;
  }

  if (inright) {
    /* assign to a temporary first */

    temp_array_num++;
    tmp=get_expr_mem(1);
    tmp->dim=expr->dim;
    tmp->shp=expr->bound;
    tmp->index=get_vect();
    *tmp->index=zero_vec;
    tmp->index->shp=expr->index->shp;
    tmp->loc=expr->loc;
    expr->loc=get_vect();
    *expr->loc=zero_vec;
    expr->loc->shp=tmp->loc->shp;
    tmp->bound=expr->bound;
    tmp->stride=expr->stride;
    tmp->ident=get_ident();
    sprintf(tmp->ident->string,"temp%d",temp_array_num);
    tmp->ident->real=1;
    tmp->ident->type=ARRAY;
    newop="=";
    add_allocation(tmp);
    UNSETALLOC(tmp->flags);
    SETUSED(tmp->ident->flags);  /* so it does'nt get allocated in code.c */
  } else {
    tmp=result;
    newop=op;
  }

  /* add a forall to the list of reduced expressions */
  fa_reduced=get_reduced();
  fa_reduced->type=FORALL;
  fa_reduced->next=reduced;

  /* start a new reduced list of the expressions that are in the scope of
     the forall */
  reduced=NULL;
  /* the first node is the forall node */
  addto_reduced(fa_expr,NULL,NULL);

  print_expr(FALSE,expr,tmp,newop);
  assign(expr,tmp,TRUE,newop,FALSE);
  if (inright) {
    print_expr(FALSE,tmp,result,op);
    assign(tmp,result,top,op,inright);
  }

  fa_reduced->d.list=reduced;  /* the resulting list of reduced expressions */
  reduced=fa_reduced;          /* restore the top level reduced */

  if (generic) {
    ptabs--;
    do_ptab(0);
    fprintf(rfile,"}\n");
  }
}


/* assign - reduce an expression on step by eliminating the top operator */

expr_t *assign(expr_t *expr, expr_t *result, int top, char *op, int inright)

{
  int copy,cnt;
  char *new_op[4],tmp_num;
  expr_t *left, *right, *tmp,*tmp2;
  vect_t *loc,*drop,*pad1;

  if (prove)
    ptabs++;

  if (expr==NULL) return(expr);

  left=expr->left;
  right=expr->right;

  /* eliminate top operator by calling its reduction rule */
  cnt=0;
  switch (expr->op) {
  case NOP:
    if (generic)
      print_expr(TRUE,expr,result,op);

    if (prove)
      fprintf(rfile,"\n");

    if (!top) return(expr);
    purify(expr,result);

    if (!empty(expr->bound))
      addto_reduced(expr,result,op);
    break;

  case TIMES:
    new_op[cnt]="*=";
    cnt++;
  case DIVIDE:
    new_op[cnt]="/=";
    cnt++;
  case PLUS:
    new_op[cnt]="+=";
     cnt++;
  case MINUS:
    new_op[cnt]="-=";
    cnt++;

    if (inright&&((*new_op[0]!='+')||(op[0]!='+'))) {
      /* assign to a temporary first */

      temp_array_num++;

      tmp=get_expr_mem(1);
      tmp->dim=expr->dim;
      tmp->shp=expr->shp;
      drop=s_vect(s_op(MINUS,expr->dim,result->dim));
      drop=vect_op(TIMES,vect_unop(IF_POS,drop),drop);
      tmp->bound=vect_drop(drop,expr->bound);
      tmp->loc=vect_drop(drop,expr->loc);
      tmp->stride=get_vect();
      tmp->stride->index=&s_const0;
      tmp->stride->loc=&s_const0;
      tmp->stride->shp=tmp->shp->shp;
      tmp->stride->ident=&const1;
      tmp->index=get_vect();
      *tmp->index=zero_vec;
      tmp->index->shp=expr->index->shp;
      tmp->ident=get_ident();
      sprintf(tmp->ident->string,"temp%d",temp_array_num);
      tmp->ident->real=1;
      if (result->ident->type==VARIABLE) tmp->ident->type=VARIABLE;
      else tmp->ident->type=ARRAY;
      add_allocation(tmp);
      SETUSED(tmp->ident->flags);
      
      loc=get_vect();
      loc->shp=expr->loc->shp;
      loc->index=&s_const0;
      loc->loc=&s_const0;
      loc->ident=&const0;
      
      copy=TRUE;
    } else {
      tmp=result;
      copy=FALSE;
      loc=expr->loc;
    }

    left->index=expr->index;
    left->bound=expr->bound;
    left->stride=expr->stride;
    left->loc=loc;

    if (copy) {
      print_expr(FALSE,left,tmp,"=");
      assign(left,tmp,TRUE,"=",FALSE);
    } else {
      print_expr(FALSE,left,tmp,op);
      assign(left,tmp,TRUE,op,FALSE);
    }
    
    if (right!=NULL) {
      right->index=expr->index;
      right->bound=expr->bound;
      right->loc=loc;
      right->stride=expr->stride;
      print_expr(FALSE,right,tmp,*new_op);
      assign(right,tmp,TRUE,*new_op,TRUE);
    }

    if (copy) {
      print_expr(FALSE,tmp,result,op);
      assign(tmp,result,TRUE,op,FALSE);
    }

    break;

  case SCALAR_EXTEND:
    assign(red_scalar_extend(expr),result,top,op,inright);
    break;

  case FORALL:
    reduce_extended(expr,result,top,op,inright);
    forall(expr,result,top,op,inright);
    break;

  case TAKE:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    right->stride=expr->stride;
    red_take(left,right);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case DROP:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    right->stride=expr->stride;
    red_drop(left,right);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case PTAKE:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    right->stride=expr->stride;
    red_ptake(left,right);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case PDROP:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    right->stride=expr->stride;
    red_pdrop(left,right);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case REVERSE:
    right->bound=expr->bound;
    right->index=expr->index;
    right->loc=expr->loc;
    right->stride=expr->stride;
    red_reverse(right);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case TIMES_RED:
    new_op[cnt]="*=";
    cnt++;
  case DIVIDE_RED:
    new_op[cnt]="/=";
    cnt++;
  case PLUS_RED:
    new_op[cnt]="+=";
     cnt++;
  case MINUS_RED:
    new_op[cnt]="-=";
    cnt++;

    /* create the identity for the operation */
    tmp2=get_expr_mem(1);
    tmp2->dim=expr->dim;
    tmp2->shp=expr->shp;
    tmp2->stride=get_vect();
    tmp2->stride->index=&s_const0;
    tmp2->stride->loc=&s_const0;
    tmp2->stride->shp=tmp2->shp->shp;
    tmp2->stride->ident=&const1;
    tmp2->index=get_vect();
    tmp2->index->index=&s_const0;
    tmp2->index->loc=&s_const0;
    tmp2->index->shp=tmp2->shp->shp;
    tmp2->index->ident=&const0;
    tmp2->bound=expr->bound;
    tmp2->loc=expr->loc;

    if ((new_op[0][0]=='-')||(new_op[0][0]=='+')) 
      tmp2->ident=&const0;
    else tmp2->ident=&const1;

    if (inright) {
      /* assign to a temporary first */

      tmp=get_expr_mem(1);
      *tmp=*tmp2;
      tmp->bound=vect_cat(&one_vec,tmp->bound);
      temp_array_num++;

      tmp->ident=get_ident();
      sprintf(tmp->ident->string,"temp%d",temp_array_num);
      tmp->ident->real=1;
      tmp->ident->type=ARRAY;
      SETALLOC(tmp->flags);
      
      copy=TRUE;
    } else {
      tmp=result;
      copy=FALSE;
    }

    /* assign the identity to the result */
    print_expr(FALSE,tmp2,tmp,"=");
    assign(tmp2,tmp,TRUE,"=",FALSE);

    /* build the forall loop to accumulate the result */
    redall(expr,tmp,top,new_op[0],FALSE);
    
    if (copy) {
      print_expr(FALSE,tmp,result,op);
      assign(tmp,result,TRUE,op,FALSE);
    }
    break;

  case RAVEL:
    assign_rav(expr,left,result,top,op,inright);
    break;

  case PSI:
    right->loc=expr->loc;
    right->index=expr->index;
    right->bound=expr->bound;
    right->stride=expr->stride;
    red_psi(left,right,expr->dim);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case CAT:
    left->bound=expr->bound;
    left->stride=expr->stride;
    left->index=expr->index;
    left->loc=expr->loc;
    right->bound=expr->bound;
    right->stride=expr->stride;
    right->index=expr->index;
    right->loc=expr->loc;
    red_cat(left,right);
    print_expr(FALSE,left,result,op);
    assign(left,result,TRUE,op,inright);
    print_expr(FALSE,right,result,op);
    assign(right,result,TRUE,op,inright);
    break;

  case EXT_OP:
    /* call external routine to handle these */
    reduce_extended(expr,result,top,op,inright);
    break;
  }

  if (prove)
    ptabs--;

  return(expr);
}


/* find_temp - searches for any access to the named temporary.  Returns true
     if it's found in a combined assignment other than the num(th) assign. */

int find_temp(reduced_t *list, char *name, int ex_num)

{
  int ret,num;
  reduced_t *node;
  reduced_t *assign;

  num=0;
  ret=FALSE;
  node=list;
  while (node!=NULL) {
    if (node->type==NOP) {
      assign=node->d.list;
      while (assign!=NULL) {
	if (strcmp(name,assign->d.frag->ident->string)==0)
	  if (num!=ex_num)
	    ret=TRUE;
	if (strcmp(name,assign->d.frag->left->ident->string)==0)
	  if (num!=ex_num)
	    ret=TRUE;
	assign=assign->next;
      }
    } else if (node->type==FORALL) {
      ret=TRUE;
    }
    node=node->next;
    num++;
  }
  
  return(ret);
}


/* check_combined_temps - check to see that temporary arrays are'nt used
     accross two different combined assignments.  */

check_combined_temps(reduced_t *ret, reduced_t **non_assigns)

{
  int local,num;
  reduced_t *old_node,*new_node,*node,*temp,*previous;
  reduced_t *na_last,*na_node;
  char *name;

  num=0;
  old_node=ret;
  while (old_node!=NULL) {
    if (old_node->type==NOP) {
      node=old_node->d.list;
      previous=NULL;
      /* find any assignments to temporary arrays */
      while (node!=NULL) {
	name=node->d.frag->left->ident->string;
	if (strncmp("temp",name,4)==0) {
	  local=!find_temp(ret,name,num);
	  if (local) {
	    node->d.frag->left->ident->type=VARIABLE;

	    /* remove allocate */
	    na_last=NULL;
	    na_node= *non_assigns;
	    while (na_node!=NULL) {
	      if (strcmp(name,na_node->d.frag->ident->string)==0) {
		/* if we find it then this is the first time so allocate it */
                declare_var (FALSE, name, 0);
		if (na_last==NULL) {
		  *non_assigns=na_node->next;
		} else {
		  na_last->next=na_node->next;
		}
	      }
	      na_last=na_node;
	      na_node=na_node->next;
	    }
	  } else {
	    /* this means the use of the temporary is split between
	       two combined lists and needs to be taken out. */
	    /* if a temp is split up then it must be the last thing in
	       the list. */
	    if (previous!=NULL) {
	      previous->next=NULL;      /* cut of list with temps */
	      new_node=get_reduced();   /* create a new combined list */
	      new_node->d.list=node;
	      new_node->next=old_node->next;
	      old_node->next=new_node;  /* insert the new combined list */
	      num++;
	      old_node=old_node->next;
	    } 
	  }
	}
	previous=node;
	if (node!=NULL)
	  node=node->next;
      }
    }
    num++;
    old_node=old_node->next;
  }

}
	  
	  

/* combine_reduced - combines assignments with the same location and 
     bound into a list that can be coded in the same loop.  If a expr
     being combined uses a temporary then that temporary can be just
     a float instead of an array.  Also if the right and left hand side
     arrays are the same and the index and location is zero then this
     is just A=A and can be thrown away. */

reduced_t *combine_reduced(reduced_t *reduced, expr_t *result, int inloop)

{
  int same;
  reduced_t *ret,*old_node,*new_node,*node;
  reduced_t *non_assigns;
  
  /* remove any assignments of the type A=A, at the same to move
     allocations out of the list. */

  old_node=NULL;
  non_assigns=NULL;
  node=reduced;
  while (node!=NULL) {
    if (node->type==EXT_OP) {
      old_node=node;
      node=node->next;
    } else if ((node->type==NOP)&&(node->d.frag->ident==result->ident)) {
      if ((vect_compare(node->d.frag->loc,node->d.frag->index))&&
	  (node->d.frag->func[0]=='=')) {
	if (old_node==NULL) {
	  reduced=node->next;
	} else {
	  old_node->next=node->next;
	}
      } else old_node=node;

      node=node->next;
    } else if (node->type==FORALL) {
      node->d.list->next=combine_reduced(node->d.list->next,result,TRUE);
      old_node=node;
      node=node->next;
    } else if (node->type!=NOP) {
      /* take non assignment out of the list */
      if (old_node==NULL) {
	reduced=node->next;
      } else {
	old_node->next=node->next;
      }
      
      /* insert it into non_assigns list */
      node->next=non_assigns;
      non_assigns=node;

      if (old_node==NULL) {
        node=reduced;
      } else {
	node=old_node->next;
      }
    } else {
      old_node=node;
      if (node!=NULL) node=node->next;
    }
  }

    /* create a list of lists.  each list is a group of assigns with the
       same location and bound also separate iota's out */
  old_node=reduced;
  if (reduced!=NULL) {
    ret=get_reduced();
    new_node=ret;
    new_node->type=NOP;
  } else ret=NULL;
  while (old_node!=NULL) {
    if (old_node->type==EXT_OP) {
      *new_node=*old_node;
      old_node=old_node->next;
    } else if (old_node->type==NOP) {
      new_node->d.list=old_node;
      node=old_node;
      old_node=old_node->next;
      if ((old_node!=NULL)&&(old_node->type==NOP)&&
	  (old_node->d.frag->left->ident!=result->ident)&&
	  (strncmp(old_node->d.frag->left->ident->string,"temp",4)==0)) {
	same=!inloop;
      } else  {
	same=(!inloop)&&(old_node!=NULL)&&(old_node->type==NOP)&&
	  (vect_compare(old_node->d.frag->loc,node->d.frag->loc));
      }
      same=same&&((old_node!=NULL)&&(old_node->type==NOP)&&
                (old_node->d.frag->ident->type!=IOTA)&&	    
                (node->d.frag->ident->type!=IOTA)&&	    
                (vect_compare(old_node->d.frag->bound,node->d.frag->bound))&&
                (vect_compare(old_node->d.frag->stride,node->d.frag->stride)));
      while (same) {
	node->next=old_node;
	node=old_node;
	old_node=old_node->next;
	if ((node->type==NOP)&&(node->d.frag->left->ident!=result->ident)) {
	  if (strncmp(node->d.frag->left->ident->string,"temp",4)==0)
	    same=!inloop;
	  else 
	    same=(!inloop)&&(old_node!=NULL)&&
	      (vect_compare(old_node->d.frag->loc,node->d.frag->loc));
	}
	same=same&&(old_node!=NULL)&&(old_node->type==NOP)&&
	  (old_node->d.frag->ident->type!=IOTA)&&	    
	    (vect_compare(old_node->d.frag->bound,node->d.frag->bound))&&
            (vect_compare(old_node->d.frag->stride,node->d.frag->stride));
      }
      node->next=NULL;
    } else {
      *new_node=*old_node;
      old_node=old_node->next;
    }
    if (old_node!=NULL) {
      new_node->next=get_reduced();
      new_node=new_node->next;
      new_node->type=NOP;
    }
  }
  if (ret!=NULL) 
    new_node->next=NULL;

  if (!inloop)
    check_combined_temps(ret,&non_assigns);

  /* merge non-assignments back in the list */
  if (non_assigns!=NULL) {
    node=non_assigns;
    while (node->next!=NULL) {
      node=node->next;
    }
    node->next=ret;
    ret=non_assigns;
  }

  return(ret);
}
      

/* psi_reduce - top level procedure for performing the reductions.  The
     initial form is created and then assign is called to reduce the
     expression */

psi_reduce(statement_t *statement,int top)

{
  statement_t *node;
  parser_t *save[2];
  expr_t *expr,*result;

  expr=statement->d.assign->expr;
  result=statement->d.assign->result;
  expr->stride=get_vect();
  expr->stride->index=&s_const0;
  expr->stride->loc=&s_const0;
  expr->stride->shp=expr->shp->shp;
  expr->stride->ident=&const1;
  expr->index=get_vect();
  expr->index->index=&s_const0;
  expr->index->loc=&s_const0;
  expr->index->shp=expr->shp->shp;
  expr->index->ident=&const0;
  expr->bound=expr->shp;
  if (result->loc==NULL) {
    expr->loc=get_vect();
    expr->loc->index=&s_const0;
    expr->loc->loc=&s_const0;
    expr->loc->shp=result->dim;
    expr->loc->ident=&const0;
  } else expr->loc=result->loc;
  result->bound=expr->shp;

  print_expr(FALSE,expr,result,"=");
  assign(expr,result,TRUE,"=",is_recursive(expr,result->ident,TRUE));
  statement->kind=REDUCED;
  
  if (top) {
  /* the node in the statement is a skip naming the result */
    statement->d.reduced=get_reduced();
    statement->d.reduced->type=SKIP;
    statement->d.reduced->d.frag=result;
    statement->d.reduced->next=combine_reduced(reverse_list(reduced),result,
      FALSE);
  }
}


/* reduction_init - clear the list of reduced expressions.  This should be
     called before every new assignment. */

reduction_init()

{
  reduced=NULL;
}


/* psi_init - intialization for the above procedures.  Called once when
     the compiler is first invoked. */

psi_init()

{
  ident_t *ident;

  s_const0.op=NOP;
  s_const0.left=NULL;
  s_const0.right=NULL;
  s_const0.ident=&const0;
  s_const1.op=NOP;
  s_const1.left=NULL;
  s_const1.right=NULL;
  s_const1.ident=&const1;

  const0.type=CONSTANT;
  const0.value=0;

  const1.type=CONSTANT;
  const1.value=1;

  ident=get_ident();
  ident->type=CONSTANT;
  ident->value=0.0;
  ident->array.dim=&const1;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const1;
  zero_vec.ident=ident;
  zero_vec.op=NOP;
  zero_vec.loc=&s_const0;
  zero_vec.index=&s_const0;
  zero_vec.shp=&s_const1;

  ident=get_ident();
  ident->type=CONSTANT;
  ident->value=1.0;
  ident->array.dim=&const1;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const1;
  one_vec.ident=ident;
  one_vec.op=NOP;
  one_vec.loc=&s_const0;
  one_vec.index=&s_const0;
  one_vec.shp=&s_const1;

  ident=get_ident();
  ident->type=CONSTANT;
  ident->value=-1.0;
  ident->array.dim=&const1;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const1;
  neg_one_vec.ident=ident;
  neg_one_vec.op=NOP;
  neg_one_vec.loc=&s_const0;
  neg_one_vec.index=&s_const0;
  neg_one_vec.shp=&s_const1;

  ident=get_ident();
  sprintf(ident->string,"empty");
  ident->type=CONST_ARRAY;
  ident->array.dim=&const1;
  ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ident->array.shp[0]=&const0;
  empty_vec.ident=ident;
  empty_vec.op=NOP;
  empty_vec.loc=&s_const0;
  empty_vec.index=&s_const0;
  empty_vec.shp=&s_const0;
}
