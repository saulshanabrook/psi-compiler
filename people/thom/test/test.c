#include <stdlib.h>
#include "moalib.e"

omega_red(double _in1[], double _in2[], double _out1[])

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  int forall_i0[1];

/*******
out1= +  +red (in1 * in2)
********/

  shift=_out1+0;
  for (i0=0; i0<(10); i0++) {
    *(shift)= 0.000000;
    shift+=1;
  }
  for (forall_i0[0]=0; forall_i0[0]<0+(10); forall_i0[0]++) {
    shift=_out1+0;
    offset0=_in1+(((int) forall_i0[0+0]))*(int) 10+(0);
    for (i1=0; i1<10; i1++) {
      *(shift)+= *(offset0);
      offset0+=1;
      shift+=1;
    }
    shift=_out1+0;
    offset0=_in2+(((int) forall_i0[0+0]))*(int) 10+(0);
    for (i1=0; i1<10; i1++) {
      *(shift)*= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


}


