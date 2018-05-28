#include "moalib.e"

#include "network.h"

heat1d(int _i, int _n, float _A[], float _lambda[])

{
  int p_,p_cont,p[3];
  int shift,offset;
  int i0;
  int i1;
  int i2;

  HOST_INIT(4);

  for (i0=0; i0<4; i0++)
    /* Send global integer */
    HOST_SEND(&_i,sizeof(int),i0);
  for (i0=0; i0<4; i0++)
    /* Send global integer */
    HOST_SEND(&_n,sizeof(int),i0);
  for (i0=0; i0<4; i0++)
    /* Send global integer */
    HOST_SEND(_lambda,sizeof(float),i0);

/* Communications for Initial Data */

  i1=((((int) _n))/(4)+(((((int) _n))%(4))>0));
  i0=((int) _n);
  for (i2=0; i2<1; i2++) p[i2]=0;
  do {
    p_=p[0+(0)];
    offset=((((int) p[0+0]))*((((int) _n))/(4)+(((((int) _n))%(4))>0)));
i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_A+offset,i2*sizeof(float),p_);
    p[0+(0)]++;
    if (p[0+(0)]==4) p_cont=FALSE;
  } while (p_cont);
}
