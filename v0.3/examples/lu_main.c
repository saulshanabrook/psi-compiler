do_LU(int n, float *in)

{
  int i,j;

  printf("input:\n");
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      printf("%f ",in[i*n+j]);
    }
    printf("\n");
  }

  LU(n,in);

  printf("output:\n");
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      printf("%f ",in[i*n+j]);
    }
    printf("\n");
  }
}


main()

{
  int n;
  float x[25]={4,8,2,13,34,23,5,8,12,4,9,74,53,4,6,43,54,2,6,9,9,5,3,21,19};
  float y[25];
  float *in;

  n=5;
  memcpy(y,x,n*n*sizeof(float));
  in=y;
  do_LU(n,in);
}
