#include "moalib.e"

#include "network.h"

test1(double _A[], double _C[])

{
  int p_,p_cont,p[3];
  int shift,offset;
  int i0;
  int i1;
  int i2;

  HOST_INIT(4);


/* Communications for Initial Data */

  i1=10*40;
  i0=40*40;
  for (i2=0; i2<2; i2++) p[i2]=0;
  p_cont=TRUE;
  do {
    p_=p[1+0]+1*(p[0+0]);
    offset=((40)*(p[1+0]))+40*(((10)*(p[0+0])));
    i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_C+offset,i2*sizeof(double),p_);
    p[1+0]++;
    if (p[1+0]>=1) {
      p[1+0]=0;
      p[0+0]++;
      if (p[0+0]>=4) p_cont=FALSE;
      }
  } while (p_cont);
  i1=10*40;
  i0=40*40;
  for (i2=0; i2<2; i2++) p[i2]=0;
  p_cont=TRUE;
  do {
    p_=p[1+0]+1*(p[0+0]);
    offset=((40)*(p[1+0]))+40*(((10)*(p[0+0])));
    i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_A+offset,i2*sizeof(double),p_);
    p[1+0]++;
    if (p[1+0]>=1) {
      p[1+0]=0;
      p[0+0]++;
      if (p[0+0]>=4) p_cont=FALSE;
      }
  } while (p_cont);
}
