#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _xnew[]={0.000000, 1.000000, 6.000000, 7.000000, 2.000000,
    3.000000, 8.000000, 9.000000, 4.000000, 5.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 18.000000,
    19.000000, 14.000000, 15.000000, 20.000000, 21.000000,
    16.000000, 17.000000, 22.000000, 23.000000};
  double _x[]={2.000000};
  double _j[]={1.000000};
  int forall_i0[1];
  double _res0[6];

/*******
res0=x drop (x take (j psi  omega <1.000000 2.000000> xnew))
********/

  for (forall_i0[0]=2; forall_i0[0]<2+0; forall_i0[0]++) {
    shift=_res0+(forall_i0[0]+-2);
    offset0=_xnew+forall_i0[0]*12+1*4+0;
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=0;
    }
  }


}


