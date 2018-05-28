/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   code.c - This module contains the procedures related to generating code
     for array operations on a uniprocessor.  In the case of multiprocessor
     code generation control is passed on to the dist.c module.
   
   v0.3 Scott Thibault - 8/93
               This code was scattered previous to v0.3.
        Scott Thibault - 10/93
	   - code_reduced was changed to reflect the fact that now NOP type
	   reduced objects are lists of assignments instead of just one.
	   - To do this code_expr was added to take the code out of the
	   switch in code_reduced and separate_reduced was added to
	   separated the list of assignments.
	   - do_location and do_gamma were changed so that offset and
	   shift include the base address now.

*/

#include <stdio.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"

#include "psi.e"
#include "dist.e"
#include "part.e"
#include "parse.e"
#include "ident.e"
#include "vect.e"
#include "sys.e"

#define NOTALLOCATED(a) ((!ISUSED(a->flags))&&(a->type!=RAV)&&(a->type!=CONST_ARRAY)&&(a->type!=CONSTANT)&&(a->type!=IOTA))


extern void code_extended (reduced_t *node);


typedef struct step_node {
  int              num;
  s_expr_t         **steps;
  struct step_node *next;
} steps_t;

typedef struct names {
  char name[18];
  struct names *next;
} name_t;


int const_num=0;
int const_array_num=0;
int max_dim=0;
int max_combined=0;
name_t *allocs,*dynamics;
steps_t *step_list;

/*
 *	the following are new (added June 94 Thom McMahon)
 *              void expand_op (FILE *, char*, char *)
 *		void declare_utils ()
 *		void declare_var (int, char*, int)
 */

/* expand_op - given varibale var and op of ( = | += | -= | *= | /= ), will
               generate code of form var =, or var = var ( + | - | * | / ), 
               which FORTRAN 90 will recognize */

void expand_op (FILE *out, char var[], char *op)
{
  fprintf(out,"%s=",var);
  if (op[0]!='=')
    fprintf(out,"%s%c",var,op[0]);
}

/* declare_utils - generate code to declare variables offset# and i# */

void declare_utils ()
{
  int    i;

  fprintf(vfile,"  INTEGER :: shift\n");
  for (i=0; i<max_combined; i++) {
    fprintf(vfile,"  INTEGER :: offset%d\n",i);
  }

  for (i=0; i<max_dim; i++) {
    fprintf(vfile,"  INTEGER :: i%d\n",i);
    if (host) fprintf(hostfile,"  INTEGER :: i%d;\n",i);
  }
}

/* declare_var - generate code to declare a scalar, or an array with integer 
                 size */

void declare_var (int integer, char *name, int len)
{
  if (integer)
    fprintf (vfile, "  INTEGER");
  else
    fprintf (vfile, "  REAL");
  if (len)
    fprintf (vfile, ", DIMENSION (0:%d) :: %s\n", len-1, name);
  else
    fprintf (vfile, " :: %s\n", name);
}
   
/*	the following are from ident.c
 *		print_ident(FILE *outfile,ident_t *ident)
 *		print_op(FILE *outfile, int op)
 */

/* print_ident - prints the value of an identifier.  If it's not a scalar then
                 rav(ident)[0] is used */

print_ident(FILE *outfile,ident_t *ident)

{
  int save;

  if (ident==NULL) {
    fprintf(outfile,"0");
    return;
  }

  switch (ident->type) {
  case CONSTANT:
    if (ident->value < 0)
      fprintf(outfile,"(%d)",(int) ident->value);
    else
      fprintf(outfile,"%d",(int) ident->value);
    break;
  case VARIABLE:
    if (int_expr&&ident->real)
      fprintf(outfile,"INT (%s)", ident->string);
    else
      fprintf(outfile,"%s",ident->string);
    break;
  case EMBEDED_ARRAY:
    if (ident->array.cnst!=NULL)
      if (ident->array.cnst[0] < 0)
        fprintf(outfile,"(%d)",(int) ident->array.cnst[0]);
      else
        fprintf(outfile,"%d",(int) ident->array.cnst[0]);
    else
      print_s_expr(outfile,ident->array.rav[0]);
    break;
  case IOTA:
    fprintf(outfile,"0");
    break;
  case CONST_ARRAY:
    if (ident->array.cnst[0] < 0)
      fprintf(outfile,"(%d)",(int) ident->array.cnst[0]);
    else
      fprintf(outfile,"%d",(int) ident->array.cnst[0]);
    break;
  case RAV:
    print_s_expr(outfile,ident->array.rav[0]);
    break;
  case ARRAY:
    fprintf(outfile,"%s(0)",ident->string);
  }
}


/* print_op - print an operator to outfile */

print_op(FILE *outfile, int op)

{
  switch (op) {
  case TIMES:
    fprintf(outfile,"*");
    break;
  case DIVIDE:
    fprintf(outfile,"/");
    break;
  case MOD:
    fprintf(outfile," MOD ");
    break;
  case PLUS:
    fprintf(outfile,"+");
    break;
  case MINUS:
    fprintf(outfile,"-");
    break;
  }
}

/* print_s - prints the value of an s_expr.  If its not a scalar then
                 rav(ident)[0] is used */

print_s(FILE *outfile,s_expr_t *s)

{
  int save;

  if (s==NULL) {
    fprintf(outfile,"0");
    return;
  }

  if ((s->op==NOP)||ISCODED(s->flags)) print_ident(outfile,s->ident);
  else {
    switch (s->op) {
    case PLUS:
      print_s(outfile,s->left);
      print_op(outfile,s->op);
      print_s(outfile,s->right);
      break;

    case TIMES:
    case DIVIDE:
    case MINUS:
      fprintf(outfile,"(");
      print_s(outfile,s->left);
      fprintf(outfile,")");

      print_op(outfile,s->op);

      fprintf(outfile,"(");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case MOD:
      fprintf(outfile,"MOD(");
      print_s(outfile,s->left);
      fprintf(outfile,",");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case MIN:
      fprintf(outfile,"MIN(");
      print_s(outfile,s->left);
      fprintf(outfile,",");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case MAX:
      fprintf(outfile,"MAX(");
      print_s(outfile,s->left);
      fprintf(outfile,",");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case IF_POS:
      fprintf(outfile,"(INT ((");
      print_s(outfile,s->left);
      fprintf(outfile,")>0))");
      break;

    case IF_NEG:
      fprintf(outfile,"(INT ((");
      print_s(outfile,s->left);
      fprintf(outfile,")<0))");
      break;

    case ABS:
      fprintf(outfile,"abs(");
      print_s(outfile,s->left);
      fprintf(outfile,")");
      break;

    case SKIP:
      if (s->left!=NULL)
        print_s(outfile,s->left);
      else print_s(outfile,s->right);
      break;
    }
  }
}

