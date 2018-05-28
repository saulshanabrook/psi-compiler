/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   ident.c - contains procedures related to manipulating or generating code
     for scalar expression.

   v0.0 Scott Thibault - 5/93
   v0.1 Scott Thibault - 6/93
   v0.2 Scott Thibault - 7/93
   V0.3 Scott Thibault - 10/93
           Added the ident_compare, and s_compare functions.

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "psi.h"

#include "psi.e"
#include "vect.e"
#include "sys.e"
#include "scalar.e"

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define MYMIN(x,y) ((x)<(y)) ? (x) : (y)
#define MYMAX(x,y) ((x)>(y)) ? (x) : (y)

/* the current number of temporary scalars */
int scalar_num=0;
int max_scalar_num=0;
int int_expr=TRUE;

/* prototypes */
s_expr_t *simplify_s_expr(s_expr_t *s);


/* make_ident - reduce a s_expr to an identifier.  Unless the s_expr is
                a simple variable access or has been coded befor, it is
		assigned to a temporary vector. */

ident_t *make_ident(s_expr_t *s)

{
  ident_t *tmp;

  if ((s->op==NOP)||ISCODED(s->flags)) return(s->ident);
  
  tmp=get_ident();
  tmp->type=VAR_FLOAT;
  if (scalar_num>=max_scalar_num)
    fprintf(vfile,"  int scalar%d;\n",scalar_num);
  sprintf(tmp->string,"scalar%d",scalar_num);
  dotab(0);
  fprintf(tfile,"%s=",tmp->string);
  print_s_expr(tfile,s);
  fprintf(tfile,";\n");
  
  scalar_num++;
  if (scalar_num>max_scalar_num)
    max_scalar_num=scalar_num;

  s->ident=tmp;
  SETCODED(s->flags);

  return(tmp);
}


/* make_s_expr - reduce a vector to a s_expr.  Unless the vector is
                a simple variable access, it is assigned to a temporary
		vector. */

s_expr_t *make_s_expr(vect_t *vect)

{
  ident_t *tmp;
  s_expr_t *ret;

  if (SCALAR(vect->shp)&&(vect->shp->ident->value==0))
    return(&s_const0);

  tmp=get_ident();
  ret=get_s_expr();
  ret->op=NOP;
  ret->ident=tmp;

  if (vect->op==NOP) 
    switch (vect->ident->type) {
    case FLOAT:
    case VAR_FLOAT:
      *tmp=*vect->ident;
      return(ret);
      break;

    case IOTA:
      if (SCALAR(vect->index)) {
	tmp->type=FLOAT;
	tmp->value=vect->index->ident->value;
	return(ret);
      }
      break;

    case CONST_ARRAY:
      if (SCALAR(vect->index)) {
	tmp->type=FLOAT;
	tmp->value=vect->ident->array.cnst[(int) vect->index->ident->value];
	return(ret);
      }
      break;
      
    case EMBEDED_ARRAY:
      if (SCALAR(vect->index)) {
	if (vect->ident->array.rav!=NULL) {
	  ret=vect->ident->array.rav[(int) vect->index->ident->value];
	} else {
	  tmp->type=FLOAT;
	  tmp->value=vect->ident->array.cnst[(int) vect->index->ident->value];
	}
	return(ret);
      }
      break;
      
    case RAV:
      if (SCALAR(vect->index)) {
	ret=vect->ident->array.rav[(int) vect->index->ident->value];
	return(ret);
      }
      break;
    }

  return(red_rav(vect,0));
}


/* print_ident - prints the value of an identifier.  If its not a scalar then
                 rav(ident)[0] is used */

print_ident(FILE *outfile,ident_t *ident)

{
  int save;

  if (ident==NULL) {
    fprintf(outfile,"0");
    return;
  }

  switch (ident->type) {
  case FLOAT:
    fprintf(outfile,"%d",(int) ident->value);
    break;
  case VAR_FLOAT:
    if (int_expr)
      fprintf(outfile,"((int) %s)",ident->string);
    else
      fprintf(outfile,"%s",ident->string);
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
  case CONST_ARRAY:
    fprintf(outfile,"%d",(int) ident->array.cnst[0]);
    break;
  case RAV:
    print_s_expr(outfile,ident->array.rav[0]);
    break;
  case ARRAY:
    if (int_expr)
      fprintf(outfile,"((int) %s[0])",ident->string);
    else
      fprintf(outfile,"%s[0]",ident->string);
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
    fprintf(outfile,"%%");
    break;
  case PLUS:
    fprintf(outfile,"+");
    break;
  case MINUS:
    fprintf(outfile,"-");
    break;
  }
}


