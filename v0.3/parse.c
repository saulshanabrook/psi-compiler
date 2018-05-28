/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   parse.c - the parser module.
   
   v0.1 Scott Thibault - 6/93
   v0.2 Scott Thibault - 7/93
   v0.3 Scott Thibault - 10/93
           At the end of proc_def a call is made to free_tmp_mem();

*/

#include <stdio.h>
#include <string.h>
#include "psi.h"
#include "dist.h"
#include "parse.h"
#include "sys.h"
#include "ops.h"

#include "code.e"
#include "part.e"
#include "dist.e"
#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
#include "moa_func.e"

#define MAXCONST 1024
#define MAXSYMHASH 512
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define sym_key(i) ((i)%MAXSYMHASH)

extern emit_t emit;
extern char *what_name();
extern int line_no;
extern int syntax_report;
extern int prove;

double const_numbers[MAXCONST];
int const_vars[MAXCONST];
ident_t *sym_hash[MAXSYMHASH];
ident_t dumb_var;
parser_t *expression();
char buf[256];
int shp_num=0;
save_t *save_list;
char expr_str[1024];
char call_str[1024];

 /* forward references */
statement_t *statement_list();  
statement_t *assignment_part();


ident_t **ret_table(int *size)

{
  *size=MAXSYMHASH;
  return(sym_hash);
}


clear_syms()

{
  int i;

  for (i=0; i<MAXSYMHASH; i++) {
    sym_hash[i]=NULL;
  }
}


ident_t *find_sym(int index,int talk)

{
  ident_t *ident;

  ident=sym_hash[sym_key(index)];
  while ((ident!=NULL)&&(ident->index!=index)) {
    ident=ident->next;
  }

  if ((ident==NULL)&&talk) report("Undefined identifier");
  return(ident);
}  


insert_sym(ident_t *ident, int index)

{
  if (find_sym(index,FALSE)!=NULL) 
    report("duplicate variable definition");
  else {
    ident->next=sym_hash[sym_key(index)];
    sym_hash[sym_key(index)]=ident;
    ident->index=index;
  }
}


search_parameters()

{
  int i;
  ident_t *ident;

  for (i=0; i<MAXSYMHASH; i++) {
    ident=sym_hash[i];
    while (ident!=NULL) {
      if (ISPARAMETER(ident->flags)) {
	if (ident->type==VAR_FLOAT) code_global_int(ident);
	else if (ident->array.dim->value==0) {
	  code_global_int(ident);
	  SETGLOBAL(ident->flags);
	}
      }
      ident=ident->next;
    }
  }
}


report(char *text)

{
  printf("Error on line %d: %s.\n",line_no,text);
}


expect(int sym)

{
  if ((emit.index!=sym)&&syntax_report) {
    report("syntax error");
    syntax_report=FALSE;
  }
  get_symbol();
}


int expect_name()

{
  int a;
  
  a=emit.arg;
  expect(NAME1);
  return(a);
}


double expect_number()

{
  int a,b,mag;
  double ret;

  a=emit.arg;
  expect(NUMBER1);
  if (emit.index==PERIOD1) {
    expect(PERIOD1);
    b=emit.arg;
    expect(NUMBER1);
    mag=1;
    ret=b;
    while (b>=mag) {
      ret/=10;
      mag*=10;
    }
  } else ret=0.0;
  ret+=a;

  return(ret);
}


statement_t *get_statement(int kind)

{
  save_t *save;
  statement_t *ret;

  ret=(statement_t *) get_mem(sizeof(statement_t));
  save=(save_t *) get_mem(sizeof(save_t));
  save->statement=ret;
  save->next=save_list;
  save_list=save;

  ret->kind=kind;
  switch (kind) {
  case LOOP:
    ret->d.loop=(loop_t *) get_mem(sizeof(loop_t));
    break;
  case ASSIGN:
    ret->d.assign=(assign_t *) get_mem(sizeof(assign_t));
    break;
  }
  
  return(ret);
}


