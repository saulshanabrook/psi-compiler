/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   vect.c - procedures to maintain, manipulate, and code vector expressions.

   v0.0 Scott Thibault - 5/93
   v0.1 Scott Thibault - 6/93
   v0.2 Scott Thibault - 7/93
   v0.3 Scott Thibault - 10/93
           Added the vect_compare function.
   v0.4 Thom McMachon
	   - moved allocate_vect, embed_const_vect, print_rav, code_vect,
	     and recursive_assign from vect.c to code.c

*/

#include <stdio.h>
#include <math.h>
#include "psi.h"
#include "sys.h"

#include "psi.e"
#include "ident.e"
#include "sys.e"

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define NOTALLOCATED(a) ((!ISUSED(a->flags))&&(!ISPARAMETER(a->flags))&&(a->type!=RAV)&&(a->type!=CONST_ARRAY))

 /* these are the current numbers for various temporary variables */
int vect_tmp_num=0;

/* prototypes for forward reference */

vect_t *purify_vect(vect_t *vect);
s_expr_t *red_rav(vect_t *vect, int i);

/* real_vect - returns true if the vector expression is of the real type */

int real_vect(vect_t *vect)
{
  /* Search the entire expression tree if any REAL variable is found the
     whole expression is real */

  if (vect==NULL) 
    return(FALSE);
  if (vect->op==NOP)
    return(vect->ident->real);

  return(real_vect(vect->left)||real_vect(vect->right));
}


/* real_expr - returns true if the expression is of the real type */

int real_expr(expr_t *expr)
{
  /* Search the entire expression tree if any REAL variable is found the
     whole expression is real */

  if (expr==NULL) 
    return(FALSE);
  if (expr->op==NOP)
    return(expr->ident->real);

  return(real_expr(expr->left)||real_expr(expr->right));
}


/* rav_value - returns the value of the ith element of vect if
               possible.  Simple is TRUE if the value is known, 
	       FALSE o/w */

double rav_value(vect_t *vect, int i, int *simple)
{
  int index;
  double value;
  s_expr_t *s;

  *simple=FALSE;   /* guilty until proven inocent */

  if (vect->op!=NOP) {
    /* still might be static, for example if op is CAT */

    s=red_rav(vect,i);  /* get a scalar expression for the ith element */
    if (SCALAR(s)) {    /* if the expression is just a constant */
      *simple=TRUE;
      return(s->ident->value);
    } else return(0);
  }

  if (!static_shps(vect))  /* if index, loc, shp of all nodes of a vector /*
                           /* expression are scalars. */
    return(0);

  index=vect->index->ident->value;  /* index is start index of vector */

  value = 0;
  if (vect->ident->type==CONSTANT) {
    value=vect->ident->value;
    *simple=TRUE;
  }
  if (vect->ident->type==IOTA) {
    value=i+index;
    *simple=TRUE;
  }
  if (vect->ident->type==CONST_ARRAY) {
    /* check for empty vector (CONST_ARRAY, but shape = const0) */
    if (vect->ident->array.shp[0]==&const0) {
      *simple=TRUE;
      return (0);
    }
    else {
      value=vect->ident->array.cnst[i+index];
      *simple=TRUE;
    }
  }
  if ((vect->ident->type==RAV)&&
      (SCALAR(vect->ident->array.rav[i+index]))) {
    value=vect->ident->array.rav[i+index]->ident->value;
    *simple=TRUE;
  }
  if (vect->ident->type==EMBEDED_ARRAY) {
    /* check if vect was a rav or cnst and use old values */
    if (vect->ident->array.cnst!=NULL) {
      value=vect->ident->array.cnst[i+index];
      *simple=TRUE;
    } else if (SCALAR(vect->ident->array.rav[i+index])) {
      value=vect->ident->array.rav[i+index]->ident->value;
      *simple=TRUE;
    }
  }
  return(value);
}


/**** the following procedures are used for expression simplification ****/

/* const_op - performs op between two constant vectors arg, and res.  If size
              is positive it is the  length of the vectors.  If size==-1 then
	      a new vector is created and to be like res and arg is assigned
	      to the new vector.   Either the new vector or res is returned,
	      whichever is used.  */

vect_t *const_op(vect_t *arg, vect_t *res, int size, int op)