/* print_s_expr - this is just a shell to add extra parens */

print_s_expr(FILE *outfile, s_expr_t *s)

{
  s=simplify_s_expr(s);
  fprintf(outfile,"(");
  print_s(outfile,s);
  fprintf(outfile,")");
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
      fprintf(outfile,"fabs(");
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


/* red_ident - reduces an identifier to a simple variable access.  If the
               identifier is an expresion then the expression is assigned
	       to a temprorary scalar variable. */

ident_t *red_ident(ident_t *ident)

{
  ident_t *ret;

  if (ident==NULL) return(ret);

  switch (ident->type) {
  case FLOAT:
  case VAR_FLOAT:
    ret=ident;
    break;
    
  case EMBEDED_ARRAY:
    if (ident->array.rav!=NULL) 
      ret=make_ident(ident->array.rav[0]);
    else {
      ret=get_ident();
      ret->type=FLOAT;
      ret->value=ident->array.cnst[0];
    }
    break;

  case IOTA:
    ret=get_ident();
    ret->type=FLOAT;
    ret->value=0;
    break;
    
  case CONST_ARRAY:    
    ret=get_ident();
    ret->type=FLOAT;
    ret->value=ident->array.cnst[0];
    break;
    
  case RAV:
    ret=make_ident(ident->array.rav[0]);
    break;
    
  default:
    ret=get_ident();
    if (scalar_num>=max_scalar_num)
      fprintf(vfile,"  int scalar%d;\n",scalar_num);
    dotab(0);
    fprintf(tfile,"scalar%d=",scalar_num);
    print_ident(tfile,ident);
    fprintf(tfile,";\n");
    
    sprintf(ret->string,"scalar%d",scalar_num);
    ret->type=VAR_FLOAT;
    scalar_num++;
    if (scalar_num>max_scalar_num)
      max_scalar_num=scalar_num;
    break;
  }
  
  return(ret);
}


/* red_s_expr - reduces an identifier to a simple variable access.  If the
               identifier is an expresion then the expression is assigned
	       to a temprorary scalar variable. */

s_expr_t *red_s_expr(s_expr_t *s)

{  
  s_expr_t *ret;

  if (s==NULL) return(s);

  ret=get_s_expr();
  if ((s->op==NOP)||(ISCODED(s->flags))) {
    ret->ident=red_ident(s->ident);
  } else {
    ret->ident=get_ident();
    ret->ident->type=VAR_FLOAT;
    if (scalar_num>=max_scalar_num)
      fprintf(vfile,"  int scalar%d;\n",scalar_num);
    sprintf(ret->ident->string,"scalar%d",scalar_num);
    dotab(0);
    fprintf(tfile,"%s=",ret->ident->string);
    print_s_expr(tfile,s);
    fprintf(tfile,";\n");
    
    scalar_num++;
    if (scalar_num>max_scalar_num)
      max_scalar_num=scalar_num;

    s->ident=ret->ident;
    SETCODED(s->flags);
  }

  return(ret);
}


/* compactor - recusively searches and expression to make simplifications. */

s_expr_t *compactor(s_expr_t *s, int *changed)

{
  s_expr_t *ret;

  if (s==NULL) {
    return(NULL);
  }

  switch (s->op) {
  case NOP:
    ret=s;
    break;
    
  case PLUS:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&(s->left->ident->value==0)) {
      ret=s->right;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      ret=s->left;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;
    
  case MINUS:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      ret=s->left;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;
    
  case TIMES:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&(s->left->ident->value==0)) {
      ret=&s_const0;
      *changed=TRUE;
    } else if (SCALAR(s->left)&&(s->left->ident->value==1)) {
      ret=s->right;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      ret=&s_const0;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==1)) {
      ret=s->left;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;
    
  case DIVIDE:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&(s->left->ident->value==0)) {
      ret=&s_const0;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      fatal("Divide by zero in compactor");
    } else if (SCALAR(s->right)&&(s->right->ident->value==1)) {
      ret=s->left;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;

  case MOD:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&SCALAR(s->right)) {
      ret=get_s_expr();
      NEW_SCALAR(ret->ident,
		 ((int) s->left->ident->value)%((int) s->right->ident->value));
      *changed=TRUE;
    }
    ret=s;
    break;

  case IF_POS:
    s->left=compactor(s->left,changed);
    if (SCALAR(s->left)) {
      if (s->left->ident->value>=0) {
	ret=&s_const1;
      } else {
	ret=&s_const0;
      }
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;

  case IF_NEG:
    s->left=compactor(s->left,changed);
    if (SCALAR(s->left)) {
      if (s->left->ident->value<0)
	ret=&s_const1;
      else 
	ret=&s_const0;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;    

  case SKIP:
    if (s->left==NULL) ret=s->right;
    else ret=s->left;
    *changed=TRUE;
    break;

  case ABS:
    s->left=compactor(s->left,changed);
    if (SCALAR(s->left)) {
      ret=get_s_expr();
      ret->ident=get_ident();
      ret->ident->type=FLOAT;
      ret->ident->value=fabs(s->left->ident->value);
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;

  case MIN:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&SCALAR(s->right)) {
      ret=get_s_expr();
      NEW_SCALAR(ret->ident,
		 MYMIN(s->left->ident->value,s->right->ident->value));
      *changed=TRUE;
    } else if (SCALAR(s->left)&&(s->left->ident->value==0)) {
      ret=&s_const0;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      ret=&s_const0;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;
    
  case MAX:
    s->left=compactor(s->left,changed);
    s->right=compactor(s->right,changed);
    if (SCALAR(s->left)&&SCALAR(s->right)) {
      ret=get_s_expr();
      NEW_SCALAR(ret->ident,
		 MYMAX(s->left->ident->value,s->right->ident->value));
      *changed=TRUE;
    } else if (SCALAR(s->left)&&(s->left->ident->value==0)) {
      ret=s->right;
      *changed=TRUE;
    } else if (SCALAR(s->right)&&(s->right->ident->value==0)) {
      ret=s->left;
      *changed=TRUE;
    } else {
      ret=s;
    }
    break;
    
  default:
    puts("compactor: internal error.");
    exit(1);
  }
  
  return(ret);
}
      

s_expr_t *simplify_s_expr(s_expr_t *s)

{
  int found,changed;
  double num;
  s_expr_t *ret,*tmp;

  ret=StandardizeSExpr(s);

  do {
    changed=FALSE;
    ret=compactor(ret,&changed);
  } while (changed);

  return(ret);
}


/* s_op - returns an expression tree for left op right */

s_expr_t *s_op(int op, s_expr_t *left, s_expr_t *right)

{
  s_expr_t *ret;

  ret=get_s_expr();
  ret->op=op;
  ret->left=left;
  ret->right=right;
  
  return(simplify_s_expr(ret));
}


/* s_vect - this function converts a s_expr into a vector */

vect_t *s_vect(s_expr_t *s)

{
  vect_t *ret;
  
  ret=get_vect();
  ret->loc=&s_const0;
  ret->index=&s_const0;
  ret->shp=&s_const1;
  ret->ident=(red_s_expr(s))->ident;

  return(ret);
}


/* ident_compare - returns TRUE if ident1 and ident2 are the same pointers
    or are string equivalent, FALSE otherwise. */

int ident_compare(ident_t *ident1, ident_t *ident2)
     
{
  int ret,i;
  int type1,type2;

  type1=ident1->type;
  if (type1==EMBEDED_ARRAY)
    type1=(ident1->array.cnst!=NULL) ? CONST_ARRAY : RAV;
  type2=ident2->type;
  if (type2==EMBEDED_ARRAY)
    type2=(ident2->array.cnst!=NULL) ? CONST_ARRAY : RAV;

  ret=FALSE;
  switch (type1) {
  case VAR_FLOAT:
    switch (type2) {
    case VAR_FLOAT:
      ret=(strcmp(ident1->string,ident2->string)==0);
      break;
    case RAV:
      if ((ident2->array.shp[0]->value==1)&&(ident2->array.rav[0]->op==NOP))
	ret=ident_compare(ident1,ident2->array.rav[0]->ident);
      break;
    }
    break;
      
  case RAV:
    switch (type2) {
    case RAV:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  ret&=s_compare(ident1->array.rav[i],ident2->array.rav[i]);
	}
      }
      break;
    case VAR_FLOAT:
    case FLOAT:
      if ((ident1->array.shp[0]->value==1)&&(ident1->array.rav[0]->op==NOP))
	ret=ident_compare(ident1->array.rav[0]->ident,ident2);
      break;
    case CONST_ARRAY:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  if ((ident1->array.rav[i]->op!=NOP)||
	      (ident1->array.rav[i]->ident->type!=FLOAT)||
	      (ident1->array.rav[i]->ident->value!=ident2->array.cnst[i]))
	    ret=FALSE;
	}
      }
      break;
    case IOTA:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  if ((ident1->array.rav[i]->op!=NOP)||
	      (ident1->array.rav[i]->ident->type!=FLOAT)||
	      (ident1->array.rav[i]->ident->value!=i))
	    ret=FALSE;
	}
      }
      break;
    }
    break;

  case FLOAT:
    switch (type2) {
    case FLOAT:
      ret=(ident1->value==ident2->value);
      break;
    case RAV:
      if ((ident2->array.shp[0]->value==1)&&(ident2->array.rav[0]->op==NOP))
	ret=ident_compare(ident1,ident2->array.rav[0]->ident);
      break;
    case CONST_ARRAY:
      ret=((ident2->array.shp[0]->value==1)&&
	   (ident2->array.cnst[0]==ident1->value));
      break;
    case IOTA:
      ret=(ident1->value==0);
      break;
    }
    break;

  case CONST_ARRAY:
    switch (type2) {
    case CONST_ARRAY:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  ret&=(ident1->array.cnst[i]==ident2->array.cnst[i]);
	}
      }
      break;
    case FLOAT:
      ret=((ident1->array.shp[0]->value==1)&&
	   (ident1->array.cnst[0]==ident2->value));
      break;
    case RAV:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  if ((ident2->array.rav[i]->op!=NOP)||
	      (ident2->array.rav[i]->ident->type!=FLOAT)||
	      (ident2->array.rav[i]->ident->value!=ident1->array.cnst[i]))
	    ret=FALSE;
	}
      }
      break;
    case IOTA:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  ret&=(ident1->array.cnst[i]==i);
	}
      }
      break;
    }
    break;

  case IOTA:
    switch (type2) {
    case CONST_ARRAY:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  ret&=(ident2->array.cnst[i]==i);
	}
      }
      break;
    case FLOAT:
      ret=((ident1->array.shp[0]->value==1)&&(ident2->value==0));
      break;
    case RAV:
      if (ident1->array.shp[0]->value==ident2->array.shp[0]->value) {
	ret=TRUE;
	for (i=0; i<ident1->array.shp[0]->value; i++) {
	  if ((ident2->array.rav[i]->op!=NOP)||
	      (ident2->array.rav[i]->ident->type!=FLOAT)||
	      (ident2->array.rav[i]->ident->value!=i))
	    ret=FALSE;
	}
      }
      break;
    case IOTA:
      ret=(ident1->array.shp[0]->value==ident2->array.shp[0]->value);
      break;
    }
    break;

  case ARRAY:
    ret=(ident1==ident2);
    break;
  }

  return(ret);
}


/* s_compare - returns TRUE if s1 and s2 are the same as defined by
    the operators at each node are equal and the leaves point to the
    same identifier or are string equiv., FALSE otherwise. */

int s_compare(s_expr_t *s1, s_expr_t *s2)

{
  int ret;

  if (s1->op==s2->op) {
    if (s1->op==NOP) {
      ret=ident_compare(s1->ident,s2->ident);
    } else {
      ret=(s_compare(s1->left,s2->left)&&s_compare(s1->right,s2->right));
    }
  } else ret=FALSE;

  return(ret);
}
