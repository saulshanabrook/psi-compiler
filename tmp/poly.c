/*
  This code was not developed under the PSI Compiler.  The University of
Missouri-Rolla is granted the right to include it in the PSI compiler by the
author.

Copyright (c) 1993 Scott Thibault
All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE DEVELOPER ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE DEVELOPER BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

  poly.c - Routines for performing operations on symbolic polynomials.

  4/93	- Scott Thibault
  10/93 - Bart Fitzgerald
	    Minor type declarsions.
	     * void - functions that have no return value.
	     * typed float constants
	    Commented out - #include "sum_polys.e"
  11/93 - Bart Fitzgerald
            proceedure new_poly - support for d = 0    
  11/93 - Scott Thibault
            Changed new_poly to support d==0 by making it one.  This avoids
	    having special cases in all the other routines.
  1/94 -  Scott Thibault
            All routines changed to deal with NULL (poly_t *) inputs by
	    assuming they are the identity.
*/

#include <stdio.h>
#include <string.h>
#include "psi.h"
#include "sys.h"
#include "poly.h"

#include "poly.e"
#include "sys.e"
   /* uses get_mem and free_mem */


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

int poly_talk=FALSE;


/* new_poly - allocate a new polynomial of d symbolic variables.  d is
	the dimension of the array representation. */

poly_t *new_poly(int d)

{
  poly_t *ret;

  ret=(poly_t *) get_mem(sizeof(poly_t));
  ret->d=(d==0) ? 1 : d;
  ret->shp=(int *) get_mem(ret->d*sizeof(int));

  return(ret);
}


/* free_poly - deallocate a polynomial */

void free_poly(poly_t *p)

{
  if (p==NULL)
    return;

  if (p->shp!=NULL) free_mem(p->shp);
  if (p->rav!=NULL) free_mem(p->rav);
  free_mem(p);
  p = NULL;
}


poly_t *poly_copy(poly_t *p)

{
  int i,tau;
  poly_t *ret;

  ret=new_poly(p->d);

  tau=1;
  for (i=0; i<p->d; i++)
    tau*=p->shp[i];

  ret->rav=(double *) get_mem(tau*sizeof(double));

  ret->d=p->d;
  memcpy(ret->shp,p->shp,p->d*sizeof(int));
  memcpy(ret->rav,p->rav,tau*sizeof(double));

  return(ret);
}
	   
  


/* poly_add - add to polygons and return the result in a new polynomial */

poly_t *poly_add(poly_t *left, poly_t *right)

{
  int c;
  poly_t *ret;
  int *vec,tau,g1,g2,g3,in1,in2,i;
  
  if (left==NULL)
    return(poly_copy(right));
  else if (right==NULL)
    return(poly_copy(left));

  ret=new_poly(left->d);
  vec=(int *) get_mem(left->d*sizeof(int));

  tau=1;
  for (i=0; i<left->d; i++) {
    ret->shp[i]=(left->shp[i]>right->shp[i]) ? left->shp[i] : right->shp[i];
    tau*=ret->shp[i];
    vec[i]=0;
  }
  ret->rav=(double *) get_mem(tau*sizeof(double));

  g1=g2=g3=0;
  c=FALSE;
  while (!c) {
    in1=TRUE;
    in2=TRUE;
    for (i=0; i<left->d; i++) {
      if (vec[i]>=left->shp[i]) in1=FALSE;
      if (vec[i]>=right->shp[i]) in2=FALSE;
    }
    ret->rav[g3]=0;
    if (in1) {
      ret->rav[g3]+=left->rav[g1];
      g1++;
    }
    if (in2) {
      ret->rav[g3]+=right->rav[g2];
      g2++;
    }
    g3++;

    i=0;
    do {
      vec[i]++;
      c=(vec[i]==ret->shp[i]);
      if (c) vec[i]=0;
      i++;
    } while (c&&(i<left->d));
  }

  if (poly_talk) {
    printf(" ");
    poly_print(left);
    printf("+");
    poly_print(right);
    printf("=");
    poly_print(ret);
  }

  free_mem(vec);
  return(ret);
}


/* poly_times - multiply to polynomials and return the result as a new 
	polynomial */

poly_t *poly_times(poly_t *p1, poly_t *p2)