{
  vect_t *old_res;
  int i,index,loc;
  double *tmp;

  if (arg==NULL) return(NULL);
  if (size!=-1) {   /* create a new vector */
    old_res=res;
    res=get_vect();
    res->index=&s_const0;
                            /* if STORE than use the same location */
    if (op==STORE) 
      res->loc=old_res->loc;
    else
      res->loc=&s_const0;
    res->shp=old_res->shp;  /* has the same shape as the old one */
    res->ident=get_ident();
    res->ident->type=CONST_ARRAY;
    res->ident->array.dim=&const1;
    res->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    res->ident->array.shp[0]=make_ident(res->shp);
    res->ident->array.cnst=(double *) get_mem(size*sizeof(double));
  }

  if (arg->shp->ident->value==0) {
    return(res);
    /* avoid tmp=get_mem(0); because get_mem reports an error for 0 */
  }

  /* assign arg to a temporary array alligned to [0] */
  tmp=(double *) get_mem(arg->shp->ident->value*sizeof(double));

  index=arg->index->ident->value;
  if (arg->ident->type==IOTA) {
    for (i=0; i<arg->shp->ident->value; i++)
      tmp[i]=i+index;
  } else if (arg->ident->type==CONST_ARRAY) {
    for (i=0; i<arg->shp->ident->value; i++)
      tmp[i]=arg->ident->array.cnst[i+index];
  } else if (arg->ident->type==EMBEDED_ARRAY) {
      /* check if rav or constant and use the original values */
    if (arg->ident->array.cnst!=NULL) {
      for (i=0; i<arg->shp->ident->value; i++)
	tmp[i]=arg->ident->array.cnst[i+index];
    } else {
    for (i=0; i<arg->shp->ident->value; i++)
      tmp[i]=arg->ident->array.rav[i+index]->ident->value;
    }
  } else if (arg->ident->type==CONSTANT) {
    for (i=0; i<arg->shp->ident->value; i++)
      tmp[i]=arg->ident->value;
  } else {
    for (i=0; i<arg->shp->ident->value; i++)
      tmp[i]=arg->ident->array.rav[i+index]->ident->value;
  }    

  /* perform the operation */
  loc=arg->loc->ident->value;
  switch (op) {
  case STORE:
    /* this is diferent than NOP because the location isn't eliminated,
       but is left in res->loc */
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i]=tmp[i];
    }
    break;

  case NOP:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]=tmp[i];
    }
    break;

  case ABS:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]=fabs(tmp[i]);
    }
    break;

  case IF_POS:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]=(tmp[i]>0);
    }
    break;

  case IF_NEG:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]=(tmp[i]<0);
    }
    break;

  case RSCAN:
    res->ident->array.cnst[(int) arg->shp->ident->value-1+loc]=
      tmp[(int) arg->shp->ident->value-1+loc];
    for (i=arg->shp->ident->value-2; i>=0; i--) {
	tmp[i+loc]*=tmp[i+loc+1];
	res->ident->array.cnst[i+loc]=tmp[i+loc];
    }
    break;

  case SCAN:
    res->ident->array.cnst[loc]=
      tmp[loc];
    for (i=1; i<arg->shp->ident->value; i++) {
	tmp[i+loc]*=tmp[i+loc-1];
	res->ident->array.cnst[i+loc]=tmp[i+loc];
    }
    break;

  case PLUS:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]+=tmp[i];
    }
    break;

  case MINUS:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]-=tmp[i];
    }
    break;

  case TIMES:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]*=tmp[i];
    }
    break;

  case DIVIDE:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]/=tmp[i];
    }
    break;

  case MOD:
    for (i=0; i<arg->shp->ident->value; i++) {
      res->ident->array.cnst[i+loc]=
	(int) res->ident->array.cnst[i+loc] % (int) tmp[i];
    }
    break;

  case MIN:
    for (i=0; i<arg->shp->ident->value; i++) {
      if (res->ident->array.cnst[i+loc]>tmp[i])
	res->ident->array.cnst[i+loc]=tmp[i];
    }
    break;

  default:
    fatal ("internal; unknown operation in red_rav");
    break;
  }
  return(res);
}


/* static_value - return TRUE if a vector has all constant values
                  and a constant index, loc, and shape, FLASE o/w */

int static_value(vect_t *vect)
{
  int i;
  ident_t *new;

  if (vect->op!=NOP) return(FALSE);

  if ((vect->ident->type!=CONST_ARRAY)&&(vect->ident->type!=CONSTANT)&&
      (vect->ident->type!=RAV)&&(vect->ident->type!=EMBEDED_ARRAY)&&
      (vect->ident->type!=IOTA))
    return(FALSE);

  if (!( SCALAR(vect->loc) && SCALAR(vect->index) && SCALAR(vect->shp) )) {
    return (FALSE);
  }

  if (((vect->ident->type==EMBEDED_ARRAY)&&(vect->ident->array.cnst==NULL))||
      (vect->ident->type==RAV)) {
    /* if rav make sure each element is a constant */
    for (i=0; i<vect->shp->ident->value; i++)
      if (!SCALAR(vect->ident->array.rav[i+(int) vect->index->ident->value]))
	return(FALSE);
  }
  return(TRUE);
}


