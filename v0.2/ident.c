/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include <math.h>
#include "psi.h"

#include "psi.e"
#include "vect.e"
#include "sys.e"

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


/* make_ident - reduce a s_expr to an identifier.  Unless the s_expr is
                a simple variable access or has been coded befor, it is
		assigned to a temporary vector. */

ident_t *make_ident(s_expr_t *s)

{
  ident_t *tmp;

  if ((s->op==NOP)||ISCODED(s->flags)) return(s->ident);
  
  tmp=get_ident();
  tmp->type=VAR_FLOAT;
  fprintf(vfile,"  int scalar%d;\n",scalar_num);
  sprintf(tmp->string,"scalar%d",scalar_num);
  dotab(0);
  fprintf(tfile,"%s=",tmp->string);
  print_s_expr(tfile,s);
  fprintf(tfile,";\n");
  
  scalar_num++;
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
    fprintf(outfile,"%s[0]",ident->string);
  }
}


print_op(FILE *outfile, int op)

{
  switch (op) {
  case TIMES:
    fprintf(outfile,"*");
    break;
  case DIVIDE:
    fprintf(outfile,"/");
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
    case MINUS:
      print_s(outfile,s->left);
      print_op(outfile,s->op);
      print_s(outfile,s->right);
      break;

    case TIMES:
    case DIVIDE:
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
      fprintf(outfile,"(");
      print_s(outfile,s->left);
      fprintf(outfile,">0)");
      break;

    case IF_NEG:
      fprintf(outfile,"(");
      print_s(outfile,s->left);
      fprintf(outfile,"<0)");
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
    fprintf(vfile,"  int scalar%d;\n",scalar_num);
    dotab(0);
    fprintf(tfile,"scalar%d=",scalar_num);
    print_ident(tfile,ident);
    fprintf(tfile,";\n");
    
    sprintf(ret->string,"scalar%d",scalar_num);
    ret->type=VAR_FLOAT;
    scalar_num++;
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
    fprintf(vfile,"  int scalar%d;\n",scalar_num);
    sprintf(ret->ident->string,"scalar%d",scalar_num);
    dotab(0);
    fprintf(tfile,"%s=",ret->ident->string);
    print_s_expr(tfile,s);
    fprintf(tfile,";\n");
    
    scalar_num++;
    SETCODED(s->flags);
  }

  return(ret);
}


s_expr_t *compactor(s_expr_t *s, float *value, int *number)

{
  int found1,found2;
  float num1,num2;
  s_expr_t *ret;

  if (s==NULL) {
    *value=0;
    *number=TRUE;
    return(NULL);
  }

  switch (s->op) {
  case NOP:
    if (s->ident->type==FLOAT) {
      *value=s->ident->value;
      *number=TRUE;
      ret=NULL;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  case PLUS:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=num1+num2;
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      *value=num1;
      *number=TRUE;
      ret=s->right;
    } else if (found2) {
      *value=num2;
      *number=TRUE;
      ret=s->left;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  case MINUS:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=num1-num2;
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      ret->left=get_s_expr();
      NEW_SCALAR(ret->left->ident,num1);
      *number=FALSE;
      ret=s;
    } else if (found2) {
      *value=-num2;
      *number=TRUE;
      ret=s->left;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  case TIMES:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=((int) num1)*((int) num2);
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      ret=s;
      ret->left=get_s_expr();
      NEW_SCALAR(ret->left->ident,num1);
      *number=FALSE;
    } else if (found2) {
      ret=s;
      ret->right=get_s_expr();
      NEW_SCALAR(ret->right->ident,num2);
      *number=FALSE;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  case DIVIDE:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=((int) num1)/((int) num2);
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      ret=s;
      ret->left=get_s_expr();
      NEW_SCALAR(ret->left->ident,num1);
      *number=FALSE;
    } else if (found2) {
      ret=s;
      ret->right=get_s_expr();
      NEW_SCALAR(ret->right->ident,num2);
      *number=FALSE;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;

  case IF_POS:
    s->left=compactor(s->left,&num1,&found1);
    if (found1) {
      *value=(num1>=0);
      *number=TRUE;
      ret=NULL;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;

  case IF_NEG:
    s->left=compactor(s->left,&num1,&found1);
    if (found1) {
      *value=(num1<0);
      *number=TRUE;
      ret=NULL;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;    

  case SKIP:
    if (s->left==NULL) ret=s->right;
    else ret=s->left;
    break;

  case ABS:
    s->left=compactor(s->left,&num1,&found1);
    if (found1) {
      *value=fabs(num1);
      *number=TRUE;
      ret=NULL;
    } else {
      *number=FALSE;
      ret=s;
    }

  case MIN:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=MYMIN(num1,num2);
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      ret->left=get_s_expr();
      NEW_SCALAR(ret->left->ident,num1);
      *number=FALSE;
      ret=s;
    } else if (found2) {
      ret->right=get_s_expr();
      NEW_SCALAR(ret->right->ident,num2);
      *number=FALSE;
      ret=s;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  case MAX:
    s->left=compactor(s->left,&num1,&found1);
    s->right=compactor(s->right,&num2,&found2);
    if (found1&&found2) {
      *value=MYMAX(num1,num2);
      *number=TRUE;
      ret=NULL;
    } else if (found1) {
      ret->left=get_s_expr();
      NEW_SCALAR(ret->left->ident,num1);
      *number=FALSE;
      ret=s;
    } else if (found2) {
      ret->right=get_s_expr();
      NEW_SCALAR(ret->right->ident,num2);
      *number=FALSE;
      ret=s;
    } else {
      *number=FALSE;
      ret=s;
    }
    break;
    
  default:
    puts("compactor: internal error.");
    exit(1);
  }
  
  return(ret);
}
      

/* simplify_ident - combines all the constants in a s_expr */

s_expr_t *simplify_s_expr(s_expr_t *s)

{
  int found;
  float num;
  s_expr_t *ret,*tmp;

  tmp=compactor(s,&num,&found);

  if (found) {
    if (tmp==NULL) {
      ret=get_s_expr();
      NEW_SCALAR(ret->ident,num);
    } else {
      ret=get_s_expr();
      ret->op=PLUS;
      ret->left=tmp;
      ret->right=get_s_expr();
      NEW_SCALAR(ret->right->ident,num);
    }
  } else ret=tmp;

  return(ret);
}


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
