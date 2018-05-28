/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* sys.c - this module contains utility rutines for memory management and
      some I/O rutines */

#include <stdio.h>
#include <math.h>
#include <memory.h>
#include "psi.h"

#include "psi.e"
#include "parse.e"

extern FILE *tfile;
extern FILE *cfile;
extern ident_t dumb_var;

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#define MAX_EXPR 1000
#define MAX_VECT 4000
#define MAX_IDENT 2000
#define MAX_S_EXPR 8000

#define MARK ((int) 0x8000)
#define NMARK ((int) 0x7fff)

int ntab=1;  /* current indentation level of output source code */

  /* static arrays for memory heaps */
static expr_t expr_mem[MAX_EXPR];
static expr_t *e_free;
static int num_e_free=MAX_EXPR;
static vect_t vect_mem[MAX_VECT];
static vect_t *v_free;
static int num_v_free=MAX_VECT;
static ident_t ident_mem[MAX_IDENT];
static ident_t *i_free;
static int num_i_free=MAX_IDENT;
static s_expr_t s_expr_mem[MAX_S_EXPR];
static s_expr_t *s_free;
static int num_s_free=MAX_S_EXPR;


/* get_expr_mem - this fuctions allocates ONE expr_t blocks and returns a
     pointer to the first one. n is obsolete */

expr_t *get_expr_mem(int n)

{
  expr_t *ret;

  if (n==0) {
    puts("Attempt to allocate 0 expression nodes, something wrong!");
    exit(1);
  }
  num_e_free--;
  if (e_free==NULL) {
    puts("Out of expression blocks!");
    exit(1);
  } else {
    ret=e_free;
    e_free=e_free->left;
    ret->op=NOP;
    ret->forall=NULL;
    ret->dim=NULL;
    ret->loc=NULL;
    ret->shp=NULL;
    ret->rot=NULL;
    ret->bound=NULL;
    ret->index=NULL;
    ret->left=NULL;
    ret->ident=NULL;
    ret->right=NULL;
    ret->scanned=FALSE;
    return(ret);
  }
}


/* expr_free - place an expr block back on the free list */

expr_free(expr_t *expr)

{
  expr->left=e_free;
  e_free=expr;
  num_e_free++;
}


/* get_vect - allocates space for one vect_t block and returns a pointer to
     it. */

vect_t *get_vect()

{
  vect_t *ret;

  num_v_free--;
  if (v_free==NULL) {
    puts("Out of vector blocks!");
    exit(1);
  } else {
    ret=v_free;
    v_free=v_free->left;
    ret->op=NOP;
    ret->flags=0;
    ret->loc=NULL;
    ret->index=NULL;
    ret->shp=NULL;
    ret->left=NULL;
    ret->ident=NULL;
    ret->right=NULL;
    return(ret);
  }
}


/* vect_free - place an vect block back on the free list */

vect_free(vect_t *vect)

{
  vect->left=v_free;
  v_free=vect;
  num_v_free++;
}


/* get_ident - allocates space for an ident_t block and returns a pointer to
     it. */

ident_t *get_ident()

{
  ident_t *ret;

  num_i_free--;
  if (i_free==NULL) {
    puts("Out of ident blocks!");
    exit(1);
  } else {
    ret=i_free;
    i_free=i_free->next;
    ret->type=FLOAT; 
    ret->flags=0;
    ret->array.dim=NULL;
    ret->array.shp=NULL;
    ret->array.rav=NULL;
    ret->next=NULL;
    return(ret);
  }
}


/* ident_free - place an ident block back on the free list */

ident_free(ident_t *ident)

{
  ident->next=i_free;
  i_free=ident;
  num_i_free++;
}


/* get_s_expr - allocates space for an s_expr_t block and returns a pointer to
     it. */

s_expr_t *get_s_expr()

{
  s_expr_t *ret;

  num_s_free--;
  if (s_free==NULL) {
    puts("Out of s_expr blocks!");
    exit(1);
  } else {
    ret=s_free;
    s_free=s_free->left;
    ret->op=NOP;
    ret->flags=0;
    ret->ident=NULL;
    ret->left=ret->right=NULL;
    return(ret);
  }
}


/* s_expr_free - place an s_expr block back on the free list */

s_expr_free(s_expr_t *s_expr)

{
  s_expr->left=s_free;
  s_free=s_expr;
  num_s_free++;
}


/* fatal - reports and error message to the screen and aborts the program */

void fatal(char *msg)

{
  printf("Error: %s\n",msg);
  exit(1);
}


/* get_mem - general allocation of size bytes from the system heap */

void *get_mem(int size)

{
  void *ret;

  if ((ret=(void *) malloc(size))==NULL) {
    fatal("Out of memory!");
  }

  return(ret);
}


/* error - reports and error message to the screen */

void error(char *msg)

{
  printf("Error: %s\n",msg);
}


/* copy_expr - not really needed anymore - allocats an expr_t block and
     copies the expr_t passed in to the new.  Returns the new block. */

expr_t *copy_expr(expr_t *expr)

{
  expr_t *new;

  new=get_expr_mem(1);
  *new=*expr;
  return(new);
}


/* dotab - print spaces up to the current idention piont in ntab */

dotab(int adj)

{
  int i;

  for (i=0; i<ntab+adj; i++) fprintf(tfile,"  ");
}


/* stats - reports the memory usage */

stats()

{
  printf("Memory usage:");
  printf(" Expr. Blks (%d)=%d",sizeof(expr_t),MAX_EXPR-num_e_free);
  printf("  Vect. Blks (%d)=%d",sizeof(vect_t),MAX_VECT-num_v_free);
  printf("  Idnt. Blks (%d)=%d",sizeof(ident_t),MAX_IDENT-num_i_free);
  printf("  S_expr. Blks (%d)=%d",sizeof(ident_t),MAX_S_EXPR-num_s_free);
  printf("\n");
}


