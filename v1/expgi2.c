#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  double *offset1;
  int i0;
  double *shift;
  double _B[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000};
  double _A[10];

/*******
A=B + B
********/

  shift=_A+0;
  offset0=_B+0;
  offset1=_B+0;
  for (i0=0; i0<10; i0++) {
    *(shift)= *(offset0);
    *(shift)+= *(offset1);
    offset1+=1;
    offset0+=1;
    shift+=1;
  }


}


