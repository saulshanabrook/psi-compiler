#include <stdlib.h>
#include "moalib.e"

test_red(double _in1[], double _in2[], double _out1[], double _out2[], double _out3[], double _out4[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  int i3;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[1];
  int forall_i3[1];
  double *temp1;
  double *temp2;
  double *temp3;
  double *temp4;

/*******
out1= *red in1
********/

  shift=_out1+0*7+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<7; i1++) {
      *(shift)= 1.000000;
      shift+=1;
    }
  }
  for (forall_i0[0]=0; forall_i0[0]<0+9; forall_i0[0]++) {
    temp1=(double *) get_mem((21)*sizeof(double));
    shift=temp1+0*7+0;
    offset0=_in1+forall_i0[0]*21+0*7+0;
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<7; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_out1+0*7+0;
    offset0=temp1+0*7+0;
    for (i0=0; i0<3; i0++) {
      for (i1=0; i1<7; i1++) {
        *(shift)*= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp1);
  }


/*******
out2= *red (<2.000000> drop in1)
********/

  shift=_out2+0*7+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<7; i1++) {
      *(shift)= 1.000000;
      shift+=1;
    }
  }
  for (forall_i1[0]=0; forall_i1[0]<0+7; forall_i1[0]++) {
    temp2=(double *) get_mem((21)*sizeof(double));
    shift=temp2+0*7+0;
    offset0=_in1+(forall_i1[0]+2)*21+0*7+0;
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<7; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_out2+0*7+0;
    offset0=temp2+0*7+0;
    for (i0=0; i0<3; i0++) {
      for (i1=0; i1<7; i1++) {
        *(shift)*= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp2);
  }


/*******
out3= *red (<1.000000> psi in2)
********/

  shift=_out3+0*8+0;
  for (i0=0; i0<6; i0++) {
    for (i1=0; i1<8; i1++) {
      *(shift)= 1.000000;
      shift+=1;
    }
  }
  for (forall_i2[0]=0; forall_i2[0]<0+5; forall_i2[0]++) {
    temp3=(double *) get_mem((48)*sizeof(double));
    shift=temp3+0*8+0;
    offset0=_in2+1*240+forall_i2[0]*48+0*8+0;
    for (i2=0; i2<6; i2++) {
      for (i3=0; i3<8; i3++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_out3+0*8+0;
    offset0=temp3+0*8+0;
    for (i0=0; i0<6; i0++) {
      for (i1=0; i1<8; i1++) {
        *(shift)*= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp3);
  }


/*******
out4= *red (<2.000000 2.000000> take in2)
********/

  shift=_out4+0*48+0*8+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<6; i1++) {
      for (i2=0; i2<8; i2++) {
        *(shift)= 1.000000;
        shift+=1;
      }
    }
  }
  for (forall_i3[0]=0; forall_i3[0]<0+2; forall_i3[0]++) {
    temp4=(double *) get_mem((96)*sizeof(double));
    shift=temp4+0*48+0*8+0;
    offset0=_in2+forall_i3[0]*240+0*48+0*8+0;
    for (i1=0; i1<2; i1++) {
      for (i2=0; i2<6; i2++) {
        for (i3=0; i3<8; i3++) {
          *(shift)= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
    }
    shift=_out4+0*48+0*8+0;
    offset0=temp4+0*48+0*8+0;
    for (i0=0; i0<2; i0++) {
      for (i1=0; i1<6; i1++) {
        for (i2=0; i2<8; i2++) {
          *(shift)*= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
    }
    free(temp4);
  }


}


test_red2(double _in1[], double _in2[], double _out1[], double _out2[], double _out3[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[1];
  int scalar0;
  int scalar1;
  double *temp5;
  double *temp6;
  double *temp7;

  scalar0=((forall_i2[0])/(21));
  scalar1=((forall_i2[0]+1)/(21));
/*******
out1= *red ((<2.000000> take in1) + in2)
********/

  shift=_out1+0*7+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<7; i1++) {
      *(shift)= 1.000000;
      shift+=1;
    }
  }
  for (forall_i0[0]=0; forall_i0[0]<0+2; forall_i0[0]++) {
    temp5=(double *) get_mem((21)*sizeof(double));
    shift=temp5+0*7+0;
    offset0=_in1+forall_i0[0]*21+0*7+0;
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<7; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=temp5+0*7+0;
    offset0=_in2+forall_i0[0]*21+0*7+0;
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<7; i2++) {
        *(shift)+= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_out1+0*7+0;
    offset0=temp5+0*7+0;
    for (i0=0; i0<3; i0++) {
      for (i1=0; i1<7; i1++) {
        *(shift)*= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp5);
  }


/*******
out2= *red (in1 cat in2)
********/

  shift=_out2+0*7+0;
  for (i0=0; i0<3; i0++) {
    for (i1=0; i1<7; i1++) {
      *(shift)= 1.000000;
      shift+=1;
    }
  }
  for (forall_i1[0]=0; forall_i1[0]<0+11; forall_i1[0]++) {
    temp6=(double *) get_mem((21)*sizeof(double));
    shift=temp6+0*7+0;
    offset0=_in1+(min(forall_i1[0],9))*21+0*7+0;
    for (i0=0; i0<(min(1,(9)-(min(forall_i1[0],9)))); i0++) {
      for (i1=0; i1<3; i1++) {
        for (i2=0; i2<7; i2++) {
          *(shift)= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      offset0+=0;
    }
    shift=temp6+(min(1,(9)-(min(forall_i1[0],9))))*7+0;
    offset0=_in2+((forall_i1[0])-(min(forall_i1[0],9)))*21+0*7+0;
    for (i0=0; i0<((1)-(min(1,(9)-(min(forall_i1[0],9))))); i0++) {
      for (i1=0; i1<3; i1++) {
        for (i2=0; i2<7; i2++) {
          *(shift)= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      offset0+=0;
    }
    shift=_out2+0*7+0;
    offset0=temp6+0*7+0;
    for (i0=0; i0<3; i0++) {
      for (i1=0; i1<7; i1++) {
        *(shift)*= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    free(temp6);
  }


/*******
out3= *red ( rav in2)
********/

  shift=_out3+0;
  *(shift)= 1.000000;
  for (forall_i2[0]=0; forall_i2[0]<0+42; forall_i2[0]++) {
    temp7=(double *) get_mem((42)*sizeof(double));
    shift=temp7+0;
    offset0=_in2+scalar0*21+0*7+0;
    *(shift)= *(offset0);
    shift=_out3+0;
    offset0=temp7+0;
    *(shift)*= *(offset0);
    free(temp7);
  }


}


