#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _x[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000,
    25.000000, 26.000000, 27.000000, 28.000000, 29.000000,
    30.000000, 31.000000, 32.000000, 33.000000, 34.000000,
    35.000000};
  double _l[]={5.000000};
  int forall_i0[1];
  int tmp_vect0[1];
  int tmp_vect1[1];
  double _i[1];
  double consta0[1];
  int consta0[1];
  double _foo[5*6];
  int scalar0;
  int scalar1;

  for (_i[0]=2; _i[0]<3; _i[0]++) {
/*******
foo=(<5.000000> take  omega <0.000000 1.000000> x) + i
********/

    shift=tmp_vect0+0;
    consta0[0]=5.000000;
    offset0=consta0+forall_i0[0];
    *(shift)= *(offset0);
    for (forall_i0[0]=0; forall_i0[0]<0+6; forall_i0[0]++) {
      shift=tmp_vect1+0;
      offset0=consta0+forall_i0[0];
      *(shift)= *(offset0);
      shift=_foo+forall_i0[0]*6+0;
      offset0=_x+forall_i0[0]*6+((tmp_vect1[0]+6)*(((tmp_vect1[0])<0)));
      scalar0=((6)-(abs(tmp_vect0[0])));
      scalar1=((6)-(abs(tmp_vect0[0])));
      for (i1=0; i1<(abs(tmp_vect0[0])); i1++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_foo+0*6+0;
    scalar0=((6)-(abs(tmp_vect0[0])));
    for (i0=0; i0<6; i0++) {
      for (i1=0; i1<(abs(tmp_vect0[0])); i1++) {
        for (i2=0; i2<6; i2++) {
          *(shift)+= _i[0];
          shift+=1;
        }
        shift+=scalar0;
      }
    }


  }
}


