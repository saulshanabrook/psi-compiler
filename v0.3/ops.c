#include <stdlib.h>
#include "moalib.e"

omega_red(double _in[], double _out1[], double _out2[], double _out3[], double _out4[], double _out5[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[2];
  int forall_i3[1];
  double *temp2;
  double *temp1;
  double *temp3;

/*******
out5=( +  omega <2.000000> in) + ( *  omega <1.000000> in)
********/

  temp2=(double *) get_mem(()*sizeof(double));
  for (forall_i0[0]=0; forall_i0[0]<0+(5); forall_i0[0]++) {
    temp1=(double *) get_mem((5)*sizeof(double));
    shift=_out5+(((int) forall_i0[0+0]))*(int) (5)+(0);
    for (i1=0; i1<5; i1++) {
      *(shift)= 0.000000;
      shift++;
    }
    for (forall_i1[0]=0; forall_i1[0]<0+(5); forall_i1[0]++) {
      shift=temp1+0;
      offset0=_in+(((int) forall_i0[0+0]))*(int) 25+(((int) forall_i1[0+0]))*(int) 5+(0);
      for (i2=0; i2<5; i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
      shift=_out5+(((int) forall_i0[0+0]))*(int) 5+(0);
      offset0=temp1+0;
      for (i0=0; i0<(5); i0++) {
        *(shift)+= *(offset0);
        offset0+=(1);
        shift++;
      }
    }
    free(temp1);
  }
  for (forall_i2[0]=0; forall_i2[0]<0+(5); forall_i2[0]++) {
    for (forall_i2[1]=0; forall_i2[1]<0+(5); forall_i2[1]++) {
      temp3=(double *) get_mem((1)*sizeof(double));
      temp2= 1.000000;
      for (forall_i3[0]=0; forall_i3[0]<0+(5); forall_i3[0]++) {
        shift=temp3+0;
        offset0=_in+(((int) forall_i2[0+0]))*(int) 25+(((int) forall_i2[1+0]))*(int) 5+(((int) forall_i3[0+0]));
        *(shift)= *(offset0);
        offset0=temp3+0;
        temp2*= *(offset0);
      }
      shift=_out5+(int) forall_i2[0+(0)]*(int) 5+(int) forall_i2[1+(0)];
      *(shift)+= temp2;
      free(temp3);
    }
  }
  free(temp2);


}