convert_shp(ident_t **ident_p, expr_t *expr, ident_t *dim)

{
  int i;
  vect_t *shp;
  s_expr_t *s;
  
  if (!SCALAR(expr->dim)) {
    report("Dimension of allocation expression unknown.");
  } else if (expr->dim->ident->value!=1) {
    report("Dimension of allocation expression must be 1.");
  }

  shp=make_vect(expr);
  if (!SCALAR(shp->shp)) {
    report("Shape of allocation vector expression unknown.");
  } else if (dim->value!=shp->shp->ident->value) {
      report("Dimension mismatch in dynamic array allocation.");
  }

  (*ident_p)->array.shp=
    (ident_t **) get_mem(shp->shp->ident->value*sizeof(ident_t *));
  for (i=0; i<shp->shp->ident->value; i++) {
    s=red_rav(shp,i);
    (*ident_p)->array.shp[i]=make_ident(s);
  }

}


parser_t *var_access()

{
  int index;
  ident_t *ident,*tmp;

  if (emit.index==NAME1) {
    sprintf(expr_str+strlen(expr_str),"%s",what_name());
    index=emit.arg;
  } else {
    index=LAST;
  }
  expect(NAME1);
  ident=find_sym(index,TRUE);
  if (!HASSHAPE(ident->flags)) {
    report("Illegal use of dynamic array (shape not defined yet).");
  }
  return(psi_access(find_sym(index,FALSE)));
}


ident_t *vector_const2()


{
  ident_t *ret;
  int i,first,use_rav;

  ret=get_ident();
  ret->array.dim=&const1;
  expect(LESS1);
  sprintf(expr_str+strlen(expr_str),"<");
  i=0;
  first=TRUE;
  use_rav=FALSE;
  while ((emit.index==NUMBER1)||(emit.index==NAME1)) {
    if (emit.index==NUMBER1) {
      const_numbers[i]=expect_number();
      sprintf(expr_str+strlen(expr_str),"%f",const_numbers[i]);
      const_vars[i]=-1;
    } else {
      use_rav=TRUE;
      sprintf(expr_str+strlen(expr_str),"%s",what_name());
      const_vars[i]=expect_name();
    }
    if (emit.index!=GREATER1) sprintf(expr_str+strlen(expr_str)," ");
    if (i<MAXCONST-1) {
      i++;
    } else {
      if (first) report("Constant to large");
      first=FALSE;
    }
  }
  ret->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ret->array.shp[0]=get_ident();
  ret->array.shp[0]->type=FLOAT;
  ret->array.shp[0]->value=i;
  if (use_rav) {
    ret->type=RAV;
    ret->array.rav=(s_expr_t **) get_mem(i*sizeof(s_expr_t *));
    i--;
    for (; i>=0; i--) {
      ret->array.rav[i]=get_s_expr();
      if (const_vars[i]>=0) {
	ret->array.rav[i]->ident=find_sym(const_vars[i],TRUE);
      } else {
	ret->array.rav[i]->ident=get_ident();
	ret->array.rav[i]->ident->type=FLOAT;
	ret->array.rav[i]->ident->value=const_numbers[i];
      }
    }
  } else {
    ret->type=CONST_ARRAY;
    ret->array.cnst=(double *) get_mem(i*sizeof(double));
    i--;
    for (; i>=0; i--) ret->array.cnst[i]=const_numbers[i];
  }
  SETGLOBAL(ret->flags);

  expect(GREATER1);
  sprintf(expr_str+strlen(expr_str),">");
  return(ret);
}
    
  

parser_t *term()

{
  parser_t *ret;

  if (emit.index==NAME1) {
    ret=var_access();
  } else if (emit.index==LESS1) {
    ret=psi_access(vector_const2());
  } else {
    report("Expecting a variable or constant");
    get_symbol();
    ret=NULL;
  }
  
  return(ret);
}


int is_unop(int x)

