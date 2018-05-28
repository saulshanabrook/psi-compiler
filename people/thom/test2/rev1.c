#include <stdlib.h>
#include "moalib.e"

test_reverse1(double _in1[], double _out1[], double _out2[], double _out3[])

{
  double *offset0;
  double *offset1;
  int i0;
  int i1;
  int i2;
  double *shift;
  int forall_i0[1];
  double *temp1;

/*******
out1= reverse in1
********/

  shift=_out1+0*12+0*4+0;
  offset0=_in1+1*12+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    offset0+=-24;
  }


/*******
out2= reverse (out1 + in1)
********/

  shift=_out2+0*12+0*4+0;
  offset0=_out1+1*12+0*4+0;
  offset1=_in1+1*12+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        offset1+=1;
        offset0+=1;
        shift+=1;
      }
    }
    offset1+=-24;
    offset0+=-24;
  }


/*******
out3= +red in1
********/

  shift=_out3+0*4+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<4; i1++) {
      *(shift)= 0.000000;
      shift+=1;
    }
  }
  for (forall_i0[0]=0; forall_i0[0]<0+2; forall_i0[0]++) {
    temp1=(double *) get_mem((12)*sizeof(double));
    shift=temp1+0*4+0;
    offset0=_in1+forall_i0[0]*12+0*4+0;
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_out3+0*4+0;
    offset0=temp1+0*4+0;
    for (i0=0; i0<3; i0++) {
      for (i1=0; i1<4; i1++) {
        *(shift)+= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp1);
  }


}


test_reverse2(double _in1[], double _out1[], double _out2[], double _out3[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;

/*******
out1= reverse ( reverse in1)
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


/*******
out2=<1.000000> take ( reverse in1)
********/

  shift=_out2+0*12+0*4+0;
  offset0=_in1+1*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


/*******
out3=<1.000000> psi ( reverse in1)
********/

  shift=_out3+0*4+0;
  offset0=_in1+0*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


}


test_reverse3(double _in1[], double _out1[], double _out2[], double _out3[])

{
  double *offset0;
  double *offset1;
  int i0;
  int i1;
  int i2;
  double *shift;
  double *temp2;

/*******
out1= reverse (<1.000000> take ( reverse in1) cat (<1.000000> drop ( reverse in1)))
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


/*******
out2=five - (<1.000000> take in1) - ( reverse (<1.000000> drop in1) * two)
********/

  temp2=(double *) get_mem((12)*sizeof(double));
  shift=_out2+0*12+0*4+0;
  offset1=_in1+0*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= 5.000000;
      *(shift)-= *(offset1);
      offset1+=1;
      shift+=1;
    }
  }
  shift=temp2+0*12+0*4+0;
  offset0=_in1+1*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }
  shift=temp2+0*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)*= 2.000000;
      shift+=1;
    }
  }
  shift=_out2+0*12+0*4+0;
  offset0=temp2+0*12+0*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)-= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }
  free(temp2);


/*******
out3= reverse (<1.000000> psi in1)
********/

  shift=_out3+0*4+0;
  offset0=_in1+1*12+2*4+0;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<4; i2++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
    offset0+=-8;
  }


}