/* simplify_vect - combines all the constants in the expression vect and
                   returns the new expression */

vect_t *simplify_vect(vect_t *vect)
{
  vect_t *new_vect;
  double value;
  char *new_op[4];
  int cnt=0,i,simple;

  if (vect==NULL) return(NULL);

  /* if empty vector */
  if (SCALAR(vect->shp)&&(vect->shp->ident->value==0))
    return(vect);

  /* for each type of operator simplify its arguments and if the
     all reduce to constants that combine the constants */

  switch (vect->op) {
  case NOP:
    return(vect);
    break;

  case SKIP:
    /* it could be either the left or right */
    if (vect->left!=NULL) return(vect->left);
    else return(vect->right);
    break;
    
  case CAT:
    vect->left=simplify_vect(vect->left);
    if (SCALAR(vect->left->shp)&&(vect->left->shp->ident->value==0))
      return(vect->right);
    vect->right=simplify_vect(vect->right);
    if (SCALAR(vect->right->shp)&&(vect->right->shp->ident->value==0))
      return(vect->left);
    if (static_value(vect->left)&&static_value(vect->right)) {
      if (vect->left->shp->ident->value+vect->right->shp->ident->value>0) {
	/* this is cat so use NOP so the location is obeyed */
	new_vect=const_op(vect->left,vect,vect->left->shp->ident->value+
			  vect->right->shp->ident->value,NOP);
	const_op(vect->right,new_vect,-1,NOP);
	return(new_vect);
      }
    }
    break;

  case PLUS:
  case MINUS:
  case TIMES:
  case DIVIDE:
  case MOD:
  case MIN:
    vect->left=simplify_vect(vect->left);
    vect->right=simplify_vect(vect->right);
    if (static_value(vect->left)&&static_value(vect->right)) {
      new_vect=const_op(vect->left,vect,vect->left->shp->ident->value,NOP);
      const_op(vect->right,new_vect,-1,vect->op);
      return(new_vect);
    } else if (static_value(vect->left)) {
      if ((vect->left->ident->type==CONSTANT)&&
	  (vect->left->ident->value==0)) {
	if (vect->op==PLUS)
	  return(vect->right);
	if ((vect->op==MIN)||(vect->op==TIMES)||(vect->op==DIVIDE)||
	    (vect->op==MOD)) return(vect->left);
      }
    } else if (static_value(vect->right)) {
      if ((vect->right->ident->type==CONSTANT)&&
	  (vect->right->ident->value==0)) {
	if ((vect->op==PLUS)||(vect->op==MINUS)||(vect->op==MOD)) 
	  return(vect->left);
	if ((vect->op==TIMES)||(vect->op==MIN))
	  return(vect->right);
      }
    }
    break;

  case ABS:
  case RSCAN:
  case SCAN:
  case IF_NEG:
  case IF_POS:
    vect->left=simplify_vect(vect->left);
    if (static_value(vect->left)) {
      new_vect=const_op(vect->left,vect,vect->left->shp->ident->value,vect->op);
      return(new_vect);
    }
    break;

  default:
    fatal ("internal; unknown operator in simplify_vect");

  }
  return(vect);
}


/* make_vect - reduces an expression (array) to a vector and returns the
               vector.  This routine is used for operations that expect
	       vector arguments. */

vect_t *make_vect(expr_t *expr)
{
  expr_t *tmp;
  vect_t *ret;

  int pure=TRUE,i;
  ret=get_vect();
  ret->index=&s_const0;
  ret->loc=&s_const0;
  if (SCALAR(expr->dim)&&(expr->dim->ident->value==0.0)) {
    /* change scalars into vectors */
    ret->shp=&s_const1;
  } else {
    ret->shp=make_s_expr(expr->shp);
  }
  
  /* naive - if the array is anything but a simple access then we assign
             it to a temporary variable and return that */
  if ((expr->op!=NOP)||(expr->index!=NULL)) {
    expr->loc=get_vect();
    expr->loc->index=&s_const0;
    expr->loc->loc=&s_const0;
    expr->loc->shp=expr->shp->shp;
    expr->loc->ident=&const0;
    expr->bound=expr->shp;
    if (expr->index==NULL) expr->index=expr->loc;  /* not sure about this */
    tmp=get_expr_mem(1);
    tmp->dim=expr->dim;
    tmp->shp=expr->shp;
    tmp->bound=expr->bound;
    tmp->ident=get_ident();
    tmp->ident->type=ARRAY;
    tmp->ident->array.dim=make_ident(expr->dim);
    if (tmp->ident->array.dim->type==CONSTANT) {
      if (tmp->ident->array.dim->value>0) {
	tmp->ident->array.shp=(ident_t **) 
	  get_mem(sizeof(ident_t *)*(tmp->ident->array.dim->value));
	for (i=0; i<tmp->ident->array.dim->value; i++)
	  tmp->ident->array.shp[i]=make_ident(red_rav(expr->shp,i));
      }	
    }

    sprintf(tmp->ident->string,"tmp_vect%d",vect_tmp_num);
    tmp->ident->real=real_expr(expr);
    allocate_vect(tmp->ident);
    vect_tmp_num++;
    assign(expr,tmp,TRUE,"=",FALSE);
    ret->ident=tmp->ident;
  } else {
    /* if its just an array access than there is no difference */
    ret->ident=expr->ident;
  }

  return(ret);
}


