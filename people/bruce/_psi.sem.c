#include <stdio.h>
#include <stdlib.h>
#include "psi.h"
#include "dist.h"
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
#include "_psi.sem.h" 
#define sym_key(i) ((i)%MAXSYMHASH)
 
extern char *what_name();
extern int line_no; /* current line number */
extern int syntax_report;  /* suppress syntax errors when FALSE */
extern int prove; /* TRUE if reductions are to be output */
#define LAST 50 
char last_name[256];
int name_no=LAST; 
int shp_num=0;
double const_numbers[MAXCONST];
int const_vars[MAXCONST];
ident_t *sym_hash[MAXSYMHASH];  /* hash table of identifiers */
ident_t dumb_var;               /* dummy variable */
char buf[256];                  /* temporary string storage */
char expr_str[1024];  /* current line being parsed */
char call_str[1024];  /* a procedure call */
/* find_sym - look up an identifier in the symbol table.  If talk is
     TRUE and the identifier is not found report an error. */
#define MAXKEY 631
#define uchar unsigned char
symbol_t *hash[MAXKEY];
int vector_const2_sprint,vector_const2_rav,vector_const2_num,use_rav;
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


/* insert_sym - insert a new identifier into the symbol table */

void insert_sym(ident_t *ident, int index)

{
  if (find_sym(index,FALSE)!=NULL)
    report("duplicate variable definition");
  else {
    ident->next=sym_hash[sym_key(index)];
    sym_hash[sym_key(index)]=ident;
    ident->index=index;
  }
}

/* insert - inserts a name into the hash table at key. */
 
symbol_t *insert(uchar isname, char *name, int index, int key)
 
{
  int size;
  symbol_t *new;
 
  new=(symbol_t *) malloc(sizeof(symbol_t));
  new->next=hash[key];
  size=strlen(name);
  new->name=(char *) malloc(size+1);
  strcpy(new->name,name);
  new->isname=isname;
  new->index=index;
  hash[key]=new;
 
  return(new);
}
/* search - search for a name in the symbol table, if none is found
     it is inserted. */
 
void search(char *name, uchar *isname, int *index)
 
{
  symbol_t *sym;
  int key_no;
  uchar done;
 
  key_no=key(name);
  sym=hash[key_no];
  done=FALSE;
  while ((!done)&&(sym!=NULL)) {
    if (strcmp(sym->name,name)==0) {
      *isname=sym->isname;
      *index=sym->index;
      done=TRUE;
    }
    if (!done) sym=sym->next;
  }
  if (!done) {
    *isname=TRUE;
    *index=(++name_no);
    sym=insert(TRUE,name,*index,key_no);
    done=TRUE;
  }
  strcpy(last_name,sym->name);
}
 

int find_index(char *name) 
{
	uchar isname;
	int index;
	search(name,&isname,&index);
	return index;
}

/*ident_t *global_dec()
{
  int index;
  ident_t *ident;
 
  if (emit.index==NAME1) {
    index=emit.arg;
  } else {
    index=LAST;
  }
  ident=find_sym(index,FALSE);
  if (!ISPARAMETER(ident->flags))
    SETGLOBAL(ident->flags);
  return ident;
}
*/
void arg_dec_int(char *name)
{
	ident_t *ident;
  ident=get_ident();
  SETPARAMETER(ident->flags);
  if (host) {
    fprintf(hostfile,"int ");
    fprintf(vfile,"  int ");
  } else fprintf(cfile,"int ");
  ident->type=VARIABLE;
  SETSHAPE(ident->flags);
  sprintf(ident->string,"_%s",name);
  if (host) {
    fprintf(hostfile,ident->string);
    fprintf(vfile,ident->string);
  } else fprintf(cfile,ident->string);
  if (host)
    fprintf(vfile,";\n");
  insert_sym(ident,find_index(name));
 
  if (!HASSHAPE(ident->flags)) {
    report("Parameters must have a specified shape");
  }
}

ident_t *var_dec_array(char *name,int number)
{
  ident_t *ident;
  ident=get_ident();
  ident->type=ARRAY;
  ident->real=TRUE;
  sprintf(ident->string,"_%s",name);
    /*i=0;*/
    /*array_def(ident);*/
    ident->array.dim=get_ident();
    ident->array.dim->type=CONSTANT;
    ident->array.dim->value=number;
}

