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
   v0.4 Thom McMahon
           - added  declare_utils, declare_var, code_idx_array
	   - moved print_ident, print_s, and print_op from ident.c to code.c
	   - moved allocate_vect, embed_const_vect, print_rav, code_vect,
	     and recursive_assign from vect.c to code.c
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

#define NOTALLOCATED(a) ((!ISUSED(a->flags))&&(!ISPARAMETER(a->flags))&&(a->type!=RAV)&&(a->type!=CONST_ARRAY)&&(a->type!=CONSTANT)&&(a->type!=IOTA))

extern code_extended (reduced_t *node);

typedef struct step_node {
  int              num;
  s_expr_t         **steps;
  struct step_node *next;
} steps_t;

typedef struct names {
  char name[18];
  struct names *next;
} name_t;

/* keep track of the number utilitiy variables */
int const_num=0;
int const_array_num=0;
int max_dim=0;       /* maximum # of dimensions for any assignment */
int max_combined=0;  /* maximum # of statements combined into 1 loop */


name_t *allocs,*dynamics; /* allocated variables in the current scope */
steps_t *step_list; /* the step list for the current  */
char *picl_file=NULL;
 
/* declare_utils - generate code to declare variables offset# and i# */

void declare_utils ()
{
  int    i;

  fprintf(vfile,"  double *shift\n");
  for (i=0; i<max_combined; i++) {
    fprintf(vfile,"  double *offset%d\n",i);
  }

  for (i=0; i<max_dim; i++) {
    fprintf(vfile,"  int i%d\n",i);
    if (host) fprintf(hostfile,"  int i%d;\n",i);
  }
}


/* declare_var - generate code to declare a scalar, or an array with integer
                 size */

void declare_var (int integer, char *name, int len)
{
  if (integer)
    fprintf (vfile, "  int");
  else
    fprintf (vfile, "  double");
  fprintf (vfile, " %s", name);
  if (len)
    fprintf (vfile, "[%d]", len);
  fprintf (vfile, ";\n");
}


/* print_ident - print an identifier to the outfile / the first 
   element of an array or raveled array.  identifier types are 
   defined, and their meanings documented in psi.h */

print_ident(FILE *outfile,ident_t *ident)
{
  int save;

  if (ident==NULL) {
    fprintf(outfile,"0");
    return;
  }
/*  printf("  ??  %d  ?? ", ident->type); */
  switch (ident->type) {
    case CONSTANT:
      fprintf(outfile,"%d",(int) ident->value);
      break;
    case ARRAY:
      if (int_expr&&ident->real)
        fprintf(outfile,"((int) %s[0])",ident->string);
      else
        fprintf(outfile,"%s[0]",ident->string);
      break;
    case CONST_ARRAY:
      fprintf(outfile,"%d",(int) ident->array.cnst[0]);
      break;
    case EMBEDED_ARRAY:
      if (ident->array.cnst!=NULL)
        fprintf(outfile,"%d",(int) ident->array.cnst[0]);
      else
        print_s_expr(outfile,ident->array.rav[0]);
      break;
    case IOTA:
      fprintf(outfile,"0");
      break;
    case RAV:
      print_s_expr(outfile,ident->array.rav[0]);
      break;
    case VARIABLE:
      if (int_expr&&ident->real)
        fprintf(outfile,"((int) %s)",ident->string);
      else
        fprintf(outfile,"%s",ident->string);
      break;
    default :
      fatal ("internal; unknown ident type in print_ident, code.c");
      break;
  }
}


/* print_op - print an operator to outfile. operators are defined in psi.h. */

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
    fprintf(outfile,"%%");
    break;
  case PLUS:
    fprintf(outfile,"+");
    break;
  case MINUS:
    fprintf(outfile,"-");
    break;
  default:
    fatal ("internal; unknown operator in print_op, code.c");
    break;
  }
}

/* print_s - prints out a scalar expression.  If its not a scalar then
                 rav(ident)[0] is used */

print_s(FILE *outfile,s_expr_t *s)
{
  int save;

  if (s==NULL) {
    fprintf(outfile,"0");
    return;
  }

  /* if op is NOP, or the scalar expression has been assigned to an
     identifier, then print the identifier, else ....
     SEE make_ident        in ident.c
         ISCODED, SETCODED in psi.h  */
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
    case MOD:
    case MINUS:
      fprintf(outfile,"(");
      print_s(outfile,s->left);
      fprintf(outfile,")");

      print_op(outfile,s->op);

      fprintf(outfile,"(");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case MIN:
      fprintf(outfile,"min(");
      print_s(outfile,s->left);
      fprintf(outfile,",");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case MAX:
      fprintf(outfile,"max(");
      print_s(outfile,s->left);
      fprintf(outfile,",");
      print_s(outfile,s->right);
      fprintf(outfile,")");
      break;

    case IF_POS:
      fprintf(outfile,"((");
      print_s(outfile,s->left);
      fprintf(outfile,")>0)");
      break;

    case IF_NEG:
      fprintf(outfile,"((");
      print_s(outfile,s->left);
      fprintf(outfile,")<0)");
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
    default:
      fatal("internal; unknown scalar expression operator in print_s, code.c");
      break;
    }
  }
}

/* allocate_vect - generate C code to declare an vect of the appropriate
     size.  Output is to the variable file. */

