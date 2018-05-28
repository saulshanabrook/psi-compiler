/* mm_main.c - This is and example driver for the moal matrix multiply */

#include <stdio.h>

main()

{
  int i,j;
/*  double a[2][2],b[2][2],c[2][2]; */
  double *a, *b, *c;
  a = (double *) malloc(4*sizeof(double));
  b = (double *) malloc(4*sizeof(double));
  c = (double *) malloc(4*sizeof(double));

  a[0]=1.0; a[1]=5.0;
  a[2]=3.0; a[3]=2.0;

  b[0]=9.0; b[1]=4.0;
  b[2]=8.0; b[3]=7.0;

  multiply(2,2,2,a,b,c);
  printf("%4lg %4lg   %4lg %4lg   %4lg %4lg\n",a[0],a[1],b[0],b[1],
         c[0],c[1]);
  printf("          *           =          \n");
  printf("%4lg %4lg   %4lg %4lg   %4lg %4lg\n",a[2],a[3],b[2],b[3],
         c[2],c[3]);
}
