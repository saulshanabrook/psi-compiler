#include "moalib.e"

#include "network.h"

#include "picl.h"

heat2d(int _i, int _n, double _A[], double _lambda[])

{
  int p_,p_cont,p[3];
  int shift,offset;
  int i0;
  int i1;
  int i2;

  HOST_INIT(4);

  TRACE_START("heat");
  for (i0=0; i0<4; i0++) {  /* Send global integer */
    START_SEND(i0,sizeof(int));
    HOST_SEND(&_i,sizeof(int),i0);
    END_SEND();
    }
  for (i0=0; i0<4; i0++) {  /* Send global integer */
    START_SEND(i0,sizeof(int));
    HOST_SEND(&_n,sizeof(int),i0);
    END_SEND();
    }
  for (i0=0; i0<4; i0++) {  /* Send global integer */
    START_SEND(i0,sizeof(double));
    HOST_SEND(_lambda,sizeof(double),i0);
    END_SEND();
    }

/* Communications for Initial Data */

  i1=((((int) _n))/(4)+(((((int) _n))%(4))>0))*(((int) _n));
  i0=((int) _n)*((int) _n);
  for (i2=0; i2<2; i2++) p[i2]=0;
  do {
    p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
    offset=((((int) p[0+0]))*((((int) _n))/(4)+(((((int) _n))%(4))>0)))*(int) (((int) _n))+((((int) p[1+0]))*(((int) _n)));
i2=(i1<(i0-offset)) ? i1 : (i0-offset);
    HOST_SEND(_A+offset,i2*sizeof(double),p_);
    p[1+(0)]++;
    if (p[1+(0)]>=1) {
      p[1+(0)]=0;
      p[0+(0)]++;
      if (p[0+(0)]>=4) p_cont=FALSE;
      }
  } while (p_cont);
  TRACE_END();
}
