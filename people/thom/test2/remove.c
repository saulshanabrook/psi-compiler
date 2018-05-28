#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  double *shift;
  double _xin[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000};
  double _xout[5*5];

/*******
<3.000000 0.000000> pdrop xout=xin
********/

  shift=_xout+3*5+0;
  offset0=_xin+0;
  for (i0=0; i0<5; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


}


