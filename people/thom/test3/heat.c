#include <stdlib.h>
#include "moalib.e"

heat2d(int _i, int _n, double _A[], double _lambda[])

{
  double *offset0;
  double *offset1;
  double *offset2;
  double *offset3;
  double *offset4;
  int i0;
  int i1;
  double *shift;
  double _b[2];
  double _m_lambda[1];
  double consta0[2];
  double consta1[2];
  double *_A2;
  double _t[1];
  int scalar0;
  int scalar1;
  int scalar2;
  int scalar3;

/*******
m_lambda=nfour * lambda + one
********/

  shift=_m_lambda+0;
  offset1=_lambda+0;
  *(shift)= -4.000000;
  *(shift)*= *(offset1);
  *(shift)+= 1.000000;


/*******
b=<n n> - <2.000000 2.000000>
********/

  shift=_b+0;
  consta0[0]=_n;
  consta0[1]=_n;
  offset0=consta0+0;
  consta1[0]=2.000000;
  consta1[1]=2.000000;
  offset1=consta1+0;
  for (i0=0; i0<2; i0++) {
    *(shift)= *(offset0);
    *(shift)-= *(offset1);
    offset1+=1;
    offset0+=1;
    shift+=1;
  }


  _A2=(double *) get_mem((_b[0+0]*_b[1+0])*sizeof(double));

  for (_t[0]=0; _t[0]<_i; _t[0]++) {
/*******
A2=((b take (<1.000000 2.000000> drop A)) + (b take (<1.000000 0.000000> drop A)) + (b take (<2.000000 1.000000> drop A)) + (b take (<0.000000 1.000000> drop A))) * lambda
********/

    shift=_A2+0*_b[1+0]+0;
    offset0=_A+1*_n+2;
    scalar0=(_n+(-1)*(_b[1+0]));
    offset1=_A+1*_n+0;
    scalar1=(_n+(-1)*(_b[1+0]));
    offset2=_A+2*_n+1;
    scalar2=(_n+(-1)*(_b[1+0]));
    offset3=_A+0*_n+1;
    scalar3=(_n+(-1)*(_b[1+0]));
    for (i0=0; i0<(int) _b[0+0]; i0++) {
      for (i1=0; i1<(int) _b[1+0]; i1++) {
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        *(shift)+= *(offset2);
        *(shift)+= *(offset3);
        *(shift)*= _lambda[0+0];
        offset3+=1;
        offset2+=1;
        offset1+=1;
        offset0+=1;
        shift+=1;
      }
      offset3+=scalar3;
      offset2+=scalar2;
      offset1+=scalar1;
      offset0+=scalar0;
      shift+=0;
    }


/*******
<1.000000 1.000000> pdrop A=(b take (<1.000000 1.000000> drop A)) * m_lambda + A2
********/

    shift=_A+1*_n+1;
    offset1=_A2+0*_b[1+0]+0;
    scalar0=(_n+(-1)*(_b[1+0]));
    for (i0=0; i0<_b[0+0]; i0++) {
      for (i1=0; i1<_b[1+0]; i1++) {
        *(shift)*= _m_lambda[0+0];
        *(shift)+= *(offset1);
        offset1+=1;
        shift+=1;
      }
      offset1+=0;
      shift+=scalar0;
    }


  }
  free(_A2);
}