{
  int c;
  poly_t *tmp,*tmp2,*ret;
  int *vec,i,g1;

  if (p1==NULL)
    return(poly_copy(p2));
  else if (p2==NULL)
    return(poly_copy(p1));

  vec=(int *) get_mem(p1->d*sizeof(int));
  ret=new_poly(p1->d);
  for (i=0; i<p1->d; i++) {
    vec[i]=0;
    ret->shp[i]=0;
  }
  ret->rav=NULL;

  g1=0;
  c=FALSE;
  while (!c) {
    tmp=poly_scale(p1->rav[g1],vec,p2);
    tmp2=poly_add(ret,tmp);
    free_poly(tmp);  /* this order of freeing helps mem management */
    free_poly(ret);
    ret=tmp2;
    g1++;

    i=0;
    do {
      vec[i]++;
      c=(vec[i]==p1->shp[i]);
      if (c) vec[i]=0;
      i++;
    } while (c&&(i<p1->d));

  }
  

  if (poly_talk) {
    printf(" ");
    poly_print(p1);
    printf("*");
    poly_print(p2);
    printf("=");
    poly_print(ret);
  }

  free_mem(vec);
  return(ret);
}


/* poly_scale - Scales the input by k times the variable product represented
     by j.  For example, if k=2 and j=[1 1] then 2*x0*x1*p(x0,x1) is returned.
*/

poly_t *poly_scale(double k, int *j, poly_t *p)

{
  poly_t *ret;
  int *vec,tau,tau2,prod,i,g1,g2,c;

  ret=new_poly(p->d);
  tau=1;
  tau2=1;
  vec=(int *) get_mem(p->d*sizeof(int));
  for (i=0; i<p->d; i++) {
    vec[i]=j[i];
    ret->shp[i]=p->shp[i]+j[i];
    tau*=ret->shp[i];
    tau2*=p->shp[i];
  }

  ret->rav=(double *) get_mem(tau*sizeof(double));
  for (i=0; i<tau; i++) ret->rav[i]=0;

  c=FALSE;
  while (!c) {
    prod=tau2;
    g2=0;
    for (i=0; i<p->d; i++) {
      prod/=p->shp[i];
      g2+=(vec[i]-j[i])*prod;
    }
    prod=tau;
    g1=0;
    for (i=0; i<p->d; i++) {
      prod/=ret->shp[i];
      g1+=vec[i]*prod;
    }

    ret->rav[g1]=k*p->rav[g2];
    
    i=p->d;
    do {
      i--;
      vec[i]++;
      c=(vec[i]==ret->shp[i]);
      if (c) vec[i]=j[i];
    } while (c&&(i>0));
  }

  if (poly_talk&&(k>0)) {
    printf("%g",k);
    for (i=0; i<p->d; i++) 
      if (vec[i]>0)
	printf("(x%d^%d)",i,vec[i]);
    printf("\n*");
    poly_print(p);
    printf("=");
    poly_print(ret);
  }

  free_mem(vec);
  return(ret);
}


/* poly_expand - this is used to create a new polynomial.  d is the
	number of symbolic variables.  The newly created polynomial will
	initialized to a polynomial of one variable.  var specifies which
	of the d variables is the variable in this polynomial of one 
	variable.  terms is the degree of the one variable polynomial and
	p is a pointer to the coeficients of the one variable polynomial. */

poly_t *poly_expand(int terms, double *p, int var, int d)

{
  poly_t *ret;
  int i;

  ret=new_poly(d);
  for (i=0; i<ret->d; i++) ret->shp[i]=1;
  ret->shp[var]=terms;
  ret->rav=(double *) get_mem(terms*sizeof(double));
  for (i=0; i<terms; i++) ret->rav[i]=p[i];

  return(ret);
}


/* poly_constant - This is used to create a new polynomial that is just
     the constant 0 with d variables. */

poly_t *poly_constant(double c, int d)

{
  poly_t *ret;
  int i;

  ret=new_poly(d);
  for (i=0; i<ret->d; i++) ret->shp[i]=1;
  ret->rav=(double *) get_mem(sizeof(double));
  ret->rav[0]=c;

  return(ret);
}


/* poly_print - you guessed it - it prints a polynomial */

void poly_print(poly_t *p)

{
  int c;
  int i, *vec, g1,first;

  if (p->rav==NULL) {
    printf("0\n");
    return;
  }
    
  vec=(int *) get_mem(p->d*sizeof(int));
  for (i=0; i<p->d; i++) vec[i]=0;
  
  g1=0;
  first=TRUE;
  c=FALSE;
  while (!c) {
    if (p->rav[g1] != 0.0f) {
      first=FALSE;
      printf("(%f)",p->rav[g1]);
      for (i=0; i<p->d; i++) {
	if (vec[i]>1) printf("(x%d^%d)",i,vec[i]);
	else if (vec[i]==1) printf("(x%d)",i);
      }
    }
    
    g1++;

    i=0;
    do {
      vec[i]++;
      c=(vec[i]==p->shp[i]);
      if (c) vec[i]=0;
      i++;
    } while (c&&(i<p->d));

    if (!c)
      if ((!first)&&(p->rav[g1]!=0.0f)) {
	printf("+");
      }
  }

  printf("\n");
  free_mem(vec);
}