/* allocate_vect - generate C code to declare an vect of the appropriate
     size.  Output is to the variable file. */

allocate_vect(ident_t *ident)

{
  int i;

  if (NOTALLOCATED(ident)) {
    if (ident->type!=VARIABLE) {
      if (ident->real)
        fprintf(vfile,"  REAL");
      else
        fprintf(vfile,"  INTEGER");
      fprintf(vfile,"  , DIMENSION ");
      if (ident->array.dim->value>0) {
        fprintf(vfile,"(0:");
        for (i=0; i<ident->array.dim->value; i++) {
          if (i==0) {
            if (ident->array.shp[i]->type==CONSTANT)
              fprintf(vfile,"%d",(int) ident->array.shp[i]->value);
            else
              fprintf(vfile,"%s",ident->array.shp[i]->string);
          } else {
            if (ident->array.shp[i]->type==CONSTANT)
              fprintf(vfile,"*%d",(int) ident->array.shp[i]->value);
            else
              fprintf(vfile,"*%s",ident->array.shp[i]->string);
          }
        }
        fprintf(vfile,"-1) :: %s\n",ident->string);
      } else fprintf(vfile,"(0:0) :: %s\n",ident->string);
    }
  }
  SETUSED(ident->flags);
}

/* print_rav - print the value of the ith element in expr */

print_rav(FILE *outfile, vect_t *expr,int i)

{
  int simple_index,index;

  if (expr==NULL) fprintf(outfile,"0");
  else {
    if (SCALAR(expr->index)) {
      simple_index=TRUE;
      index=expr->index->ident->value;
    }
    else simple_index=FALSE;

    switch (expr->ident->type) {
    case CONSTANT:
      fprintf(outfile,"%d",(int) expr->ident->value);
      break;

    case VARIABLE:
      if (int_expr&&expr->ident->real)
        fprintf(outfile,"INT (%s)",expr->ident->string);
      else
        fprintf(outfile,"%s",expr->ident->string);
      break;

    case IOTA:
      if (!simple_index) {
        print_s_expr(outfile,expr->index);
      } else {
        fprintf(outfile,"%d",index+i);
      }
      break;


    case EMBEDED_ARRAY:
      if (!simple_index) {
        if (int_expr&&expr->ident->real)
          fprintf(outfile,"INT (%s(",expr->ident->string);
        else
          fprintf(outfile,"%s(",expr->ident->string);
        print_s_expr(outfile,expr->index);
        fprintf(outfile,")");
        if (int_expr&&expr->ident->real)
          fprintf(outfile,")");
      } else {
        if (expr->ident->array.cnst!=NULL)
          fprintf(outfile,"%d", (int) expr->ident->array.cnst[index+i]);
        else
          print_s_expr(outfile,expr->ident->array.rav[index+i]);
      }
      break;

    case CONST_ARRAY:
      if (!simple_index) {
        embed_const_vect(expr->ident);
        if (int_expr&&expr->ident->real)
          fprintf(outfile,"INT (%s(",expr->ident->string);
        else
          fprintf(outfile,"%s(",expr->ident->string);
        print_s_expr(outfile,expr->index);
        fprintf(outfile,")");
        if (int_expr&&expr->ident->real)
          fprintf(outfile,")");
      } else
        fprintf(outfile,"%d",(int) expr->ident->array.cnst[index+i]);
      break;

    case RAV:
      if (!simple_index) {
        embed_const_vect(expr->ident);
        if (int_expr&&expr->ident->real)
          fprintf(outfile,"INT (%s(",expr->ident->string);
        else
          fprintf(outfile,"%s(",expr->ident->string);
        print_s_expr(outfile,expr->index);
        fprintf(outfile,")");
        if (int_expr&&expr->ident->real)
          fprintf(outfile,")");
      } else
        print_s_expr(outfile,expr->ident->array.rav[index+i]);
      break;

    case ARRAY:
      if (int_expr&&expr->ident->real)
        fprintf(outfile,"INT (%s(%d",expr->ident->string,i);
      else
        fprintf(outfile,"%s(%d",expr->ident->string,i);
      fprintf(outfile,"+");
      print_s_expr(outfile,expr->index);
      fprintf(outfile,")");
      if (int_expr&&expr->ident->real)
        fprintf(outfile,")");
      break;
    }
  }
}

/* embed_const_vect - store a constant array in a temprorary variable so
                      it can be used for random access. */

embed_const_vect(ident_t *ident)

{
  int i;

  if (ident->real)
    fprintf(vfile,"  REAL");
  else
    fprintf(vfile,"  INTEGER");
  if (ident->type==CONST_ARRAY) {
    ident->array.rav=NULL;
    fprintf(vfile,"  , DIMENSION (:) :: const%d = (/",const_num);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      if (i>0) fprintf(vfile,",");
      fprintf(vfile,"%d",(int) ident->array.cnst[i]);
    }
    fprintf(vfile,"/)\n");
  } else {
    ident->array.cnst=NULL;
    fprintf(vfile,"  , DIMENSION (0:%d) :: const%d\n",(int) ident->array.shp[0]->value-1,const_num);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      dotab(0);
      fprintf(tfile,"const%d(%d)=",const_num,i);
      print_s_expr(tfile,ident->array.rav[i]);
      fprintf(tfile,"\n");
    }
  }
  sprintf(ident->string,"const%d",const_num);
  ident->type=EMBEDED_ARRAY;
}

/* code_vect_do_op - added 6/94 Thom McMahon;  used exclusively by code_vect.
                     given op of =, +=, -=, *=, or /=, will generate code in
                     the form of x = y, or x = x ( + | - | * | / ) y, which
                     FORTRAN 90 will recognize */

void code_vect_do_op (char *idx_begin, vect_t *res, char *op, char *pre)
{
  fprintf(tfile,"%s(%s",res->ident->string,idx_begin);
  print_s_expr(tfile,res->loc);
  fprintf(tfile,")=");
  if (op[0]=='=')
    fprintf(tfile,"%s",pre);
  else
  {
    fprintf(tfile,"%s(%s",res->ident->string,idx_begin);
    print_s_expr(tfile,res->loc);
    fprintf(tfile,")%c%s",op[0],pre);
  }     
}

/* code_vect - generates code to assign a vector to another with op,
               using format to print the source vector. */