/**** the following rutines perform operations between vectors ****/

/* vect_len - returns the lenght of a vector */

vect_t *vect_len(vect_t *vect)

{
  vect_t *ret;

  if (vect==NULL) return(&zero_vec);
  ret=get_vect();
  ret->loc=&s_const0;
  ret->index=&s_const0;
  ret->shp=&s_const1;
  ret->ident=make_ident(vect->shp);
  return(ret);
}


/* vect_op - perform op between left and right.  This just makes
             op the root of the expression tree. */

vect_t *vect_op(int op, vect_t *left, vect_t *right)

{
  vect_t *ret;

  ret=get_vect();
  ret->op=op;
  ret->loc=&s_const0;
  ret->index=&s_const0;
  ret->shp=left->shp;
  ret->left=left;
  ret->right=right;
  
  return(simplify_vect(ret));
}


/* vect_take - take (*left) elements from the right vect.  This is done
               by adjusting the shape of every node in the expression
	       right. */

vect_t *vect_take(vect_t *left, vect_t *right)

{
  vect_t *ret;

  if (right==NULL) return(NULL);
  if (SCALAR(left->shp)&&(left->shp->ident->value==0))
    return(right);
  ret=get_vect();
  *ret=*right;
  propagate_take(ret,make_s_expr(left));

  return(simplify_vect(ret));
}


/* propagate_take - searchs the tree inforcing the new bounds on each node */

propagate_take(vect_t *vect, s_expr_t *bound)

{
  int children;
  vect_t *copy;
  s_expr_t *left,*right,*right_bound;
  s_expr_t *shp;

  if (vect==NULL) return;
  
  children=(vect->op!=NOP);

  /* if we have a cat we need to check if the bound crosses over the
     concatenation point. */
  if (vect->op==CAT) {
    shp=red_s_expr(vect->left->shp);
    if (SCALAR(shp)&&SCALAR(bound)) {
      if (bound->ident->value<shp->ident->value) {
	if (vect->left!=NULL) {
	  copy=get_vect();
	  *copy=*vect->left;
	  vect->left=copy;
	  propagate_take(vect->left,bound);
	}
      }
      if (bound->ident->value>shp->ident->value) {
	right_bound=get_s_expr();
	right_bound->ident=get_ident();
	right_bound->ident->type=CONSTANT;
	right_bound->ident->value=bound->ident->value-shp->ident->value;
      } else {
	vect->op=SKIP;
	vect->right=NULL;
	right_bound=NULL;
      }
    } else {
      left=s_op(MIN,shp,bound);
      if (vect->left!=NULL) {
	copy=get_vect();
	*copy=*vect->left;
	vect->left=copy;
	propagate_take(vect->left,left);
      }

      right_bound=s_op(MINUS,bound,left);
    }

    if (right_bound!=NULL) {
      shp=red_s_expr(vect->right->shp);
      if (SCALAR(shp)&&SCALAR(right_bound)) {
	if (right_bound->ident->value<shp->ident->value) {
	  if (vect->right!=NULL) {
	    copy=get_vect();
	    *copy=*vect->right;
	    vect->right=copy;
	    propagate_take(vect->right,right_bound);
	  }
	}
      } else {
	right=s_op(MIN,shp,right_bound);

	if (vect->right!=NULL) {
	  copy=get_vect();
	  *copy=*vect->right;
	  vect->right=copy;
	  propagate_take(vect->right,right);
	}
      }
    }

    children=FALSE;
  }

  /* the new bound */
  vect->shp=bound;

  if (children) {
    if (vect->left!=NULL) {
      copy=get_vect();
      *copy=*vect->left;
      vect->left=copy;
      propagate_take(vect->left,bound);
    }
    if (vect->right!=NULL) {
      copy=get_vect();
      *copy=*vect->right;
      vect->right=copy;
      propagate_take(vect->right,bound);
    }
  }
}


/* vect_drop - drop (*left) elments from the vect right.  This is done
               by adding *left to the index of every node in (right) */

vect_t *vect_drop(vect_t *left, vect_t *right)