/* init_mem - initializes the memory for our private memory management */

mem_init()

{
  int i;
  
  for (i=0; i<MAX_EXPR-1; i++) {
    expr_mem[i].left=expr_mem+i+1;
    expr_mem[i].op=NOP;
  }
  expr_mem[i].left=NULL;
  expr_mem[i].op=NOP;
  e_free=expr_mem;

  for (i=0; i<MAX_S_EXPR-1; i++) {
    s_expr_mem[i].left=s_expr_mem+i+1;
    s_expr_mem[i].op=NOP;
  }
  s_expr_mem[i].left=NULL;
  s_expr_mem[i].op=NOP;
  s_free=s_expr_mem;

  for (i=0; i<MAX_VECT-1; i++) {
    vect_mem[i].left=vect_mem+i+1;
    vect_mem[i].op=NOP;
  }
  vect_mem[i].left=NULL;
  vect_mem[i].op=NOP;
  v_free=vect_mem;

  for (i=0; i<MAX_IDENT-1; i++) {
    ident_mem[i].next=ident_mem+i+1;
    ident_mem[i].type=FLOAT;
    ident_mem[i].array.dim=NULL;
    ident_mem[i].array.shp=NULL;
    ident_mem[i].array.rav=NULL;
  }
  ident_mem[i].next=NULL;
  ident_mem[i].type=FLOAT;
  ident_mem[i].array.dim=NULL;
  ident_mem[i].array.shp=NULL;
  ident_mem[i].array.rav=NULL;
  i_free=ident_mem;

}


mark_ident(ident_t *ident)

{
  int i,tau,bound;

  if (ident!=NULL) {
    ident->type|=MARK; 
    mark_ident(ident->array.dim);
    if (ident->array.shp!=NULL) {
      tau=1;
        /* if dim is NULL it must be a vector */
        /* otherwise since shp!=NULL the dim must have a value */
      bound=(ident->array.dim==NULL) ? 1 : ident->array.dim->value;
      for (i=0; i<bound; i++) {
	if ((ident->array.shp[i]->type&0x7fff)==FLOAT)
	  tau*=ident->array.shp[i]->value;
	mark_ident(ident->array.shp[i]);
      }

      if (ident->array.rav!=NULL) {  /* if rav!=NULL then tau must be valid */
	for (i=0; i<tau; i++) {
	  mark_s_expr(ident->array.rav[i]);
	}
      }
    }
  }
}


mark_ident_list(ident_t *ident)

{
  while (ident!=NULL) {
    mark_ident(ident);
    ident=ident->next;
  }
}


mark_vect(vect_t *vect)

{
  if (vect!=NULL) {
    vect->op|=MARK;
    mark_s_expr(vect->index);
    mark_s_expr(vect->loc);
    mark_s_expr(vect->shp);
    mark_ident(vect->ident);
    mark_vect(vect->left);  
    mark_vect(vect->right);
  }
}


mark_expr(expr_t *expr)

{
  if (expr!=NULL) {
    expr->op|=MARK;
    mark_s_expr(expr->dim);
    if (expr->forall!=NULL) mark_vect(expr->forall->bound);
    mark_vect(expr->index);
    mark_vect(expr->bound);
    mark_vect(expr->loc);
    mark_vect(expr->shp);
    mark_vect(expr->rot);
    mark_ident(expr->ident);
    mark_expr(expr->left);
    mark_expr(expr->right);
  }
}


mark_s_expr(s_expr_t *s_expr)

{
  if (s_expr!=NULL) {
    s_expr->op|=MARK;
    mark_s_expr(s_expr->left);
    mark_s_expr(s_expr->right);
    mark_ident(s_expr->ident);
  }
}


collect_mem(parser_t *p_buf[],int n)

{
  ident_t **sym_table;
  int i,s;

  for (i=0; i<n; i++) {
    mark_ident(p_buf[i]->ident);
    mark_expr(p_buf[i]->psi);
  }

  sym_table=ret_table(&s);
  for (i=0; i<s; i++) {
    mark_ident_list(sym_table[i]);
  }
  
  e_free=NULL;
  num_e_free=0;
  for (i=0; i<MAX_EXPR; i++) {
    if ((expr_mem[i].op&(MARK))>0)
      expr_mem[i].op&=NMARK;
    else
      expr_free(expr_mem+i);
  }

  s_free=NULL;
  num_s_free=0;
  for (i=0; i<MAX_S_EXPR; i++) {
    if ((s_expr_mem[i].op&(MARK))>0)
      s_expr_mem[i].op&=NMARK;
    else
      s_expr_free(s_expr_mem+i);
  }
  s_const0.op&=NMARK;
  s_const1.op&=NMARK;

  v_free=NULL;
  num_v_free=0;
  for (i=0; i<MAX_VECT; i++) {
    if ((vect_mem[i].op&(MARK))>0)
      vect_mem[i].op&=NMARK;
    else
      vect_free(vect_mem+i);
  }
  empty_vec.op&=NMARK;
  zero_vec.op&=NMARK;
  one_vec.op&=NMARK;

  i_free=NULL;
  num_i_free=0;
  for (i=0; i<MAX_IDENT; i++) {
    if ((ident_mem[i].type&(MARK))>0)
      ident_mem[i].type&=NMARK;
    else
      ident_free(ident_mem+i); 
  }

  const0.type&=NMARK;
  const1.type&=NMARK;
  dumb_var.type&=NMARK;
}