code_vect(vect_t *vect, vect_t *res, char *op, char *pre ,char *post, char *mid)
{
  int i;
  char idx_begin[10];

  if ((vect->ident->type==CONSTANT)||(vect->ident->type==VARIABLE)) {
    if ((!SCALAR(vect->shp))||(vect->shp->ident->value>0)) {
      if (SCALAR(vect->shp)&&(vect->shp->ident->value==1)) {
        dotab(0);
        sprintf(idx_begin,"");
        code_vect_do_op (idx_begin,res,op,pre);
        print_ident(tfile,vect->ident);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s(",mid,res->ident->string);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,")");
        }
        fprintf(tfile,"%s\n",post);
      } else {
        dotab(0);
        fprintf(tfile,"DO i=0, ");
        print_s_expr(tfile,vect->shp);
        fprintf(tfile,"-1 ");
        sprintf (idx_begin,"i+");
        code_vect_do_op (idx_begin,res,op,pre);
        print_ident(tfile,vect->ident);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s(i+",mid,res->ident->string);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,")");
        }
        fprintf(tfile,"%s END DO\n",post);
      }
    }
  } else if (vect->ident->type==CONST_ARRAY) {
    if (SCALAR(vect->index)&&SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        sprintf(idx_begin,"%d+",i);
        code_vect_do_op (idx_begin,res,op,pre);
        fprintf(tfile,"%d",(int)
                vect->ident->array.cnst[i+(int) vect->index->ident->value]);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s(%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,")");
        }
        fprintf(tfile,"%s\n",post);

      }
    } else {
      embed_const_vect(vect->ident);
      recursive_assign(vect,res,op);
    }
  } else if (vect->ident->type==IOTA) {
    if (SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        sprintf(idx_begin,"%d+",i);
        code_vect_do_op (idx_begin,res,op,pre);
        fprintf(tfile,"(%d+");
        print_s_expr(tfile,vect->index);
        fprintf(tfile,")");
        if (mid!=NULL) {
          fprintf(tfile,"%s%s(%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,")");
        }
        fprintf(tfile,"%s\n",post);
      }
    } else {
      dotab(0);
      fprintf(tfile,"DO i=0, ");
      print_s_expr(tfile,vect->shp);
      fprintf(tfile,"-1 ");
      sprintf(idx_begin,"i+");
      code_vect_do_op (idx_begin,res,op,pre);
      fprintf(tfile,"i+");
      print_s_expr(tfile,vect->index);
      if (mid!=NULL) {
        fprintf(tfile,"%s%s(i+",mid,res->ident->string);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,")");
      }
      fprintf(tfile,"%s END DO\n",post);
    }
  } else if (vect->ident->type==RAV) {
    if (SCALAR(vect->index)&&SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        sprintf(idx_begin,"%d+",i);
        code_vect_do_op (idx_begin,res,op,pre);
        print_s_expr(tfile,
                     vect->ident->array.rav[i+(int)vect->index->ident->value]);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s(%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,")");
        }
        fprintf(tfile,"%s\n",post);
      }
    } else {
      embed_const_vect(vect->ident);
      recursive_assign(vect,res,op);
    }
  } else if ((!SCALAR(vect->shp))||(vect->shp->ident->value>0)) {
    if (SCALAR(vect->shp)&&(vect->shp->ident->value==1)) {
      dotab(0);
      sprintf(idx_begin,"");
      code_vect_do_op (idx_begin,res,op,pre);
      fprintf(tfile,"%s(",vect->ident->string);
      print_s_expr(tfile,vect->index);
      fprintf(tfile,")%s\n",post);
    } else {
      dotab(0);
      fprintf(tfile,"DO i=0, ");
      print_s_expr(tfile,vect->shp);
      fprintf(tfile,"-1 ");
      sprintf(idx_begin,"i+");
      code_vect_do_op (idx_begin,res,op,pre);
      fprintf(tfile,"%s(i+",vect->ident->string);
      print_s_expr(tfile,vect->index);
      if (mid!=NULL) {
        fprintf(tfile,"%s%s(i+",mid,res->ident->string);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,")");
      }
      fprintf(tfile,")%s END DO\n",post);
    }
  }
}

/* recursive_assign - search the expression tree generating code to assign
                      the result of vect to res.  op is the operator string
                      "=", "+=", "-=", "*=", or "/=" */

recursive_assign(vect_t *vect, vect_t *res, char *op)

{
  char *new_op[10];
  char temp_var[40];
  int cnt=0,i,first_cat,save;

  /* some simplification is done by checking is the shp of an operation
     is 0 or 1.  If zero then throw it away, if one then we don't need a
     loop construct just a simple scalar assignment */

  if (vect==NULL) {
    if ((!SCALAR(res->shp))||(res->shp->ident->value>0)) {
      if (SCALAR(res->shp)||(res->shp->ident->value==1)) {
        dotab(0);
        sprintf(temp_var,"%s(0)",res->ident->string);
        expand_op (tfile,temp_var,op);
        fprintf(tfile,"0\n\n");
      } else {
        dotab(0);
        fprintf(tfile,"DO i=0, ");
        print_s_expr(tfile,res->shp);
        fprintf(tfile,"-1 ");
        sprintf(temp_var,"%s(i)",res->ident->string);
        expand_op(tfile,temp_var,op);
        fprintf(tfile,"0 END DO\n\n");
      }
    }
    return;
  }

  if (ISCODED(vect->flags)) {
    code_vect(vect,res,op,"","",NULL);
    return;
  }

  switch (vect->op) {
  case SKIP:
    if (vect->left!=NULL)
      recursive_assign(vect->left,res,op);
    recursive_assign(vect->right,res,op);
    break;

  case CAT:
    recursive_assign(vect->left,res,op);
    recursive_assign(vect->right,res,op);
    break;

  case MIN:
    recursive_assign(vect->left,res,op);
    vect->right=purify_vect(vect->right);
    code_vect(vect->right,res,"min","","",NULL);
    break;

  case PLUS:
    new_op[cnt]="+=";
    cnt++;
  case MINUS:
    new_op[cnt]="-=";
    cnt++;
  case TIMES:
    new_op[cnt]="*=";
    cnt++;
  case DIVIDE:
    new_op[cnt]="/=";
    cnt++;
  case MOD:
    new_op[cnt]="%=";
    cnt++;

    recursive_assign(vect->left,res,op);
    vect->right=purify_vect(vect->right);
    recursive_assign(vect->right,res,new_op[0]);
    break;

  case ABS:
    vect->left=purify_vect(vect->left);
    code_vect(vect->left,res,op,"fabs(",")",NULL);
    break;

  case IF_POS:
    vect->left=purify_vect(vect->left);
    code_vect(vect->left,res,op,"(INT(",">0))",NULL);
    break;

  case IF_NEG:
    vect->left=purify_vect(vect->left);
    code_vect(vect->left,res,op,"(INT(","<0))",NULL);
    break;

  case RSCAN:
    vect->left=purify_vect(vect->left);
    dotab(0);
    fprintf(tfile,"DO i=");
    print_s_expr(tfile,vect->left->shp);
    fprintf(tfile,"-2, 0, -1\n");
    dotab(1);
    sprintf(temp_var,"%s(i)",res->ident->string);
    expand_op(tfile,temp_var,op);
    fprintf(tfile,"%s(i+1)*%s(i)\n",res->ident->string,
      vect->left->ident->string);
    dotab(0);
    fprintf(tfile,"END DO");
    break;

  case SCAN:
    vect->left=purify_vect(vect->left);
    dotab(0);
    fprintf(tfile,"DO i=1, ");
    print_s_expr(tfile,vect->left->shp);
    fprintf(tfile,"-1\n");
    dotab(1);
    sprintf(temp_var,"%s(i)",res->ident->string);
    expand_op(tfile,temp_var,op);
    fprintf(tfile,"%s(i-1)*%s(i)\n",res->ident->string,
      vect->left->ident->string);
    dotab(0);
    fprintf(tfile,"END DO");
    break;

  case NOP:
    code_vect(vect,res,op,"","",NULL);
    break;
  }
}