{
  int ret;
  
  ret=FALSE;
  ret|=(emit.index==LEFTBRACKET1);
  ret|=(emit.index==IOTA1);
  ret|=(emit.index==SHP1);
  ret|=(emit.index==DIM1);
  ret|=(emit.index==TAU1);
  ret|=(emit.index==RAV1);
  ret|=(emit.index==PLUS1);
  ret|=(emit.index==MINUS1);
  ret|=(emit.index==TIMES1);
  ret|=(emit.index==DIVIDE1);

  return(ret);
}


op_t *operator()

{
  op_t *op;

  op=(op_t *) get_mem(sizeof(op_t));

  if (emit.index==LEFTBRACKET1) {
    expect(LEFTBRACKET1);
    sprintf(expr_str+strlen(expr_str)," (");
    op->omega=TRUE;
    op->func=NULL;
    op->next=operator();
    if (!op->next->omega) report("Expecting omega as an operator.");
    expect(RIGHTBRACKET1);
    sprintf(expr_str+strlen(expr_str),")");
    expect(OMEGA1);
    sprintf(expr_str+strlen(expr_str)," omega ");
    op->part=psi_access(vector_const2());
    sprintf(expr_str+strlen(expr_str)," ");
  } else {
    op->next=NULL;
    switch (emit.index) {
    case PLUS1:
      sprintf(expr_str+strlen(expr_str)," + ");
      expect(emit.index);
      if (emit.index==RED1) {
        sprintf(expr_str+strlen(expr_str)," +red ");
	expect(RED1);
	op->func=psi_red_plus;
      } else {
	sprintf(expr_str+strlen(expr_str)," + ");
	op->func=psi_plus;
      }
      break;
    case MINUS1:
      expect(emit.index);
      if (emit.index==RED1) {
	sprintf(expr_str+strlen(expr_str)," -red ");
	expect(RED1);
	op->func=psi_red_minus;
      } else {
	sprintf(expr_str+strlen(expr_str)," - ");
	op->func=psi_minus;
      }
      break;
    case TIMES1:
      expect(emit.index);
      if (emit.index==RED1) {
	sprintf(expr_str+strlen(expr_str)," *red ");
	expect(RED1);
	op->func=psi_red_times;
      } else {
	sprintf(expr_str+strlen(expr_str)," * ");
	op->func=psi_times;
      }
      break;
    case DIVIDE1:
      expect(emit.index);
      if (emit.index==RED1) {
	sprintf(expr_str+strlen(expr_str)," /red ");
	expect(RED1);
	op->func=psi_red_div;
      } else {
	sprintf(expr_str+strlen(expr_str)," / ");
	op->func=psi_div;
      }
      break;
    case PSI1:
      sprintf(expr_str+strlen(expr_str)," psi ");
      op->func=psi_psi;
      expect(emit.index);
      break;
    case IOTA1:
      sprintf(expr_str+strlen(expr_str)," iota ");
      op->func=psi_iota;
      expect(emit.index);
      break;
    case SHP1:
      sprintf(expr_str+strlen(expr_str)," shp ");
      op->func=psi_shp;
      expect(emit.index);
      break;
    case DIM1:
      sprintf(expr_str+strlen(expr_str)," dim ");
      op->func=psi_dim;
      expect(emit.index);
      break;
    case TAU1:
      sprintf(expr_str+strlen(expr_str)," tau ");
      op->func=psi_tau;
      expect(emit.index);
      break;
    case RAV1:
      sprintf(expr_str+strlen(expr_str)," rav ");
      op->func=psi_rav;
      expect(emit.index);
      break;
    case TAKE1:
      sprintf(expr_str+strlen(expr_str)," take ");
      op->func=psi_take;
      expect(emit.index);
      break;
    case DROP1:
      sprintf(expr_str+strlen(expr_str)," drop ");
      op->func=psi_drop;
      expect(emit.index);
      break;
    case PTAKE1:
      sprintf(expr_str+strlen(expr_str)," take ");
      op->func=psi_ptake;
      expect(emit.index);
      break;
    case PDROP1:
      sprintf(expr_str+strlen(expr_str)," drop ");
      op->func=psi_pdrop;
      expect(emit.index);
      break;
    case CAT1:
      sprintf(expr_str+strlen(expr_str)," cat ");
      op->func=psi_cat;
      expect(emit.index);
      break;
    default:
      report("Expecting an operator");
      expect(emit.index);
      break;
    }
    op->omega=(emit.index==OMEGA1);
    if (op->omega) {
      expect(OMEGA1);
      sprintf(expr_str+strlen(expr_str)," omega ");
      op->part=psi_access(vector_const2());
      sprintf(expr_str+strlen(expr_str)," ");
    }
  }

  return(op);
}