ident_t *var_dec_array_2(char *name,int tauvec, int tau, ident_t *ident)
{  
  int i;

  if (tau==0) {
    ident->array.shp=NULL;
  } else ident->array.shp=(ident_t **) get_mem(tau*sizeof(ident_t *));
  /* {check to make sure tauvec == tau, issue error... */
  for (i=0; i<tau; i++) {
    if (const_vars[i] == -1) {
       ident->array.shp[i]=get_ident();
       ident->array.shp[i]->type=CONSTANT;
       ident->array.shp[i]->value=const_numbers[i];
    } else {
      ident->array.shp[i]=find_sym(const_vars[i],FALSE);
      if (ident->array.shp[i]==NULL) {
        report("undeclared variable");
        ident->array.shp[i]=&dumb_var;
      }
      if (!ISPARAMETER(ident->array.shp[i]->flags))
        report("only formal parameters are allowed in the shape definition");
    }
  }
  SETSHAPE(ident->flags);
  insert_sym(ident,find_index(name)); 
  return ident;
}

ident_t *var_dec_array_3(char *name,ident_t *ident)
{
	UNSETSHAPE(ident->flags);
	SETDYNAMIC(ident->flags);
	insert_sym(ident,find_index(name));
	return ident;
}

ident_t *const_dec_array(char *name,int number)
{
  ident_t *ident;
  ident=get_ident();
  SETUSED(ident->flags);
     ident->type=EMBEDED_ARRAY;
    sprintf(ident->string,"_%s",name);

  ident->type=ARRAY;
  ident->real=TRUE;
    /* i=0; */
    /*array_def(ident);*/
    ident->array.dim=get_ident();
    ident->array.dim->type=CONSTANT;
    ident->array.dim->value=number;
	return ident;
}

ident_t *const_dec_array_2(int tauvec, int tau, ident_t *ident)
{  
  int i;
  if (tau==0) {
    ident->array.shp=NULL;
  } else ident->array.shp=(ident_t **) get_mem(tau*sizeof(ident_t *));
  /* {check to make sure tauvec == tau, issue error... */
  for (i=0; i<tau; i++) {
    if (const_vars[i] == -1) {
       ident->array.shp[i]=get_ident();
       ident->array.shp[i]->type=CONSTANT;
       ident->array.shp[i]->value=const_numbers[i];
    } else {
      ident->array.shp[i]=find_sym(const_vars[i],FALSE);
      if (ident->array.shp[i]==NULL) {
        report("undeclared variable");
        ident->array.shp[i]=&dumb_var;
      }
      if (!ISPARAMETER(ident->array.shp[i]->flags))
        report("only formal parameters are allowed in the shape definition");
    }
  }
  SETSHAPE(ident->flags); 
  return ident;
}

ident_t *const_dec_array_3(char *name,ident_t *ident) 
{
  int tau,i;
  double num;
 
  tau=1;
  for (i=0; i<ident->array.dim->value; i++) {
    tau*=ident->array.shp[i]->value;
  }
  fprintf(vfile,"  double %s[]={",ident->string,tau);
  ident->array.cnst=(double *) get_mem(tau*sizeof(double));
  for (i=0; i<tau; i++) {
    num=const_numbers[i];
    ident->array.cnst[i]=num;
    if (i==0)
      fprintf(vfile,"%f",num);
    else {
      if (!(i%5))
        fprintf(vfile,",\n    %f",num);
      else
        fprintf(vfile,", %f",num);
    }
   }
   fprintf(vfile,");\n");

    insert_sym(ident,find_index(name));
	return ident;
}

ident_t *const_dec_array_4(char *name,ident_t *ident,float number)
{
    ident->type=CONSTANT;
    ident->real=TRUE;
    ident->value=number;
    insert_sym(ident,find_index(name));
	return ident;
}

ident_t *arg_dec_array(char *name,int number)
{
  ident_t *ident;

  ident=get_ident();
  SETPARAMETER(ident->flags);
    if (host) {
      fprintf(hostfile,"double ");
      fprintf(vfile,"  double *");
    } else fprintf(cfile,"double ");
    ident->type=ARRAY;
  sprintf(ident->string,"_%s",name);
  if (host) {
    fprintf(hostfile,ident->string);
    fprintf(vfile,ident->string);
  } else fprintf(cfile,ident->string);
 
    if (host) {
      fprintf(hostfile,"[]");
    } else fprintf(cfile,"[]");
    /* i=0; */
    /*array_def(ident);*/
    ident->array.dim=get_ident();
    ident->array.dim->type=CONSTANT;
    ident->array.dim->value=number;
	return ident;
}