/* added June 94, Thom McMahon;
 *      code_idx_array - generates code for indexing an array, printing to a
 *      string
 */

void code_idx_array (char *where, char *array, char *index)
{
  sprintf(where, "%s(%s)", array, index);
}
 
/*	the following are the original code.c functions modified to output
 *		FORTRAN 90 code instead of C
 */

/* addto_allocs - adds expr to the list of arrays that need to be 
     allocated. */

/*
 *	here to end of file is modified original code.c
 */

addto_allocs(expr_t *expr)

{
  name_t *node;

  node=(name_t *) get_mem(sizeof(name_t));
  strncpy(node->name,expr->ident->string,17);
  node->next=allocs;
  allocs=node;
}


/* addto_dynamics - adds expr to the list of arrays that need to be allocated
     dynamically with get_mem. */

addto_dynamics(expr_t *expr)

{
  name_t *node;

  node=(name_t *) get_mem(sizeof(name_t));
  strncpy(node->name,expr->ident->string,17);
  node->next=dynamics;
  dynamics=node;
}


/* allocate_array - generate FORTRAN 90 code to declare an array of the
     appropriate size.  Arrays are allocated as one dimensional arrays to
     allow linear access.  Output is to the variable file. */

allocate_array(ident_t *ident)

{
  int i,dynamic;
  char atype[7];

  SETUSED(ident->flags);

  if (ident->type!=VARIABLE) {
    if (ident->real)
      sprintf (atype, "REAL");
    else
      sprintf (atype, "INTEGER");
    if (ident->array.dim->value>0) {
      dynamic=FALSE;
      for (i=0; i<ident->array.dim->value; i++) {
	if (ident->array.shp[i]->type!=CONSTANT)
	  dynamic=TRUE;
      }

      if (dynamic&&(strncmp(ident->string,"tmp_vect",8)==0)) {
	fprintf(vfile,"  %s, DIMENSION (:), ALLOCATABLE :: %s\n",atype,
             ident->string);
	fprintf(tfile,"  ALLOCATE (%s(0:", ident->string);

        for (i=0; i<ident->array.dim->value; i++) {
          if (i==0) {
	    if (ident->array.shp[i]->type==CONSTANT)
	      fprintf(tfile,"%d",(int) ident->array.shp[i]->value);
	    else
	      fprintf(tfile,"%s",ident->array.shp[i]->string);
	  } else {
	    if (ident->array.shp[i]->type==CONSTANT)
	      fprintf(tfile,"*%d",(int) ident->array.shp[i]->value);
	    else
	      fprintf(tfile,"*%s",ident->array.shp[i]->string);
          }
        }
        fprintf (tfile, "-1");
        if (ident->array.dim->value==0)
          fprintf(tfile,"0");
        else
          fprintf(tfile,"))\n");

      } else {
	fprintf(vfile,"  %s, DIMENSION ",atype);
	fprintf(vfile,"(0:");

        for (i=0; i<ident->array.dim->value; i++) {
          if (i==0) {
	    if (ident->array.shp[i]->type==CONSTANT)
	      fprintf(vfile,"%d",(int) ident->array.shp[i]->value);
	    else
	      fprintf(vfile,"%s",ident->array.shp[i]->string);
	  } else {
	    if (ident->array.shp[i]->type==CONSTANT)
	      fprintf(vfile,"*%d",(int) ident->array.shp[i]->value);
	    else
	      fprintf(vfile,"*%s",ident->array.shp[i]->string);
          }
        }
        fprintf (vfile, "-1");
        if (ident->array.dim->value==0)
          fprintf(vfile,"0");
        else
          fprintf(vfile,") :: %s\n", ident->string);
      }
    } else fprintf(vfile,"  %s, DIMENSION (0:0) :: %s\n",atype,ident->string);
  }     
} 


/* do_shapes - if expr and result's shapes have not been scanned then they
     are scanned.  Scanning results in storing *SCAN(shape) in the shape
     field for calculating loop steps.  */

do_shapes(expr_t *expr, expr_t *result)

{
  if (!ISSCANNED(expr->flags)) {
    expr->shp=vect_unop(SCAN,expr->shp);
    expr->shp=purify_vect(expr->shp);
    SETSCANNED(expr->flags);
  }
  if (!ISSCANNED(result->flags)) {
    result->shp=vect_unop(SCAN,result->shp);
    result->shp=purify_vect(result->shp);
    SETSCANNED(result->flags);
  }
}


/* my_gamma - generates FORTRAN 90 code to calculate Gamma(index,shp) and
     assign it to name.  dim is the length of index, and shp.  The resulting
     FORTRAN 90 code is output to file out. */

int my_gamma(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim)

{
  int ret,d;
  int i,j;

  index=vect_drop(s_vect(s_op(MINUS,index->shp,dim)),index);
  if (SCALAR(dim)) {
    d=dim->ident->value;
    if (dim->ident->value>0) {
      dotabf(out,0);
      fprintf(out,"%s",name);
      print_rav(out,index,0);
      for (i=1; i<d; i++) {
	fprintf(out,"+");
	print_rav(out,index,i);
	fprintf(out,"*");
	print_rav(out,shp,i-1);
      }
      fprintf(out,"\n");
      ret=TRUE;
    } else {
      dotabf(out,0);
      fprintf(out,"%s0\n",name);
      ret=TRUE;
    }
  } else {
    ret=TRUE;
    shp=vect2array("gamma_shp",shp);
    index=vect2array("gamma_index",index);
    dotabf(out,0);
    fprintf(out,"DO i = 0, ");
    print_s_expr(out,dim);
    fprintf(out,"-1\n");
    dotabf(out,0);
    fprintf(out,"%s = %s + %s (I",name,name,index->ident->string);
    if (index->index!=NULL) {
      fprintf(out,"+");
      print_s_expr(out,index->index);
    }
    fprintf(out,") * %s (I)\n",shp->ident->string);
  }
 
  return(ret);
}


