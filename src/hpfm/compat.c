#include <stdio.h>
#include "f90.h"
#include "psi.h"
#include "op.h"
#include "sys.h"

#include "psi.e"
#include "ident.e"
#include "sys.e"
#include "vect.e"

extern parser_t *non_psi (parser_t *arg1, parser_t *arg2);
extern parser_t *unon_psi (parser_t *arg1);
extern parser_t *unon2_psi (parser_t *arg1);

extern int curtempf90;
extern reduced_t *reduced;

reduced_t *rnode;
char *hpfstr;

/* make_compatable:  this function accepts a parser_t type, arg, which 
   contains an expression tree with root node at arg->psi, and func which
   is a psiop_t variable containing a pointer to a function.  make_compatable
   makes sure that the expression tree is compatable with the function.
   for examples, if the expression tree is CEILING (A) which can not be
   expanded into MOAL, and the function is MATMUL, which can be expanded into
   MOAL, then CEILING (A) must be assigned to a temporary variable and the
   temporary used as an argument to the MATMUL function */
parser_t *make_compatable (parser_t *arg, psiop_t func)
{
  ident_t *temp;
  parser_t *new_arg;
  expr_t *result;
  vect_t *tvect;
  s_expr_t *s;
  int i;
  
  if ((((func.func==non_psi)||(func.func==unon_psi)||(func.func==unon2_psi))&& 
       (arg->psi->op!=EXT_OP)&&(arg->psi->op!=NOP)) || 
      (((func.func!=non_psi)&&(func.func!=unon_psi)&&(func.func!=unon2_psi))&& 
       ((arg->psi->op==EXT_OP)&&(arg->psi->ext_op!=HPFASSIGN)))) {
      /* create the variable that will be used in moa expressions */
      temp = get_ident ();
      sprintf (temp->string,"TEMPF90%d",curtempf90);
      temp->type=ARRAY;
      temp->array.dim=make_ident (arg->psi->dim);
      temp->array.shp=(ident_t **)
        get_mem(arg->psi->shp->shp->ident->value*sizeof(ident_t *));
      for (i=0; i<arg->psi->shp->shp->ident->value; i++) {
        s=red_rav(arg->psi->shp,i);
        temp->array.shp[i]=make_ident(s);
      }
      result=get_expr_mem (1);
      result->ext_str=(char *) get_mem(17);
      sprintf(result->ext_str,"TEMPF90%d",curtempf90);
      result->op=NOP;
      result->shp=arg->psi->shp;
      result->dim=arg->psi->dim;
      result->ident=temp;
  
      /* create new_arg */
      new_arg=(parser_t *) get_mem(sizeof(parser_t));
      new_arg->psi=get_expr_mem (1);
      new_arg->psi->op=EXT_OP;
      new_arg->psi->ext_op=HPFASSIGN;
      new_arg->psi->shp=arg->psi->shp;
      new_arg->psi->dim=arg->psi->dim;
      new_arg->psi->left=result;
      new_arg->psi->right=arg->psi;
      new_arg->ident=result->ident;
      new_arg->psi->ident=result->ident;
      new_arg->psi->ext_str=(char *) get_mem(17);
      sprintf(new_arg->psi->ext_str,"TEMPF90%d",curtempf90);
      curtempf90++;
      return(new_arg);
  }
  else return (arg);
}

/* this function is called from the function assign in psi.c, when it
   encounters an expression node with an operator of type EXT_OP.  */
void reduce_extended(expr_t *expr, expr_t *result, int top, char *op,
  int inright)
{
  statement_t *subassign;

  if (expr==NULL)
    return;

  switch (expr->ext_op) {
    case FUNC:
    case SPLIT:
      reduce_extended(expr->left,result,FALSE,op,inright);
      reduce_extended(expr->right,result,FALSE,op,inright);
      break;
    case UNRECOGNIZED:
      reduce_extended(expr->left,result,FALSE,op,inright);
      reduce_extended(expr->right,result,FALSE,op,inright);
      if (top) {
        hpfstr=(char *) get_mem(strlen(result->ext_str)+
          strlen(expr->ext_str)+1);
        sprintf(hpfstr,"%s=%s",result->ext_str,
          expr->ext_str);
        free(expr->ext_str);
        expr->ext_str=hpfstr;
        rnode=get_reduced();
        rnode->type=EXT_OP;
        rnode->d.frag=copy_expr(expr);
        rnode->d.frag->func="=";
        rnode->d.frag->left=NULL;
        rnode->next=reduced;
        reduced=rnode;
      }
      break;
    case PREORDER:
      reduce_extended(expr->right,result,FALSE,op,inright);
      expr->right=NULL;
      break;
    case HPFASSIGN:
      if (expr->right->op == EXT_OP) {
        reduce_extended(expr->right,result,FALSE,op,inright);
        hpfstr=(char *) get_mem(strlen(expr->left->ext_str)+
          strlen(expr->right->ext_str)+1);
        sprintf(hpfstr,"%s=%s",expr->left->ext_str,
          expr->right->ext_str);
        free(expr->ext_str);
        expr->ext_str=hpfstr;
        rnode=get_reduced();
        rnode->type=EXT_OP;
        rnode->d.frag=copy_expr(expr);
        rnode->d.frag->func="=";
        rnode->d.frag->left=NULL;
        rnode->next=reduced;
        reduced=rnode;
        expr->op=NOP; /* so assign will addto_reduced */
        expr->ext_op=NOP;  /* to prevent more than one assignment */
        assign(expr,result,top,op,inright);
      } else {
        subassign=(statement_t *) get_mem(sizeof(statement_t));
        subassign->str="array assignment";
        expr->left->loc=NULL;
        expr->left->bound=expr->right->shp;
	subassign->d.assign=(assign_t *) get_mem(sizeof(assign_t));
        subassign->d.assign->expr=expr->right;
        subassign->d.assign->result=expr->left;
        psi_reduce(subassign,FALSE);
        free(subassign);
      }
      break;
    case NOP:  /* variable or constant reference if all goes well */
      break;
    default:
      fatal ("Internal error: reduce_extended -- unknown external op");
  }
}

/* this function is called from function code_reduced in code.c when it
   encounters a node with type of EXT_OP. */
void code_extended (reduced_t *node)
{
  dotab(0);
  fprintf (tfile,"%s\n",node->d.frag->ext_str);
}

/* this function is called from function collect_garbage in sys.c when
   it encounters a node with statement->kind of EXTENDED */
void mark_extended (statement_t *node)
{
  printf ("mark_extended called.  e-mail tmcmahon@cs.umr.edu\n");
  printf (" and tell him to do something about it");
}