ident_t *arg_dec_array_2(char *name,int tauvec, int tau, ident_t *ident)
{  
  int i;

  if (tau==0) {
    ident->array.shp=NULL;
  } else ident->array.shp=(ident_t **) get_mem(tau*sizeof(ident_t *));
  /* {check to make sure tauvec == tau, issue error... */
  for (i=0; i<tau; i++) {
    if (const_vars[i] == -1) {
       ident->array.shp[i]=get_ident();
       ident->array.shp[i]->type=CONSTANT;
       ident->array.shp[i]->value=const_numbers[i];
    } else {
      ident->array.shp[i]=find_sym(const_vars[i],FALSE);
      if (ident->array.shp[i]==NULL) {
        report("undeclared variable");
        ident->array.shp[i]=&dumb_var;
      }
      if (!ISPARAMETER(ident->array.shp[i]->flags))
        report("only formal parameters are allowed in the shape definition");
    }
  }
  SETSHAPE(ident->flags); 
  if (host)
    fprintf(vfile,";\n");
 
  insert_sym(ident,find_index(name));
 
  if (!HASSHAPE(ident->flags)) {
    report("Parameters must have a specified shape");
  }
  if(tau!=tauvec) {
	report("Number of components in shape does not match dimension");
  }
  return ident;
}

ident_t *arg_dec_array_3(char *name,ident_t *ident)
{
	UNSETSHAPE(ident->flags);
	SETDYNAMIC(ident->flags);
	insert_sym(ident,find_index(name));
	return ident;
}

statement_t *assignment_psi(ident_t *ident, char *name,parser_t *expr)
{
	uchar isname;
	int index; 
	statement_t *assign,*alloc,*ret;
  ident_t *tmp;
	vect_t *loc;
  parser_t *result;

	expr_str[0]=0;

 	loc=get_vect();
    loc->ident=ident;
    loc->loc=&s_const0;
    loc->index=&s_const0;
    loc->shp=get_s_expr();
    loc->shp->ident=get_ident();
    loc->shp->ident->type=CONSTANT;
    loc->shp->ident->real=FALSE;
    loc->shp->ident->value=loc->ident->array.shp[0]->value;
      sprintf(expr_str+strlen(expr_str)," psi ");
	search(name,&isname,&index);
	reduction_init();

  assign=get_statement(ASSIGN);

  strcat(expr_str,name);
  tmp=find_sym(index,TRUE);
  sprintf(expr_str+strlen(expr_str),"=");
  assign->str=(char *) get_tmp_mem(strlen(expr_str)+1);
  strcpy(assign->str,expr_str);
  if (prove)
    fprintf(rfile,"Reducing:\n%s\n",expr_str);
 
  result=psi_access(tmp);
  result->psi->loc=loc;
  result->psi->bound=expr->psi->shp;
  assign->d.assign->expr=expr->psi;
  assign->d.assign->result=result->psi;
  psi_reduce(assign,TRUE);
	return(assign);
}

statement_t *assignment_pdrop(ident_t *ident, char *name,parser_t *expr)
{
	uchar isname;
	int index; 
	statement_t *assign,*alloc,*ret;
  ident_t *tmp;
	vect_t *loc;
  parser_t *result;

	expr_str[0]=0;

 	loc=get_vect();
    loc->ident=ident;
    loc->loc=&s_const0;
    loc->index=&s_const0;
    loc->shp=get_s_expr();
    loc->shp->ident=get_ident();
    loc->shp->ident->type=CONSTANT;
    loc->shp->ident->real=FALSE;
    loc->shp->ident->value=loc->ident->array.shp[0]->value;
      sprintf(expr_str+strlen(expr_str)," pdrop ");
	search(name,&isname,&index);
	reduction_init();

  assign=get_statement(ASSIGN);
      tmp=find_sym(index,TRUE);
      expr=psi_access(tmp);
      loc=make_vect(expr->psi);
    sprintf(expr_str+strlen(expr_str),name);
    sprintf(expr_str+strlen(expr_str)," drop ");
    index=find_index(name);

  strcat(expr_str,name);
  tmp=find_sym(index,TRUE);
  sprintf(expr_str+strlen(expr_str),"=");
  assign->str=(char *) get_tmp_mem(strlen(expr_str)+1);
  strcpy(assign->str,expr_str);
  if (prove)
    fprintf(rfile,"Reducing:\n%s\n",expr_str);
 
  result=psi_access(tmp);
  result->psi->loc=loc;
  result->psi->bound=expr->psi->shp;
  assign->d.assign->expr=expr->psi;
  assign->d.assign->result=result->psi;
  psi_reduce(assign,TRUE);
	return(assign);
}