/* do_location - generates FORTRAN 90 code that assigns the location of the
     assignment in the shift variable for the assignment of expr to result.
     Output is to the temporary code file.  */

int do_location(expr_t *expr, expr_t *result)

{
  char buf[256];

  if (!ISSCANNED(result->flags)) {
    result->shp=vect_unop(SCAN,result->shp);
    result->shp=purify_vect(result->shp);
    SETSCANNED(result->flags);
  }

  if (expr==NULL) return;
  if (expr->loc==NULL) {
    dotab(0);
    fprintf(tfile,"shift=0\n");
  } else {
    sprintf(buf,"shift=");
    return(my_gamma(tfile,buf,expr->loc,result->shp,result->dim));
  }
}


/* do_gamma - generates FORTRAN 90 code that assigns the index of the
     assignment in the offset variable for the assignment of expr to result.
     Output is to the temporary code file.  */

do_gamma(expr_t *expr, expr_t *result, int num)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->index==NULL) {
    dotab(0);
    fprintf(tfile,"offset%d=0\n",num);
  } else {
    sprintf(buf,"offset%d=",num);
    return(my_gamma(tfile,buf,expr->index,expr->shp,expr->dim));
  }
}


/* add_steps - calculates the step for each loop in an assigment, eliminating
     a step if possible.  */

add_steps(vect_t *bound, vect_t *shp1, s_expr_t *dim , int num, int scalar)

{
  int i,j,constant,d,d2,k;
  s_expr_t **step_mask;
  int pos,last;
  double value1,value2,value3;
  vect_t *step,*pad1;
  expr_t *tmp_expr;
  steps_t *node;

  step_mask=NULL;
  if (SCALAR(dim)) {
    d=dim->ident->value;

    if (SCALAR(bound->shp)) {
      if ((int) bound->shp->ident->value<d) {
	pad1=get_vect();
	*pad1=one_vec;
	pad1->shp=get_s_expr();
	pad1->shp->ident=get_ident();
	pad1->shp->ident->type=CONSTANT;
	pad1->shp->ident->value=d-(int) bound->shp->ident->value;
	bound=vect_cat(pad1,bound);
      } else if (bound->shp->ident->value>d) {
	bound=vect_drop(s_vect(s_op(MINUS,bound->shp,dim)),bound);
      }
    }
    
    if (scalar) {
      i=0;
      if (d>0)
	step_mask=(s_expr_t **) get_mem(d*sizeof(s_expr_t *));
      while (i<d) {
	step_mask[i]=NULL;
	i++;
      }
    } else {
      if (d>0) {
	step_mask=(s_expr_t **) get_mem(d*sizeof(s_expr_t *));
	value1=rav_value(bound,d-1-(d-1),&constant);
	if ((!constant)||(value1>1)) step_mask[d-1]=&s_const1;
	else step_mask[d-1]=&s_const0;
	last=d-1-(d-1);
      }       
      for (i=d-2; i>=0; i--) {
	value1=rav_value(bound,d-1-i,&constant);
	if ((constant)&&(value1>1)) {
	  j=i+1;
	  value1=1;
	  while ((constant)&&(j<=d-1-last)) {
 	    value1*=rav_value(bound,d-1-j,&constant);
	    j++;
	  }
	  if (constant)
	    value2=rav_value(shp1,d-1-(i+1),&constant);
	  if (constant)
	    value3=(last>d-1-(d-1)) ? rav_value(shp1,last-1,&constant) : 
	      (step_mask[d-1])->ident->value;
	  if (constant) {
	    if (value2-value3*value1>0) {
	      last=i;
	      step_mask[i]=get_s_expr();
	      step_mask[i]->ident=get_ident();
	      step_mask[i]->ident->type=CONSTANT;
	      step_mask[i]->ident->value=value2-value3*value1;
	    } else step_mask[i]=NULL;
	  }
	} else if (constant) {
	  step_mask[i]=NULL;
	} else {

/* new new new new new new new new */
          j=i+1;
          step_mask[i]=red_rav(bound,last);
          while(j<d-1-last) {
            step_mask[i]=s_op(TIMES,step_mask[i],red_rav(bound,d-1-j));
            j++;
          }
/* end end end end end end end end  */
 
	  if (last>d-1-(d-1)) {

/* new new new new new new new new */
            step_mask[i]=s_op(MINUS,red_rav(shp1,d-1-(i+1)),
                              s_op(TIMES,red_rav(shp1,last-1),
                                   step_mask[i]));
/* end end end end end end end end  */
 
/* old old old old old old old old
	    step_mask[i]=s_op(MINUS,red_rav(shp1,d-1-(i+1)),
			      s_op(TIMES,red_rav(shp1,last-1),
				   red_rav(bound,last)));
*/

	  } else {

/* new new new new new new new new */
            step_mask[i]=s_op(MINUS,red_rav(shp1,d-1-(i+1)),
                              s_op(TIMES,step_mask[d-1],step_mask[i]));
/* end end end end end end end end  */
 
/* old old old old old old old old
	    step_mask[i]=s_op(MINUS,red_rav(shp1,d-1-(i+1)),
			      s_op(TIMES,step_mask[d-1],red_rav(bound,last)));
*/

	  }
	  last=d-1-i;
	}
	step_mask[i]=red_s_expr(step_mask[i]);
      }
    }
  } else {
    fatal("Unknown dimension in add_steps");
  }
  
  node=(steps_t *) get_tmp_mem(sizeof(steps_t));
  node->num=num;
  node->steps=step_mask;
  node->next=step_list;
  step_list=node;
  
}


/* do_loop_open - generates the FORTRAN 90 code for loops for an assigment
     with bound and dimension dim. */

do_loop_open(vect_t *bound, s_expr_t *dim)

{
  int i,j,constant,d;
  double value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    d=dim->ident->value;
    for (i=0; i<d; i++) {
      value=rav_value(bound,d-1-i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"DO i%d = 0, ", i);
	print_rav(tfile,bound,d-1-i);
	fprintf(tfile,"-1\n");
	ntab++;
      }
    }
  } else {
    fatal("Unknown dimension in do_loop_open");
  }
}


/* do_loop_close - generates FORTRAN 90 code to calculate the step for each
     loop as well as close it with an END DO.  mask indicates which loops
     require a step.  name is unused. */

