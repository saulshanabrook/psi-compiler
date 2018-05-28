#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  double *offset1;
  int i0;
  double *shift;
  double _res[1];
  double consta0[1];
  double consta1[1];
  double _shape[1];
  double consta2[0];
  double consta3[1];

/*******
res=<2.000000> + <3.000000>
********/

  shift=_res+0;
  consta0[0]=2.000000;
  offset0=consta0+0;
  consta1[0]=3.000000;
  offset1=consta1+0;
  *(shift)= *(offset0);
  *(shift)+= *(offset1);


/*******
shape= shp res
********/

  shift=_shape+0;
  offset0=consta2+0;
  *(shift)= *(offset0);


/*******
shape= shp (<2.000000> + <3.000000>)
********/

  shift=_shape+0;
  consta3[0]=1;
  offset0=consta3+0;
  *(shift)= *(offset0);


}


