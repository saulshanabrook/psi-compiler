/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   dist.c - the module contains procedures related to code generation of
     distributed arrays and their assignments.

   v3.0 Scott Thibault - 8/93
           Module creation.
        Scott Thibault - 10/93
           Renamed dist_assign to be code_dist and changed it to 
           accomodate the new structure of a list of lists for combined
           expressions.
           Procedures dist_assign, combine_distributed, and dist_compare were
           added to support the change.
        Scott Thibault - 3/94
           New intersection algorithm used that would work for dimensions
           higher than one.

*/

#include <stdio.h>
#include "psi.h"
#include "sys.h"
#include "dist.h"

#include "psi.e"
#include "code.e"
#include "part.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"

#define OUT_LEFT 0
#define OUT_RIGHT 1
#define NO_OUT 2

int max_c_dim,max_p_dim,max_l_dim,max_buffer_no;
char *host_name;
int host=FALSE;    /* generate host program T/F */
int para_trace=FALSE;
dist_t *distribution;



/* find_dist - search the distribution list to see if array as a distribution
     defined.  If found, the distribution for array is returned, NULL 
     otherwise. */

dist_t *find_dist(ident_t *array)

{
  dist_t *node;
  
  node=distribution;
  while ((node!=NULL)&&(node->ident!=array)) {
    node=node->next;
  }

  return(node);
}


int dist_compare(dist_t *dist1, dist_t *dist2)

{
  int ret;

  ret=vect_compare(dist1->c,dist2->c);
  ret&=vect_compare(dist1->g,dist2->g);
  ret&=vect_compare(dist1->e,dist2->e);
  ret&=vect_compare(dist1->pl,dist2->pl);
  ret&=vect_compare(dist1->pb,dist2->pb);

  return(ret);
}


reduced_t *copy_list(reduced_t *list)

{
  reduced_t *ret,*node;

  if (list==NULL) {
    ret=NULL;
  } else {
    ret=node=get_reduced();
    while (list!=NULL) {
      *node=*list;
      list=list->next;
      if (list==NULL) node->next=NULL;
      else {
        node->next=get_reduced();
        node=node->next;
      }
    }
  }

  return(ret);
}


/* inv_gamma - generates code to calculate the inverse gamma function with
     rav and shp as arguments and the result stored in res. */

inv_gamma(char *rav, vect_t *shp, char *res)

{
  int dim,i;

  if (max_dim<3) max_dim=3;
  dim=shp->shp->ident->value;
  
  dotab(0);
  fprintf(tfile,"i0=%s\n",rav);
  dotab(0);
  fprintf(tfile,"i1=");
  for (i=1; i<dim; i++) {
    if (i>1) fprintf(tfile,"*");
    print_rav(tfile,shp,i);
  }
  fprintf(tfile,"\n");
  for (i=0; i<dim-1; i++) {
    dotab(0);
    fprintf(tfile,"%s(%d)=i0/i1\n",res,i);
    dotab(0);
    fprintf(tfile,"i0= MOD (i0, i1)\n");
    dotab(0);
    fprintf(tfile,"i1=i1/");
    print_rav(tfile,shp,i+1);
    fprintf(tfile,"\n");
  }
  fprintf(tfile,"%s(%d)=i0\n",res,dim-1);
}


/* build_vect - a useful utility to allocate a vector with the name name and
     shp of length.  */

vect_t *build_vect(char *name, s_expr_t *shp)

{
  vect_t *ret;

  ret=get_vect();
  ret->loc=&s_const0;
  ret->index=&s_const0;
  ret->shp=shp;
  ret->ident=get_ident();
  SETUSED(ret->ident->flags);
  sprintf(ret->ident->string,"%s",name);
  ret->ident->type=ARRAY;
  ret->ident->array.dim=&const1;
  ret->ident->array.shp=(ident_t **) get_mem(sizeof(ident_t *));
  ret->ident->array.shp[0]=shp->ident;

  return(ret);
}


/* check_zero - returns TRUE if vect is constant and contains all zeros. */

int check_zero(vect_t *vect)

{
  int i,ret;

  if (vect->op==NOP) {
    if (vect->ident->type==CONST_ARRAY) {
      ret=TRUE;
      for (i=0; i<vect->ident->array.shp[0]->value; i++) {
        if (vect->ident->array.cnst[i]) ret=FALSE;
      }
    } else if (vect->ident->type==CONSTANT) {
      ret=(vect->ident->value==0);
    } else ret=FALSE;
  } else ret=FALSE;

  return(ret);
}


/* index_vect - generate code to access the index'th element of vect. */

index_vect(vect_t *vect, char *index)

{
  switch (vect->ident->type) {
  case CONST_ARRAY:
  case RAV:
    embed_const_vect(vect->ident);
    
  case EMBEDED_ARRAY:
  case ARRAY:
    fprintf(tfile,"%s(%s)",vect->ident->string,index);
    break;
        
  case IOTA:
    fprintf(tfile,"%s",index);
    break;
        
  case CONSTANT:
  case VARIABLE:
    if (vect->ident->type==VARIABLE) {
      fprintf(tfile,"%s",vect->ident->string);
    } else {
      fprintf(tfile,"%f",vect->ident->value);
    }
    break;
  }
}


/* if_bounded - generate code to check if the vector var is between
     lower and upper bounds lbound and rbound.  The boolean result
     is stored in res. */

if_bounded(vect_t *var, vect_t *lbound, vect_t *rbound, char *res, int out)

{
  var=purify_vect(var);
  if ((var->ident->type==CONST_ARRAY)||(var->ident->type==RAV))
    embed_const_vect(var->ident);
  if (lbound!=NULL) {
    lbound=purify_vect(lbound);
    if ((lbound->ident->type==CONST_ARRAY)||(lbound->ident->type==RAV))
      embed_const_vect(lbound->ident);
  }
  if (rbound!=NULL) {
    rbound=purify_vect(rbound);
    if ((rbound->ident->type==CONST_ARRAY)||(rbound->ident->type==RAV))
      embed_const_vect(rbound->ident);
  }

  dotab(0);
  fprintf(tfile,"DO i0 = 0, ");
  print_s_expr(tfile,var->shp);
  fprintf(tfile,"-1\n");
  ntab++;

  if ((out==OUT_LEFT)&&(lbound!=NULL)) {
    dotab(0);
    fprintf(tfile,"IF (");
    index_vect(var,"i0");
    fprintf(tfile,"<");
    index_vect(lbound,"i0");
    fprintf(tfile,") out=.TRUE.\n");
  }
  if ((out==OUT_RIGHT)&&(rbound!=NULL)) {
    dotab(0);
    fprintf(tfile,"IF (");
    index_vect(var,"i0");
    fprintf(tfile,">=");
    index_vect(rbound,"i0");
    fprintf(tfile,") out=.TRUE.\n");
  }
  
  ntab--;
  dotab(0);
  fprintf(tfile,"END DO\n");
}