do_loop_close(s_expr_t *dim, vect_t *bound, s_expr_t *rdim)

{
  int i,j,constant,d,rd,k;
  double value;
  steps_t *node;
  
  if (SCALAR(rdim)) {
    rd=rdim->ident->value;
  } else {
    fatal("Unknown dimension: do_loop_close");
  }

  if (SCALAR(dim)) {
    d=dim->ident->value;
    k=rd-1;
    if (rd>d)
      k-=(rd-d);
    if (d>0) {
      value=rav_value(bound,d-1-(d-1),&constant);
      if ((!constant)||(value>1)) {
	node=step_list->next;
	while (node!=NULL) {
	  if ((node->steps[d-1]!=NULL)&&(node->steps[d-1]!=&s_const0)) {
	    dotab(0);
	    fprintf(tfile,"offset%d=offset%d+",node->num, node->num);
	    print_s_expr(tfile,node->steps[d-1]);
	    fprintf(tfile,"\n");
	  }
	  node=node->next;
	}
        if (k>=0) {
	  if ((step_list->steps[k]!=NULL)&&
	      (step_list->steps[k]!=&s_const0)) {
	    dotab(0);
	    fprintf(tfile,"shift=shift+");
	    print_s(tfile,step_list->steps[k]);
	    fprintf(tfile,"\n");
          }
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"END DO\n");
	k--;
      }
    }
    for (i=d-2; i>=0; i--) {
      value=rav_value(bound,d-1-i,&constant);
      if ((!constant)||(value>1)) {
	node=step_list->next;
	while (node!=NULL) {
	  if (node->steps[i]!=NULL) {
	    dotab(0);
	    fprintf(tfile,"offset%d=offset%d+",node->num, node->num);
	    print_s(tfile,node->steps[i]);
	    fprintf(tfile,"\n");
	  }
	  node=node->next;
	}
        if (k>0) {
 	  if (step_list->steps[k]!=NULL) {
	    dotab(0);
	    fprintf(tfile,"shift=shift+");
	    print_s(tfile,step_list->steps[k]);
	    fprintf(tfile,"\n");
	  }
        }
	ntab--;
	dotab(0);
	fprintf(tfile,"END DO\n");
	k--;
      }
    }
  } else {
    fatal("Unknown dimension in do_loop_close");
  }
}


/* iota_loop_open - generates special loop code required for an assigment
     of iota.  */

iota_loop_open(vect_t *index, vect_t *bound, s_expr_t *dim)

{
  int i,constant;
  double value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value-1; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"DO i%d = ", i);
	print_rav(tfile,index,i);
	fprintf(tfile,", ");
	print_rav(tfile,index,i);
	fprintf(tfile,"+");
	print_rav(tfile,bound,i);
	fprintf(tfile,"-1\n");
	ntab++;
      }
    }
  } else {
    fatal("Help, I don't know the dimension");
  }
}


/* iota_loop_close - generates code to close special loops require for 
     assigments involving iota. */

iota_loop_close(s_expr_t *dim, vect_t *bound)

{
  int i,constant;
  double value;

  if (SCALAR(dim)) {
    for (i=0; i<dim->ident->value-1; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	ntab--;
	dotab(0);
	fprintf(tfile,"END DO\n");
      }
    }
  } else {
    fatal("Help! I don't know the dimension");
  }
}

/* global_assign - generates FORTRAN 90 code to implement a single array
     assigment of expr to result. */

global_assign(reduced_t *global, expr_t *result)

{
  int scalar_num_save;
  double value;
  int tau,i,constant;
  int num,last_num;
  s_expr_t **mask;
  reduced_t *node;
  char temp_var[40];

  /* any scalars  used during the assign can be reused */
  scalar_num_save=scalar_num;

  step_list=NULL;

  /* skip all the temporary assignments */
  node=global;
  while ((node!=NULL)&&
	 (strncmp(node->d.frag->left->ident->string,"temp",4)==0)) {
    node=node->next;
  }
  if (node!=NULL)
    /* use the location of the first non-temporary assignments */
    do_location(node->d.frag,result);
  else {
    /* must be all temporary so used first one */
    if (global->d.frag->left->ident->type!=VARIABLE)
      do_location(global->d.frag,result);
  }

  num=0;
  node=global;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
      tau=1;
      for (i=0; i<node->d.frag->ident->array.dim->value; i++) {
	tau*=node->d.frag->ident->array.shp[i]->value;
      }
      if (node->d.frag->ident->real)
        fprintf(vfile,"  REAL");
      else
        fprintf(vfile,"  INTEGER");
      fprintf(vfile,"  , DIMENSION (0:%d-1) :: consta%d\n",
        tau,const_array_num);
      for (i=0; i<tau; i++) {
	dotab(0);
	fprintf(tfile,"consta%d (%d) =",const_array_num,i);
	if (node->d.frag->ident->type==CONST_ARRAY) {
	  fprintf(tfile,"%f",node->d.frag->ident->array.cnst[i]);
	} else {
	  print_s_expr(tfile,node->d.frag->ident->array.rav[i]);
	}
	fprintf(tfile,"\n");
      }
      sprintf(node->d.frag->ident->string,"consta%d",const_array_num);
      node->d.frag->ident->type=EMBEDED_ARRAY;
      const_array_num++;
      /* continue to the ARRAY case */

    case EMBEDED_ARRAY:
    case ARRAY:
      do_shapes(node->d.frag,result);
      do_gamma(node->d.frag,result,num);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->dim,num,FALSE);
      num++;
      break;
    case IOTA:
      do_shapes(node->d.frag,result);
      break;
    case CONSTANT:
    case VARIABLE:
      do_shapes(node->d.frag,result);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->dim,num,TRUE);
      num++;
      break;
    }
    node=node->next;
  }

  last_num=num-1;

  if (num>max_combined) max_combined=num;

  if (global->d.frag->ident->type==IOTA) 
    iota_loop_open(global->d.frag->index,global->d.frag->bound,
		     global->d.frag->dim);
  else {
    add_steps(result->bound,result->shp,result->dim,num,FALSE);
    do_loop_open(global->d.frag->bound,global->d.frag->dim);
  }

  node=global;
  num=0;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
    case EMBEDED_ARRAY:
    case ARRAY:
      dotab(0);
      if (node->d.frag->left->ident->type==VARIABLE) {
	sprintf(temp_var,node->d.frag->left->ident->string);
      } else {
	sprintf(temp_var,"%s(shift)",node->d.frag->left->ident->string);
      }
      expand_op (tfile,temp_var,node->d.frag->func);
      fprintf(tfile,"%s(offset%d)\n",node->d.frag->ident->string,num);
      num++;
      break;
      
    case IOTA:
      for (i=0; i<node->d.frag->dim->ident->value-1; i++) {
	value=rav_value(node->d.frag->bound,i,&constant);
	if ((!constant)||(value>1)) {
	  dotab(0);
	  sprintf(temp_var,"%s(shift)",result->ident->string);
          expand_op(tfile,temp_var,node->d.frag->func);
          fprintf(tfile,"i%d\n",i);
	} else {
	  dotab(0);
	  sprintf(temp_var,"%s(shift)",result->ident->string);
          expand_op(tfile,temp_var,node->d.frag->func);
	  print_rav(tfile,node->d.frag->index,i);
	  fprintf(tfile,"\n");
	}
	dotab(0);
	fprintf(tfile,"shift=shift+1\n");
      }
      break;
      
    case CONSTANT:
    case VARIABLE:
      dotab(0);
      if (node->d.frag->left->ident->type==VARIABLE) {
	sprintf(temp_var,node->d.frag->left->ident->string);
      } else {
	sprintf(temp_var,"%s(shift)",node->d.frag->left->ident->string);
      }
      expand_op(tfile,temp_var,node->d.frag->func);
      if (node->d.frag->ident->type==VARIABLE) {
	fprintf(tfile,"%s\n",node->d.frag->ident->string);
      } else {
	fprintf(tfile,"%f\n",node->d.frag->ident->value);
      }
      num++;
      break;
    }

    node=node->next;
  }

  if (global->d.frag->ident->type==IOTA) 
    iota_loop_close(global->d.frag->dim,global->d.frag->bound);
  else {
    do_loop_close(global->d.frag->dim,global->d.frag->bound,result->dim);
  }

  /* any scalars used during the assign can be reused */
  scalar_num=scalar_num_save;
}


