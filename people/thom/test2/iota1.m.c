#include <stdlib.h>
#include "moalib.e"

iota1(double _out0[], double _out1[], double _out2[], double _out3[], double _out4[], double _out5[], double _out6[], double _arr0_1[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  int i3;
  double *shift;
  double _in1[]={2.000000};
  double _in2[]={5.000000, 6.000000};
  double _in3[]={5.000000, 6.000000, 7.000000};
  double _five[]={5.000000};
  double _numb3[]={2.000000, 0.000000};

/*******
out0= iota ten
********/

  shift=_out0+0;
  for (i0=0; i0<0+10; i0++) {
    *(shift)= i0;
    shift++;
  }


/*******
out1= iota five
********/

  shift=_out1+0;
  for (i0=0; i0<0+5; i0++) {
    *(shift)= i0;
    shift++;
  }


/*******
out2= iota in2
********/

  shift=_out2+0*12+0*2+0;
  for (i0=0; i0<0+5; i0++) {
    for (i1=0; i1<0+6; i1++) {
      *(shift)= i0;
      shift++;
      *(shift)= i1;
      shift++;
    }
  }


/*******
out3= iota in3
********/

  shift=_out3+0*126+0*21+0*3+0;
  for (i0=0; i0<0+5; i0++) {
    for (i1=0; i1<0+6; i1++) {
      for (i2=0; i2<0+7; i2++) {
        *(shift)= i0;
        shift++;
        *(shift)= i1;
        shift++;
        *(shift)= i2;
        shift++;
      }
    }
  }


/*******
out4=<3.000000> psi ( iota ten)
********/

  shift=_out4+0;
  *(shift)= 3;
  shift++;


/*******
out5=<2.000000 5.000000 1.000000> psi ( iota in3)
********/

  shift=_out5+0;
  *(shift)= 2;
  shift++;
  *(shift)= 5;
  shift++;
  *(shift)= 1;
  shift++;


/*******
out6= iota in1
********/

  shift=_out6+0;
  for (i0=0; i0<0+2; i0++) {
    *(shift)= i0;
    shift++;
  }


/*******
arr0_1=(numb3 + ( iota numb2))
********/

  shift=_arr0_1+0;
  offset0=_numb3+0;
  for (i0=0; i0<2; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }
  shift=_arr0_1+0;
  for (i0=0; i0<0+2; i0++) {
    *(shift)+= i0;
    shift++;
  }


/*******
arr0_1=(( iota numb2) + numb3)
********/

  shift=_arr0_1+0;
  for (i0=0; i0<0+2; i0++) {
    *(shift)= i0;
    shift++;
  }
  shift=_arr0_1+0;
  offset0=_numb3+0;
  for (i0=0; i0<2; i0++) {
    *(shift)+= *(offset0);
    offset0+=1;
    shift+=1;
  }


}