statement_t *assignment_normal(char *name,parser_t *expr)
{
	uchar isname;
	int index; 
	statement_t *assign,*alloc,*ret;
  ident_t *tmp;
  parser_t *result;
	vect_t *loc;

	expr_str[0]=0;
	loc = NULL;
	reduction_init();
	search(name,&isname,&index);
  assign=get_statement(ASSIGN);
  strcat(expr_str,name);
  tmp=find_sym(index,TRUE);
  sprintf(expr_str+strlen(expr_str),"=");
  assign->str=(char *) get_tmp_mem(strlen(expr_str)+1);
  strcpy(assign->str,expr_str);
  if (prove)
    fprintf(rfile,"Reducing:\n%s\n",expr_str);
 
  result=psi_access(tmp);
  result->psi->loc=loc;
  result->psi->bound=expr->psi->shp;
  assign->d.assign->expr=expr->psi;
  assign->d.assign->result=result->psi;
  psi_reduce(assign,TRUE);
	return(assign);
}

void declaration_footer()
{
	dual_fprintf(")\n\n");
	if(n_procs>1) {
		/* initialize int and float scalar parameters */
		search_parameters();
	}
}

void dual_fprintf(char *msg)
{
	fprintf(cfile,msg);
	if(host) fprintf(hostfile,msg);
}

void executable_header()
{
  dumb_var.type=CONSTANT;
  dumb_var.value=0;
  SETPARAMETER(dumb_var.flags);
  
  fprintf(cfile,"#include <stdlib.h>\n");
  fprintf(cfile,"#include \"moalib.e\"\n\n");
  vector_const2_sprint=0; 
}

void exectutable_post_declaration()
{
  if(picl) {
    fpprintf(cfile,"#include \"picl.h\"\n\n");
    if(host) 
      fprintf(cfile,"#include \"picl.h\"\n\n");
  }
}

void executable_footer()
{
   if (host) fclose(hostfile);
}

parser_t *expression_unary_operator(char *name, parser_t *expr2,
	parser_t *(*func)())
{
	strcat(expr_str,name);
	return (*func)(expr2);
}

parser_t *expression_binary_operator(parser_t *expr1,char *name, parser_t *expr2,
	parser_t *(*func)())
{
	strcat(expr_str,name);
	return (*func)(expr1,expr2);
}

parser_t *expression_name(char *name)
{
	int index;
	uchar isname;
  ident_t *ident,*tmp;
 
  strcat(expr_str,name);
  search(name,&isname,&index);
  ident=find_sym(index,TRUE);
  if (!HASSHAPE(ident->flags)) {
    report("Illegal use of dynamic array (shape not defined yet).");
  }
	return psi_access (find_sym(index,FALSE));
}

statement_t *for_statement(parser_t *expr1,parser_t *expr2,
	parser_t *expr3,statement_t *state1)
{
	statement_t *loop;

	loop=get_statement(LOOP);
	loop->d.loop->lower=expr1->psi;
	loop->d.loop->var=expr2->psi;
	loop->d.loop->upper=expr3->psi;
	loop->d.loop->body=state1;
	return loop;
}

void procedure_header()
{
  int i;
  char buf[1024];
  int index;
  char *name;
  statement_t *body;

  clear_syms(); 
  /* reset the counts of utility variables used */
  max_dim=0;
  max_combined=0;
  forall_num=0;
  red_num=0;
  const_array_num=0;
 
  /* open temporary files */
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
 
  fprintf(vfile,"  double *shift;\n");
  vector_const2_sprint=0;
}

void procedure_post_declaration()
{
	clear_saves();
  vector_const2_sprint=1;
}

