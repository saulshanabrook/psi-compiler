/* heat_main.c - A driver module for the heat.m implementation of a finite
     difference approximation to the heat equation */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 8
#define I 200

extern int heat2d(int i, int n, double *_A, double *_lambda);


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
    step[i]=L/shp[i];
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


main()

{
  int i,j;
  long shp[2];
  double A[N*N];
  double lambda;
  
  lambda=0.25;
  shp[0]=N;
  shp[1]=N;

  /* set initial and boundry conditions */
  init_grid(A,2,shp,2*M_PI);

  /* call the compile MOAL implementation */
  heat2d(I,N,A,&lambda);

  /* print results */
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++)
      printf("%15lg ",A[j+N*i]);
    printf("\n");
  }

}