{
  s_expr_t *tmp;
  vect_t *ret;

  if (right==NULL) return(NULL);
  if (SCALAR(left->shp)&&(left->shp->ident->value==0))
    return(right);
  ret=get_vect();
  *ret=*right;

  tmp=make_s_expr(left);
  propagate_drop(ret,tmp);
  update_locs(ret,tmp);

  return(simplify_vect(ret));
}


/* update_locs - changes the location of every vector in the expression 
     to reflect the drop. If the location is not zero then the new
     location is the location-drop_value or zero if this is negative. */

update_locs(vect_t *vect, s_expr_t *drop)

{
  s_expr_t *loc;
  vect_t *copy;

  if (vect==NULL) return;

  loc=red_s_expr(vect->loc);
  if (SCALAR(loc)&&SCALAR(drop)) {
    vect->loc=get_s_expr();
    vect->loc->ident=get_ident();
    vect->loc->ident->type=CONSTANT;
    vect->loc->ident->value=(loc->ident->value-drop->ident->value>0) ? 
      loc->ident->value-drop->ident->value : 0;
  } else {
    vect->loc=s_op(MAX,loc,drop);
  }

  if (vect->left!=NULL) {
    copy=get_vect();
    *copy=*vect->left;
    update_locs(copy,drop);
    vect->left=copy;
  }
  if (vect->right!=NULL) {
    copy=get_vect();
    *copy=*vect->right;
    update_locs(copy,drop);
    vect->right=copy;
  }
}


/* propagate_drop - search the tree and add index to each nodes
                    old index */

propagate_drop(vect_t *vect, s_expr_t *index)

{
  int children;
  vect_t *copy;
  s_expr_t *left,*right,*new_index;
  s_expr_t *shp1,*shp2,*shp,*tmp;

  if (vect==NULL) return;
  
  children=(vect->op!=NOP);

  /* if cat we have to check to see if the index crosses the concatenation
     point */
  if (vect->op==CAT) {
    shp1=red_s_expr(vect->left->shp);
    shp2=red_s_expr(vect->right->shp);

    if (SCALAR(shp1)&&SCALAR(index)) {
      if (index->ident->value>=shp1->ident->value) {
	right=get_s_expr();
	right->ident=get_ident();
	right->ident->type=CONSTANT;
	right->ident->value=index->ident->value-shp1->ident->value;
      } else right=NULL;
    } else {
      right=s_op(MAX,index,shp1);
    }
    
    if (right!=NULL) {
      if (vect->right!=NULL) {
	copy=get_vect();
	*copy=*vect->right;
	vect->right=copy;
	propagate_drop(vect->right,right);
      }
    }

    if (right==NULL) {
      if (vect->left!=NULL) {
	copy=get_vect();
	*copy=*vect->left;
	vect->left=copy;
	propagate_drop(vect->left,index);
      }
    } else if (!SCALAR(right)) {
      left=s_op(MIN,shp1,index);

      if (vect->left!=NULL) {
	copy=get_vect();
	*copy=*vect->left;
	vect->left=copy;
	propagate_drop(vect->left,left);
      }
    } else {
      vect->left=NULL;
      vect->op=SKIP;
    }

    children=FALSE;
  }

  vect->shp=s_op(MINUS,vect->shp,index);

  vect->index=s_op(PLUS,vect->index,index);

  if (children) {
    if (vect->left!=NULL) {
      copy=get_vect();
      *copy=*vect->left;
      vect->left=copy;
      propagate_drop(vect->left,index);
    }
    if (vect->right!=NULL) {
      copy=get_vect();
      *copy=*vect->right;
      vect->right=copy;
      propagate_drop(vect->right,index);
    }
  }
}


/* vect_cat - concatenate two vectors.  A new root is created with the
              CAT operator and the right sub-tree has a new location
	      within the result. */

vect_t *vect_cat(vect_t *left, vect_t *right)

{
  ident_t *shp,*shp1,*loc,*tmp,*loc1;
  vect_t *ret;

  if (left==NULL) return(right);
  if (right==NULL) return(left);
  ret=get_vect();
  ret->op=CAT;
  ret->loc=&s_const0;
  ret->index=&s_const0;

  ret->shp=s_op(PLUS,left->shp,right->shp);

  ret->left=left;
  ret->right=get_vect();
  *ret->right=*right;

  /* prop. (left->shp) to the location of the right sub-tree */
  propagate_cat(ret->right,left->shp);

  return(simplify_vect(ret));
}


/* propagate_cat - searches the expression tree adding location to the
                   old location of each node. */

propagate_cat(vect_t *vect, s_expr_t *location)

