#include <stdio.h>

printout(int iter, int n, float A[], float lambda[])

{
  int i;

  printf("%d iterations on %d elements with labmda=%f\n",iter,n,lambda[0]);
  for (i=0; i<(n/4); i++)
    printf("%f ",A[i]);
  printf("\n");
}


main()

{
  heat1d();
}
