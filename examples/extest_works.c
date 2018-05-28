#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  double _w[]={30.000000, 30.000000};
  double _k[]={30.000000, 1.000000};
  double _x[]={30.000000};
  double _one[]={1.000000};
  double _m[]={10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000,
    30.000000, 31.000000, 32.000000, 33.000000, 34.000000,
    35.000000, 36.000000, 37.000000, 38.000000, 39.000000};
  double _y[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000};

  int forall_i0[1];
  int forall_i1[1];
  int tmp_vect0[1];
  int forall_i2[1];
  double _n[30];
  double _l[30*1];
  double consta0[1];

/*******
n=( iota q) *  omega <0.000000 0.000000> sone
********/

  for (forall_i0[0]=0; forall_i0[0]<0+30; forall_i0[0]++) {
    shift=_n+forall_i0[0];
    *(shift)= forall_i0[0];
    shift++;
    shift=_n+forall_i0[0];
    *(shift)*= 1.000000;
  }


/*******
n=( iota x) psi  omega <1.000000 1.000000> m
********/

  for (forall_i1[0]=0; forall_i1[0]<0+30; forall_i1[0]++) {
/*    shift=tmp_vect0+0; */
    shift=_m+tmp_vect0[0];
    *(shift)= forall_i1[0];
    shift++;
    shift=_n+forall_i1[0];
/*    offset0=_m+tmp_vect0[0]; */
   offset0=_m+forall_i1[0]; 
    *(shift)= *(offset0);
    printf("%f\n ", *(shift));
  }


/*******
l=( iota <30.000000>) *  omega <1.000000 1.000000> <1.000000>
********/

  for (forall_i2[0]=0; forall_i2[0]<0+30; forall_i2[0]++) {
    shift=_l+forall_i2[0]*1+0;
    *(shift)= forall_i2[0];
    shift++;
    shift=_l+forall_i2[0]*1+0;
    consta0[0]=1.000000;
    offset0=consta0+0;
    *(shift)*= *(offset0);
  }


}