int isop(int i)

{
  int ret;

  ret=FALSE;
  ret|=(i==PLUS1);
  ret|=(i==MINUS1);
  ret|=(i==TIMES1);
  ret|=(i==DIVIDE1);
  ret|=(i==PSI1);
  ret|=(i==DROP1);
  ret|=(i==TAKE1);
  ret|=(i==PDROP1);
  ret|=(i==PTAKE1);
  ret|=(i==CAT1);
  ret|=(i==LEFTBRACKET1);
  return(ret);
}


parser_t *factor()

{
  op_t *op;
  parser_t *ret,*right;

  if (emit.index==LEFTPAREN1) {
    expect(LEFTPAREN1);
    sprintf(expr_str+strlen(expr_str),"(");
    ret=expression();
    expect(RIGHTPAREN1);
    sprintf(expr_str+strlen(expr_str),")");
  } else if ((emit.index==LESS1)||(emit.index==NAME1)) {
    ret=term();
  } else if (is_unop(emit.index)) {
    op=operator();
    right=expression();
    if (op->omega) ret=psi_omega1(right,op);
    else {
      ret=(*(op->func))(right);
      free(op);
    }
  } else {
    report("Expecting a factor.");
    get_symbol();
    ret=NULL;
  }

  return(ret);
}


parser_t *expression()

{
  parser_t *left,*right;
  op_t *op;

  left=factor();
  while (isop(emit.index)) {
    op=operator();
    right=factor();

    if (op->omega) left=psi_omega2(left,right,op);
    else {
      left=(*(op->func))(left,right);
      free(op);
    }
  }

  return(left);
}  


statement_t *assignment()

{
  int index;
  char *name;
  statement_t *ret;
  vect_t *loc;

  expr_str[0]=0;

  if (emit.index==LESS1) {
    loc=get_vect();
    loc->ident=vector_const2();
    loc->loc=&s_const0;
    loc->index=&s_const0;
    loc->shp=get_s_expr();
    loc->shp->ident=get_ident();
    loc->shp->ident->type=FLOAT;
    loc->shp->ident->value=loc->ident->array.shp[0]->value;
    expect(PDROP1);
    sprintf(expr_str+strlen(expr_str)," pdrop ");
  } else loc=NULL;
  
  name=what_name();
  index=expect_name();
  ret=assignment_part(loc,index,name);
  
  return(ret);
}


statement_t *assignment_part(vect_t *loc, int index, char *name)

{
  statement_t *assign,*alloc,*ret;
  ident_t *tmp;
  parser_t *result,*expr;
  
  reduction_init();

  assign=get_statement(ASSIGN);

  if (emit.index==PDROP1) {
    if (loc==NULL) {
      tmp=find_sym(index,TRUE);
      expr=psi_access(tmp);
      loc=make_vect(expr->psi);
    } else {
      report("Syntax error");
    }
    sprintf(expr_str+strlen(expr_str),name);
    sprintf(expr_str+strlen(expr_str)," drop ");
    expect(PDROP1);
    name=what_name();
    index=expect_name();
  }
  sprintf(expr_str+strlen(expr_str),name);
  tmp=find_sym(index,TRUE);
  expect(EQUAL1);
  sprintf(expr_str+strlen(expr_str),"=");
  expr=expression();
  assign->str=(char *) get_tmp_mem(strlen(expr_str)+1);
  strcpy(assign->str,expr_str);
  if (prove)
    fprintf(rfile,"Reducing:\n%s\n",expr_str);
  
  result=psi_access(tmp);
  result->psi->loc=loc;
  result->psi->bound=expr->psi->shp;
  assign->d.assign->expr=expr->psi;
  assign->d.assign->result=result->psi;
  psi_reduce(assign);
  
  return(assign);
}