{
  vect_t *copy;
  s_expr_t *loc,*loc1,*tmp;

  if (vect==NULL) return;

  if (vect->left!=NULL) {
    copy=get_vect();
    *copy=*vect->left;
    vect->left=copy;
    propagate_cat(vect->left,location);
  }
  if (vect->right!=NULL) {
    copy=get_vect();
    *copy=*vect->right;
    vect->right=copy;
    propagate_cat(vect->right,location);
  }

  vect->loc=s_op(PLUS,vect->loc,location);
}


/* vect_unop - returns a new root with the op operator */

vect_t *vect_unop(int op, vect_t *vect)

{
  vect_t *ret;

  if (vect==NULL) return(NULL);
  if (SCALAR(vect->shp)&&(vect->shp->ident->value==0))
    return(vect);
  ret=get_vect();
  ret->op=op;
  ret->index=&s_const0;
  ret->loc=&s_const0;
  ret->shp=vect->shp;
  ret->left=vect;

  return(simplify_vect(ret));
}


/* expand_vect - returns a vector free from a scalar ident.
     Some vectors have a shape but still point to a scalar meaning
     that scalar is repeated. This type of vector is expaned into
     one that points to a constant array ident. */

vect_t *expand_vect(vect_t *vect)

{
  int i;
  ident_t *new;
  vect_t *ret;

  ret=vect;

  if (vect->op!=NOP)
    fatal("Internal error: vect_expand");

  if (SCALAR(vect->shp)&&(vect->ident->type==CONSTANT)) {
    if (vect->shp->ident->value>0) {
      new=get_ident();
      new->type=CONST_ARRAY;
      new->array.dim=&const1;
      new->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
      new->array.shp[0]=vect->shp->ident;
      new->array.cnst=(double *) get_mem(vect->shp->ident->value*sizeof(double));
      for (i=0; i<vect->shp->ident->value; i++) {
	new->array.cnst[i]=vect->ident->value;
      }
      ret=get_vect();
      *ret=*vect;
      ret->ident=new;
    } 
  }
  return(ret);
}


/* vect_compare - returns TRUE if vect1 is the same as vect2, FALSE
     if they are not the same or indeterminable (variable length). */

int vect_compare(vect_t *vect1, vect_t *vect2) 

{
  if (vect1==NULL)
    return(vect2==NULL);

  vect1=purify_vect(vect1);
  vect1=expand_vect(vect1);
  vect2=purify_vect(vect2);
  vect2=expand_vect(vect2);

  return(ident_compare(vect1->ident,vect2->ident));
}


/**** the following rutines are use for code generation ****/

/* print_scalar - make the vector a scalar and print it */

print_scalar(vect_t *expr)

{
  if (expr==NULL) {
    fprintf(tfile,"0");
    return;
  }
  if (expr->op==NOP) {
    print_ident(tfile,expr->ident);
    return;
  }
  if (expr->op==MIN)
    fprintf(tfile,"min(");
  if ((expr->op==IF_NEG)||(expr->op==IF_POS)) fprintf(tfile,")");
  print_scalar(expr->left);
  switch(expr->op) {
  case PLUS:
    fprintf(tfile,"+");
    break;
  case MINUS:
    fprintf(tfile,"-");
    break;
  case TIMES:
    fprintf(tfile,"*");
    break;
  case DIVIDE:
    fprintf(tfile,"/");
    break;
  case MOD:
    fprintf(tfile,"%");
    break;
  case MIN:
    fprintf(tfile,",");
    break;
  case IF_POS:
    fprintf(tfile,">");
    break;
  case IF_NEG:
    fprintf(tfile,"<");
    break;
  }
  if (expr->op!=CAT)
    print_scalar(expr->right);
  if ((expr->op==MIN)||
      (expr->op==IF_NEG)||(expr->op==IF_POS))
    fprintf(tfile,")");
}


/* vect_assign - calls a recursive function to assign to vectors and
                 adds a \n at the end */

vect_assign(vect_t *vect, vect_t *res, char *op)

{
  int i;
  vect_t *tmp;

  if (static_shps(vect)) {
    tmp=get_vect();
    tmp->index=&s_const0;
    tmp->loc=&s_const0;
    tmp->shp=vect->shp;
    tmp->ident=get_ident();
    tmp->ident->type=RAV;
    tmp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    tmp->ident->array.shp[0]=make_ident(tmp->shp);
    tmp->ident->array.dim=&const1;
    tmp->ident->array.rav=(s_expr_t **) 
      get_mem(vect->shp->ident->value*sizeof(s_expr_t *));
    for (i=0; i<vect->shp->ident->value; i++) {
      tmp->ident->array.rav[i]=red_rav(vect,i);
    }
  } else tmp=vect;

  recursive_assign(tmp,res,op);

  /*  fprintf(tfile,"\n"); */
}


/* static_shps - returns TRUE if the index,loc, and shp of a vector
     expression are scalars and the expression is just a variable access */