void allocate_vect(ident_t *ident)
{
  int i;
  char atype[10];

  if (ident==NULL) 
    fatal ("internal; NULL identifier in allocat_vect, code.c");

  if (NOTALLOCATED(ident)) {
    if (ident->type!=VARIABLE) {
      if (ident->real)
        sprintf(atype,"double");
      else 
        sprintf(atype,"int");
      fprintf(vfile,"  %s %s",atype,ident->string);
      if (ident->array.dim->value>0) {
        fprintf(vfile,"[");
        for (i=0; i<ident->array.dim->value; i++) {
          if (i>0) fprintf (vfile,"*");
          if (ident->array.shp[i]->type==CONSTANT)
            fprintf(vfile,"%d",(int) ident->array.shp[i]->value);
          else
            fprintf(vfile,"%s",ident->array.shp[i]->string);
        }
        fprintf(vfile,"];\n");
      } else fprintf(vfile,"[1];\n");
    }
  }
  SETUSED(ident->flags);
}

/* embed_const_vect - store a constant array in a temprorary variable so
                      it can be used for random access. */

embed_const_vect(ident_t *ident)
{
  int i;
  char atype [10];

  if (ident==NULL) 
    fatal ("internal; NULL identifier in embed_const_vect, code.c");

  if (ident->type==CONST_ARRAY) {
    ident->array.rav=NULL;
    /*
      if (ident->real)
    */
        sprintf(atype,"double");
    /*
      else
        sprintf(atype,"int");
    */
    fprintf(vfile,"  %s const%d[]={",atype,const_num);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      if (i>0) fprintf(vfile,",");
      fprintf(vfile,"%d",(int) ident->array.cnst[i]);
    }
    fprintf(vfile,"};\n");
  } else {
    ident->array.cnst=NULL;
    fprintf(vfile,"  %s const%d[%d];\n",atype,const_num,
	    (int) ident->array.shp[0]->value);
    for (i=0; i<ident->array.shp[0]->value; i++) {
      dotab(0);
      fprintf(tfile,"const%d[%d]=",const_num,i);
      print_s_expr(tfile,ident->array.rav[i]);
      fprintf(tfile,";\n");
    }
  }
  sprintf(ident->string,"const%d",const_num);
  ident->type=EMBEDED_ARRAY;
  const_num++;
}


/* print_rav - print the value of the ith element of a vector */

print_rav(FILE *outfile, vect_t *vect,int i)
{
  int simple_index,index;

  if (vect==NULL) {
    fprintf(outfile,"0");
  } else {
    if (SCALAR(vect->index)) {
      simple_index=TRUE;
      index=vect->index->ident->value;
    }
    else simple_index=FALSE;

    if (vect->ident == NULL) {
      fatal ("internal; NULL identifier in print_rav, code.c");
    }

/*    printf("Print_Rav of type %d ", vect->ident->type);  */

    switch (vect->ident->type) {
      case CONSTANT:
         fprintf(outfile,"%d",(int) vect->ident->value);
         break;
  
      case ARRAY:
        /* if integer expression and expression contains real numbers */
        if (int_expr&&vect->ident->real)
          fprintf(outfile,"(int) %s[%d",vect->ident->string,i);
        else
          fprintf(outfile,"%s[%d",vect->ident->string,i);
        if (!((simple_index) && (index == 0))) {
          fprintf(outfile,"+");
          print_s_expr(outfile,vect->index);
        }
        fprintf(outfile,"]");
        break;
  
      case CONST_ARRAY:
/*	printf("NEED TO DO CONST_ARRAY!!!\n"); */
        if (!simple_index) {
	  printf("HHH!!!");
          embed_const_vect(vect->ident);
          /* if integer expression and expression contains real numbers */
          if (int_expr&&vect->ident->real)
            fprintf(outfile,"(int) %s[",vect->ident->string);
          else
            fprintf(outfile,"%s[",vect->ident->string);
          print_s_expr(outfile,vect->index);
          fprintf(outfile,"]");
        } else
          fprintf(outfile,"%d",(int) vect->ident->array.cnst[index+i]);
        break;
  
      case EMBEDED_ARRAY:
	printf("NEED TO DO EMBEDDED_ARRAY!!!\n");
        if (!simple_index) {
          /* if integer expression and expression contains real numbers */
          if (int_expr&&vect->ident->real)
            fprintf(outfile,"(int) %s[",vect->ident->string);
          else
            fprintf(outfile,"%s[",vect->ident->string);
          print_s_expr(outfile,vect->index);
          fprintf(outfile,"]");
        } else {
          if (vect->ident->array.cnst!=NULL)
            fprintf(outfile,"%d", (int) vect->ident->array.cnst[index+i]);
          else
            print_s_expr(outfile,vect->ident->array.rav[index+i]);
        }
        break;
  
      case IOTA:
	printf("NEED TO DO IOTA!!!\n");
        if (!simple_index) {
          print_s_expr(outfile,vect->index);
        } else {
          fprintf(outfile,"%d",index+i);
        }
        break;
  
      case RAV:
	/* NEED TO DO RAV */
        if (!simple_index) {
          embed_const_vect(vect->ident);
          /* if integer expression and expression contains real numbers */
          if (int_expr&&vect->ident->real)
            fprintf(outfile,"(int) %s[",vect->ident->string);
          else
            fprintf(outfile,"%s[",vect->ident->string);
          print_s_expr(outfile,vect->index);
          fprintf(outfile,"]");
        } else { printf("HHH!!!");
          print_s_expr(outfile,vect->ident->array.rav[index+i]);
	}
        break;
  
      case VARIABLE:
	printf("NEED TO DO VAR!!!\n");
        /* if integer expression and expression contains real numbers */
        if (int_expr&&vect->ident->real)
          fprintf(outfile,"(int) %s",vect->ident->string);
        else
          fprintf(outfile,"%s",vect->ident->string);
        break;

      default:
        fatal ("internal; unknown ident type in print_rav, code.c");
        break;
    }
  }
}


/* code_vect - generates code to assign a vector to another with op
               using format to print the source vector. */