/* close_while - generate the end of a while loop used for the implementation
     of nested loops of unknown depth. s contains the loop counters, s_bound
     is the bound, and cont is the name of a temporay variable that is used.
     Output is to the file fd. */

close_while(FILE *fd, vect_t *s, vect_t *s_bound, char *cont)

{
  int i,tab;

  int_expr=FALSE;
  for (i=s->shp->ident->value-1; i>0; i--) {
    dotabf(fd,0);
    print_rav(fd,s,i);
    fprintf(fd,"=");
    print_rav(fd,s,i);
    fprintf(fd,"+1\n");
    dotabf(fd,0);
    fprintf(fd,"IF (");
    print_rav(fd,s,i);
    fprintf(fd,">=");
    print_rav(fd,s_bound,i);
    fprintf(fd,") THEN\n");
    ntabf++;
    dotabf(fd,0);
    print_rav(fd,s,i);
    fprintf(fd,"=0\n");
  }
  dotabf(fd,0);
  print_rav(fd,s,0);
  fprintf(fd,"=");
  print_rav(fd,s,0);
  fprintf(fd,"+1\n");
  dotabf(fd,0);
  fprintf(fd,"IF (");
  print_rav(fd,s,0);
  fprintf(fd,">=");
  print_rav(fd,s_bound,0);
  fprintf(fd,") %s=.FALSE.\n",cont);
  for (i=1; i<s->shp->ident->value; i++) {
    ntabf--;
    dotabf(fd,0);
    fprintf(fd,"END IF\n");
  }
  dotabf(fd,0);
  fprintf(fd,"IF (.NOT. %s) EXIT\n",cont);
  dotabf(fd,-1);
  fprintf(fd,"END DO\n",cont);
  int_expr=TRUE;
}


reduced_t *combine_distributed(reduced_t *reduced)

{
  int same;
  reduced_t *old_node,*node,*new_node,*ret;
  dist_t *dist;

    /* create a list of lists.  each list is a group of assigns with the
       same location and bound also separate iota's out */
  old_node=reduced;
  ret=get_reduced();
  new_node=ret;
  new_node->type=NOP;
  while (old_node!=NULL) {
    if (old_node->type==NOP) {
      new_node->d.list=old_node;
      node=old_node;
      dist=find_dist(node->d.frag->ident);
      old_node=old_node->next;
      same=((old_node!=NULL)&&
            (vect_compare(old_node->d.frag->index,node->d.frag->index))&&
            (dist_compare(find_dist(old_node->d.frag->ident),dist)));
      while (same) {
        node->next=old_node;
        node=old_node;
        old_node=old_node->next;
        same=((old_node!=NULL)&&
              (vect_compare(old_node->d.frag->index,node->d.frag->index))&&
              (dist_compare(find_dist(old_node->d.frag->ident),dist)));
      }
      node->next=NULL;
    } else {
      *new_node=*old_node;
      old_node=old_node->next;
    }
    if (old_node!=NULL) {
      new_node->next=get_reduced();
      new_node->type=NOP;
      new_node=new_node->next;
    }
  }
  new_node->next=NULL;

  return(ret);
}


/* dist_lhs - Intersection processing for the left-hand side */

vect_t *dist_lhs(expr_t *expr, expr_t *res, dist_t *l_dist, vect_t *ip, 
                 vect_t *lp, vect_t *bp, vect_t *p2, vect_t *j)