int static_shps(vect_t *vect)

{
  if (vect==NULL) return(TRUE);
  if (vect->op==NOP) {
    if (!SCALAR(vect->index)) return(FALSE);
    if (!SCALAR(vect->loc)) return(FALSE);
    if (!SCALAR(vect->shp)) return(FALSE);
    return(TRUE);
  }
  return(static_shps(vect->left)&&static_shps(vect->right));
}


/* red_rav - returns a scalar expression representing the ith element of
     a vector expression.  For example, element 1 of (a+b) is a[1]+b[1] */

s_expr_t *red_rav(vect_t *vect, int i)

{
  int index,x,k;
  s_expr_t *ret;
  char idx[10];

  ret=NULL;

  if (vect==NULL) {
    return(ret);
  }
  
  switch (vect->op) {
  case NOP:
    ret=get_s_expr();
    index=vect->index->ident->value;
    x=i-vect->loc->ident->value;

    switch (vect->ident->type) {
    case VARIABLE:
    case CONSTANT:
      ret->ident=vect->ident;
      break;

    case IOTA:
      ret->ident=get_ident();
      ret->ident->type=CONSTANT;
      ret->ident->real=FALSE;
      ret->ident->value=index+x;
      break;

    case EMBEDED_ARRAY:
      if (vect->ident->array.cnst!=NULL) {
	ret->ident=get_ident();
	ret->ident->type=CONSTANT;
        ret->ident->real=vect->ident->real;
	ret->ident->value=vect->ident->array.cnst[index+x];
      }	else {
	ret=vect->ident->array.rav[index+x];
      }
      break;

    case CONST_ARRAY:
      ret->ident=get_ident();
      ret->ident->type=CONSTANT;
      ret->ident->real=vect->ident->real;
      ret->ident->value=vect->ident->array.cnst[index+x];
      break;
      
    case RAV:
      ret=vect->ident->array.rav[index+x];
      break;
      
    case ARRAY:
      if (NOTALLOCATED(vect->ident))
	allocate_vect(vect->ident);
      ret->ident=get_ident();
      ret->ident->type=VARIABLE;
      ret->ident->flags=vect->ident->flags;
      ret->ident->real=vect->ident->real;
      sprintf(idx,"%d+%d",x,index);
      code_idx_array(ret->ident->string,vect->ident->string,idx);
      break;
      
    default:
      puts("red_rav: opps");
      exit(1);
    }
  break;

  case PLUS:
  case MINUS:
  case TIMES:
  case DIVIDE:
  case MOD:
  case MIN:
    ret=get_s_expr();
    ret->op=vect->op;
    ret->left=red_rav(vect->left,i);
    ret->right=red_rav(vect->right,i);
    break;

  case IF_NEG:
  case IF_POS:
  case ABS:
  case SKIP:
    ret=get_s_expr();
    ret->op=vect->op;
    ret->left=red_rav(vect->left,i);
    break;
    
  case CAT:
    if (i<vect->left->loc->ident->value+vect->left->shp->ident->value)
      ret=red_rav(vect->left,i);
    else
      ret=red_rav(vect->right,i);
    break;
    
  case RSCAN:
    ret=red_rav(vect->left,vect->shp->ident->value-1);
    for (k=vect->shp->ident->value-2; k>=i; k--) 
      ret=s_op(TIMES,ret,red_rav(vect->left,k));
    break;

  case SCAN:
    ret=red_rav(vect->left,0);
    for (k=1; k<i; k++) 
      ret=s_op(TIMES,ret,red_rav(vect->left,k));
    break;

  default:
    puts("red_rav: can't do this yet");
    exit(1);
    break;
  }

  return(ret);
}
  

/* purify_vect - returns a vector that is a simple vector access.  If the
                 vector passed in is just that, then it is returned; otherwise
		 we have an expression and it is assigned to a temporary 
		 vector. */

