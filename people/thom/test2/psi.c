#include <stdlib.h>
#include "moalib.e"

hw1(double _A[], double _B[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;

  printout(_six);
/*******
A=<0.000000> psi B
********/

  shift=_A+0*40+0;
  offset0=_B+0*1200+0*40+0;
  for (i1=0; i1<30; i1++) {
    for (i2=0; i2<40; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


  printout(_six);
}


hw2(double _A[], double _B[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;

  printout(_six);
/*******
A=<0.000000> psi B + six
********/

  shift=_A+0*40+0;
  offset0=_B+0*1200+0*40+0;
  for (i1=0; i1<30; i1++) {
    for (i2=0; i2<40; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }
  shift=_A+0*40+0;
  for (i0=0; i0<30; i0++) {
    for (i1=0; i1<40; i1++) {
      *(shift)+= 6.000000;
      shift+=1;
    }
  }


  printout(_six);
}