code_vect(vect_t *vect, vect_t *res, char *op, char *pre ,char *post, 
	  char *mid)
{
  int i;

  if ((vect->ident->type==CONSTANT)||(vect->ident->type==VARIABLE)) {
    if ((!SCALAR(vect->shp))||(vect->shp->ident->value>0)) {
      if (SCALAR(vect->shp)&&(vect->shp->ident->value==1)) {
        dotab(0);
        fprintf(tfile,"%s[",res->ident->string);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]%s%s",op,pre);
        print_ident(tfile,vect->ident);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s[",mid,res->ident->string);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,"]");
        }
        fprintf(tfile,"%s;\n",post);
      } else {
        dotab(0);
        fprintf(tfile,"for (i=0; i<");
        print_s_expr(tfile,vect->shp);
        fprintf(tfile,"; i++)  %s[i+",res->ident->string);
        print_s_expr(tfile,vect->loc);
/* the following line may be wrong */
        fprintf(tfile,"]%s%s",op,pre);
        print_ident(tfile,vect->ident);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s[i+",mid,res->ident->string);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,"]");
        }
        fprintf(tfile,"%s;\n",post);
      }
    }
  } else if (vect->ident->type==CONST_ARRAY) {
    if (SCALAR(vect->index)&&SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        fprintf(tfile,"%s[%d+",res->ident->string,i);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]%s%s",op,pre);
        fprintf(tfile,"%d",(int)
                vect->ident->array.cnst[i+(int) vect->index->ident->value]);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s[%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,"]");
        }
        fprintf(tfile,"%s;\n",post);

      }
    } else {
      embed_const_vect(vect->ident);
      recursive_assign(vect,res,op);
    }
  } else if (vect->ident->type==IOTA) {
    if (SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        fprintf(tfile,"%s[%d+",res->ident->string,i);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]%s%s",op,pre);
        fprintf(tfile,"(%d+");
        print_s_expr(tfile,vect->index);
        fprintf(tfile,")");
        if (mid!=NULL) {
          fprintf(tfile,"%s%s[%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,"]");
        }
        fprintf(tfile,"%s;\n",post);
      }
    } else {
      dotab(0);
      fprintf(tfile,"for (i=0; i<");
      print_s_expr(tfile,vect->shp);
      fprintf(tfile,"; i++)  %s[i+",res->ident->string);
      print_s_expr(tfile,vect->loc);
      fprintf(tfile,"]%s%si+",op,pre);
      print_s_expr(tfile,vect->index);
      if (mid!=NULL) {
        fprintf(tfile,"%s%s[i+",mid,res->ident->string);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]");
      }
      fprintf(tfile,"%s;\n",post);
    }
  } else if (vect->ident->type==RAV) {
    if (SCALAR(vect->index)&&SCALAR(vect->shp)) {
      for (i=0; i<vect->shp->ident->value; i++) {
        dotab(0);
        fprintf(tfile,"%s[%d+",res->ident->string,i);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]%s%s",op,pre);
        print_s_expr(tfile,
                     vect->ident->array.rav[i+(int)vect->index->ident->value]);
        if (mid!=NULL) {
          fprintf(tfile,"%s%s[%d",mid,res->ident->string,i);
          print_s_expr(tfile,vect->loc);
          fprintf(tfile,"]");
        }
        fprintf(tfile,"%s;\n",post);
      }
    } else {
      embed_const_vect(vect->ident);
      recursive_assign(vect,res,op);
    }
  } else if ((!SCALAR(vect->shp))||(vect->shp->ident->value>0)) {
    if (SCALAR(vect->shp)&&(vect->shp->ident->value==1)) {
      dotab(0);
      fprintf(tfile,"%s[",res->ident->string);
      print_s_expr(tfile,vect->loc);
      fprintf(tfile,"]%s%s%s[",op,pre,vect->ident->string);
      print_s_expr(tfile,vect->index);
      fprintf(tfile,"]%s;\n",post);
    } else {
      dotab(0);
      fprintf(tfile,"for (i=0; i<");
      print_s_expr(tfile,vect->shp);
      fprintf(tfile,"; i++)  %s[i+",res->ident->string);
      print_s_expr(tfile,vect->loc);
      fprintf(tfile,"]%s%s%s[i+",op,pre,vect->ident->string);
      print_s_expr(tfile,vect->index);
      if (mid!=NULL) {
        fprintf(tfile,"%s%s[i+",mid,res->ident->string);
        print_s_expr(tfile,vect->loc);
        fprintf(tfile,"]");
      }
      fprintf(tfile,"]%s;\n",post);
    }
  }
}


/* recursive_assign - search the expression tree generating code to assign
                      the result of vect to res.  op is the operator string
                      "=", "+=", "-=", "*=", or "/=" */

recursive_assign(vect_t *vect, vect_t *res, char *op)

