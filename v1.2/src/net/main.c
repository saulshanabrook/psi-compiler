/* main.c - This is the example driver module for the node program for the
    distributed implementation of the heat equation. */

#include <stdio.h>

printout(int iter, int n, double A[], double lambda[])

{
  int i,j;

  printf("%d iterations on %d elements with labmda=%lf\n",iter,n,lambda[0]);
  
  for (i=0; i<(n/4); i++)
    for (j=0; j<n; j++) 
      printf("%lg ",A[i*n+j]);
  printf("\n");
}


main()

{
  heat2d();
}
