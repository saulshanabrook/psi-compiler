#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  int forall_i0;
  int tmp_vect0[1];
  int forall_i1[1];
  int forall_i2[1];
  int tmp_vect1[1];
  double consta0[1];
  double consta1[1];
  double consta2[1];
  double _b5[30];
  double _fish[30];

/*******
b5=(( iota <30.000000> *  omega <1.000000 1.000000> <1.000000>) +  omega <1.000000 1.000000> <0.000000>) psi  omega <1.000000 1.000000> fish
********/

  shift=tmp_vect0+0;
  consta0[0]=30.000000;
  offset0=consta0+0;
  *(shift)= *(offset0);
  shift=tmp_vect0+0;
  consta1[0]=1.000000;
  offset0=consta1+0;
  *(shift)*= *(offset0);
  for (forall_i2[0]=0; forall_i2[0]<0+tmp_vect0[0]; forall_i2[0]++) {
    forall_i1[0]=forall_i2[0];
    shift=tmp_vect1+((-1)*(forall_i2[0])+forall_i1[0]);
    *(shift)= forall_i1[0];
    shift++;
    shift=tmp_vect1+((-1)*(forall_i2[0])+forall_i1[0]);
    consta2[0]=0.000000;
    offset0=consta2+0;
    *(shift)+= *(offset0);
    shift=_b5+forall_i2[0];
    offset0=_fish+tmp_vect1[0];
    *(shift)= *(offset0);
  }


}


