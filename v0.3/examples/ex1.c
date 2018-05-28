#include <stdlib.h>
#include "moalib.e"

main()

{
  float *offset0;
  float *offset1;
  int i0;
  int i1;
  int i2;
  float *shift;
  float _RAMY[]={1.000000, 2.000000, 3.000000, 4.000000, 5.000000, 6.000000, 7.000000, 8.000000, 9.000000, 10.000000, 11.000000, 12.000000, 1.000000, 2.000000, 3.000000, 4.000000, 5.000000, 6.000000, 7.000000, 8.000000, 9.000000, 10.000000, 11.000000, 12.000000};
  float _AMY[]={9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000, 9.000000};
  float _Y[]={8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000, 8.000000};
  float _V[]={1.000000, 1.000000};
  int forall_i0[2];
  int forall_i0[2];
  float _Ams[2*3*4];
  float _RAMY[2*3*4];
  float _AMY[2*3*4];
  float _Amts[2*3*8];
  float _Y[2*3*4];
  float _A[8];

/*******
Ams=RAMY + AMY
********/

  shift=_Ams+0*(3)+0*(4)+0;
  offset0=_RAMY+0*12+0*4+0;
  offset1=_AMY+0*12+0*4+0;
  for (i0=0; i0<(2); i0++) {
    for (i1=0; i1<(3); i1++) {
      for (i2=0; i2<(4); i2++) {
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        offset1+=(1);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
Amts=Y cat  omega <1.000000 1.000000> (Ams + RAMY)
********/

  for (forall_i0[0]=0; forall_i0[0]<0+2; forall_i0[0]++) {
    for (forall_i0[1]=0; forall_i0[1]<0+3; forall_i0[1]++) {
      shift=_Amts+(forall_i0[0+0])*(3)+(forall_i0[1+0])*(8)+(0);
      offset0=_Y+(forall_i0[0+0])*12+(forall_i0[1+0])*4+(0);
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
      shift=_Amts+(forall_i0[0+0])*24+(forall_i0[1+0])*8+(4);
      offset0=_Ams+(forall_i0[0+0])*12+(forall_i0[1+0])*4+(0);
      offset1=_RAMY+(forall_i0[0+0])*12+(forall_i0[1+0])*4+(0);
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        offset1+=(1);
        offset0+=(1);
        shift++;
      }
    }
  }


/*******
A=V psi Amts
********/

  shift=_A+0;
  offset0=_Amts+1*24+1*8+0;
  for (i2=0; i2<8; i2++) {
    *(shift)= *(offset0);
    offset0+=(1);
    shift++;
  }


/*******
Amts=<2.000000> take (<2.000000> drop (RAMY cat AMY))
********/

  shift=_Amts+0*(3)+0*(8)+0;
  offset0=_AMY+0*12+0*4+0;
  for (i0=0; i0<2; i0++) {
    for (i1=0; i1<3; i1++) {
      for (i2=0; i2<4; i2++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
      shift+=4;
    }
  }


}


