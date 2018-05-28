#include <stdlib.h>
#include "moalib.e"

iota1(double _out0[],double _out1[],double _out2[],double _out3[],double _out4[],double _out5[],double _out6[],double _arr0_1[])

  double *offset0;
  int i0;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  double *shift;
  double _in1[]={2.000000, 6.000000);
  double _in2[]={5.000000, 6.000000, 7.000000, 3.000000, 0.000000);
  double _in3[]={5.000000, 6.000000, 7.000000, 3.000000, 0.000000);
  double _five[]={5.000000, 6.000000, 7.000000, 3.000000, 0.000000);
  double _numb3[]={2.000000, 0.000000);

/*******
out0=
********/

  shift=_out0+0;
  for (i0=0; i0<0+10; i0++) {
    *(shift)= i0;
    shift++;
  }


/*******
out1=
********/

  shift=_out1+0;
  for (i0=0; i0<0+((int) _five[0+0]); i0++) {
    for (i1=0; i1<0+((int) _five[1+0]); i1++) {
      for (i2=0; i2<0+((int) _five[2+0]); i2++) {
        for (i3=0; i3<0+((int) _five[3+0]); i3++) {
          for (i4=0; i4<0+((int) _five[4+0]); i4++) {
            *(shift)= i0;
            shift++;
            *(shift)= i1;
            shift++;
            *(shift)= i2;
            shift++;
            *(shift)= i3;
            shift++;
            *(shift)= i4;
            shift++;
          }
        }
      }
    }
  }


/*******
out2=
********/

  shift=_out2+0*12+0*2+0;
  for (i0=0; i0<0+((int) _in2[0+0]); i0++) {
    for (i1=0; i1<0+((int) _in2[1+0]); i1++) {
      for (i2=0; i2<0+((int) _in2[2+0]); i2++) {
        for (i3=0; i3<0+((int) _in2[3+0]); i3++) {
          for (i4=0; i4<0+((int) _in2[4+0]); i4++) {
            *(shift)= i0;
            shift++;
            *(shift)= i1;
            shift++;
            *(shift)= i2;
            shift++;
            *(shift)= i3;
            shift++;
            *(shift)= i4;
            shift++;
          }
        }
      }
    }
  }


/*******
out3=
********/

  shift=_out3+0*126+0*21+0*3+0;
  for (i0=0; i0<0+((int) _in3[0+0]); i0++) {
    for (i1=0; i1<0+((int) _in3[1+0]); i1++) {
      for (i2=0; i2<0+((int) _in3[2+0]); i2++) {
        for (i3=0; i3<0+((int) _in3[3+0]); i3++) {
          for (i4=0; i4<0+((int) _in3[4+0]); i4++) {
            *(shift)= i0;
            shift++;
            *(shift)= i1;
            shift++;
            *(shift)= i2;
            shift++;
            *(shift)= i3;
            shift++;
            *(shift)= i4;
            shift++;
          }
        }
      }
    }
  }


/*******
out4=
********/

  shift=_out4+0;
  *(shift)= 3;
  shift++;


/*******
out5=
********/

  shift=_out5+0;
  for (i3=0; i3<0+((int) _in3[0+3]); i3++) {
    for (i4=0; i4<0+((int) _in3[1+3]); i4++) {
      *(shift)= 2;
      shift++;
      *(shift)= 5;
      shift++;
      *(shift)= 1;
      shift++;
      *(shift)= i3;
      shift++;
      *(shift)= i4;
      shift++;
    }
  }


/*******
out6=
********/

  shift=_out6+0;
  for (i0=0; i0<0+((int) _in1[0+0]); i0++) {
    for (i1=0; i1<0+((int) _in1[1+0]); i1++) {
      *(shift)= i0;
      shift++;
      *(shift)= i1;
      shift++;
    }
  }


/*******
arr0_1=
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
arr0_1=
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


