/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include <math.h>
#include "psi.h"

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

 /* these are the current numbers for various temporary variables */
int const_num=0;
int vect_tmp_num=0;

/* prototypes for forward reference */

vect_t *purify_vect(vect_t *vect);
s_expr_t *red_rav(vect_t *vect, int i);


/* rav_value - returns the value of the ith element of vect if
               possible.  Simple is TRUE if the value is know
	       FALSE o/w */

float rav_value(vect_t *vect, int i, int *simple)

{
  float value;

  *simple=FALSE;   /* guilty until proven inocent */
  if (vect->ident->type==FLOAT) {
    value=vect->ident->value;
    *simple=TRUE;
  }
  if (vect->ident->type==IOTA) {
    value=i;
    *simple=TRUE;
  }
  if (vect->ident->type==CONST_ARRAY) {
    value=vect->ident->array.cnst[i];
    *simple=TRUE;
  }
  if ((vect->ident->type==RAV)&&(SCALAR(vect->ident->array.rav[i]))) {
    value=vect->ident->array.rav[i]->ident->value;
    *simple=TRUE;
  }
  if (vect->ident->type==EMBEDED_ARRAY) {
    /* check if vect was a rav or cnst and use old values */
    if (vect->ident->array.cnst!=NULL) {
      value=vect->ident->array.cnst[i];
      *simple=TRUE;
    } else if (SCALAR(vect->ident->array.rav[i])) {
      value=vect->ident->array.rav[i]->ident->value;
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
  float *tmp;

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
    res->ident->array.cnst=(float *) get_mem(size*sizeof(float));
  }

  /* assign arg to a temporary array alligned to [0] */
  tmp=(float *) get_mem(arg->shp->ident->value*sizeof(float));
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
  } else if (arg->ident->type==FLOAT) {
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
    /* this is diferent than NOP because the location is'nt eliminated
       and is left in res->loc */
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

  case MIN:
    for (i=0; i<arg->shp->ident->value; i++) {
      if (res->ident->array.cnst[i+loc]>tmp[i])
	res->ident->array.cnst[i+loc]=tmp[i];
    }
    break;
  }
  
  
  free(tmp);
  return(res);
}


/* static_value - return TRUE if a vector has all constant values
                  and a constant index, loc, and shape, FLASE o/w */