do_assign(expr_t *expr, expr_t *result)

{
  reduced_t reduced;

  reduced.type=NOP;
  reduced.d.frag=expr;
  reduced.next=NULL;
  expr->left=result;
  
  global_assign(&reduced,result);
}
    

/* start_loop - generates FORTRAN 90 code for the forall statement.  var is 
     the looping variable and left is the lower bound. */

int start_loop(expr_t *var, expr_t *left, expr_t *right)

{
  int i,len,simple;
  vect_t *l_bound;
  vect_t *r_bound;

/*			question: do the following 2 lines need 
				to be repeated in end_loop		*/
  if (NOTALLOCATED(var->ident))
    allocate_array(var->ident);
  l_bound=make_vect(left);
  r_bound=make_vect(right);

  len=rav_value(var->shp,0,&simple);
  if (simple) {
    for (i=0; i<len; i++) {
      dotab(0);
      fprintf(tfile,"%s(%d)=",var->ident->string,i);
      print_rav(tfile,l_bound,i);
      fprintf(tfile,"\n");
      dotab(0);
      fprintf(tfile,"DO\n");
      ntab++;
      dotab(0);
      fprintf(tfile,"IF (%s(%d) == ",var->ident->string,i);
      print_rav(tfile,r_bound,i);
      fprintf(tfile,") EXIT\n");
    }
  } else {
    error("forall vector must have a static shape.");
  }

  return(len);
}


/* end_loop - generates END DO's for a forall statement of depth dimension. 
     var is the looping variable and right is the upper bound. */

end_loop(expr_t *var, int depth)

{
  int i;

  for (i=depth-1; i>=0; i--) {
    dotab(0);
    fprintf(tfile,"%s(%d)=%s(%d)+1\n",var->ident->string,i,
            var->ident->string,i);
    ntab--;
    dotab(0);
    fprintf(tfile,"END DO\n");
  }
}


/* open_forall - generates FORTRAN 90 code for an internal forall generated by 
     an omega expression.  fa_expr describes the forall. */

open_forall(expr_t *fa_expr)

{
  int i,d;

  d=fa_expr->forall->bound->shp->ident->value;
  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      dotab(0);
      fprintf(tfile,"%s(%d)=",fa_expr->forall->fa->string,i);
      print_rav(tfile,fa_expr->index,i);
      fprintf(tfile,"\n");
      dotab(0);
      fprintf(tfile,"DO\n");
      ntab++;
      dotab(0);
      fprintf(tfile,"IF (%s(%d) == ",fa_expr->forall->fa->string,i);
      print_rav(tfile,fa_expr->index,i);
      fprintf(tfile,"+");
      print_rav(tfile,fa_expr->bound,i);
      fprintf(tfile,") EXIT\n");
    }
  }
}


/* close_forall - generates FORTRAN 90 code to close the loops resulting
     from an internal forall command.  */

close_forall(expr_t *fa_expr)

{
  int i,d;

  d=fa_expr->forall->bound->shp->ident->value;
  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=fa_expr->forall->bound->shp->ident->value-1; i>=0; i--) {
      dotab(0);
      fprintf(tfile,"%s(%d)=%s(%d)+1\n",fa_expr->forall->fa->string,i,
              fa_expr->forall->fa->string,i);
      ntab--;
      dotab(0);
      fprintf(tfile,"END DO\n");
    }
  }

  free(fa_expr->forall);
  fa_expr->forall=NULL;
}


allocate_actuals(reduced_t *list)

{
  reduced_t *node;

  node=list;
  while (node!=NULL) {
    if (NOTALLOCATED(node->d.frag->ident)) {
      allocate_array(node->d.frag->ident);
      SETUSED(node->d.frag->ident->flags);
    }
    node=node->next;
  }
}


/* separate_reduced - separates a list of assignments into two lists:
     global if the right hand side is a global array, or distributed if
     the right hand side is a distributed array. */

reduced_t *separate_reduced(reduced_t *list)

{
  dist_t *dist;
  reduced_t *ret,*new_list;
  reduced_t *last_node;

  if (list!=NULL) {
    ret=get_reduced();
    new_list=ret;
    new_list->type=NOP;
    new_list->d.list=list;
  } else ret=NULL;

  last_node=NULL;

  while (list!=NULL) {
    dist=find_dist(list->d.frag->ident);

    last_node=list;
    list=list->next;
    while ((list!=NULL)&&
	   ((find_dist(list->d.frag->ident)==NULL)==(dist==NULL))) {
      last_node=list;
      list=list->next;
    }
    last_node->next=NULL;

    if (list!=NULL) {
      new_list->next=get_reduced();
      new_list=new_list->next;
      new_list->type=NOP;
      new_list->d.list=list;
    }
  }
  
  if (new_list!=NULL)
    new_list->next=NULL;

  return(ret);
}


/* code_expr - generate FORTRAN 90 code for a simple expression list */

