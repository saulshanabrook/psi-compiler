#include <stdlib.h>
#include "moalib.e"

shp_tau_dim_iota_ex(int _j)

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  int i3;
  double *shift;
  int scalar0;
  int forall_i0[3];
  int tmp_vect0[3];
  double _g[1];
  double *_b=(double *) get_mem(4*_j*5*sizeof(double));
  double *_a=(double *) get_mem(4*_j*5*sizeof(double));
  int scalar1;

  scalar0=((20)*(_j));
/*******
g= tau a
********/

  shift=_g+0;
  *(shift)= scalar0;


/*******
g= dim a
********/

  shift=_g+0;
  *(shift)= 3.000000;


/*******
b=( iota ( shp a)) psi  omega <1.000000 3.000000> a
********/

  for (forall_i0[0]=0; forall_i0[0]<0+4; forall_i0[0]++) {
    for (forall_i0[1]=0; forall_i0[1]<0+_j; forall_i0[1]++) {
      for (forall_i0[2]=0; forall_i0[2]<0+5; forall_i0[2]++) {
        shift=tmp_vect0+0;
        *(shift)= forall_i0[0];
        shift++;
        *(shift)= forall_i0[0];
        shift++;
        *(shift)= forall_i0[0];
        shift++;
        shift=_b+forall_i0[0]*((5)*(_j))+forall_i0[1]*5+forall_i0[2];
        offset0=_a+tmp_vect0[0]*((5)*(_j))+tmp_vect0[1]*5+tmp_vect0[2];
        scalar1=((5)*(_j));
        *(shift)= *(offset0);
      }
    }
  }


}


red_ex()

{
