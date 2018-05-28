/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include "psi.h"
#include "parse.h"
#include "ops.h"

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

float const_numbers[MAXCONST];
int const_vars[MAXCONST];
ident_t *sym_hash[MAXSYMHASH];
ident_t dumb_var;
parser_t *expression();
char buf[256];
int shp_num=0;


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


ident_t *find_sym(index)

{
  ident_t *ident;

  ident=sym_hash[sym_key(index)];
  while ((ident!=NULL)&&(ident->index!=index)) {
    ident=ident->next;
  }

  return(ident);
}  


insert_sym(ident_t *ident, int index)

{
  if (find_sym(index)!=NULL) 
    report("duplicate variable definition");
  else {
    ident->next=sym_hash[sym_key(index)];
    sym_hash[sym_key(index)]=ident;
    ident->index=index;
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


float expect_number()

{
  int a,b,mag;
  float ret;

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


ident_t **convert_shp(vect_t *shp, ident_t *dim)

{
  int i;
  s_expr_t *s;
  ident_t **new_shp,*ident;
  
  if (!SCALAR(shp->shp)) {
    fatal("Dimension of dynamic array undetermined.");
  } else {
    if (dim->value!=shp->shp->ident->value)
      report("Dimension mismatch in dynamic array allocation.");
  }
  new_shp=(ident_t **) get_mem(shp->shp->ident->value);
  for (i=0; i<shp->shp->ident->value; i++) {
    s=red_rav(shp,i);
    if (!SCALAR(s)) {
      fprintf(vfile,"  int shp%d;\n",shp_num);
      dotab(0);
      fprintf(tfile,"shp%d=",shp_num);
      print_s_expr(tfile,s);
      fprintf(tfile,";\n");
      ident=get_ident();
      ident->type=VAR_FLOAT;
      sprintf(ident->string,"shp%d",shp_num);
      shp_num++;
    } else ident=s->ident;
    new_shp[i]=ident;
  }

  return(new_shp);
}


ident_allocation(ident_t *ident)

{
  int i;

  dotab(0);
  fprintf(tfile,"  %s=(float *) malloc(",ident->string);
  for (i=0; i<ident->array.dim->value; i++) {
    if (i>0) fprintf(tfile,"*");
    print_ident(tfile,ident->array.shp[i]);
  }
  fprintf(tfile,"*sizeof(float));\n\n");
}


parser_t *var_access()

{
  int index;
  ident_t *ident,*tmp;

  if (emit.index==NAME1) {
    index=emit.arg;
  } else {
    index=LAST;
  }
  expect(NAME1);
  ident=find_sym(index);
  if (!HASSHAPE(ident->flags)) {
    report("Illegal use of dynamic array (shape not defined yet).");
    tmp=ident;
    ident=get_ident();
    *ident=*tmp;
    ident->type=VAR_FLOAT;
  }
  return(psi_access(find_sym(index)));
}


ident_t *vector_const2()


{
  ident_t *ret;
  int i,first,use_rav;

  ret=get_ident();
  ret->array.dim=&const1;
  expect(LESS1);
  i=0;
  first=TRUE;
  use_rav=FALSE;
  while ((emit.index==NUMBER1)||(emit.index==NAME1)) {
    if (emit.index==NUMBER1) {
      const_numbers[i]=expect_number();
      const_vars[i]=-1;
    } else {
      use_rav=TRUE;
      const_vars[i]=expect_name();
    }
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
    ret->array.rav=(s_expr_t **) get_mem(i*sizeof(float));
    i--;
    for (; i>=0; i--) {
      ret->array.rav[i]=get_s_expr();
      if (const_vars[i]>=0) {
	ret->array.rav[i]->ident=find_sym(const_vars[i]);
      } else {
	ret->array.rav[i]->ident=get_ident();
	ret->array.rav[i]->ident->type=FLOAT;
	ret->array.rav[i]->ident->value=const_numbers[i];
      }
    }
  } else {
    ret->type=CONST_ARRAY;
    ret->array.cnst=(float *) get_mem(i*sizeof(float));
    i--;
    for (; i>=0; i--) ret->array.cnst[i]=const_numbers[i];
  }
  
  expect(GREATER1);
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


parser_t *factor()

{
  parser_t *ret;

  if (emit.index==LEFTPAREN1) {
    expect(LEFTPAREN1);
    ret=expression();
    expect(RIGHTPAREN1);
  } else if ((emit.index==LESS1)||(emit.index==NAME1)) {
    ret=term();
  } else if (is_unop(emit.index)) {
    switch (emit.index) {
    case IOTA1:
      expect(IOTA1);
      ret=psi_iota(expression());
      break;
    case SHP1:
      expect(SHP1);
      ret=psi_shp(expression());
      break;
    case DIM1:
      expect(DIM1);
      ret=psi_dim(expression());
      break;
    case TAU1:
      expect(TAU1);
      ret=psi_tau(expression());
      break;
    case RAV1:
      expect(RAV1);
      ret=psi_rav(expression());
      break;
    case PLUS1:
      expect(PLUS1);
      expect(RED1);
      ret=psi_red_plus(expression());
      break;
    case MINUS1:
      expect(MINUS1);
      expect(RED1);
      ret=psi_red_minus(expression());
      break;
    case TIMES1:
      expect(TIMES1);
      expect(RED1);
      ret=psi_red_times(expression());
      break;
    case DIVIDE1:
      expect(DIVIDE1);
      expect(RED1);
      ret=psi_red_div(expression());
      break;

    }
  } else {
    report("Expecting a factor.");
    get_symbol();
    ret=NULL;
  }

  return(ret);
}


op_t *operator()

{
  op_t *op;

  op=(op_t *) get_mem(sizeof(op_t));

  if (emit.index==LEFTPAREN1) {
    expect(LEFTPAREN1);
    op->omega=TRUE;
    op->func=NULL;
    op->next=operator();
    if (!op->next->omega) report("Expecting omega as an operator.");
    expect(RIGHTPAREN1);
    expect(OMEGA1);
    op->part=psi_access(vector_const2());
  } else {
    op->next=NULL;
    switch (emit.index) {
    case PLUS1:
      op->func=psi_plus;
      expect(emit.index);
      break;
    case MINUS1:
      op->func=psi_minus;
      expect(emit.index);
      break;
    case TIMES1:
      op->func=psi_times;
      expect(emit.index);
      break;
    case DIVIDE1:
      op->func=psi_div;
      expect(emit.index);
      break;
    case PSI1:
      op->func=psi_psi;
      expect(emit.index);
      break;
    case TAKE1:
      op->func=psi_take;
      expect(emit.index);
      break;
    case DROP1:
      op->func=psi_drop;
      expect(emit.index);
      break;
    case PTAKE1:
      op->func=psi_ptake;
      expect(emit.index);
      break;
    case PDROP1:
      op->func=psi_pdrop;
      expect(emit.index);
      break;
    case CAT1:
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
      op->part=psi_access(vector_const2());
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
  ret|=(i==LEFTPAREN1);
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


assignment()

{
  ident_t *tmp;
  parser_t *result,*expr;

  tmp=find_sym(expect_name());
  expect(EQUAL1);
  expr=expression();
  if (!HASSHAPE(tmp->flags)) {
    tmp->array.shp=convert_shp(expr->psi->shp,tmp->array.dim);
    ident_allocation(tmp);
    SETSHAPE(tmp->flags);
  }
  result=psi_access(tmp);  /* prolong this in case the shape was'nt defined */
  psi_assign(expr,result);
}


forall_statement()

{
  int depth;
  parser_t *left_bound,*right_bound,*loop_var;

  expect(FORALL1);
  expect(LEFTPAREN1);
  left_bound=term();
  expect(LEQ1);
  loop_var=term();
  expect(LESS1);
  right_bound=term();
  expect(RIGHTPAREN1);

  depth=start_loop(loop_var->psi,left_bound->psi,right_bound->psi);
  expect(LEFTBRACE1);
  statement_list();
  expect(RIGHTBRACE1);
  end_loop(depth);
}


statement()

{
  if (emit.index==NAME1) {
    assignment();
    expect(SEMI1);
  }
  else if (emit.index==FORALL1)
    forall_statement();
}


statement_list()

{
  while ((emit.index==NAME1)||(emit.index==FORALL1)) {
    statement();
  }
}


array_def(ident_t *ident)

{
  int i,tau;
  float num;

  expect(HAT1);
  num=expect_number();
  ident->array.dim=get_ident();
  ident->array.dim->type=FLOAT;
  ident->array.dim->value=num;
  tau=num;
  if (emit.index==LESS1) {
    expect(LESS1);
    ident->array.shp=(ident_t **) get_mem(tau*sizeof(ident_t *));
    for (i=0; i<tau; i++) {
      if (emit.index==NUMBER1) {
	num=expect_number();
	ident->array.shp[i]=get_ident();
	ident->array.shp[i]->type=FLOAT;
	ident->array.shp[i]->value=num;
      } else {
	ident->array.shp[i]=find_sym(expect_name());
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
  if (HASSHAPE(ident->flags)) {
    fprintf(vfile,"  float %s",ident->string);
    if (ident->array.dim->value>0) {
      fprintf(vfile,"[");
      for (i=0; i<ident->array.dim->value; i++) {
	if (i==0) {
	  if (ident->array.shp[i]->type==FLOAT)
	    fprintf(vfile,"%d",(int) ident->array.shp[i]->value);
	  else
	    fprintf(vfile,"%s",ident->array.shp[i]->string);
	} else {
	  if (ident->array.shp[i]->type==FLOAT)
	    fprintf(vfile,"*%d",(int) ident->array.shp[i]->value);
	  else
	    fprintf(vfile,"*%s",ident->array.shp[i]->string);
	}	
      }
      fprintf(vfile,"]");
    }
  } else {
    fprintf(vfile,"  float *%s",ident->string);
  }

  fprintf(vfile,";\n");
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
  float num;

  tau=1;
  for (i=0; i<ident->array.dim->value; i++) {
    tau*=ident->array.shp[i]->value;
  }
  fprintf(vfile,"  float %s[]={",ident->string,tau);
  expect(LESS1);
  ident->array.cnst=(float *) get_mem(tau*sizeof(float));
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
  float num;
  ident_t *ident;

  ident=get_ident();
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


def_part()

{
  while ((emit.index==CONST1)||(emit.index==ARRAY1)) {
    if (emit.index==CONST1)
      const_def_part();
    if (emit.index==ARRAY1)
      var_def_part();
  }
}
    

blockbody()

{
  expect(LEFTBRACE1);
  if ((emit.index==CONST1)||(emit.index==ARRAY1)) def_part();
  statement_list();
  expect(RIGHTBRACE1);
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
    fprintf(cfile,"int ");
    ident->type=VAR_FLOAT;
    SETSHAPE(ident->flags);
  }
  if (emit.index==ARRAY1) {
    expect(ARRAY1);
    fprintf(cfile,"float ");
    ident->type=ARRAY;
  }
  index=expect_name();
  sprintf(ident->string,"_%s",what_name());
  fprintf(cfile,ident->string);
  if (ident->type==ARRAY) {
    fprintf(cfile,"[]");
    array_def(ident);
  }
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
  
  max_dim=0;
  forall_num=0;
  red_num=0;
  temp_array_num=0;
  const_array_num=0;
  vect_tmp_num=0;
  scalar_num=0;
  temp_used=FALSE;

  if ((tfile=fopen("temp$$$$.moa","wt"))==NULL) {
    fatal("Could'nt create temporary file.");
  }

  if ((vfile=fopen("vtemp$$$$.moa","wt"))==NULL) {
    fatal("Could'nt create temporary file.");
  }

/*
  if ((afile=fopen("atemp$$$$.moa","wt"))==NULL) {
    fatal("Could'nt create temporary file.");
  }
*/

  fprintf(vfile,"  int shift,offset;\n");

  index=expect_name();
  name=what_name();
  fprintf(cfile,name);
  expect(LEFTPAREN1);
  fprintf(cfile,"(");
  if (emit.index==INT1)
    formal_list();
  if (emit.index==ARRAY1)
    formal_list();
  expect(RIGHTPAREN1);
  fprintf(cfile,")\n\n");
  fprintf(cfile,"{\n");

  blockbody();

  fclose(tfile);
  fclose(vfile);
/*  fclose(afile); */

  for (i=0; i<max_dim; i++) {
    fprintf(cfile,"  int i%d;\n",i);
  }
  fprintf(cfile,"  int step1[%d];\n",max_dim);
  fprintf(cfile,"  int step2[%d];\n",max_dim);

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

/*
  if ((afile=fopen("atemp$$$$.moa","r"))==NULL) {
    fatal("Could'nt open temporary file.");
  }
  fgets(buf,1024,afile);
  while (!feof(afile)) {
    fputs(buf,cfile);
    fgets(buf,1024,afile);
  }
  fclose(afile);
*/

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
}


programx()

{
  int i;

  dumb_var.type=FLOAT;
  dumb_var.value=0;
  SETPARAMETER(dumb_var.flags);

  fprintf(cfile,"#include \"moalib.e\"\n\n");
  while (emit.index==NAME1) {
    clear_syms();
    proc_def();
    fprintf(cfile,"\n\n");
  }
}
