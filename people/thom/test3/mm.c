#include <stdlib.h>
#include "moalib.e"

multiply(int _m, int _n, int _p, double _A[], double _B[], double _C[])

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[1];
  int forall_i3[1];
  double tmp_vect0[1];
  double *temp1;

/*******
C= +red  omega <2.000000> (A ( *  omega <sig1 sig2> ) omega <1.000000 2.000000> B)
********/

  for (forall_i2[0]=0; forall_i2[0]<0+_m; forall_i2[0]++) {
    shift=_C+forall_i2[0+0]*_p+0;
    for (i0=0; i0<_p; i0++) {
      *(shift)= 0.000000;
      shift+=1;
    }
    for (forall_i3[0]=0; forall_i3[0]<0+_n; forall_i3[0]++) {
      temp1=(double *) get_mem((_p)*sizeof(double));
      for (forall_i0[0]=forall_i2[0+0]; forall_i0[0]<forall_i2[0+0]+1; forall_i0[0]++) {
        for (forall_i1[0]=forall_i3[0+0]; forall_i1[0]<forall_i3[0+0]+1; forall_i1[0]++) {
          shift=tmp_vect0+0;
          offset0=_A+forall_i0[0+0]*_n+forall_i1[0+0];
          *(shift)= *(offset0);
          shift=temp1+0;
          for (i0=0; i0<_p; i0++) {
            *(shift)= tmp_vect0[0+0];
            shift+=1;
          }
          shift=temp1+0;
          offset0=_B+forall_i1[0+0]*_p+0;
          for (i1=0; i1<_p; i1++) {
            *(shift)*= *(offset0);
            offset0+=1;
            shift+=1;
          }
        }
      }
      shift=_C+forall_i2[0+0]*_p+0;
      offset0=temp1+0;
      for (i0=0; i0<_p; i0++) {
        *(shift)+= *(offset0);
        offset0+=1;
        shift+=1;
      }
      free(temp1);
    }
  }


}


