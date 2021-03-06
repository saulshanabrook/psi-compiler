/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   part.c - the partition module examines a procedure body and chooses
     a distribution for each array used in the procedure.

   v0.3 Scott Thibault - 8/93
        Scott Thibault - 10/93
           partition_reduced was changed to handle a NOP reduced_t 
           as begin a list of reduced_t's.


*/

#include <stdio.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"

#include "psi.e"
#include "dist.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
int n_procs=1;
rule_t *rules;


/* add_rule - add a new rule to the list of rules. */

rule_t *add_rule(ident_t *ident, vect_t *shp)

{
  rule_t *node;

  node=get_rule();
  node->type=DEFAULT_RULE;
  node->ident=ident;
  node->shp=shp;
  node->next=rules;
  rules=node;

  return(node);
}


/* find_rule - search for a rule for ident */

rule_t *find_rule(ident_t *ident)

{
  rule_t *node;

  node=rules;
  while ((node!=NULL)&&(node->ident!=ident))
    node=node->next;

  if ((node==NULL)&&(ident->array.rule!=NULL)) {
    node=ident->array.rule;
    node->next=rules;
    rules=node;
  }

  return(node);
}


/* build_rule - make a rule based on the assignment expr to res */

build_rule(expr_t *expr, expr_t *res)

{
  rule_t *lrule,*rrule;

  lrule=find_rule(res->ident);
  if (lrule==NULL) lrule=add_rule(res->ident,res->shp);
  rrule=find_rule(expr->ident);
  if (rrule==NULL) rrule=add_rule(expr->ident,expr->shp);
  
  lrule->dist=TRUE;
  rrule->dist=TRUE;
}


/* resolve_rules - examine the list of rules for each array a pick a 
     distribution for it based on the rules. */

dist_t *resolve_rules()

{
  dist_t *ret,*node;
  rule_t *rule,*tmp;
  vect_t *e,*pad1,*p_vec,*tmp_e;

  p_vec=get_vect();
  p_vec->loc=&s_const0;
  p_vec->index=&s_const0;
  p_vec->shp=&s_const1;
  p_vec->ident=get_ident();
  p_vec->ident->type=CONSTANT;
  p_vec->ident->value=n_procs;

  ret=NULL;
  rule=rules;
  while (rule!=NULL) {
    if (rule->dist&&(n_procs>1)) {
      if (!GLOBAL(rule->ident->flags)) {
        node=get_dist();
        node->ident=rule->ident;
        node->shp=rule->shp;
        switch (rule->type) {
        case CYCLIC:
          node->e=rule->part;
          node->g=node->pb=rule->proc;
          node->c=vect_unop(IF_POS,vect_op(MOD,node->shp,node->g));
          node->c=vect_op(PLUS,vect_op(DIVIDE,node->shp,node->g),node->c);
          *node->pl=pad_zero;
          node->pl->shp=node->pb->shp;
          break;
        case BLOCK:
          node->c=NULL;
          node->e=rule->part;
          node->g=node->pb=rule->proc;
          *node->pl=pad_zero;
          node->pl->shp=node->pb->shp;
          break;
        case DEFAULT_RULE:
          node->c=NULL;
          tmp_e=vect_take(&one_vec,rule->shp);
          e=vect_op(DIVIDE,tmp_e,p_vec);
          /*
          e=vect_op(PLUS,e,vect_unop(IF_POS,vect_op(MOD,tmp_e,p_vec)));
          */
          node->e=vect_cat(e,vect_drop(&one_vec,rule->shp));
          pad1=get_vect();
          *pad1=pad_one;
          pad1->shp=s_op(MINUS,node->e->shp,&s_const1);
          node->g=node->pb=vect_cat(p_vec,pad1);
          node->pl=get_vect();
          *node->pl=pad_zero;
          node->pl->shp=node->pb->shp;
          break;
        }
        node->c=purify_vect(node->c);
        node->e=purify_vect(node->e);
        node->g=purify_vect(node->g);
        node->pl=purify_vect(node->pl);
        node->pb=purify_vect(node->pb);
        node->next=ret;
        ret=node;
      }
    }
    rule=rule->next;
  }

  return(ret);
}


/* partition_reduced - generated rules for a reduced expression. */

partition_reduced(reduced_t *reduced)

{
  reduced_t *node,*sub_node;
  
  node=reduced;
  while (node!=NULL) {
    switch (node->type) {
    case SKIP:
      break;

    case NOP:
      sub_node=node->d.list;
      while (sub_node!=NULL) {
        build_rule(sub_node->d.frag,sub_node->d.frag->left);
        sub_node=sub_node->next;
      }
      break;

    case ALLOCATE:
    case EXT_OP:
      break;

    case FORALL:
      partition_reduced(node->d.list->next);
      break;

    default:
      fatal("Unknown type encountered in partition_reduced");
    }
    node=node->next;
  }
}


/* rec_partition - generate rule for the procedure body. */

rec_partition(statement_t *body)

{
  statement_t *node;

  node=body;
  while (node!=NULL) {
    switch (node->kind) {
    case REDUCED:
      partition_reduced(node->d.reduced);
      break;

    case LOOP:
      rec_partition(node->d.loop->body);
      break;

    case DYNAMIC:
    case CALL:
    case EXTENDED:
      break;

    default:
      fatal("unknown kind in rec_partition");
    }
    node=node->next;
  }
}


/* partition - determine a partitioning scheme or distribution for each array
     in a procedure body. */

dist_t *partition(statement_t *body)

{
  dist_t *ret;

  rules=NULL;

  rec_partition(body);
  ret=resolve_rules();
  return(ret);
}