{
  char *new_op[3];
  int i,first_cat,save;

  /* some simplification is done by checking is the shp of an operation
     is 0 or 1.  If zero then throw it away, if one then we don't need a
     loop construct just a simple scalar assignment */

  if (vect==NULL) {
    if ((!SCALAR(res->shp))||(res->shp->ident->value>0)) {
      if (SCALAR(res->shp)||(res->shp->ident->value==1)) {
        dotab(0);
        fprintf(tfile,"%s[0]%s0;\n\n",res->ident->string,op);
      } else {
        dotab(0);
        fprintf(tfile,"for (i=0; i<");
        print_s_expr(tfile,res->shp);
        fprintf(tfile,"; i++) %s[i]%s0;\n\n",res->ident->string,op);
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
    new_op[0]="+=";
  case MINUS:
    new_op[0]="-=";
  case TIMES:
    new_op[0]="*=";
  case DIVIDE:
    new_op[0]="/=";
  case MOD:
    new_op[0]="%=";

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
    code_vect(vect->left,res,op,"(",">0)",NULL);
    break;

  case IF_NEG:
    vect->left=purify_vect(vect->left);
    code_vect(vect->left,res,op,"(","<0)",NULL);
    break;

  case RSCAN:
    vect->left=purify_vect(vect->left);
    dotab(0);
    fprintf(tfile,"for (i=");
    print_s_expr(tfile,vect->left->shp);
    fprintf(tfile,"-2; i>=0; i--)");
    dotab(1);
    fprintf(tfile,"%s[i]%s%s[i+1]*%s[i];\n",res->ident->string,op,res->ident->string,
           vect->left->ident->string);
    break;

  case SCAN:
    vect->left=purify_vect(vect->left);
    dotab(0);
    fprintf(tfile,"for (i=1; i<");
    print_s_expr(tfile,vect->left->shp);
    fprintf(tfile,"; i++)");
    dotab(1);
    fprintf(tfile,"%s[i]%s%s[i-1]*%s[i];\n",res->ident->string,op,res->ident->string,
           vect->left->ident->string);
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
  sprintf(where, "%s[%s]", array, index);
}


/* addto_allocs - adds expr to the list of arrays that need to be 
     allocated. */

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


/* allocate_array - generate C code to declare an array of the appropriate
     size.  Arrays are allocated as one dimensional arrays to allow linear
     access. Output is to the variable file. */

allocate_array(ident_t *ident)
{
  int i,dynamic;
  char atype[10];

  SETUSED(ident->flags);

  if (ident->type!=VARIABLE) {
    if (ident->real)
       sprintf(atype,"double");
    else 
       sprintf(atype,"int");
    if (ident->array.dim->value>0) {
      dynamic=FALSE;
      for (i=0; i<ident->array.dim->value; i++) {
	if (ident->array.shp[i]->type!=CONSTANT)
	  dynamic=TRUE;
      }

      if (dynamic) {
	fprintf(vfile,"  %s *%s", atype, ident->string);
	fprintf(vfile,"=(%s *) get_mem(", atype);
      } else {
	fprintf(vfile,"  %s %s", atype, ident->string);
	fprintf(vfile,"[");
      }
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
      if (ident->array.dim->value==0)
	fprintf(vfile,"1");
      if (dynamic)
	fprintf(vfile,"*sizeof(%s));\n", atype);
      else
	fprintf(vfile,"];\n");
    } else fprintf(vfile,"  %s %s[1];\n", atype, ident->string);
  }     
} 


/* do_shapes - if expr and result's shapes have not been scanned then they
     are scanned.  Scanning results in storing *SCAN(shape) in the shape
     field for calculating loop steps.  */

do_shapes(expr_t *expr, expr_t *result)

{
  if (!ISSCANNED(expr->flags)) {
    expr->shp=vect_unop(RSCAN,expr->shp);
    expr->shp=purify_vect(expr->shp);
    SETSCANNED(expr->flags);
  }
  if (!ISSCANNED(result->flags)) {
    result->shp=vect_unop(RSCAN,result->shp);
    result->shp=purify_vect(result->shp);
    SETSCANNED(result->flags);
  }
}

/* my_gamma2 - generates C code to calculate Gamma(index,shp) and assign
     it to name.  dim is the length of index, and shp.  The resulting
     C code is output to file out. used for shapes that have not been
     rscanned.  */
 
int my_gamma2(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim)
{
  int ret;
  int i,j;
 
  index=vect_drop(s_vect(s_op(MINUS,index->shp,dim)),index);
  if (SCALAR(dim)) {
    if (dim->ident->value>0) {
      dotabf(out,0);
      fprintf(out,"%s",name);
      for (i=dim->ident->value-1; i>0; i--) {
        print_rav(out,index,i);
        fprintf(out,"+");
        print_rav(out,shp,i);
        fprintf(out,"*(");
      }
      print_rav(out,index,0);
      for (i=dim->ident->value-1; i>0; i--) fprintf (out, ")");
      fprintf(out,";\n");
      ret=TRUE;
    } else {
      dotabf(out,0);
      fprintf(out,"%s0;\n",name);
      ret=TRUE;
    }
  } else {
    /* this is wrong for un-rscanned shapes.  needs to be changed */
    ret=TRUE;
    shp=vect2array("gamma_shp",shp);
    index=vect2array("gamma_index",index);
    dotabf(out,0);
    fprintf(out,"for (i=0; i<");
    print_s_expr(out,dim);
    fprintf(out,"; i++)\n");
    dotabf(out,0);
    fprintf(out,"%s+=%s[i",name,index->ident->string);
    if (index->index!=NULL) {
      fprintf(out,"+");
      print_s_expr(out,index->index);
    }
    fprintf(out,"]*%s[i];\n",shp->ident->string);
  }
  return(ret);
}
 
/* my_gamma - generates C code to calculate Gamma(index,shp) and assign
     it to name.  dim is the length of index, and shp.  The resulting
     C code is output to file out. */

int my_gamma(FILE *out, char *name, vect_t *index, vect_t *shp, s_expr_t *dim)

{
  int ret;
  int i,j;
 
/*  printf("INDEX 1  "); print_vector(index);printf("\n"); */
  index=vect_drop(s_vect(s_op(MINUS,index->shp,dim)),index);
/*  printf("INDEX 2  "); print_vector(index);printf("\n"); */
/*  printf("SHAPE    "); print_vector(shp); printf("\n"); */
  if (SCALAR(dim)) {
    if (dim->ident->value>0) {
      dotabf(out,0);
      fprintf(out,"%s",name);
      for (i=0; i<dim->ident->value-1; i++) {
	if (i>0) fprintf(out,"+");
	print_rav(out,index,i);
	fprintf(out,"*");
	print_rav(out,shp,i+1);
      }
      if (i>0) fprintf(out,"+");
      print_rav(out,index,dim->ident->value-1);
      fprintf(out,";\n");
      ret=TRUE;
    } else {
      dotabf(out,0);
      fprintf(out,"%s0;\n",name);
      ret=TRUE;
    }
  } else {
    ret=TRUE;
    shp=vect2array("gamma_shp",shp);
    printf("GAMMA SHAPE "); print_vector(shp);printf("\n");
    index=vect2array("gamma_index",index);
    printf("GAMMA INDEX "); print_vector(index);printf("\n");
    dotabf(out,0);
    fprintf(out,"for (i=0; i<");
    print_s_expr(out,dim);
    fprintf(out,"; i++)\n");
    dotabf(out,0);
    fprintf(out,"%s+=%s[i",name,index->ident->string);
    if (index->index!=NULL) {
      fprintf(out,"+");
      print_s_expr(out,index->index);
    }
    fprintf(out,"]*%s[i];\n",shp->ident->string);
  }
 
  return(ret);
}


/* do_location - generates C code that assigns the location of the assignment
     in the shift variable for the assignment of expr to result.  Output is
     to the temporary code file.  */

int do_location(expr_t *expr, expr_t *result)

{
  char buf[256];
  expr_t *temp_res;

/* scan result shape and hopefully it isn't needed unscanned later on */
/* this makes the second if in do_shapes unnecessary.  should change later */
  if (!ISSCANNED(result->flags)) {
    result->shp=vect_unop(RSCAN,result->shp);
    result->shp=purify_vect(result->shp);
    SETSCANNED(result->flags);
  }

  if (expr==NULL) return;
  if (expr->loc==NULL) {
    dotab(0);
    fprintf(tfile,"shift=%s;\n",result->ident->string);
  } else {
    sprintf(buf,"shift=%s+",result->ident->string);
    return(my_gamma(tfile,buf,expr->loc,result->shp,result->dim));
  }
  expr_free(temp_res);
}


/* do_gamma - generates C code that assigns the index of the assignment
     in the offset variable for the assignment of expr to result.  Output is
     to the temporary code file.  */

do_gamma(expr_t *expr, expr_t *result, int num)

{
  char buf[256];

  if (expr==NULL) return;
  if (expr->index==NULL) {
    dotab(0);
    fprintf(tfile,"offset%d=%s;\n",num,expr->ident->string);
  } else {
    sprintf(buf,"offset%d=%s+",num,expr->ident->string);
    return(my_gamma(tfile,buf,expr->index,expr->shp,expr->dim));
  }
}


/* add_steps - calculates the step for each loop in an assigment, eliminating
     a step if possible.  */

add_steps(vect_t *bound, vect_t *shp1, vect_t *stride, s_expr_t *dim,
          int num, int scalar)
{
  int i,j,constant,d,d2,k;
  s_expr_t **step_mask;
  int pos,last;
  double value1,value2,value3,value4;
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
	value1=rav_value(bound,d-1,&constant);
	if ((!constant)||(value1>1)) step_mask[d-1]=&s_const1;
	else step_mask[d-1]=&s_const0;
	if (stride!=NULL) {
          step_mask[d-1]=s_op (TIMES,step_mask[d-1],red_rav(stride,d-1));
        }
	last=d-1;
      }       
      for (i=d-2; i>=0; i--) {
	value4=rav_value(bound,i,&constant);
	j=i+1;
	value1=1;
	while ((constant)&&(j<=last)) {
	  value1*=rav_value(bound,j,&constant);
	  j++;
	}
	if (constant)
	  value2=rav_value(shp1,i+1,&constant);
	if (constant&&(stride!=NULL))
	  value2*=rav_value(stride,i,&constant);
	if (constant)
	  value3=(last<d-1) ? rav_value(shp1,last+1,&constant) : 
	    (step_mask[d-1])->ident->value;
	if (constant&&(value4>1)) {
	  if (value2-value3*value1!=0) {
	    last=i;
	    step_mask[i]=get_s_expr();
	    step_mask[i]->ident=get_ident();
	    step_mask[i]->ident->type=CONSTANT;
	    step_mask[i]->ident->value=value2-value3*value1;
	  } else step_mask[i]=NULL;
	} else if (constant) {
	  step_mask[i]=NULL;
	} else {

/* new new new new new new new new */
          j=i+1;
          step_mask[i]=red_rav(bound,last);
          while(j<last) {
            step_mask[i]=s_op(TIMES,step_mask[i],red_rav(bound,j));
            j++;
          }
/* end end end end end end end end  */

          if (last<d-1) {

/* new new new new new new new new */
            step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
                              s_op(TIMES,red_rav(shp1,last+1),
                                   step_mask[i]));
/* end end end end end end end end  */

/* old old old old old old old old 
            step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
                              s_op(TIMES,red_rav(shp1,last+1),
                                   red_rav(bound,last)));
*/

          } else {

/* new new new new new new new new */
            step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
                              s_op(TIMES,step_mask[d-1],step_mask[i]));
/* end end end end end end end end  */

/* old old old old old old old old
            step_mask[i]=s_op(MINUS,red_rav(shp1,i+1),
                              s_op(TIMES,step_mask[d-1],red_rav(bound,last)));
*/

          }
          last=i;
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


/* do_loop_open - generates the C for loops for an assigment with bound and
     dimension dim. */

do_loop_open(vect_t *bound, s_expr_t *dim)

{
  int i,j,constant;
  double value;

  if (SCALAR(dim)) {
    if (dim->ident->value>max_dim) max_dim=dim->ident->value;

    for (i=0; i<dim->ident->value; i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=0",i);
	fprintf(tfile,"; i%d<",i);
	print_rav(tfile,bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
	ntab++;
      }
    }
  } else {
    fatal("Unknown dimension in do_loop_open");
  }
}


/* do_loop_close - generates C code to calculate the step for each loop
     as well as close it with a {.  mask indicates which loops require
     a step.  name is unused. */

do_loop_close(s_expr_t *dim, vect_t *bound, s_expr_t *rdim)

{
  int i,j,constant,d,rd,k,delta,skip;
  double value;
  steps_t *node;
  printf("do_loop_close...\n");
  if (SCALAR(rdim)) {
    rd=rdim->ident->value;
  } else {
    fatal("Unknown dimension: do_loop_close");
  }

  if (SCALAR(dim)) {
    d=dim->ident->value;
    k=rd-1;
    skip=0;
    delta=(d>rd) ? d-rd : 0;
    for (i=d-1; i>=0; i--) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	node=step_list->next;
	while (node!=NULL) {
	  if ((node->steps[i]!=NULL)||(node->steps[i]==&s_const0)) {
	    dotab(0);
	    fprintf(tfile,"offset%d+=",node->num);
	    print_s(tfile,node->steps[i]);
	    fprintf(tfile,";\n");
	  }
	  node=node->next;
	}
        if (k >= 0) {
	  if ((step_list->steps[k]!=NULL)||(step_list->steps[k]==&s_const0)) {
	    dotab(0);
	    fprintf(tfile,"shift+=");
	    print_s(tfile,step_list->steps[k]);
	    fprintf(tfile,";\n");
          }
	  k--;
	}
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      } else {
	if (skip<delta)
	  skip++;
	else
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

    for (i=0; i<(i==0 ? 1 : dim->ident->value-1); i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	dotab(0);
	fprintf(tfile,"for (i%d=",i);
	print_rav(tfile,index,i);
	fprintf(tfile,"; i%d<",i);
	print_rav(tfile,index,i);
	fprintf(tfile,"+");
	print_rav(tfile,bound,i);
	fprintf(tfile,"; i%d++) {\n",i);
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

  printf("iota_loop_close...\n");
  if (SCALAR(dim)) {
    for (i=0; i<(i==0 ? 1 : dim->ident->value-1); i++) {
      value=rav_value(bound,i,&constant);
      if ((!constant)||(value>1)) {
	ntab--;
	dotab(0);
	fprintf(tfile,"}\n");
      }
    }
  } else {
    fatal("Help! I don't know the dimension");
  }
}


/* global_assign - generates C code to implement a single array assigment of
     expr to result. */

global_assign(reduced_t *global, expr_t *result)

{
  int scalar_num_save;
  double value;
  int tau,i,constant;
  int num,last_num;
  s_expr_t **mask;
  reduced_t *node;
  int fish[7];

  /* any scalars  used during the assign can be reused */
  scalar_num_save=scalar_num;

  step_list=NULL;

  /* skip all the temporary assignments */
  node=global;
  while ((node!=NULL)&&
	 (strncmp(node->d.frag->left->ident->string,"temp",4)==0)) {
    node=node->next;
  }
  if (node!=NULL) {
    /* use the location of the first non-temporary assignments */
    printf("(N) LOP IS %s START ", result->ident->string);
    print_vector(node->d.frag->loc);
    printf("STOP(-1) "); print_vector(node->d.frag->bound);
/*    pgi_vect2array(fish, node->d.frag->bound,
		   node->d.frag->ident->array.dim->value);
*/
    printf("STRIDE "); print_vector(node->d.frag->stride); printf("\n");
    do_location(node->d.frag,result);
  }
  else {
    /* must be all temporary so used first one */
    if (global->d.frag->left->ident->type!=VARIABLE) {
      printf("(G) LOP IS %s INDEXED BY ", result->ident->string);
      print_vector(global->d.frag->loc);
      printf("STOP(-1) "); print_vector(global->d.frag->bound);
      printf("STRIDE "); print_vector(global->d.frag->stride); printf("\n");
      do_location(global->d.frag,result);
    }
  }
  printf("global_assign breakpoint 1\n");

  num=0;
  node=global;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
      printf("g_a C_A & RAV\n");
      tau=1;
      for (i=0; i<node->d.frag->ident->array.dim->value; i++) {
	tau*=node->d.frag->ident->array.shp[i]->value;
      }
/*
      if (node->d.frag->ident->real)
*/
        fprintf(vfile,"  double");
/*
      else 
        fprintf(vfile,"  int");
*/
      fprintf(vfile," consta%d[%d];\n",const_array_num,tau);
      for (i=0; i<tau; i++) {
	dotab(0);
	fprintf(tfile,"consta%d[%d]=",const_array_num,i);
	if (node->d.frag->ident->type==CONST_ARRAY) {
	  fprintf(tfile,"%f",node->d.frag->ident->array.cnst[i]);
	} else {
	  print_s_expr(tfile,node->d.frag->ident->array.rav[i]);
	}
	fprintf(tfile,";\n");
      }
      sprintf(node->d.frag->ident->string,"consta%d",const_array_num);
      node->d.frag->ident->type=EMBEDED_ARRAY;
      const_array_num++;
      /* continue to the ARRAY case */

    case EMBEDED_ARRAY:
    case ARRAY:
      printf("g_a ARRAY case\n");
      do_shapes(node->d.frag,result);
      do_gamma(node->d.frag,result,num);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->stride,node->d.frag->dim,num,FALSE);
      num++;
      break;
    case IOTA:
      printf("g_a IOTA\n");
      do_shapes(node->d.frag,result);
      break;
    case CONSTANT:
    case VARIABLE:
      printf("g_a CONST & VAR\n");
      do_shapes(node->d.frag,result);
      add_steps(node->d.frag->bound,node->d.frag->shp,
		node->d.frag->stride,node->d.frag->dim,num,TRUE);
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
    add_steps(result->bound,result->shp,NULL,result->dim,num,FALSE);
    do_loop_open(global->d.frag->bound,global->d.frag->dim);
    printf("OPENED LOOP: ");
    printf("BOUND "); print_vector(global->d.frag->bound); printf("\n");
    
  }

  printf("global_assign Breakpoint 2\n");
  node=global;
  num=0;
  while (node!=NULL) {
    switch (node->d.frag->ident->type) {
    case CONST_ARRAY:
    case RAV:
    case EMBEDED_ARRAY:
    case ARRAY:
      printf("ARRAYS...\n");
      dotab(0);
      if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
	  (node->d.frag->left->ident->type==VARIABLE)) {
	printf("LOP TEMP #%d    ", atoi(node->d.frag->left->ident->string+4));
	fprintf(tfile,node->d.frag->left->ident->string);
      } else {
	printf("LOP TEMP #0    ");
	fprintf(tfile,"*(shift)");
      }
      printf(" ROP OFFSET #%d    ",num);
      printf("\n(1) ROP IS %s INDEXED BY ", node->d.frag->ident->string);
      print_vector(node->d.frag->index);
      printf("STOP(-1) "); print_vector(node->d.frag->bound);
      printf("STRIDE "); print_vector(node->d.frag->stride); printf("\n");
      fprintf(tfile,"%s *(offset%d);\n",node->d.frag->func,num);
      num++;
      break;
      
    case IOTA:
      printf("IOTA...\n");
      for (i=0; i<(i==0 ? 1 : node->d.frag->dim->ident->value-1); i++) {
	value=rav_value(node->d.frag->bound,i,&constant);
	if ((!constant)||(value>1)) {
	  dotab(0);
	  fprintf(tfile,"*(shift)%s i%d;\n",node->d.frag->func,i);
	} else {
	  dotab(0);
	  fprintf(tfile,"*(shift)%s ",node->d.frag->func);
	  print_rav(tfile,node->d.frag->index,i);
	  fprintf(tfile,";\n");
	}
	dotab(0);
	fprintf(tfile,"shift++;\n");
      }
      break;
      
    case CONSTANT:
    case VARIABLE:
      printf("CONST/VAR...\n");
      dotab(0);
      if ((strncmp("temp",node->d.frag->left->ident->string,4)==0)&&
	  (node->d.frag->left->ident->type==VARIABLE)) {
	printf("LOP TEMP #%d    ", atoi(node->d.frag->left->ident->string+4));
	fprintf(tfile,node->d.frag->left->ident->string);
      } else {
	printf("LOP TEMP #0     ");
	fprintf(tfile,"*(shift)");
      }
      if (node->d.frag->ident->type==VARIABLE) {
	if (strncmp("temp",node->d.frag->ident->string,4)==0)
	  printf("ROP TEMP #%d    ", atoi(node->d.frag->ident->string+4));
	else if (strncmp("offset",node->d.frag->ident->string,6)==0) {
	  printf("ROP OFFSET #%d    ", atoi(node->d.frag->ident->string+6));
	  printf("\n(2) ROP IS %s INDEXED BY ", node->d.frag->ident->string);
	  print_vector(node->d.frag->index); printf("\n");
	  printf("STOP(-1) "); print_vector(node->d.frag->bound);
	  printf("STRIDE "); print_vector(node->d.frag->stride); printf("\n");
	}
	fprintf(tfile,"%s %s;\n",node->d.frag->func,
		node->d.frag->ident->string);
      } else {
	fprintf(tfile,"%s %f;\n",node->d.frag->func,
		node->d.frag->ident->value);
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


/* do_assign - calls global_assign.  This remains to be compatible with
an older routine. */

do_assign(expr_t *expr, expr_t *result)

{
  reduced_t reduced;

  reduced.type=NOP;
  reduced.d.frag=expr;
  reduced.next=NULL;
  expr->left=result;
  
  global_assign(&reduced,result);
}
    

/* start_loop - generates C code for the forall statement.  var is the looping
     variable and left and right are its bounds. */

int start_loop(expr_t *var, expr_t *left, expr_t *right)

{
  int i,len,simple;
  vect_t *l_bound,*r_bound;

  if (NOTALLOCATED(var->ident))
    allocate_array(var->ident);
  l_bound=make_vect(left);
  r_bound=make_vect(right);

  len=rav_value(var->shp,0,&simple);
  if (len == 0) ++len;  /* var is a constant; rav_value returns 0, but add
                           1 to it so something is done. */
  if (simple) {
    for (i=0; i<len; i++) {
      dotab(0);
      fprintf(tfile,"for (%s[%d]=",var->ident->string,i);
      print_rav(tfile,l_bound,i);
      fprintf(tfile,"; %s[%d]<",var->ident->string,i);
      print_rav(tfile,r_bound,i);
      fprintf(tfile,"; %s[%d]++) {\n",var->ident->string,i);
      ntab++;
    }
  } else {
    report("forall vector must have a static shape.");
  }

  return(len);
}


/* end_loop - generates end }s for a forall statement of depth dimension. */

end_loop(int depth)

{
  int i,simple,len;

  for (i=0; i<depth; i++) {
    ntab--;
    dotab(0);
    fprintf(tfile,"}\n");
  }
}


/* open_forall - generates C code for an internal forall generated by 
     and omega expression.  fa_expr describes the forall. */

open_forall(expr_t *fa_expr)

{
  int i, simple;

  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      /* if the loop bound is 1, there's no need to do a loop */
      if (rav_value(fa_expr->bound, i, &simple) == 1) {
        dotab(0);
        fprintf (tfile,"%s[%d]=",fa_expr->forall->fa->string,i);
        print_rav(tfile,fa_expr->index,i);
        fprintf (tfile,";\n");
      } else {
        dotab(0);
        fprintf(tfile,"for (%s[%d]=",fa_expr->forall->fa->string,i);
        print_rav(tfile,fa_expr->index,i);
        fprintf(tfile,"; %s[%d]<",fa_expr->forall->fa->string,i);
        print_rav(tfile,fa_expr->index,i);
        fprintf(tfile,"+");
        print_rav(tfile,fa_expr->bound,i);
        fprintf(tfile,"; %s[%d]++) {\n",fa_expr->forall->fa->string,i);
        ntab++;
      }
    }
  }
}


/* close_forall - generates code to close the loops resulting from an internal
     forall command.  */

close_forall(expr_t *fa_expr)

{
  int i, simple;

  if (SCALAR(fa_expr->forall->bound->shp)) {
    for (i=0; i<fa_expr->forall->bound->shp->ident->value; i++) {
      /* if the loop bound is 1, no loop was opened, so don't close it */
      if (rav_value(fa_expr->bound, i, &simple) != 1) {
        ntab--;
        dotab(0);
        fprintf(tfile,"}\n");
      }
    }
    
  }
  
  free(fa_expr->forall);
  fa_expr->forall=NULL;
}


/* allocate_actuals - allocates actuals in a procedure call that have not
     been allocated yet. */

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


/* separate_reduced - separates a list of assignments into two lists,
     global if the right hand side is a global array or distributed if
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


/* code_expr - generate code for a simple expression list */

code_expr(reduced_t *reduced)

{
  dist_t *l_dist;
  expr_t *result;
  reduced_t *node,*list;
  reduced_t *sep;
  int i = 0;

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
      if (find_dist(node->d.frag->ident)==NULL) {
	printf("calling global_assign from within code_expr\n");
	global_assign(node,result);
      }
      else{
	code_dist(node,result,l_dist);
	printf("calling code_dist #1 from within code_expr\n");
      }
    } else {
      printf("calling code_dist #2 from within code_expr\n");
      code_dist(node,result,l_dist);
    }
    list=list->next;
    collect_garbage(list,save_list,distribution);
  }
}


/* code_reduced - generates code for an entire reduced expression. */

code_reduced(reduced_t *reduced)

{
  name_t  *alloc_list,*nnode,*junk;
  reduced_t *node,*sub_node;
  char atype[10];
  
  allocs=NULL;
  node=reduced;
  while (node!=NULL) {

    switch (node->type) {
    case SKIP:
      printf("Printing reduced node SKIP\n");
      break;

    case NOP:
      printf("Printing reduced node NOP\n");
      code_expr(node->d.list);
      break;

    case ALLOCATE:
      printf("Printing reduced node ALLOCATE\n");
      if (node->d.frag->ident->real)
        sprintf (atype,"double");
      else
        sprintf (atype,"int");
      fprintf(vfile,"  %s *%s;\n",atype,node->d.frag->ident->string);
      dotab(0);
      fprintf(tfile,"%s=(%s *) get_mem((",node->d.frag->ident->string,atype);
      tau(tfile,node->d.frag);
      fprintf(tfile,")*sizeof(%s));\n",atype);
      addto_allocs(node->d.frag);
      break;

    case FORALL:
      printf("Printing reduced node FORALL\n");
      alloc_list=allocs;
      allocs=NULL;
      open_forall(node->d.list->d.frag);
      code_reduced(node->d.list->next);
      close_forall(node->d.list->d.frag);
      allocs=alloc_list;
      break;
    case EXT_OP:
      printf("Printing reduced node EXT_OP\n");
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
    fprintf(tfile,"free(%s);\n",nnode->name);
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

}


/* code_c_rec - generates code for an entire procedure body. */

code_c_rec(statement_t *body)
{
  dist_t *dist;
  statement_t *node;
  name_t *alloc,*dynamic_list,*junk;
  int depth,i;
  char atype[10];

  dynamics=NULL;
  node=body;
  while (node!=NULL) {
    /*T*/    printf("\nNow handling node of type %d\n", node->kind);

    switch (node->kind) {
    case REDUCED:

      fprintf(tfile,"/*******\n%s\n********/\n\n",node->str);
      code_reduced(node->d.reduced);
      fprintf(tfile,"\n\n");
      break;

    case DYNAMIC:
      if (node->d.dynamic->ident->real)
        sprintf (atype,"double");
      else
        sprintf (atype,"int");
      dist=find_dist(node->d.dynamic->ident);
      fprintf(vfile,"  %s *%s;\n",atype,node->d.dynamic->ident->string);
      dotab(0);
      fprintf(tfile,"%s=(%s *) get_mem((",
	      node->d.dynamic->ident->string,atype);
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
      fprintf(tfile,")*sizeof(%s));\n\n",atype);
      addto_dynamics(node->d.dynamic);
      break;

    case LOOP:
      dynamic_list=dynamics;
      depth=start_loop(node->d.loop->var,node->d.loop->lower,
		       node->d.loop->upper);
      code_c_rec(node->d.loop->body);
      end_loop(depth);
      dynamics=dynamic_list;
      break;
    case CALL:
      dotab(0);
      allocate_actuals(node->d.reduced->next);
      fprintf(tfile,node->str);
      break;
    default:
      fatal("unknown kind in code_c_rec");
    }
    collect_garbage(NULL,save_list,distribution);
    node=node->next;
  }

  alloc=dynamics;
  while (alloc!=NULL) {
    junk=alloc;
    dotab(0);
    fprintf(tfile,"free(%s);\n",alloc->name);
    alloc=alloc->next;
    free(junk);
  }
}