statement_t *allocate()

{
  statement_t *ret;
  ident_t *array;
  parser_t *expr;

  ret=get_statement(DYNAMIC);
  expect(ALLOCATE1);
  array=find_sym(expect_name(),TRUE);
  expr=expression();
  if (expr->psi->op==NOP) {
  } else {
    report("Expecting an identifier");
  }
  if (!HASSHAPE(array->flags)) {
    convert_shp(&array,expr->psi,array->array.dim);
    SETSHAPE(array->flags);
    SETUSED(array->flags);
    ret->d.dynamic=(psi_access(array))->psi;
  } else {
    report("Array argument to allocate is not dynamic.");
  }

  return(ret);
}


statement_t *forall_statement()

{
  statement_t *loop;
  int depth;
  parser_t *left_bound,*right_bound,*loop_var;

  loop=get_statement(LOOP);

  expect(FOR1);
  expect(LEFTPAREN1);
  left_bound=term();
  loop->d.loop->lower=left_bound->psi;
  expect(LEQ1);
  loop_var=term();
  loop->d.loop->var=loop_var->psi;
  expect(LESS1);
  right_bound=term();
  loop->d.loop->upper=right_bound->psi;
  expect(RIGHTPAREN1);

  expect(LEFTBRACE1);
  loop->d.loop->body=statement_list();
  expect(RIGHTBRACE1);

  return(loop);
}


expr_t *actual()

{
  int index;
  expr_t *expr;
  ident_t *ident,*tmp;

  if (emit.index==NAME1) {
    sprintf(call_str+strlen(call_str),"_%s",what_name());
    index=emit.arg;
  } else {
    index=LAST;
  }
  expect(NAME1);
  ident=find_sym(index,FALSE);
  expr=(psi_access(ident))->psi;

  if (!HASSHAPE(ident->flags)) {
    report("Illegal use of dynamic array (shape not defined yet).");
  }

  return(expr);
}


statement_t *actual_list()

{
  statement_t *ret;
  reduced_t *node;

  node=get_reduced();
  node->type=SKIP;
  node->d.frag=actual();
  node->next=get_reduced();
  node->next->type=ALLOCATE;
  node->next->d.frag=node->d.frag;
  node->next->next=NULL;
  ret=get_statement(CALL);
  ret->d.reduced=node;
  node=node->next;
  
  while (emit.index==COMMA1) {
    expect(COMMA1);
    sprintf(call_str+strlen(call_str),",");
    node->next=get_reduced();
    node=node->next;
    node->type=ALLOCATE;
    node->d.frag=actual();
    node->next=NULL;
  }

  return(ret);
}


statement_t *call_statement(char *name)

{
  statement_t *ret;
  
  call_str[0]=0;

  sprintf(call_str+strlen(call_str),"%s(",name);
  expect(LEFTPAREN1);
  ret=actual_list();
  sprintf(call_str+strlen(call_str),");\n");
  expect(RIGHTPAREN1);
  expect(SEMI1);

  ret->str=(char *) get_mem(strlen(call_str)+1);
  strcpy(ret->str,call_str);

  return(ret);
}


statement_t *statement()

