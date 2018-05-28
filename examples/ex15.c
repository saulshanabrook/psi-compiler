#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  double _C[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000};
  double _nsh[]={3.000000, 3.000000};
  double _zero[]={0.000000};
  double _one[]={1.000000};
  double _mone[]={-1.000000};
  double _vdrop[]={0.000000, 1.000000};
  double _A[3*3];

/*******
A=nsh take (vdrop drop (one drop (mone drop C)))
********/

  shift=_A+0*3+0;
  offset0=_C+1*5+1;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<3; i1++) {
      *(shift)= *(offset0);
      printf("%4lg ", *(shift));
      offset0+=1;
      shift+=1;
    }
    offset0+=2;
  }


}


