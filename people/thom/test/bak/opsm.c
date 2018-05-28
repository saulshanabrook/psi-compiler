#include <stdlib.h>
#include "moalib.e"

ADD_SUB1(double _in1[], double _in2[], double _in3[], double _out[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;

/*******
out=in1
********/

  shift=_out+0*(int) (3)+0*(int) (4)+0;
  offset0=_in1+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
out=out +  + in2
********/

  shift=_out+0*(int) (3)+0*(int) (4)+0;
  offset0=_in2+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)+= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
out=out +  + in3
********/

  shift=_out+0*(int) (3)+0*(int) (4)+0;
  offset0=_in3+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)+= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


}


ADD_SUB2(double _in1[], double _in2[], double _in3[], double _out[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _temp[2*3*4];

/*******
temp=in1
********/

  shift=_temp+0*(int) (3)+0*(int) (4)+0;
  offset0=_in1+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
temp=temp * in2
********/

  shift=_temp+0*(int) (3)+0*(int) (4)+0;
  offset0=_in2+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)*= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
temp=temp - in3
********/

  shift=_temp+0*(int) (3)+0*(int) (4)+0;
  offset0=_in3+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)-= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
out=temp
********/

  shift=_out+0*(int) (3)+0*(int) (4)+0;
  offset0=_temp+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
  }


}


ADD_SUB3(double _in1[], double _in2[], double _in3[], double _out[])

{
  double *offset0;
  double *offset1;
  double *offset2;
  double *offset3;
  double *offset4;
  double *offset5;
  double *offset6;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _temp[2*3*4];

/*******
temp=in2 * in3
********/

  shift=_temp+0*(int) (3)+0*(int) (4)+0;
  offset0=_in2+0*(int) 12+0*(int) 4+0;
  offset1=_in3+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        *(shift)*= *(offset1);
        offset1+=(1);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
out=in1 - four * in3 +  + tfive * temp / in3 - in2
********/

  shift=_out+0*(int) (3)+0*(int) (4)+0;
  offset0=_in1+0*(int) 12+0*(int) 4+0;
  offset2=_in3+0*(int) 12+0*(int) 4+0;
  offset4=_temp+0*(int) 12+0*(int) 4+0;
  offset5=_in3+0*(int) 12+0*(int) 4+0;
  offset6=_in2+0*(int) 12+0*(int) 4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        *(shift)-= 4.000000;
        *(shift)*= *(offset2);
        *(shift)+= 25.000000;
        *(shift)*= *(offset4);
        *(shift)/= *(offset5);
        *(shift)-= *(offset6);
        offset6+=(1);
        offset5+=(1);
        offset4+=(1);
        offset2+=(1);
        offset0+=(1);
        shift++;
      }
    }
  }


}