{
  int index;
  char *name;
  
  statement_t *statement;

  if (emit.index==NAME1) {
    name=what_name();
    index=expect_name();
    if (emit.index==LEFTPAREN1) {
      statement=call_statement(name);
    } else {
      expr_str[0]=0;
      statement=assignment_part(NULL,index,name);
      expect(SEMI1);
    }
  } else if (emit.index==LESS1) {
    statement=assignment();
    expect(SEMI1);
  }
  else if (emit.index==FOR1)
    statement=forall_statement();
  else if (emit.index==ALLOCATE1) {
    statement=allocate();
    expect(SEMI1);
  } else statement=NULL;

  return(statement);
}


statement_t *statement_list()

{
  statement_t *list,*node;

  if ((emit.index==NAME1)||(emit.index==FOR1)||(emit.index==LESS1)||
      (emit.index==ALLOCATE1)) {
    list=statement();
    list->next=NULL;
    collect_garbage(NULL,save_list,NULL);
    node=list;
    while ((emit.index==NAME1)||(emit.index==FOR1)||(emit.index==LESS1)||
	   (emit.index==ALLOCATE1)) {
      node->next=statement();
      node=node->next;
      node->next=NULL;
      collect_garbage(NULL,save_list,NULL);
    }
  } else list=NULL;

  return(list);
}


array_def(ident_t *ident)

{
  int i,tau;
  double num;

  expect(HAT1);
  num=expect_number();
  ident->array.dim=get_ident();
  ident->array.dim->type=FLOAT;
  ident->array.dim->value=num;
    
  tau=num;
  if (emit.index==LESS1) {
    expect(LESS1);
    if (tau==0) {
      ident->array.shp=NULL;
    } else ident->array.shp=(ident_t **) get_mem(tau*sizeof(ident_t *));
    for (i=0; i<tau; i++) {
      if (emit.index==NUMBER1) {
	num=expect_number();
	ident->array.shp[i]=get_ident();
	ident->array.shp[i]->type=FLOAT;
	ident->array.shp[i]->value=num;
      } else {
	ident->array.shp[i]=find_sym(expect_name(),FALSE);
	if (ident->array.shp[i]==NULL) {
	  report("undeclared variable");
	  ident->array.shp[i]=&dumb_var;
	}
	if (!ISPARAMETER(ident->array.shp[i]->flags))
	  report("only formal parameters are allowed in the shape definition");
      }
    }
    expect(GREATER1);
    SETSHAPE(ident->flags);
  } else {
    UNSETSHAPE(ident->flags);
    SETDYNAMIC(ident->flags);
  }
}


var_def()

{
  ident_t *ident;
  int index,i;

  expect(ARRAY1);
  index=expect_name();
  ident=get_ident();
  ident->type=ARRAY;
  sprintf(ident->string,"_%s",what_name());
  array_def(ident);
  insert_sym(ident,index);
}


var_def_part()

{
  var_def();
  expect(SEMI1);
  while (emit.index==ARRAY1) {
    var_def();
    expect(SEMI1);
  }
}


vector_const(ident_t *ident)

{
  int tau,i;
  double num;

  tau=1;
  for (i=0; i<ident->array.dim->value; i++) {
    tau*=ident->array.shp[i]->value;
  }
  fprintf(vfile,"  double %s[]={",ident->string,tau);
  expect(LESS1);
  ident->array.cnst=(double *) get_mem(tau*sizeof(double));
  for (i=0; i<tau; i++) {
    num=expect_number();
    ident->array.cnst[i]=num;
    if (i==0) 
      fprintf(vfile,"%f",num);
    else
      fprintf(vfile,", %f",num);
  }
  fprintf(vfile,"};\n");
  expect(GREATER1);
}


const_def()

{
  int index;
  int i,tau;
  double num;
  ident_t *ident;

  ident=get_ident();
  SETUSED(ident->flags);
  expect(CONST1);
  if (emit.index==ARRAY1) {
    expect(ARRAY1);
    ident->type=EMBEDED_ARRAY;
    index=expect_name();
    sprintf(ident->string,"_%s",what_name());
    array_def(ident);
    expect(EQUAL1);
    if (ident->array.dim->value==0) {
      ident->type=FLOAT;
      ident->value=expect_number();
    } else 
      vector_const(ident);
    insert_sym(ident,index);
  } else {
    report("expecting 'array'");
    get_symbol();
  }
} 


