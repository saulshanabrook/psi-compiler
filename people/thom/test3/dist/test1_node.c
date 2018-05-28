#include <stdlib.h>
#include "moalib.e"

#include "network.h"

test1()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double *_A;
  double *_C;
  int tmp_vect0[2];
  int tmp_vect1[2];
  int tmp_vect2[2];
  int tmp_vect3[2];
  int tmp_vect4[2];
  int tmp_vect5[2];
  int scalar0;
  int scalar1;
  int j_cont,p_cont,s_cont,out;
  int p_,sp_,mode,offset;
  int p[3];
  int c[3];
  int s[3];
  int sp2[3];
  int ip[3];
  int lp[3];
  int bp[3];
  int ipp[3];
  int lpp[3];
  int bpp[3];

  NODE_INIT(4);

  /* Communications for Initial Data */

  _C=(double *) get_mem(10*40*sizeof(double));
  i1=10*40;
  RECV_HOST(_C,i1*sizeof(double));
  _A=(double *) get_mem(10*40*sizeof(double));
  i1=10*40;
  RECV_HOST(_A,i1*sizeof(double));

/* Procedure body */

  printout2(_A,MY_PROC());
/*******
C=A
********/

  tmp_vect0[0+0]=10;
  tmp_vect0[1+0]=40;
  for (i0=0; i0<2; i0++) p[i0]=0;
  p[0]=MY_PROC();
  tmp_vect1[0+0]=0;
  tmp_vect1[1+0]=0;
  tmp_vect2[0+0]=40;
  tmp_vect2[1+0]=40;
  tmp_vect3[0+0]=((p[0+0])*(tmp_vect0[0+0]));
  tmp_vect3[1+0]=((p[1+0])*(tmp_vect0[1+0]));
  tmp_vect4[0+0]=((p[0+0])*(tmp_vect0[0+0])+tmp_vect0[0+0]);
  tmp_vect4[1+0]=((p[1+0])*(tmp_vect0[1+0])+tmp_vect0[1+0]);
  ip[0+0]=((p[0+0])*(tmp_vect0[0+0]));
  ip[1+0]=((p[1+0])*(tmp_vect0[1+0]));
  lp[0+0]=tmp_vect3[0+0];
  lp[1+0]=tmp_vect3[1+0];
  bp[0+0]=((-1)*(lp[0+0])+tmp_vect4[0+0]);
  bp[1+0]=((-1)*(lp[1+0])+tmp_vect4[1+0]);
  tmp_vect5[0+0]=10;
  tmp_vect5[1+0]=40;
  shift=_C+((-1)*(tmp_vect3[0+0])+lp[0+0])*tmp_vect0[1+0]+((-1)*(tmp_vect3[1+0])+lp[1+0]);
  offset0=_A+ip[0+0]*tmp_vect5[1+0]+ip[1+0];
  scalar0=(tmp_vect5[1+0]+(-1)*(bp[1+0]));
  scalar1=(tmp_vect0[1+0]+(-1)*(bp[1+0]));
  for (i0=0; i0<bp[0+0]; i0++) {
    for (i1=0; i1<bp[1+0]; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
    offset0+=scalar0;
    shift+=scalar1;
  }


  printout2(_C,MY_PROC());
}


