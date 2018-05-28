#include <stdio.h>
#include <stdlib.h>

#define N 32
#define I 100

heat1ds(int _i, int _n, float _A[], float _lambda[])

{
  int i0;
  int shift,offset;
  float _ntwo[1];
  float _m_lambda[1];
  float _one[1];
  float _b[1];
  float consta0[1];
  float consta1[1];
  float *_A2;
  float _t[1];

  *(_m_lambda)=-2.000000;

  *(_m_lambda)*=*(_lambda);

  *(_m_lambda)+=1.000000;

  consta0[0]=(_n);
  shift=0;
  offset=0;
  *(_b+shift)=*(consta0+offset);

  consta1[0]=2.000000;
  shift=0;
  offset=0;
  *(_b+shift)-=*(consta1+offset);

  _A2=(float *) malloc(((_b[0+0]))*sizeof(float));

  for (_t[0]=0; _t[0]<(_i); _t[0]++) {
    shift=0;
    offset=0;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A2+shift)=*(_A+offset);
      offset++;
      shift++;
    }

    shift=0;
    offset=2;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A2+shift)+=*(_A+offset);
      offset++;
      shift++;
    }

    shift=0;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A2+shift)*=_lambda[0+0];
      shift++;
    }

    shift=1;
    offset=1;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A+shift)=*(_A+offset);
      offset++;
      shift++;
    }

    shift=1;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A+shift)*=_m_lambda[0+0];
      shift++;
    }

    shift=1;
    offset=0;
    for (i0=0; i0<(_b[0+0]); i0++) {
      *(_A+shift)+=*(_A2+offset);
      offset++;
      shift++;
    }

  }
  free(_A2);
}

extern int heat1d(int i, int n, float *_A, float *_lambda);

main()

{
  int i;
  float A[N];
  float lambda;
  
  lambda=0.125;
  
  for (i=0; i<N; i++) A[i]=0.0;
  A[0]=5.0;
  A[N-1]=5.0;

  heat1ds(I,N,A,&lambda);
  puts("Expected:");
  for (i=0; i<N; i++)
    printf("%f,",A[i]);
  printf("\n");

  for (i=0; i<N; i++) A[i]=0.0;
  A[0]=5.0;
  A[N-1]=5.0;

  heat1d(I,N,A,&lambda);
}