const_def_part()

{
  const_def();
  expect(SEMI1);
  while (emit.index==CONST1) {
    const_def();
    expect(SEMI1);
  }
}


global_def()

{
  int index;
  ident_t *ident;

  expect(GLOBAL1);
  if (emit.index==NAME1) {
    index=emit.arg;
  } else {
    index=LAST;
  }
  expect(NAME1);
  ident=find_sym(index,FALSE);
  if (!ISPARAMETER(ident->flags))
    SETGLOBAL(ident->flags);
  expect(SEMI1);
}


def_part()

{
  while ((emit.index==CONST1)||(emit.index==ARRAY1)||(emit.index==GLOBAL1)) {
    if (emit.index==CONST1)
      const_def_part();
    if (emit.index==ARRAY1)
      var_def_part();
    if (emit.index==GLOBAL1)
      global_def();
  }
}
    

statement_t *blockbody()

{
  statement_t *body;

  expect(LEFTBRACE1);
  if ((emit.index==CONST1)||(emit.index==ARRAY1)) def_part();
  save_list=NULL;
  body=statement_list();
  expect(RIGHTBRACE1);

  return(body);
}


param_def()
     
{
  ident_t *ident;
  int index;
  char *name;

  ident=get_ident();
  SETPARAMETER(ident->flags);
  if (emit.index==INT1) {
    expect(INT1);
    if (host) {
      fprintf(hostfile,"int ");
      fprintf(vfile,"  int ");
    } else fprintf(cfile,"int ");
    ident->type=VAR_FLOAT;
    SETSHAPE(ident->flags);
  }
  if (emit.index==ARRAY1) {
    expect(ARRAY1);
    if (host) {
      fprintf(hostfile,"double ");
      fprintf(vfile,"  double *");
    } else fprintf(cfile,"double ");
    ident->type=ARRAY;
  }
  index=expect_name();
  sprintf(ident->string,"_%s",what_name());
  if (host) {
    fprintf(hostfile,ident->string);
    fprintf(vfile,ident->string);
  } else fprintf(cfile,ident->string);

  if (ident->type==ARRAY) {
    if (host) {
      fprintf(hostfile,"[]");
    } else fprintf(cfile,"[]");
    array_def(ident);
  }

  if (host)
    fprintf(vfile,";\n");
    
  insert_sym(ident,index);

  if (!HASSHAPE(ident->flags)) {
    report("Parameters must have a specified shape");
  }
}


formal_list()

{
  param_def();
  while (emit.index==COMMA1) {
    expect(COMMA1);
    if (host) 
      fprintf(hostfile,", ");
    else 
      fprintf(cfile,", ");
    param_def();
  }
}


proc_def()

