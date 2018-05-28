#include <stdlib.h>
#include "moalib.e"

test_reverse1(double _in1[], double _out1[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  int forall_i0[1];

/*******
out1= reverse ( reverse  omega <2.000000> in1)
********/

  for (forall_i0[0]=3; forall_i0[0]<3+4; forall_i0[0]++) {
    shift=_out1+(forall_i0[0]+-3)*12+0*2+0;
    offset0=_in1+forall_i0[0]*12+5*2+0;
    for (i1=0; i1<6; i1++) {
      for (i2=0; i2<2; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      offset0+=-4;
    }
  }


}