void procedure_footer(statement_t *body)
{
  int i;
  code_c(body,partition(body));
 
  fclose(tfile);
  fclose(vfile);
  if (host)  fclose(hfile);
 
  /* allocate utility variables */
  for (i=0; i<max_combined; i++) {
    fprintf(cfile,"  double *offset%d;\n",i);
  }
 
  for (i=0; i<max_dim; i++) {
    fprintf(cfile,"  int i%d;\n",i);
    if (host) fprintf(hostfile,"  int i%d;\n",i);
  }
 
  /* copy temporary files to the output */
 
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
 
 
  if (n_procs>1) {
    if (genmpi) fprintf (cfile,"  NODE_INIT(argc,argv);\n");
    else fprintf(cfile,"  NODE_INIT(%d);\n\n",n_procs);
  }
 
  if (host) {
    fprintf(hostfile,"\n  HOST_INIT(%d);\n\n",n_procs);
  }
 
  if (picl) {
    fprintf(cfile,"  TRACE_START(\"%s\");\n",picl_file);
    if (host)
      fprintf(hostfile,"  TRACE_START(\"%s\");\n",picl_file);
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
 
  if (picl) {
    fprintf(cfile,"  TRACE_END();\n");
    if (host)
      fprintf(hostfile,"  TRACE_END();\n");
  }
 
  if (genmpi) fprintf (cfile,"  NODE_CLEANUP();\n");
  fprintf(cfile,"}\n");
  if (host) {
    fprintf(hostfile,"}\n");
  }
 
  free_tmp_mem();    /* free any temporary memory used for this procdure */
  fprintf(cfile,"\n\n");
}

statement_t *do_procedure_call (char *name, parser_t *expr)
{
  return (NULL);
}

int vector_const2_number(float num) 
{
  int i;

  i=vector_const2_num;
  const_numbers[i]=num;
  if(vector_const2_sprint) {
     sprintf(expr_str+strlen(expr_str),"%f ",const_numbers[i]);
  }
  const_vars[i]=-1;
  if (i<MAXCONST-1) {
    vector_const2_num++;
  } else {
    /*if (first) */
    report("Constant to large");
    /*first=FALSE;*/
  }
  return (1);
}

void vector_const2_init()
{
	if(vector_const2_sprint) sprintf(expr_str+strlen(expr_str),"<");
	vector_const2_rav=FALSE;
	vector_const2_num=0;
}

void vector_const2_footer()
{
	if(vector_const2_sprint) sprintf(expr_str+strlen(expr_str),">");
}

ident_t *vector_const2_ident()  
/* this routine will create ident type for previously parsed vector */
{
	ident_t *ret;
  int i,use_rav;
 
	use_rav=vector_const2_rav;
  ret=get_ident();
  ret->array.dim=&const1;
  ret->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ret->array.shp[0]=get_ident();
  ret->array.shp[0]->type=CONSTANT;
  ret->array.shp[0]->real=FALSE;
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
        ret->array.rav[i]->ident->type=CONSTANT;
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
  return(ret);
}

int vector_const2_name(char *name) 
{
  int i;

  i=vector_const2_num;
  use_rav=TRUE;
  sprintf(expr_str+strlen(expr_str),"%s",what_name());
  const_vars[i]=name;
  sprintf(expr_str+strlen(expr_str)," ");
  if (i<MAXCONST-1) {
    vector_const2_num++;
  } else {
    /*if (first) */report("Constant to large");
    /*first=FALSE;*/
  }
  return (1);
}

void directive_trace()
{
   /* have parallel programs print information while running */
   para_trace=TRUE;
}

void directive_procs(int number)
{
    /* number of processors */
    n_procs=number;
}  

void directive_arch(char *option)
{
    /* archtecture type */
    if (strcmp(option,"mpimac")==0) {
      if (host) fatal ("mpi not allowed with host");
      else genmpi=TRUE;
    }
    fprintf(cfile,"#include \"%s.h\"\n\n",option);
    if (host) fprintf(hostfile,"#include \"%s.h\"\n\n",option);
}

void directive_hostname(char *option) 
{
    /* name of a host file */
    if (genmpi) fatal ("host not allowed with mpi");
    host_name=(char *) get_mem(strlen(option)*sizeof(char));
    strcpy(host_name,option);
    if ((hostfile=fopen(host_name,"wt"))==NULL) {
      fatal("Couldn't open host output file");
    }
    fprintf(hostfile,"#include \"moalib.e\"\n\n");
    host=TRUE;
}

void directive_picl(char *option)
{
    /* generate picl trace files */
    picl_file=(char *) get_mem(strlen(option)*sizeof(char));
    strcpy(picl_file,option);
    picl=TRUE;
}

void declaration_name(char *name)
{
  dual_fprintf(name); 
  dual_fprintf("(");
  if(genmpi) fprtinf(cfile,"int argc, char *argv[],");
}