{
  int i;
  char buf[1024];
  int index;
  char *name;
  statement_t *body;
  
  max_dim=0;
  max_combined=0;
  forall_num=0;
  red_num=0;
  const_array_num=0;

  if ((tfile=fopen("temp$$$$.moa","wt"))==NULL) {
    fatal("Could'nt create temporary file.");
  }

  if ((vfile=fopen("vtemp$$$$.moa","wt"))==NULL) {
    fatal("Could'nt create temporary file.");
  }

  if (host) {
    if ((hfile=fopen("htemp$$$$.moa","wt"))==NULL)
      fatal("Could'nt create temporary file.");
  }

  fprintf(vfile,"  double *shift;\n");

  name=what_name();
  index=expect_name();
  fprintf(cfile,name);
  if (host) fprintf(hostfile,name);
  expect(LEFTPAREN1);
  fprintf(cfile,"(");
  if (host) fprintf(hostfile,"(");
  if (emit.index==INT1)
    formal_list();
  if (emit.index==ARRAY1)
    formal_list();
  expect(RIGHTPAREN1);
  fprintf(cfile,")\n\n");
  if (host) fprintf(hostfile,")\n\n");
  fprintf(cfile,"{\n");
  if (host) fprintf(hostfile,"{\n");
  if (n_procs>1)
    /* initailize int and float scalar paramenters */
    search_parameters();

  body=blockbody();
  code_c(body,partition(body));

  fclose(tfile);
  fclose(vfile);
  if (host)  fclose(hfile);

  for (i=0; i<max_combined; i++) {
    fprintf(cfile,"  double *offset%d;\n",i);
  }

  for (i=0; i<max_dim; i++) {
    fprintf(cfile,"  int i%d;\n",i);
    if (host) fprintf(hostfile,"  int i%d;\n",i);
  }

  if ((vfile=fopen("vtemp$$$$.moa","r"))==NULL) {
    fatal("Could'nt open temporary file.");
  }
  fgets(buf,1024,vfile);
  while (!feof(vfile)) {
    fputs(buf,cfile);
    fgets(buf,1024,vfile);
  }
  fclose(vfile);
  fputs("\n",cfile);

  if (n_procs>1) fprintf(cfile,"  NODE_INIT(%d);\n\n",n_procs);

  if (host) {
    fprintf(hostfile,"\n  HOST_INIT(%d);\n\n",n_procs);

    if ((hfile=fopen("htemp$$$$.moa","r"))==NULL) {
      fatal("Could'nt open temporary file.");
    }
    fgets(buf,1024,hfile);
    while (!feof(hfile)) {
      fputs(buf,hostfile);
      fgets(buf,1024,hfile);
    }
    fclose(hfile);
  }

  if ((tfile=fopen("temp$$$$.moa","r"))==NULL) {
    fatal("Could'nt open temporary file.");
  }
  fgets(buf,1024,tfile);
  while (!feof(tfile)) {
    fputs(buf,cfile);
    fgets(buf,1024,tfile);
  }
  fclose(tfile);

  fprintf(cfile,"}\n");
  if (host) {
    fprintf(hostfile,"}\n");
  }

  free_tmp_mem();    /* free any temporary memory used for this procdure */
}

directive()

{
  int name;
  char *tmp;

  expect(DOLLAR1);
  tmp=what_name();
  if (strcmp(tmp,"procs")==0) {
    name=expect_name();
    n_procs=expect_number();
  } else if (strcmp(tmp,"arch")==0) {
    name=expect_name();
    tmp=what_name();
    fprintf(cfile,"#include \"%s.h\"\n\n",tmp);
    if (host) fprintf(hostfile,"#include \"%s.h\"\n\n",tmp);
    expect_name();
  } else if (strcmp(tmp,"hostname")==0) {
    name=expect_name();
    tmp=what_name();
    host_name=(char *) get_mem(strlen(tmp)*sizeof(char));
    strcpy(host_name,tmp);
    if ((hostfile=fopen(host_name,"wt"))==NULL) {
      fatal("Could'nt open host output file");
    }
    fprintf(hostfile,"#include \"moalib.e\"\n\n");
    expect_name();
    host=TRUE;
  } else if (strcmp(tmp,"trace")==0) {
    para_trace=TRUE;
    expect_name();
  } else {
    name=expect_name();
  }
}


programx()

{
  int i;

  dumb_var.type=FLOAT;
  dumb_var.value=0;
  SETPARAMETER(dumb_var.flags);

  fprintf(cfile,"#include <stdlib.h>\n");
  fprintf(cfile,"#include \"moalib.e\"\n\n");

  while (emit.index==DOLLAR1) {
    directive();
  }

  while (emit.index==NAME1) {
    clear_syms();
    proc_def();
    fprintf(cfile,"\n\n");
  }
  if (host) fclose(hostfile);
}
