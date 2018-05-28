/* host_main.c - This example program drivers the host program of the 
     distributed implementation of the heat equation. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256
#define I 25

/* this procedure sets the initial conditions on the grid */

init_grid(grid, d, shp, L)
double *grid;
long d;
long *shp;
double L;

{
  float step[3];
  long i,j,k,cnt[3],tau,off;

  memcpy(cnt,shp,d*sizeof(long));
  for (i=d; i<3; i++) cnt[i]=3;

  tau=1;
  for (i=0; i<d; i++) {
    tau*=shp[i];
    step[i]=2*L/shp[i];
  }
  for (i=0; i<tau; i++) grid[i]=0.0;

  switch (d) {
  case 1:
    off=1;
    break;

  case 2:
    off=shp[1]+1;
    break;

  case 3:
    off=shp[1]*shp[2]+shp[2]+1;
    break;
  }

  for (i=1; i<cnt[0]-1; i++) {
    for (j=1; j<cnt[1]-1; j++) {
      for (k=1; k<cnt[2]-1; k++) {
        grid[off]=sin((float) i*step[0]-L);
        if (d>1) grid[off]*=sin((float) j*step[1]-L);
        if (d>2) grid[off]*=sin((float) k*step[2]-L);
        off++;
      }
      if (d>2) off+=2;
    }
    if (d>2) off+=2*shp[2];
    else if (d>1) off+=2;
  }
}


/* This is the sequential program produced by the compiler used to check
     the results against. */


heat2ds(int _i, int _n, double _A[], double _lambda[])

{
  double *offset0;
  double *offset1;
  double *offset2;
  double *offset3;
  double *offset4;
  int i0;
  int i1;
  double *shift;
  double _b[2];
  double _m_lambda[1];
  double _nfour[1];
  double _one[1];
  double consta0[2];
  double consta1[2];
  double *_A2;
  double _t[1];
  int scalar0;
  int scalar1;
  int scalar2;
  int scalar3;
  int scalar4;

/*******
m_lambda=nfour * lambda + one
********/

  shift=_m_lambda+0;
  offset1=_lambda+0;
  *(shift)= -4.000000;
  *(shift)*= *(offset1);
  *(shift)+= 1.000000;


/*******
b=<n n> - <2.000000 2.000000>
********/

  shift=_b+0;
  consta0[0]=(((int) _n));
  consta0[1]=(((int) _n));
  offset0=consta0+0;
  consta1[0]=2.000000;
  consta1[1]=2.000000;
  offset1=consta1+0;
  for (i0=0; i0<(2); i0++) {
    *(shift)= *(offset0);
    *(shift)-= *(offset1);
    offset1+=(1);
    offset0+=(1);
    shift++;
  }


  _A2=(double *) get_mem(((((int) _b[0+0]))*(((int) _b[1+0])))*sizeof(double));

  for (_t[0]=0; _t[0]<(((int) _i)); _t[0]++) {
/*******
A2=((b take (<1.000000 2.000000> drop A)) + (b take (<1.000000 0.000000> drop A)) + (b take (<2.000000 1.000000> drop A)) + (b take (<0.000000 1.000000> drop A))) * lambda
********/

    shift=_A2+0*(((int) _b[1+0]))+0;
    offset0=_A+1*(((int) _n))+2;
    scalar0=(((int) _n)+(-1)*(((int) _b[1+0])));
    offset1=_A+1*(((int) _n))+0;
    scalar1=(((int) _n)+(-1)*(((int) _b[1+0])));
    offset2=_A+2*(((int) _n))+1;
    scalar2=(((int) _n)+(-1)*(((int) _b[1+0])));
    offset3=_A+0*(((int) _n))+1;
    scalar3=(((int) _n)+(-1)*(((int) _b[1+0])));
    for (i0=0; i0<_b[0+(0)]; i0++) {
      for (i1=0; i1<_b[1+(0)]; i1++) {
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        *(shift)+= *(offset2);
        *(shift)+= *(offset3);
        *(shift)*= _lambda[0+0];
        offset3+=(1);
        offset2+=(1);
        offset1+=(1);
        offset0+=(1);
        shift++;
      }
      offset3+=((int) scalar3);
      offset2+=((int) scalar2);
      offset1+=((int) scalar1);
      offset0+=((int) scalar0);
      shift+=0;
    }


/*******
<1.000000 1.000000> pdrop A=(b take (<1.000000 1.000000> drop A)) * m_lambda + A2
********/

    shift=_A+1*(((int) _n))+1;
    offset1=_A2+0*(((int) _b[1+0]))+0;
    scalar4=(((int) _n)+(-1)*(((int) _b[1+0])));
    for (i0=0; i0<(((int) _b[0+0])); i0++) {
      for (i1=0; i1<(((int) _b[1+0])); i1++) {
        *(shift)*= _m_lambda[0+0];
        *(shift)+= *(offset1);
        offset1+=(1);
        shift++;
      }
      offset1+=0;
      shift+=((int) scalar4);
    }


  }
  free(_A2);
}


extern int heat2d(int i, int n, double *_A, double *_lambda);

main()

{
  int i,j;
  long shp[2];
  double A[N*N];
  double lambda;
  
  lambda=0.125;
  shp[0]=N;
  shp[1]=N;

  init_grid(A,2,shp,2*M_PI);

  heat2ds(I,N,A,&lambda);
  puts("Expected:");
  for (i=0; i<N*N; i++)
    printf("%lg,",A[i]);
  printf("\n");

  init_grid(A,2,shp,2*M_PI);

  heat2d(I,N,A,&lambda);
}