int static_value(vect_t *vect)

     
{
  int i;
  ident_t *new;

  if (vect->op!=NOP) return(FALSE);

  if ((vect->ident->type!=CONST_ARRAY)&&(vect->ident->type!=FLOAT)&&
      (vect->ident->type!=RAV)&&(vect->ident->type!=EMBEDED_ARRAY)&&
      (vect->ident->type!=IOTA))
    return(FALSE);

  if (vect->loc->op!=NOP) return(FALSE);
  if (vect->loc->ident->type!=FLOAT) return(FALSE);

  if (vect->index->op!=NOP) return(FALSE);
  if (vect->index->ident->type!=FLOAT) return(FALSE);

  if (vect->shp->op!=NOP) return(FALSE);
  if (vect->shp->ident->type!=FLOAT) return(FALSE);

  if (vect->ident->type==RAV) {
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
  float value;
  char *new_op[4];
  int cnt=0,i,simple;

  if (vect==NULL) return(NULL);

  /* for each type of operator simplify its arguments and if the
     all reduce to constants that combine the constants */

  switch (vect->op) {
  case NOP:
    if ((vect->ident->type==FLOAT)||(vect->ident->type==VAR_FLOAT))
      return(vect);
    if (static_value(vect)) {
      /* use store so the location does'nt get distroyed */
      
      new_vect=const_op(vect,vect,vect->shp->ident->value,STORE);
      if (new_vect->ident->array.shp[0]->type==FLOAT)
	if (new_vect->ident->array.shp[0]->value==1.0) {
	  new_vect->ident->type=FLOAT;
	  new_vect->ident->value=new_vect->ident->array.cnst[0];
	}
      return(new_vect);
    }
    break;

  case SKIP:
    /* it could be either the left or right */
    if (vect->left!=NULL) return(vect->left);
    else return(vect->right);
    break;

  case CAT:
    vect->left=simplify_vect(vect->left);
    vect->right=simplify_vect(vect->right);
    if (static_value(vect->left)&&static_value(vect->right)) {
      /* this is cat so use NOP so the location is obeyed */
      new_vect=const_op(vect->left,vect,vect->left->shp->ident->value+
			vect->right->shp->ident->value,NOP);
      const_op(vect->right,new_vect,-1,NOP);
      return(new_vect);
    }
    break;

  case PLUS:
  case MINUS:
  case TIMES:
  case DIVIDE:
  case MIN:
    vect->left=simplify_vect(vect->left);
    vect->right=simplify_vect(vect->right);
    if (static_value(vect->left)&&static_value(vect->right)) {
      new_vect=const_op(vect->left,vect,vect->left->shp->ident->value,NOP);
      const_op(vect->right,new_vect,-1,vect->op);
      return(new_vect);
    } else if (static_value(vect->left)) {
      if ((vect->left->ident->type==FLOAT)&&
	  (vect->left->ident->value==0)) {
	if (vect->op==PLUS)
	  return(vect->right);
	if ((vect->op==MIN)||(vect->op==TIMES)||(vect->op==DIVIDE))
	  return(vect->left);
      }
    } else if (static_value(vect->right)) {
      if ((vect->right->ident->type==FLOAT)&&
	  (vect->right->ident->value==0)) {
	if ((vect->op==PLUS)||(vect->op==MINUS)) 
	  return(vect->left);
	if ((vect->op==TIMES)||(vect->op==MIN))
	  return(vect->right);
      }
    }
    break;

  case ABS:
  case RSCAN:
  case IF_NEG:
  case IF_POS:
    vect->left=simplify_vect(vect->left);
    if (static_value(vect->left)) {
      new_vect=const_op(vect->left,vect,vect->left->shp->ident->value,vect->op);
      return(new_vect);
    }
    break;

  }

  return(vect);
}


/* make_vect - reduces an expression (array) to a vector and returns the
               vector.  This rutine is used for operations that expect
	       vector arguments. */

vect_t *make_vect(expr_t *expr)

{
  expr_t *tmp;
  vect_t *ret;

  int pure=TRUE, old_temp_used,i;

  ret=get_vect();
  ret->index=&s_const0;
  ret->loc=&s_const0;
  ret->shp=make_s_expr(expr->shp);
  
  /* naive - if the array is anything but a simple access then we assign
             it to a temporary variable and return that */
  if ((expr->op!=NOP)||(expr->index!=NULL)) {
    old_temp_used=temp_used;
    temp_used=FALSE;
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
    tmp->ident=get_ident();
    tmp->ident->type=ARRAY;
    tmp->ident->array.dim=make_ident(expr->dim);
    if (tmp->ident->array.dim->type==FLOAT) {
      tmp->ident->array.shp=(ident_t **) 
	get_mem(sizeof(ident_t *)*(tmp->ident->array.dim->value));
      for (i=0; i<tmp->ident->array.dim->value; i++)
	tmp->ident->array.shp[i]=make_ident(red_rav(expr->shp,i));
    }

    fprintf(vfile,"  float *tmp_vect%d;\n",vect_tmp_num);
    dotab(0);
    fprintf(tfile,"  tmp_vect%d=(float *) malloc((",vect_tmp_num);
    tau(tfile,tmp);
    fprintf(tfile,")*sizeof(float));\n");
    sprintf(tmp->ident->string,"tmp_vect%d",vect_tmp_num);
    vect_tmp_num++;
    assign(expr,tmp,TRUE,"=",FALSE);
    temp_used=old_temp_used;
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
	right_bound->ident->type=FLOAT;
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
  ret=get_vect();
  *ret=*right;

  tmp=make_s_expr(left);
  propagate_drop(ret,tmp);
  update_locs(ret,tmp);

  return(simplify_vect(ret));
}


update_locs(vect_t *vect, s_expr_t *drop)

{
  s_expr_t *loc;
  vect_t *copy;

  if (vect==NULL) return;

  loc=red_s_expr(vect->loc);
  if (SCALAR(loc)&&SCALAR(drop)) {
    vect->loc=get_s_expr();
    vect->loc->ident=get_ident();
    vect->loc->ident->type=FLOAT;
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
	right->ident->type=FLOAT;
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
  ret=get_vect();
  ret->op=op;
  ret->index=&s_const0;
  ret->loc=&s_const0;
  ret->shp=vect->shp;
  ret->left=vect;

  return(simplify_vect(ret));
}


/**** the following rutines are use for code generation ****/

/* embed_const_vect - store a constant array in a temprorary variable so
                      it can be used for random access. */

embed_const_vect(ident_t *ident)

{
  int i;

  dotab(0);
  fprintf(tfile,"float const%d[%d];\n",const_num,(int) ident->array.shp[0]->value);
  for (i=0; i<ident->array.shp[0]->value; i++) {
    dotab(0);
    if (ident->type==CONST_ARRAY) 
      fprintf(tfile,"const%d[%d]=%d;\n",const_num,i,(int) ident->array.cnst[i]);
    else {
      fprintf(tfile,"const%d[%d]=",const_num,i);
      print_s_expr(tfile,ident->array.rav[i]);
      fprintf(tfile,";\n");
    }    
  }
  sprintf(ident->string,"const%d",const_num);
  ident->type=EMBEDED_ARRAY;
  const_num++;
}


/* print_rav - print the value of the ith element in expr */

print_rav(vect_t *expr,int i)

{
  int simple_index,index;

  if (expr==NULL) fprintf(tfile,"0");
  else {
    if (SCALAR(expr->index)) {
      simple_index=TRUE;
      index=expr->index->ident->value;
    }
    else simple_index=FALSE;

    switch (expr->ident->type) {
    case FLOAT:
      fprintf(tfile,"%d",(int) expr->ident->value);
      break;
      
    case VAR_FLOAT:
      fprintf(tfile,"%s",expr->ident->string);
      break;

    case IOTA:
      if (!simple_index) {
	print_s_expr(tfile,expr->index);
      } else {
	fprintf(tfile,"%d",index+i);
      }
      break;
      
	
    case EMBEDED_ARRAY:
      if (!simple_index) {
	fprintf(tfile,"%s[",expr->ident->string);
	print_s_expr(tfile,expr->index);
	fprintf(tfile,"]");
      } else {
	if (expr->ident->array.cnst!=NULL)
	  fprintf(tfile,"%d", (int) expr->ident->array.cnst[index+i]);
	else
	  print_s_expr(tfile,expr->ident->array.rav[index+i]);
      }
      break;

    case CONST_ARRAY:
      if (!simple_index) {
	embed_const_vect(expr->ident);
	fprintf(tfile,"%s[",expr->ident->string);
	print_s_expr(tfile,expr->index);
	fprintf(tfile,"]");
      } else
	fprintf(tfile,"%d",(int) expr->ident->array.cnst[index+i]);
      break;
      
    case RAV:
      if (!simple_index) {
	embed_const_vect(expr->ident);
	fprintf(tfile,"%s[",expr->ident->string);
	print_s_expr(tfile,expr->index);
	fprintf(tfile,"]");
      } else
	print_s_expr(tfile,expr->ident->array.rav[index+i]);
      break;
      
    case ARRAY:
      fprintf(tfile,"%s[%d",expr->ident->string,i);
      fprintf(tfile,"+");
      print_s_expr(tfile,expr->index);
      fprintf(tfile,"]");
      break;
    }
  }
}


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
  recursive_assign(vect,res,op);
  fprintf(tfile,"\n");
}


/* code_vect - generates code to assign a vector to another with op
               using format to print the source vector. */

code_vect(vect_t *vect, vect_t *res, char *op, char *pre ,char *post, char *mid)

{
  int i;

  if ((vect->ident->type==FLOAT)||(vect->ident->type==VAR_FLOAT)) {
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
  char *new_op[4];
  int cnt=0,i,first_cat,save;

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
    
    recursive_assign(vect->left,res,op);
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
    
  case NOP:
    code_vect(vect,res,op,"","",NULL);
    break;
  }
}


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


s_expr_t *red_rav(vect_t *vect, int i)

{
  int index,x,k;
  s_expr_t *ret;

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
    case VAR_FLOAT:
    case FLOAT:
      ret->ident=vect->ident;
      break;

    case IOTA:
      ret->ident=get_ident();
      ret->ident->type=FLOAT;
      ret->ident->value=index+x;
      break;

    case EMBEDED_ARRAY:
      if (vect->ident->array.cnst!=NULL) {
	ret->ident=get_ident();
	ret->ident->type=FLOAT;
	ret->ident->value=vect->ident->array.cnst[index+x];
      }	else {
	ret=vect->ident->array.rav[index+x];
      }
      break;

    case CONST_ARRAY:
      ret->ident=get_ident();
      ret->ident->type=FLOAT;
      ret->ident->value=vect->ident->array.cnst[index+x];
      break;
      
    case RAV:
      ret=vect->ident->array.rav[index+x];
      break;
      
    case ARRAY:
      ret->ident=get_ident();
      ret->ident->type=VAR_FLOAT;
      sprintf(ret->ident->string,
	      "%s[%d+%d]",vect->ident->string,x,index);
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

  default:
    puts("red_rav: can't do this yet");
    exit(1);
    break;
  }

  return(ret);
}
  

/* purify_vect - returns a vector that is a simple vector access.  If the
                 vector passed is just that then it is returned otherwise
		 we have an expression and its assigned to a temporary 
		 vector. */

vect_t *purify_vect(vect_t *vect)

{
  int i;
  vect_t *tmp;

  vect=simplify_vect(vect);
  if (vect==NULL) return(vect);
  if (vect->op==NOP) {
    return(vect);
  }

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
    tmp->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
    tmp->ident->array.shp[0]=make_ident(tmp->shp);
    tmp->ident->array.dim=&const1;
    tmp->ident->array.rav=(s_expr_t **) 
      get_mem(vect->shp->ident->value*sizeof(s_expr_t *));
    for (i=0; i<vect->shp->ident->value; i++) {
      tmp->ident->array.rav[i]=red_rav(vect,i);
    }
  } else {
    fprintf(vfile,"  float *tmp_vect%d;\n",vect_tmp_num);
    dotab(0);
    fprintf(tfile,"  tmp_vect%d=(float *) malloc((",vect_tmp_num);
    print_s_expr(tfile,vect->shp);
    fprintf(tfile,")*sizeof(float));\n");
    sprintf(tmp->ident->string,"tmp_vect%d",vect_tmp_num);
    tmp->ident->type=ARRAY;
    vect_tmp_num++;
    vect_assign(vect,tmp,"=");
  }
  
  vect->ident=tmp->ident;
  SETCODED(vect->flags);

  return(tmp);
}