code_expr(reduced_t *reduced)

{
  dist_t *l_dist;
  expr_t *result;
  reduced_t *node,*list;
  reduced_t *sep;

  /* find result */
  node=reduced;
  while ((node!=NULL)&&
	 (strncmp(node->d.frag->left->ident->string,"temp",4)==0))
    node=node->next;
  result=(node==NULL) ? reduced->d.frag->left : node->d.frag->left;

  l_dist=find_dist(result->ident);
  
  if ((l_dist==NULL)&&NOTALLOCATED(result->ident)) {
    allocate_array(result->ident);
    SETUSED(result->ident->flags);
  }
  
  sep=separate_reduced(reduced);
  
  /* allocate global variables */
  list=sep;
  while (list!=NULL) {
    node=list->d.list;
    if (find_dist(node->d.frag->ident)!=NULL)
      node=NULL;
    while (node!=NULL) {
      if (NOTALLOCATED(node->d.frag->ident)) {
	allocate_array(node->d.frag->ident);
	SETUSED(node->d.frag->ident->flags);
      }
      node=node->next;
    }
    list=list->next;
  }
  
  list=sep;
  while (list!=NULL) {
    node=list->d.list;
    if (l_dist==NULL) {
      if (find_dist(node->d.frag->ident)==NULL)
	global_assign(node,result);
      else
	code_dist(node,result,l_dist);
    } else {
      code_dist(node,result,l_dist);
    }
    list=list->next;
    collect_garbage(list,save_list,distribution);
  }
}


/* code_reduced - generates FORTRAN 90 code for an entire reduced
     expression. */

code_reduced(reduced_t *reduced)

{
  int i,cnst;
  s_expr_t *s;
  name_t  *alloc_list,*nnode,*junk;
  reduced_t *node,*sub_node;
  
  allocs=NULL;
  node=reduced;
  while (node!=NULL) {
    switch (node->type) {
    case SKIP:
      break;

    case NOP:
      code_expr(node->d.list);
      break;

    case ALLOCATE:
      if (node->d.frag->ident->real)
        fprintf(vfile,"  REAL");
      else
        fprintf(vfile,"  INTEGER");
      if (node->d.frag->ident->type==VARIABLE) {
	fprintf(vfile," :: %s\n",node->d.frag->ident->string);
      } else {
	if (static_shps(node->d.frag->shp)) {
	  cnst=TRUE;
	  for (i=node->d.frag->shp->index->ident->value;
	       i<node->d.frag->shp->shp->ident->value; i++) {
	    s=red_rav(node->d.frag->shp,i);
	    cnst&=SCALAR(s);
	  }
	} else cnst=FALSE;
	if (cnst) {
	  fprintf(vfile,", DIMENSION (0:");
	  tau(vfile,node->d.frag);
	  fprintf(vfile,"-1)");
	  fprintf(vfile," :: %s\n",node->d.frag->ident->string);
	} else {
	  fprintf(vfile,", DIMENSION (:), ALLOCATABLE :: %s\n",
		  node->d.frag->ident->string);
	  dotab(0);
	  fprintf(tfile,"ALLOCATE (%s(0:",node->d.frag->ident->string);
	  tau(tfile,node->d.frag);
	  fprintf(tfile,"-1))\n");
	  addto_allocs(node->d.frag);
	}
      }
      break;

    case FORALL:
      alloc_list=allocs;
      allocs=NULL;
      open_forall(node->d.list->d.frag);
      code_reduced(node->d.list->next);
      close_forall(node->d.list->d.frag);
      allocs=alloc_list;
      break;
    case EXT_OP:
      code_extended (node);
      break;
    default:
      fatal("Unknown type encountered in code_reduced");
    }
    node=node->next;
  }

  nnode=allocs;
  while (nnode!=NULL) {
    junk=nnode;
    dotab(0);
    fprintf(tfile,"DEALLOCATE(%s);\n",nnode->name);
    nnode=nnode->next;
    free(junk);
  }
}


/* code_c - initializes any distributed arrays and calls a recursive function
     to generate code for an entire procedure body.  */

code_c(statement_t *body, dist_t *dist)

{
  init_dist_arrays(dist);
  code_c_rec(body);
  if (n_procs>1) {
    allocate_utils();
  }
  init_collect_arrays(dist);
}


/* code_c_rec - generates FORTRAN 90 code for an entire procedure body. */

code_c_rec(statement_t *body)

{
  dist_t *dist;
  statement_t *node;
  name_t *alloc,*dynamic_list,*junk;
  int depth,i;

  dynamics=NULL;
  node=body;
  while (node!=NULL) {
    switch (node->kind) {
    case REDUCED:
      dotab(0);
      fprintf(tfile,"! MOA\n");
      dotab(0);
      fprintf(tfile,"! %s\n",node->str);
      dotab(0);
      fprintf(tfile,"!\n\n");
      code_reduced(node->d.reduced);
      fprintf(tfile,"\n\n");
      break;

    case DYNAMIC:
      dist=find_dist(node->d.dynamic->ident);
      if (node->d.dynamic->ident->real)
        fprintf(vfile,"  REAL");
      else
        fprintf(vfile,"  INTEGER");
      fprintf(vfile,"  , DIMENSION (:), ALLOCATABLE :: %s\n",
          node->d.dynamic->ident->string);
      dotab(0);
      fprintf(tfile,"ALLOCATE (%s(0:",node->d.dynamic->ident->string);
      if (dist==NULL) {
	tau(tfile,node->d.dynamic);
      } else {
	if (dist->e->shp->ident->value>0) {
	  for (i=0; i<dist->e->shp->ident->value; i++) {
	    if (i>0) fprintf(tfile,"*");
	    print_rav(tfile,dist->e,i);
	  }
	} else fprintf(tfile,"1");
      }
      fprintf(tfile,"-1))\n");
      addto_dynamics(node->d.dynamic);
      break;

    case LOOP:
      dynamic_list=dynamics;
      depth=start_loop(node->d.loop->var,node->d.loop->lower,
        node->d.loop->upper);
      code_c_rec(node->d.loop->body);
      end_loop(node->d.loop->var,depth);
      dynamics=dynamic_list;
      break;
    case CALL:
      dotab(0);
      allocate_actuals(node->d.reduced->next);
      fprintf(tfile,node->str);
      break;
    default:
      fatal("unknown kind in code_c");
    }
    collect_garbage(NULL,save_list,distribution);
    node=node->next;
  }

  alloc=dynamics;
  while (alloc!=NULL) {
    junk=alloc;
    dotab(0);
    fprintf(tfile,"DEALLOCATE(%s);\n",alloc->name);
    alloc=alloc->next;
    free(junk);
  }
}
