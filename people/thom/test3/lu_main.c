/* lu_main.c - This is a driver module that call the compiled MOAL 
     implementation of LU decomposition with a small example array. */

main()

{
  int i,j,n;
  double x[25]={4,8,2,13,34,23,5,8,12,4,9,74,53,4,6,43,54,2,6,9,9,5,3,21,19};

  n=5;

  /* print the initial array */
  printf("input:\n");
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      printf("%4lg ",x[i*n+j]);
    }
    printf("\n");
  }

  /* call the LU procedure */
  LU(n,&x);

  /* print the result of the LU decomposition */
  printf("output:\n");
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      printf("%4lg ",x[i*n+j]);
    }
    printf("\n");
  }
}
