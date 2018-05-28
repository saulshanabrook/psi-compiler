#include "moalib.e"

#include "network.h"

test2(double _in1[], double _out1[])

{
  int p_,p_cont,p[3];
  int shift,offset;
  int i0;
  int i1;
  int i2;

  HOST_INIT(4);


/* Communications for Initial Data */

  i1=25;
  i0=100;
  for (i2=0; i2<1; i2++) p[i2]=0;
  p_cont=TRUE;
  do {
    p_=p[0+0];
    offset=((25)*(p[0+0]));
    i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_out1+offset,i2*sizeof(double),p_);
    p[0+0]++;
    if (p[0+0]>=4) p_cont=FALSE;
  } while (p_cont);
  i1=25;
  i0=100;
  for (i2=0; i2<1; i2++) p[i2]=0;
  p_cont=TRUE;
  do {
    p_=p[0+0];
    offset=((25)*(p[0+0]));
    i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_in1+offset,i2*sizeof(double),p_);
    p[0+0]++;
    if (p[0+0]>=4) p_cont=FALSE;
  } while (p_cont);
}
