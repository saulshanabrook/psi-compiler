#include <stdlib.h>
#include "moalib.e"

SCALARCAT_M(double _in1[], double _out1[], double _out2[], double _out3[])

{
  double *offset0;
  int i0;
  double *shift;

/*******
out1=in1 cat five
********/

  shift=_out1+0;
  offset0=_in1+0;
  for (i0=0; i0<5; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }
  shift=_out1+5;
  *(shift)= 5.000000;


/*******
out2=five cat in1
********/

  shift=_out2+0;
  *(shift)= 5.000000;
  shift=_out2+1;
  offset0=_in1+0;
  for (i0=0; i0<5; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


/*******
out3=five cat five
********/

  shift=_out3+0;
  *(shift)= 5.000000;
  shift=_out3+1;
  *(shift)= 5.000000;


}


SCALAROPS_M(double _in1[], double _out1[])

{
  double *offset0;
  double *offset1;
  int i0;
  int i1;
  int i2;
  double *shift;

/*******
out1=in1 + five
********/

  shift=_out1+0*12+0*4+0;
  offset0=_in1+0*12+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        *(shift)+= 5.000000;
        offset0+=1;
        shift+=1;
      }
    }
  }


}


SCALAROPS2_M(double _in1[], double _in2[], double _out1[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;

/*******
out1=(in1 cat in2) + five
********/

  shift=_out1+0*12+0*4+0;
  offset0=_in1+0*12+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
  }
  shift=_out1+2*12+0*4+0;
  offset0=_in2+0*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }
  shift=_out1+0*12+0*4+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)+= 5.000000;
        shift+=1;
      }
    }
  }


}