{
  int do_lower;
  vect_t *p,*tmp,*tmp2;
  vect_t *x1,*x2,*y1,*y2;
  vect_t *y1_x1,*y2_x2,*x2_y2;


  ip = expr->index;
  lp = expr->loc; 
  bp = vect_cat(vect_op(TAKE,&one_vec,l_dist->e),
                vect_op(DROP,&one_vec,expr->bound));
  return (NULL);

  /* keep track of the max size of everything for variable declarations */

  if (l_dist->c!=NULL) {                         /* forall j in l_dist->c */
    if (l_dist->c->shp->ident->value>max_c_dim)
      max_c_dim=l_dist->c->shp->ident->value;
    dotab(0);
    fprintf(tfile,"DO i0 = 0, ");
    print_s_expr(tfile,l_dist->c->shp);
    fprintf(tfile,"-1\n");
    dotab(1);
    fprintf(tfile,"j(i0)=0\n");
    dotab(0);
    fprintf(tfile,"END DO\n");
    dotab(0);
    fprintf(tfile,"j_cont=.TRUE.\n");
    dotab(0);
    fprintf(tfile,"DO\n");
    ntab++;
  }
  
  /*
  dotab(0);
  fprintf(tfile,"DO i0 = 0, ");
  print_s_expr(tfile,p2->shp);
  fprintf(tfile,"-1\n");
  dotab(1);
  fprintf(tfile,"p(i0)=0\n");
  dotab(0);
  fprintf(tfile,"END DO\n");
  dotab(0);
  fprintf(tfile,"p_cont=.TRUE.\n");
  dotab(0);
  fprintf(tfile,"DO\n");
  ntab++;
  p=vect_op(PLUS,p2,l_dist->pl);
  /* new junk 
  dotab (0);
  fprintf(tfile,"p(0)=MY_PROC()\n");
  /* end new junk 
  */


  x1=expr->loc;
  x2=vect_op(PLUS,x1,expr->bound);
  if (l_dist->c!=NULL) {
    tmp=vect_op(TIMES,vect_op(TIMES,j,l_dist->g),l_dist->e);
    y1=vect_op(PLUS,vect_op(TIMES,p2,l_dist->e),tmp);
  } else {
    y1=vect_op(TIMES,p2,l_dist->e);
  }    
  y2=vect_op(PLUS,y1,l_dist->e);

  y1_x1=vect_op(MINUS,y1,x1);
  /*
  y2_x2=vect_op(MINUS,y2,x2);
  x2_y2=vect_op(MINUS,x2,y2);
  */

  x1=force_vect(x1);
  x2=force_vect(x2);
  y1=force_vect(y1);
  y2=force_vect(y2);
  y1_x1=force_vect(y1_x1);
  /*
  y2_x2=force_vect(y2_x2);
  x2_y2=force_vect(x2_y2);
  */

  if (para_trace) {
    if (strlen(x1->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"x1:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,x1->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",x1->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"x1:0\"\n");
    }
    if (strlen(x2->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"x2:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,x2->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",x2->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"x2:0\"\n");
    }
    if (strlen(y1->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"y1:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,y1->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",y1->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"y1:0\"\n");
    }
    if (strlen(y2->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"y2:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,y2->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",y2->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"y2:0\"\n");
    }
  }

  /*
  dotab(0);
  fprintf(tfile,"out=.FALSE.\n");
  if (check_zero(x1)) {
    if_bounded(y1,NULL,x2,"tl_in",OUT_RIGHT);
  } else {
    if_bounded(y1,x1,x2,"tl_in",OUT_RIGHT);
    if_bounded(y2,x1,x2,"br_in",OUT_LEFT);
  }

  dotab(0);
  fprintf(tfile,"IF (out) THEN\n");
  ntab++;
  tmp=get_vect();
  *tmp=pad_zero; 
  tmp->shp=ip->shp;
  vect_assign(tmp,ip,"=");
  tmp->shp=lp->shp;
  vect_assign(tmp,lp,"=");
  tmp->shp=bp->shp;
  vect_assign(tmp,bp,"=");
  ntab--;
  dotab(0);

  fprintf(tfile," ELSE\n");
  ntab++;
  */
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y1_x1),y1_x1);
  */
  vect_assign(y1_x1,ip,"=");
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y1_x1),y1_x1);
  tmp=vect_op(PLUS,tmp,x1);
  */
  vect_assign(y1,lp,"=");
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y2_x2),x2_y2);
  */
  tmp=vect_op(MINUS,y2,lp);
  vect_assign(tmp,bp,"=");
  /*
  ntab--;
  dotab(0);
  fprintf(tfile,"END IF\n");
  */

  if (para_trace) {
    fprintf(tfile,"PRINT \"(A)\", \"ip:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,ip->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", ip(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");

    fprintf(tfile,"PRINT \"(A)\", \"lp:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,lp->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", lp(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");

    fprintf(tfile,"PRINT \"(A)\", \"bp:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,bp->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", bp(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
  }

  /*
  my_gamma(tfile,"p_=",p,l_dist->g,l_dist->g->shp);
  */

  return(y1);
}


/* dist_rhs - intersection processing for the right-hand side */

vect_t *dist_rhs(expr_t *expr, dist_t *r_dist, vect_t *ip, vect_t *lp, 
                 vect_t *bp, vect_t *ipp, vect_t *lpp, vect_t *bpp, vect_t *s)

{
  vect_t *tmp,*c,*sp;
  vect_t *sp2,*tmp2,*tmp3;
  vect_t *x1,*x2,*y1,*y2;
  vect_t *y1_x1,*y2_x2,*x2_y2;

  ipp = ip;
  lpp = lp;
  bpp = bp;

  return (NULL);

  dotab(0);
  fprintf(tfile,"s_cont=.TRUE.\n");
  dotab(0);
  fprintf(tfile,"DO i0=0, ");
  print_s_expr(tfile,bp->shp);
  fprintf(tfile,"-1\n");
  dotab(1);
  fprintf(tfile,"s(i0)=0\n");
  dotab(0);
  fprintf(tfile,"END DO\n");
  dotab(0);
  fprintf(tfile,"DO\n");
  ntab++;
  
  c=build_vect("c",ip->shp);
  tmp=vect_op(PLUS,vect_op(DIVIDE,ip,r_dist->e),s);
  tmp2=vect_op(DIVIDE,tmp,r_dist->pb);
  vect_assign(tmp2,c,"=");
  tmp2=vect_op(MOD,tmp,r_dist->pb);
  sp2=build_vect("sp2",tmp2->shp);
  vect_assign(tmp2,sp2,"=");
  sp=vect_op(PLUS,sp2,r_dist->pl);
  sp=purify_vect(sp);

  x1=ip;
  x2=vect_op(PLUS,x1,bp);
  tmp=vect_op(TIMES,vect_op(TIMES,c,r_dist->g),r_dist->e);
  y1=vect_op(PLUS,vect_op(TIMES,sp2,r_dist->e),tmp);
  y2=vect_op(PLUS,y1,r_dist->e);

  y1_x1=vect_op(MINUS,y1,x1);
  y2_x2=vect_op(MINUS,y2,x2);
  x2_y2=vect_op(MINUS,x2,y2);

  x1=force_vect(x1);
  x2=force_vect(x2);
  y1=force_vect(y1);
  y2=force_vect(y2);
  y1_x1=force_vect(y1_x1);
  y2_x2=force_vect(y2_x2);
  x2_y2=force_vect(x2_y2);

  if (para_trace) {
    if (strlen(x1->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"x1:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,x1->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",x1->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"x1:0\"\n");
    }
    if (strlen(x2->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"x2:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,x2->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",x2->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"x2:0\"\n");
    }
    if (strlen(y1->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"y1:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,y1->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",y1->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"y1:0\"\n");
    }
    if (strlen(y2->ident->string)>0) {
      fprintf(tfile,"PRINT \"(A)\", \"y2:<\"\n");
      fprintf(tfile,"DO i0=0, ");
      print_s_expr(tfile,y2->shp);
      fprintf(tfile,"-1\n  PRINT \"(I6)\", INT (%s (i0))\nEND DO",y2->ident->string);
      fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
    } else {
      fprintf(tfile,"PRINT *, \"y2:0\"\n");
    }
  }

  /*
  dotab(0);
  fprintf(tfile,"out=.FALSE.\n");
  if_bounded(y1,x1,x2,"tl_in",OUT_RIGHT);
  if_bounded(y2,x1,x2,"br_in",OUT_LEFT);
  */

  /*
  dotab(0);
  fprintf(tfile,"IF (out) THEN\n");
  ntab++;
  tmp=get_vect();
  *tmp=pad_zero; 
  tmp->shp=ip->shp;
  vect_assign(tmp,ipp,"=");
  tmp->shp=lp->shp;
  vect_assign(tmp,lpp,"=");
  tmp->shp=bp->shp;
  vect_assign(tmp,bpp,"=");
  ntab--;
  dotab(0);

  fprintf(tfile,"ELSE\n");
  ntab++;
  */
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y1_x1),y1_x1);
  tmp=vect_op(PLUS,tmp,x1);
  */
  vect_assign(y1,ipp,"=");
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y1_x1),y1_x1);
  */
  tmp=vect_op(PLUS,tmp,lp);
  vect_assign(tmp,lpp,"=");
  /*
  tmp=vect_op(TIMES,vect_unop(IF_POS,y2_x2),x2_y2);
  */
  tmp=vect_op(MINUS,vect_op(PLUS,tmp,y2),ipp);
  vect_assign(tmp,bpp,"=");
  /*
  ntab--;
  dotab(0);
  fprintf(tfile,"END IF\n");
  */

  if (para_trace) {
    fprintf(tfile,"PRINT \"(A)\", \"ipp:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,ipp->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", ipp(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");

    fprintf(tfile,"PRINT \"(A)\", \"lpp:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,lpp->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", lpp(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");

    fprintf(tfile,"PRINT \"(A)\", \"bpp:<\"\n");
    fprintf(tfile,"DO i0=0, ");
    print_s_expr(tfile,bpp->shp);
    fprintf(tfile,"-1\n  PRINT \"(I6)\", bpp(i0)\nEND DO");
    fprintf(tfile,"PRINT \"(A,/)\", \">\"\n");
  }

  my_gamma(tfile,"sp_=",sp,r_dist->g,r_dist->g->shp);

  return(y1);
}


/* dist_assign - list is a list of expressions that have the same distribution,
     location, and index. */

dist_assign(reduced_t *list, vect_t *loc_adj, vect_t *ip, vect_t *lp,
            vect_t *bp, dist_t *l_dist, expr_t *res)

{
  reduced_t *node,*global;
  int i,flag;
  expr_t *expr,*local;
  dist_t *r_dist,*dist;
  expr_t *send,*recv,*assign;
  vect_t *s,*tmp;
  vect_t *s_bound;
  vect_t *ipp,*lpp,*bpp;
  vect_t *index_adj;

  expr=list->d.frag;  /* since the list is essentially identical we can pick
                         anyone to use for all calculations. */

  /*
  ip=vect_op(PLUS,ip,expr->index);
  */

  r_dist=find_dist(expr->ident);

  if (r_dist!=NULL) {
    /*
    r_dist->e=force_vect(r_dist->e);
    ipp=build_vect("ipp",expr->index->shp);
    lpp=build_vect("lpp",expr->loc->shp);
    bpp=build_vect("bpp",expr->bound->shp);
    s=build_vect("s",bp->shp);
    tmp=vect_op(TIMES,vect_op(DIVIDE,ip,r_dist->e),r_dist->e);
    tmp=vect_op(MINUS,vect_op(PLUS,ip,bp),tmp);
    s_bound=vect_op(PLUS,vect_op(DIVIDE,tmp,r_dist->e),
                    vect_unop(IF_POS,vect_op(MOD,tmp,r_dist->e)));
    s_bound=force_vect(s_bound);
    index_adj=dist_rhs(expr,r_dist,ip,lp,bp,ipp,lpp,bpp,s);
    */
    /* new junk */
    index_adj = NULL;
    ipp = ip;
    lpp = lp;
    bpp = bp;
    /* end new junk */
  } else {
    index_adj=NULL;
    ipp=vect_op(PLUS,ip,expr->index);
    lpp=lp;
    bpp=bp;
  }

  if (loc_adj!=NULL) lpp=purify_vect(vect_op(MINUS,lpp,loc_adj));
  if (index_adj!=NULL) ipp=purify_vect(vect_op(MINUS,ipp,index_adj));

  if (para_trace) {
    fprintf(tfile,"PRINT *, \"p=\", p_\n");
    fprintf(tfile,"PRINT *, \"sp=\", sp_\n");
  }

  res->bound=bpp; /* set the proper bound on the result */

  /*
  flag=0;
  if (l_dist!=NULL) flag+=1;
  if (r_dist!=NULL) flag+=2;

  switch (flag) {
  case 3:
    dotab(0);
    fprintf(tfile,"IF ((MY_PROC()==p_) .AND. (MY_PROC()==sp_)) THEN\n");
    ntab++;
    break;
  case 1:
    dotab(0);
    fprintf(tfile,"IF (MY_PROC()==p_) THEN\n");
    ntab++;
    break;
  case 2:
    dotab(0);
    fprintf(tfile,"IF (MY_PROC()==sp_) THEN\n");
    ntab++;
    break;
  }
  dotab(0);
  fprintf(tfile,"IF (mode==1) THEN\n");
  ntab++;
  */

  global=node=copy_list(list);
  while (node!=NULL) {
    assign=node->d.frag=copy_expr(node->d.frag);
    assign->loc=lpp;
    assign->index=ipp;
    assign->bound=bpp;
    dist=find_dist(assign->ident);
      if (dist!=NULL)
        /* set the shape of the local partition of the array */
        assign->shp=dist->e;
    node=node->next;

  }
  global_assign(global,res);
 
  /* 
  ntab--;
  dotab(0);
  fprintf(tfile,"END IF\n");

  if (flag!=0) ntab--;

  if ((flag&2)!=0) {
    dotab(0);
    if (flag==3)
      fprintf(tfile,"ELSE IF (MY_PROC()==p_) THEN\n");
    else
      fprintf(tfile,"ELSE\n");

    ntab++;

    dotab(0);
    fprintf(tfile,"IF (mode==0) THEN\n");
    ntab++;
    i=0;
    global=node=copy_list(list);
    while (node!=NULL) {
      recv=copy_expr(&buffer);
      recv->dim=res->dim;
      recv->loc=lpp;
      recv->index=get_vect();
      *recv->index=pad_zero;
      recv->index->shp=res->dim;
      recv->bound=recv->shp=bpp;
      recv->func=node->d.frag->func;
      recv->left=res;
      node->d.frag=recv;

      dotab(0);
      fprintf(tfile,"ALLOCATE (buffer%dr(sp_)%%store(0:",i);
      tau(tfile,recv);
      fprintf(tfile,"-1))\n");

      dotab(0);
      fprintf(tfile,"call RECV(buffer%dr(sp_)%%store,",i);
      tau(tfile,recv);
      fprintf(tfile,",sp_)\n");
      sprintf(recv->ident->string,"buffer%dr(sp_)%%store",i);
      i++;
      node=node->next;
    }
    if (i>max_buffer_no)
      max_buffer_no=i;

    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");

    dotab(0);
    fprintf(tfile,"IF (mode==1) THEN\n");
    ntab++;
    global_assign(global,res);
    for (i=i-1; i>=0; i--) {
      dotab(0);
      fprintf(tfile,"DEALLOCATE(buffer%dr(sp_)%%store)\n",i);
    }
    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");
    
    ntab--;
    
    dotab(0);
    if (flag==3)
      fprintf(tfile,"ELSE IF (MY_PROC()==sp_) THEN\n");
    else {
      fprintf(tfile,"END IF\n");
      dotab(0);
      fprintf(tfile,"IF (MY_PROC()==sp_) THEN\n");
    }

    ntab++;

    dotab(0);
    fprintf(tfile,"IF (mode==0) THEN\n");
    ntab++;
    i=0;
    node=list;
    while (node!=NULL) {
      expr=node->d.frag;
      assign=copy_expr(expr);
      assign->loc=get_vect();
      *assign->loc=pad_zero;
      assign->loc->shp=res->dim;
      assign->index=ipp;
      assign->bound=bpp;
      dist=find_dist(assign->ident);
      if (dist!=NULL)
        /* set the shape of the local partition of the array 
        assign->shp=dist->e;
      assign->func="=";
      send=copy_expr(&buffer);
      send->dim=assign->dim;
      send->bound=send->shp=bpp;
      sprintf(send->ident->string,"buffer%ds(sp_)%%store",i);

      dotab(0);
      fprintf(tfile,"ALLOCATE (buffer%ds(sp_)%%store(0:",i);
      tau(tfile,send);
      fprintf(tfile,"-1))\n");

      do_assign(assign,send);
      i++;
      node=node->next;
    }
    if (i>max_buffer_no)
      max_buffer_no=i;
    
    if (flag==2) {
      dotab(0);
      fprintf(tfile,"DO i0=0, %d\n",n_procs-1);
      ntab++;
      dotab(0);
/* this line 
      fprintf(tfile,"IF (i0 /= MY_PROC ()) THEN\n");
/* use to be
      fprintf(tfile,"IF (i0/=mp) THEN\n");
   and I'm assuming mp is supposed to be MY_PROC () 
      ntab++;
      dotab(0);
    } else dotab(0);

    node=list;
    i=0;
    while (node!=NULL) {
      fprintf(tfile,"call SEND(buffer%ds(sp_)%%store,",i);
      tau(tfile,send);
      if (flag==3)
        fprintf(tfile,",p_)\n");
      else
        fprintf(tfile,",i0)\n");      

      i++;
      node=node->next;
      if (node!=NULL) dotab(0);
    }
    if (i>max_buffer_no)
      max_buffer_no=i;

    if (flag==2) {
      ntab--;
      dotab(0);
      fprintf(tfile,"END IF\n");
      ntab--;
      dotab(0);
      fprintf(tfile,"END DO\n");
    }

    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");

    dotab(0);
    fprintf(tfile,"IF (mode==1) THEN\n");
    ntab++;
    for (i=i-1; i>=0; i--) {
      dotab(0);
      fprintf(tfile,"DEALLOCATE(buffer%ds(sp_)%%store)\n",i);
    }

    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");

    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");
  } else {
    if (flag==1) {
      dotab(0);
      fprintf(tfile,"END IF\n");
    }
  }
  
  if (r_dist!=NULL) {
    s_bound=purify_vect(s_bound);
    close_while(tfile,s,s_bound,"s_cont");
    ntab--;
  }
  */
}


/* code_dist - generate code for a single distributed assignment */


code_dist(reduced_t *list, expr_t *res, dist_t *l_dist)

{
  int scalar_num_save;
  reduced_t *node,dumb_list;
  expr_t *expr;
  vect_t *j,*p2;
  vect_t *ip,*lp,*bp;
  vect_t *loc_adj;

  /*
  if (l_dist!=NULL) {
    l_dist->e=force_vect(l_dist->e);
    res=copy_expr(res);
    res->shp=l_dist->e; /* set the shape of the local partition of the array 
  }
  */

  dumb_list.next=NULL;

  node=list;
  while (node!=NULL) {
    /* any scalars used during the assign can be reused */
    scalar_num_save=scalar_num;

    /*
    dotab(0);
    fprintf(tfile,"DO mode=0, 1\n");
    ntab++;
    
    if (para_trace)
      fprintf(tfile,"PRINT *, \"mode=\", mode\n");
    */

    
    expr=node->d.frag;

    if (max_dim<1) max_dim=1;
    if (res->dim->ident->value>max_l_dim)
      max_l_dim=res->dim->ident->value;
  
    if (l_dist!=NULL) {
      if (l_dist->pl->shp->ident->value>max_p_dim)
        max_p_dim=l_dist->pl->shp->ident->value;
      /*
      ip=build_vect("ip",expr->index->shp);
      lp=build_vect("lp",expr->loc->shp);
      bp=build_vect("bp",expr->bound->shp);
      p2=build_vect("p",l_dist->pl->shp);
      if (l_dist->c!=NULL) j=build_vect("j",l_dist->c->shp);
      loc_adj=dist_lhs(expr,res,l_dist,ip,lp,bp,p2,j);
      */
      /* new junk */
      loc_adj=NULL;
      ip=expr->index;
      lp=expr->loc;
      bp = vect_cat(vect_take(&one_vec,l_dist->e),
                    vect_drop(&one_vec,expr->bound));
      /* end new junk */
    } else {
      loc_adj=NULL;
      ip=expr->index;
      lp=expr->loc;
      bp=expr->bound;
    }
    
    dumb_list.d.frag=node->d.frag;
    dist_assign(&dumb_list,loc_adj,ip,lp,bp,l_dist,res);

    /*
    if (l_dist!=NULL) {
      close_while(tfile,p2,l_dist->pb,"p_cont");
      ntab--;
      
      if (l_dist->c!=NULL) {
        close_while(tfile,j,l_dist->c,"j_cont");
        ntab--;
      }
    }
    */

    /*
    dotab(0);
    fprintf(tfile,"IF (mode==0) call WAIT ()\n");

    ntab--;
    dotab(0);
    fprintf(tfile,"END DO\n\n");
    */

    node=node->next;

    /* any scalars used during the assign can be reused */
    scalar_num=scalar_num_save;
  }
}


/* code_global_int - generates communication code for replicating an integer
     on all the processors. */

code_global_int(ident_t *ident)

/*                        question                */
{
  if (1>max_dim) max_dim=1;

  if (host) {
    dotabf(hfile,0);
    fprintf(hfile,"DO i0=0, %d\n!    Send global integer \n",n_procs-1);
    dotabf(hfile,1);
    if (ident->type==VARIABLE)
      fprintf(hfile,"call HOST_SEND(%s,1,i0)\n",ident->string);
    else
      fprintf(hfile,"call HOST_SEND(%s,1,i0)\n",ident->string);
    dotabf(hfile,0);
    fprintf(hfile,"END DO\n");
    dotab(0);
    if (ident->type==VARIABLE)
      fprintf(tfile,"call RECV_HOST(%s,1)\n",ident->string);
    else {
      fprintf(tfile,"ALLOCATE (%s(0:0))\n",ident->string);
      dotab(0);
      fprintf(tfile,"call RECV_HOST(%s,1)\n",ident->string);
    }
  } else {
    dotab(0);
    fprintf(tfile,"IF (MY_PROC()==0) THEN\n");
    dotab(1);
    fprintf(tfile,"!  Send global integer \n");
    dotab(1);
    fprintf(tfile,"DO i0=1, %d\n",n_procs-1);
    dotab(2);
    if (ident->type==VARIABLE)
      fprintf(tfile,"call SEND(%s,1,i0)\n",ident->string);
    else
      fprintf(tfile,"call SEND(%s,1,i0)\n",ident->string);
    dotab(1);
    fprintf(tfile,"END DO\n");
    dotab(0);
    fprintf(tfile,"ELSE\n");
    dotab(1);
    if (ident->type==VARIABLE)
      fprintf(tfile,"call RECV(%s,1,0)\n",ident->string);
    else
      fprintf(tfile,"call RECV(%s,1,0)\n",ident->string);
    dotab(0);
    fprintf(tfile,"END IF\n");
  }
  
  fprintf(tfile,"\n");
}
/*                        question                */

/* collect_array - generates communication code to collect distributed 
     arrays. */

collect_array(dist_t *dist)
{
  int dim,i;
  vect_t *p,*s;

  if (max_dim<3) max_dim=3;
  p=build_vect("p",dist->g->shp);

  dim=dist->ident->array.dim->value;

  if (host) {
    dotabf(hfile,0);
    fprintf(hfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(hfile,"*");
      print_rav(hfile,dist->e,i);
    }
    fprintf(hfile,"\n");
    dotabf(hfile,0);
    fprintf(hfile,"i0=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(hfile,"*");
      print_ident(hfile,dist->ident->array.shp[i]);
    }
    fprintf(hfile,"\n");
    dotabf(hfile,0);
    fprintf(hfile,"DO i2=0, %d\n",dim-1);
    dotabf(hfile,1);
    fprintf(hfile,"p(i2)=0\n");
    dotabf(hfile,0);
    fprintf(hfile,"END DO\n");
    dotabf(hfile,0);
    fprintf(hfile,"p(0)=1\n");
    dotab(0);
    fprintf(tfile,"p_cont=.TRUE.\n");
    dotabf(hfile,0);
    fprintf(hfile,"DO\n");
    ntabf++;
    s=purify_vect(vect_op(PLUS,p,dist->pl));
    my_gamma(hfile,"p_=",s,dist->g,dist->g->shp);
    s=purify_vect(vect_op(TIMES,p,dist->e));
    my_gamma(hfile,"offset=",s,dist->shp,dist->shp->shp);
    /*
    dotabf(hfile,0);
    fprintf(hfile,"IF (i1<(i0-offset)) THEN\n");
    dotabf(hfile,1);
    fprintf(hfile,"i2=i1\n");
    dotabf(hfile,0);
    fprintf(hfile,"ELSE\n");
    dotabf(hfile,1);
    fprintf(hfile,"i2=(i0-offset)\n");
    dotabf(hfile,0);
    fprintf(hfile,"END IF\n");
    */
    dotabf(hfile,0);
    fprintf(hfile,"call HOST_RECV(%s(offset:offset+i1-1),i2,p_)\n",
            dist->ident->string);
    close_while(hfile,p,dist->pb,"p_cont");
    ntabf--;
    
    dotab(0);
    fprintf(tfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_rav(tfile,dist->e,i);
    }
    fprintf(tfile,"\n");
    if (dist->g==dist->pb) {
      dotab(0);
      fprintf(tfile,"call SEND_HOST(%s,i1)\n",dist->ident->string);
    } else {
      inv_gamma("proc",dist->g,"p");
      if (check_zero(dist->pl)) if_bounded(p,dist->pl,dist->pb,"in",NO_OUT);
      else if_bounded(p,NULL,dist->pb,"in",NO_OUT);
      dotab(0);
      fprintf(tfile,"IF (in /= 0) call SEND_HOST(%s,i1)\n",
              dist->ident->string);
    }
    fprintf (hostfile,"  call HOST_CLEANUP()\n");
  } else {
    dotab(0);
    fprintf(tfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_rav(tfile,dist->e,i);
    }
    fprintf(tfile,"\n");
    dotab(0);
    fprintf(tfile,"IF (MY_PROC()==0) THEN\n");
    ntab++;
    dotab(0);
    fprintf(tfile,"i0=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_ident(tfile,dist->ident->array.shp[i]);
    }
    fprintf(tfile,"\n");
    dotab(0);
    fprintf(tfile,"DO i2=0, %d\n",dim-1);
    dotab(1);
    fprintf(tfile,"p(i2)=0\n");
    dotab(0);
    fprintf(tfile,"END DO\n");
    dotab(0);
    fprintf(tfile,"p(0)=1\n");
    dotab(0);
    fprintf(tfile,"p_cont=.TRUE.\n");
    dotab(0);
    fprintf(tfile,"DO\n");
    ntab++;
    s=purify_vect(vect_op(PLUS,p,dist->pl));
    my_gamma(tfile,"p_=",s,dist->g,dist->g->shp);
    s=purify_vect(vect_op(TIMES,p,dist->e));
    my_gamma(tfile,"offset=",s,dist->shp,dist->shp->shp);
    /*
    dotab(0);
    fprintf(tfile,"IF (i1<(i0-offset)) THEN\n");
    dotab(1);
    fprintf(tfile,"i2=i1\n");
    dotab(0);
    fprintf(tfile,"ELSE\n");
    dotab(1);
    fprintf(tfile,"i2=(i0-offset)\n");
    dotab(0);
    fprintf(tfile,"END IF\n");
    */
    dotab(0);
    fprintf(tfile,"call RECV(%s(offset:offset+i1-1),i2,p_)\n",
            dist->ident->string);
    close_while(tfile,p,dist->pb,"p_cont");
    ntab--;
    
    ntab--;
    dotab(0);
    fprintf(tfile,"ELSE\n");
    ntab++;
    if (dist->g==dist->pb) {
      dotab(0);
      fprintf(tfile,"call SEND(%s,i1,0)\n",dist->ident->string);
    } else {
      inv_gamma("proc",dist->g,"p");
      if (check_zero(dist->pl)) if_bounded(p,dist->pl,dist->pb,"in",NO_OUT);
      else if_bounded(p,NULL,dist->pb,"in",NO_OUT);
      dotab(0);
      fprintf(tfile,"!IF (in /= 0) call SEND(%s,i1,0)\n",
              dist->ident->string);
    }
    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");
  }
  if (n_procs > 1) fprintf (tfile,"  call NODE_CLEANUP()\n");
}


/* dist_array - generates communication code to initialize distributed 
     arrays. */

dist_array(dist_t *dist)

{
  int dim,i;
  vect_t *p,*s;

  if (max_dim<3) max_dim=3;
  p=build_vect("p",dist->g->shp);

  dim=dist->ident->array.dim->value;

  if (host) {
    dotabf(hfile,0);
    fprintf(hfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(hfile,"*");
      print_rav(hfile,dist->e,i);
    }
    fprintf(hfile,"\n");
    dotabf(hfile,0);
    fprintf(hfile,"i0=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(hfile,"*");
      print_ident(hfile,dist->ident->array.shp[i]);
    }
    fprintf(hfile,"\n");
    dotabf(hfile,0);
    fprintf(hfile,"DO i2=0, %d\n",dim-1);
    dotabf(hfile,1);
    fprintf(hfile,"p(i2)=0\n");
    dotabf(hfile,0);
    fprintf(hfile,"END DO\n");
    dotabf(hfile,0);
    fprintf(hfile,"p(0)=1\n");
    dotab(0);
    fprintf(tfile,"p_cont=.TRUE.\n");
    dotabf(hfile,0);
    fprintf(hfile,"DO\n");
    ntabf++;
    s=purify_vect(vect_op(PLUS,p,dist->pl));
    my_gamma(hfile,"p_=",s,dist->g,dist->g->shp);
    s=purify_vect(vect_op(TIMES,p,dist->e));
    my_gamma(hfile,"offset=",s,dist->shp,dist->shp->shp);
    /*
    dotabf(hfile,0);
    fprintf(hfile,"IF (i1<(i0-offset)) THEN\n");
    dotabf(hfile,1);
    fprintf(hfile,"i2=i1\n");
    dotabf(hfile,0);
    fprintf(hfile,"ELSE\n");
    dotabf(hfile,1);
    fprintf(hfile,"i2=(i0-offset)\n");
    dotabf(hfile,0);
    fprintf(hfile,"END IF\n");
    */
    dotabf(hfile,0);
    fprintf(hfile,"call HOST_SEND(%s(offset:offset+i1-1),i2,p_)\n",
            dist->ident->string);
    close_while(hfile,p,dist->pb,"p_cont");
    ntabf--;
    
    dotab(0);
    fprintf(tfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_rav(tfile,dist->e,i);
    }
    fprintf(tfile,"\n");
    if (dist->g==dist->pb) {
      dotab(0);
      fprintf(tfile,"call RECV_HOST(%s,i1)\n",dist->ident->string);
    } else {
      inv_gamma("proc",dist->g,"p");
      if (check_zero(dist->pl)) if_bounded(p,dist->pl,dist->pb,"in",NO_OUT);
      else if_bounded(p,NULL,dist->pb,"in",NO_OUT);
      dotab(0);
      fprintf(tfile,"IF (in /= 0) call RECV_HOST(%s,i1)\n",
              dist->ident->string);
    }
  } else {
    dotab(0);
    fprintf(tfile,"i1=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_rav(tfile,dist->e,i);
    }
    fprintf(tfile,"\n");
    dotab(0);
    fprintf(tfile,"IF (MY_PROC()==0) THEN\n");
    ntab++;
    dotab(0);
    fprintf(tfile,"i0=");
    for (i=0; i<dim; i++) {
      if (i>0) fprintf(tfile,"*");
      print_ident(tfile,dist->ident->array.shp[i]);
    }
    fprintf(tfile,"\n");
    dotab(0);
    fprintf(tfile,"DO i2=0, %d\n",dim-1);
    dotab(1);
    fprintf(tfile,"p(i2)=0\n");
    dotab(0);
    fprintf(tfile,"END DO\n");
    dotab(0);
    fprintf(tfile,"p(0)=1\n");
    dotab(0);
    fprintf(tfile,"p_cont=.TRUE.\n");
    dotab(0);
    fprintf(tfile,"DO\n");
    ntab++;
    s=purify_vect(vect_op(PLUS,p,dist->pl));
    my_gamma(tfile,"p_=",s,dist->g,dist->g->shp);
    s=purify_vect(vect_op(TIMES,p,dist->e));
    my_gamma(tfile,"offset=",s,dist->shp,dist->shp->shp);
    /*
    dotab(0);
    fprintf(tfile,"IF (i1<(i0-offset)) THEN\n");
    dotab(1);
    fprintf(tfile,"i2=i1\n");
    dotab(0);
    fprintf(tfile,"ELSE\n");
    dotab(1);
    fprintf(tfile,"i2=(i0-offset)\n");
    dotab(0);
    fprintf(tfile,"END IF\n");
    */
    dotab(0);
    fprintf(tfile,"call SEND(%s(offset:offset+i1-1),i2,p_)\n",
            dist->ident->string);
    close_while(tfile,p,dist->pb,"p_cont");
    ntab--;
    
    ntab--;
    dotab(0);
    fprintf(tfile,"ELSE\n");
    ntab++;
    if (dist->g==dist->pb) {
      dotab(0);
      fprintf(tfile,"call RECV(DIST_%s,i1,0)\n",dist->ident->string);
      dotab(0);
      fprintf(tfile,"%s => DIST_%s\n",dist->ident->string,dist->ident->string);
    } else {
      inv_gamma("proc",dist->g,"p");
      if (check_zero(dist->pl)) if_bounded(p,dist->pl,dist->pb,"in",NO_OUT);
      else if_bounded(p,NULL,dist->pb,"in",NO_OUT);
      dotab(0);
      fprintf(tfile,"!IF (in /= 0) call RECV(%s,i1,0)\n",
              dist->ident->string);
    }
    ntab--;
    dotab(0);
    fprintf(tfile,"END IF\n");
  }
}


/* init_collect_arrays */

void init_collect_arrays (dist_t *dist)
{
  if (n_procs>1) {
    dotab(0);
    if (host) fprintf(hfile,"\n!  Communications for Collecting Data\n\n");
    fprintf(tfile,"!  Communications for Collecting Data\n\n");
    while (dist!=NULL) {
      if (ISPARAMETER(dist->ident->flags)) {
        collect_array(dist);
      }
      dist=dist->next;
    }
  }
}

/* init_dist_arrays - allocates space on each processor for distibuted 
     arrays and calls dist_array.  */

init_dist_arrays(dist_t *dist)
{
  int i;

  distribution=dist;

  if (n_procs>1) {
    dotab(0);
    if (host) fprintf(hfile,"\n!  Communications for Initial Data\n\n");
    fprintf(tfile,"!  Communications for Initial Data\n\n");
    while (dist!=NULL) {
      if (!ISUSED(dist->ident->flags)) {
        /* allocate the appropriate amount of memory */
        
        if (!ISPARAMETER(dist->ident->flags))
          fprintf(vfile,"  REAL, DIMENSION (:), ALLOCATABLE :: %s\n",
              dist->ident->string);
        dotab(0);
        if (!host) {
          fprintf(tfile,"IF (MY_PROC()>0)");
          dotab(1);
        }
        fprintf (vfile, "  REAL, DIMENSION (:), POINTER :: %s\n",
          dist->ident->string); 
        fprintf (vfile, "  REAL, DIMENSION (:), ALLOCATABLE, TARGET :: DIST_%s\n",
          dist->ident->string); 
        fprintf(tfile,"ALLOCATE (DIST_%s(0:",dist->ident->string);
        if (dist->e->shp->ident->value>0) {
          for (i=0; i<dist->e->shp->ident->value; i++) {
            if (i>0) fprintf(tfile,"*");
            print_rav(tfile,dist->e,i);
          }
        } else fprintf(tfile,"1");
        fprintf(tfile,"-1))\n");
      }
      /* code communications for initial data from host (or node 0) */
      if (ISPARAMETER(dist->ident->flags)) {
        dist_array(dist);
      }
      
      dist=dist->next;
    }
    fprintf(tfile,"\n");
    dotab(0);
    fprintf(tfile,"! Procedure body\n\n");
  }
}


allocate_utils()

{
  int i;

  fprintf(vfile,"  INTEGER :: p_,offset\n");
  fprintf(vfile,"  LOGICAL :: p_cont\n");
  /*
  fprintf(vfile,"  LOGICAL :: j_cont,p_cont,s_cont,out\n");
  fprintf(vfile,"  INTEGER :: p_,sp_,mode,offset\n");
  */
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: p\n",max_dim-1);
  /*
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: c\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: s\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: sp2\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: ip\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: lp\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: bp\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: ipp\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: lpp\n",max_dim-1);
  fprintf(vfile,"  INTEGER, DIMENSION (0:%d) :: bpp\n",max_dim-1);
  fprintf(vfile,"  TYPE BUF\n");
  fprintf(vfile,"    REAL, DIMENSION (:), POINTER :: store\n");
  fprintf(vfile,"  END TYPE BUF\n");
  for (i=0; i<max_buffer_no; i++) {
    fprintf(vfile,"  TYPE(BUF), DIMENSION (0:%d) :: buffer%dr, buffer%ds\n",
      n_procs-1,i,i);
  }
  */
  if (host) {
    fprintf(hostfile,"  INTEGER :: p_,p_cont\n");
    fprintf(hostfile,"  INTEGER, DIMENSION (0:%d) :: p\n",max_dim-1);
    fprintf(hostfile,"  INTEGER :: shift,offset\n");
  }
}


/* dist_init - initialization for the dist.c module */

dist_init()

{
  max_buffer_no=0;
  buffer.ident=get_ident();
  sprintf(buffer.ident->string,"buffer");
  buffer.ident->type=ARRAY;
  pad_one.loc=&s_const0;
  pad_one.index=&s_const0;
  pad_one.shp=&s_const1;
  pad_one.ident=&const1;
  pad_zero.loc=&s_const0;
  pad_zero.index=&s_const0;
  pad_zero.shp=&s_const1;
  pad_zero.ident=&const0;
}