/* vect2array - converts a vector to an array. */

vect_t *vect2array(char *name,vect_t *vect)

{
  vect_t *new_vect;
  
  if (vect->ident->type!=ARRAY) {
    new_vect=get_vect();
    new_vect->index=&s_const0;
    new_vect->loc=&s_const0;
    new_vect->shp=vect->shp;
    new_vect->ident=get_ident();
    sprintf(new_vect->ident->string,"%s",name);
    new_vect->ident->type=ARRAY;
    vect_assign(vect,new_vect,"=");
    return(new_vect);
  } else 
    return(vect);
}


tau(FILE *fd, expr_t *expr)

{
  int i,t,simple;

  if (static_value(expr->shp)) {
    t=1;
    if (expr->scanned) {
      t=rav_value(expr->shp,0,&simple);
      fprintf(fd,"%d",t);
    } else {
      switch (expr->shp->ident->type) {
      case FLOAT:
	fprintf(fd,"%d",(int) expr->shp->ident->value);
	break;
      case VAR_FLOAT:
	fprintf(fd,"%s",expr->shp->ident->string);
	break;
      default:
	for (i=0; i<expr->shp->ident->array.shp[0]->value; i++) {
	  t*=rav_value(expr->shp,i,&simple);
	}
	fprintf(fd,"%d",t);
	break;
      }
    }
  } else {
    if (expr->scanned) print_s_expr(fd,red_rav(expr->shp,0));
    else 
      for (i=0; i<expr->shp->shp->ident->value; i++) {
	print_s_expr(fd,red_rav(expr->shp,i));
      }
  }
}
