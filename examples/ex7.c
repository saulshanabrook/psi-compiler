#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _A[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000,
    30.000000, 31.000000, 32.000000, 33.000000, 34.000000,
    35.000000, 36.000000, 37.000000, 37.000000, 39.000000,
    40.000000, 41.000000, 42.000000, 43.000000, 44.000000,
    45.000000, 46.000000, 47.000000, 48.000000, 49.000000,
    50.000000, 51.000000, 52.000000, 53.000000, 54.000000,
    55.000000, 56.000000, 57.000000, 58.000000, 59.000000};
  int forall_i0[1];
  int forall_i1[1];
  int tmp_vect0[1];
  double consta0[1];
  double consta1[1];
  double _R[4];

/*******
R=<1.000000 2.000000> psi (<3.000000> take ((<5.000000> - <1.000000>) -  omega <1.000000 1.000000> ( iota <5.000000>)) psi  omega <1.000000 3.000000> A)
********/

  forall_i1[0]=1;
  forall_i0[0]=forall_i1[0];
  shift=tmp_vect0+((-1)*(forall_i1[0])+forall_i0[0]);
  consta0[0]=5.000000;
  offset0=consta0+0;
  *(shift)= *(offset0);
  shift=tmp_vect0+((-1)*(forall_i1[0])+forall_i0[0]);
  consta1[0]=1.000000;
  offset0=consta1+0;
  *(shift)-= *(offset0);
  shift=tmp_vect0+((-1)*(forall_i1[0])+forall_i0[0]);
  *(shift)-= forall_i0[0];
  shift++;
  shift=_R+(forall_i1[0]+-1);
  offset0=_A+tmp_vect0[0]*12+2*4+0;
  for (i2=0; i2<4; i2++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


}

