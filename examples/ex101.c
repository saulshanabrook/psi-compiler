#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _s[]={30.000000, 30.000000, 30.000000, 30.000000};
  double _w[]={30.000000, 30.000000};
  double _b0[]={0.000000, 0.000000};
  double _b1[]={0.000000};
  double _z[]={3.000000};
  double _k[]={30.000000, 1.000000};
  double _b5[]={30.000000, 1.000000, 30.000000, 1.000000};
  double _x[]={30.000000};
  double _l[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000};
  double _zoo[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000};
  double _foo[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000};
  double _r[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000,
    0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000};
  int forall_i0[2];
  int tmp_vect0[2];
  double _a10[4*3];

/*******
a10=(( iota ( shp foo)) psi  omega <1.000000 2.000000> foo)
********/

  for (forall_i0[0]=0; forall_i0[0]<0+4; forall_i0[0]++) {
    for (forall_i0[1]=0; forall_i0[1]<0+3; forall_i0[1]++) {
      shift=tmp_vect0+0;
      *(shift)= forall_i0[0];
      shift++;
      *(shift)= forall_i0[0];
      shift++;
      shift=_a10+forall_i0[0]*3+forall_i0[1];
      offset0=_foo+tmp_vect0[0]*3+tmp_vect0[1];
      *(shift)= *(offset0);
    }
  }


}