vect_t *purify_vect(vect_t *vect)
{
  int i;
  vect_t *tmp;
  expr_t *expr;

  vect=simplify_vect(vect);
  if (vect==NULL) return(vect);
  if (vect->op==NOP)
    if ((SCALAR(vect->index))&&(vect->index->ident->value==0)) {
      return(vect);
    } 

  if ((SCALAR(vect->shp))&&(vect->shp->ident->value==0))
    return(&empty_vec);

  tmp=get_vect();
  tmp->index=&s_const0;
  tmp->loc=&s_const0;
  tmp->shp=vect->shp;

  if (ISCODED(vect->flags)) {
    tmp->ident=vect->ident;
    return(tmp);
  }
    
  tmp->ident=get_ident();
  if (static_shps(vect)) {
    tmp->ident->type=RAV;
    tmp->ident->real=real_vect(vect);
    tmp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    tmp->ident->array.shp[0]=make_ident(tmp->shp);
    tmp->ident->array.dim=&const1;
    tmp->ident->array.rav=(s_expr_t **) 
      get_mem(vect->shp->ident->value*sizeof(s_expr_t *));
    for (i=0; i<vect->shp->ident->value; i++) {
      tmp->ident->array.rav[i]=red_rav(vect,i);
    }
  } else {
    sprintf(tmp->ident->string,"tmp_vect%d",vect_tmp_num);
    tmp->ident->type=ARRAY;
    tmp->ident->array.dim=&const1;
    tmp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    tmp->ident->array.shp[0]=make_ident(vect->shp);
    tmp->ident->real=real_vect(vect);
    expr=get_expr_mem(1);
    expr->dim=&s_const1;
    expr->shp=s_vect(tmp->shp);
    expr->ident=tmp->ident;
    allocate_vect(expr->ident);
    vect_tmp_num++;

    vect_assign(vect,tmp,"=");
  }
  
  if (vect->op==NOP) {
    /* since it's been coded ident is going to change and the index=loc=0 */
    vect->index=&s_const0;
    vect->loc=&s_const0;
  }
  vect->ident=tmp->ident;
  SETCODED(vect->flags);

  return(tmp);
}


/* force_vect - like purify vector only even if the vector expressions have
     static shapes and can be made into a RAV identifer, the vector is
     assigned to a temporary variable. */

vect_t *force_vect(vect_t *vect)

{
  expr_t *expr;
  vect_t *tmp;

  vect=purify_vect(vect);
  
  if (ISCODED(vect->ident->flags))
    return(vect);

  if ((vect->ident->type!=ARRAY)&&(vect->ident->type!=EMBEDED_ARRAY)) {
    SETCODED(vect->ident->flags);
    tmp=get_vect();
    tmp->index=&s_const0;
    tmp->loc=&s_const0;
    tmp->shp=vect->shp;
    tmp->ident=get_ident();
    sprintf(tmp->ident->string,"tmp_vect%d",vect_tmp_num);
    tmp->ident->type=ARRAY;
    tmp->ident->array.dim=&const1;
    tmp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    tmp->ident->array.shp[0]=make_ident(vect->shp);
    tmp->ident->real=real_vect(vect);
    expr=get_expr_mem(1);
    expr->dim=&s_const1;
    expr->shp=s_vect(tmp->shp);
    expr->ident=tmp->ident;
    allocate_array(expr->ident);
    vect_tmp_num++;

    vect_assign(vect,tmp,"=");
  } else {
    tmp=vect;
  }

  return(tmp);
}


/* vect2array - converts a vector to an array.  The array is declared in
   the C output with name of name.  This function calls vect_assign, in
   order to assign the vector to the array in the C output. */

vect_t *vect2array(char *name,vect_t *vect)
{
  vect_t *new_vect;
  
  if (vect->ident->type!=ARRAY) {
    new_vect=get_vect();
    new_vect->index=&s_const0;
    new_vect->loc=&s_const0;
    new_vect->shp=vect->shp;
    new_vect->ident=get_ident();
    if (name==NULL) {
      sprintf(new_vect->ident->string,"tmp_vect%d",vect_tmp_num);
      vect_tmp_num++;
    } else {
      sprintf(new_vect->ident->string,"%s",name);
    }
    new_vect->ident->real=real_vect(vect);
    new_vect->ident->type=ARRAY;
    vect_assign(vect,new_vect,"=");
    return(new_vect);
  } else 
    return(vect);
}


/* tau - compute the product of the shape of expr.  The product expression
     is output to the file fd */

void tau(FILE *fd, expr_t *expr)
{
  int i,t,simple;

  if (static_value(expr->shp)) {
    t=1;
    if (ISSCANNED(expr->flags)) {
      t=rav_value(expr->shp,0,&simple);
      fprintf(fd,"%d",t);
    } else {
      switch (expr->shp->ident->type) {
      case CONSTANT:
	fprintf(fd,"%d",(int) expr->shp->ident->value);
	break;
      case VARIABLE:
	fprintf(fd,"%s",expr->shp->ident->string);
	break;
      default:
	for (i=0; i<expr->shp->shp->ident->value; i++) {
	  t*=rav_value(expr->shp,i,&simple);
	}
	fprintf(fd,"%d",t);
	break;
      }
    }
  } else {
    if (ISSCANNED(expr->flags)) print_s_expr(fd,red_rav(expr->shp,0));
    else {
      for (i=0; i<expr->shp->shp->ident->value; i++) {
	if (i>0) fprintf(fd,"*");
	print_s_expr(fd,red_rav(expr->shp,i));
      }
      if (i==0)
	fprintf(fd,"1");
    }
  }
}
