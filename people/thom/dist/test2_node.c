#include <stdlib.h>
#include "moalib.e"

#include "network.h"

test2()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double *_in1;
  double *_out1;
  int tmp_vect0[1];
  int tmp_vect1[1];
  int tmp_vect2[1];
  int tmp_vect3[1];
  int tmp_vect4[1];
  int tmp_vect5[1];
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

  _out1=(double *) get_mem(25*sizeof(double));
  i1=25;
  RECV_HOST(_out1,i1*sizeof(double));
  _in1=(double *) get_mem(25*sizeof(double));
  i1=25;
  RECV_HOST(_in1,i1*sizeof(double));

/* Procedure body */

  printout(_in1);
/*******
out1=in1
********/

  tmp_vect0[0+0]=25;
  for (i0=0; i0<1; i0++) p[i0]=0;
  p[0]=MY_PROC();
  tmp_vect1[0+0]=0;
  tmp_vect2[0+0]=100;
  tmp_vect3[0+0]=((p[0+0])*(tmp_vect0[0+0]));
  tmp_vect4[0+0]=((p[0+0])*(tmp_vect0[0+0])+tmp_vect0[0+0]);
  ip[0+0]=((p[0+0])*(tmp_vect0[0+0]));
  lp[0+0]=tmp_vect3[0+0];
  bp[0+0]=((-1)*(lp[0+0])+tmp_vect4[0+0]);
  tmp_vect5[0+0]=25;
  shift=_out1+((-1)*(tmp_vect3[0+0])+lp[0+0]);
  offset0=_in1+ip[0+0];
  for (i0=0; i0<bp[0+0]; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


  printout(_out1);
}


