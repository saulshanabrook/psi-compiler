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
    20.000000, 21.000000, 22.000000, 23.000000};
  double _Two[]={2.000000};
  double _Mfour[]={-4.000000};
  double _A[2*4];
  double _B[2*4];

/*******
A=Two take C
********/

  shift=_A+0*4+0;
  offset0=_C+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<4; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


/*******
B=Mfour drop C
********/

  shift=_B+0*4+0;
  offset0=_C+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<4; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


}


