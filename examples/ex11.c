#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  int i3;
  double *shift;
  double _a[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000};
  double _xnew[]={0.000000, 1.000000, 6.000000, 7.000000, 2.000000,
    3.000000, 8.000000, 9.000000, 4.000000, 5.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 18.000000,
    19.000000, 14.000000, 15.000000, 20.000000, 21.000000,
    16.000000, 17.000000, 22.000000, 23.000000};
  double _x[]={6.000000};
  double _y[]={2.000000};
  double _i[]={2.000000};
  double _j[]={0.000000};
  int forall_i0[2];
  double _res0[6];
  double _res1[6];

/*******
res0=i psi a
********/

  shift=_res0+0;
  offset0=_a+2*6+0;
  for (i1=0; i1<6; i1++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


/*******
res1=x take (x drop ( rav (j psi  omega <1.000000 2.000000> xnew)))
********/

  forall_i0[0]=1;
  for (forall_i0[1]=0; forall_i0[1]<0+3; forall_i0[1]++) {
    shift=_res1+(forall_i0[0]+-1);
    offset0=_xnew+forall_i0[0]*12+forall_i0[0]*4+0*2+0;
    for (i3=0; i3<2; i3++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


}


