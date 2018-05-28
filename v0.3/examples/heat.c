#include <stdlib.h>
#include "moalib.e"

#include "distributed.h"

heat1d(int _i, int _n, float _A[], float _lambda[])

{
  float *offset0;
  float *offset1;
  float *offset2;
  int i0;
  int i1;
  int i2;
  float *shift;
  float _b[1];
  float _m_lambda[1];
  float p[1];
  float _ntwo[1];
  float _one[1];
  float consta0[1];
  float consta1[1];
  float *_A2;
  float _t[1];
  float tmp_vect0[1];
  float p[1];
  float const0[1];
  float const1[1];
  float const2[1];
  float lp[1];
  float bp[1];
  float tmp_vect1[1];
  float ip[1];
  float tmp_vect2[1];
  float s[1];
  float sp2[1];
  float c[1];
  float const3[1];
  float const4[1];
  float const5[1];
  float const6[1];
  float lpp[1];
  float ipp[1];
  float bpp[1];
  float tmp_vect3[1];
  float tmp_vect4[1];
  float s[1];
  float sp2[1];
  float c[1];
  float const7[1];
  float const8[1];
  float const9[1];
  float const10[1];
  float lpp[1];
  float ipp[1];
  float bpp[1];
  float tmp_vect5[1];
  float p[1];
  float const11[1];
  float const12[]={1};
  float const13[1];
  float const14[1];
  float lp[1];
  float bp[1];
  float tmp_vect6[1];
  float ip[1];
  float tmp_vect7[1];
  float s[1];
  float sp2[1];
  float c[1];
  float const15[1];
  float const16[1];
  float const17[1];
  float lpp[1];
  float ipp[1];
  float bpp[1];
  int br_in,tl_in,j_cont,p_cont,s_cont,out;
  int p_,sp_;
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
  float *buffer;

  NODE_INIT(4);

  RECV_HOST(&_i,sizeof(int)); 

  RECV_HOST(&_n,sizeof(int)); 

  RECV_HOST(_lambda,sizeof(float)); 

  /* Communications for Initial Data */

  _A=(float *) malloc(((((int) _n))/(4)+(((((int) _n))%(4))>0))*sizeof(float));
  i1=((((int) _n))/(4)+(((((int) _n))%(4))>0));
  RECV_HOST(_A,i1*sizeof(float));

/* Procedure body */

/*******
m_lambda=ntwo * lambda + one
********/

  shift=_m_lambda+0;
  offset1=_lambda+0;
  *(shift)= -2.000000;
  *(shift)*= *(offset1);
  *(shift)+= 1.000000;


/*******
b=<n> - <2.000000>
********/

  shift=_b+0;
  consta0[0]=(((int) _n));
  offset0=consta0+0;
  consta1[0]=2.000000;
  offset1=consta1+0;
  *(shift)= *(offset0);
  *(shift)-= *(offset1);


  _A2=(float *) malloc((((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0)))*sizeof(float));

  for (_t[0]=0; _t[0]<(((int) _i)); _t[0]++) {
/*******
A2=((b take (<0.000000> drop A)) + (b take (<2.000000> drop A))) * lambda
********/

    tmp_vect0[0+(0)]=((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0));
    buffer=(float *) malloc(((((int) _n)))*sizeof(float));
    for (i0=0; i0<(1); i0++) p[i0]=0;
    p_cont=TRUE;
    do {
            const0[0]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
      const1[0]=(((int) _b[0+0]));
      tl_in=TRUE;
      for (i0=0; i0<(1); i0++) {
        if (const0[i0]>=const1[i0]) out=TRUE;
      }
      const2[0]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
      br_in=TRUE;
      for (i0=0; i0<(1); i0++) {
        if (const2[i0]>=const1[i0]) br_in=FALSE;
      }
      if (tl_in&&br_in) {
        ip[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        lp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        bp[0+(0)]=(((int) tmp_vect0[0+0]));
      } else if (tl_in) {
        ip[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        lp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        bp[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
      } else if (br_in) {
        ip[0+(0)]=(0);
        lp[0+(0)]=(0);
        bp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
      } else {
        ip[0+(0)]=(0);
        lp[0+(0)]=(0);
        bp[0+(0)]=(0);
      }
      p_=p[0+(0)];
      if (MY_PROC()==p_) {
        shift=_A2+(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) lp[0+0]));
        for (i0=0; i0<bp[0+(0)]; i0++) {
          *(shift)*= _lambda[0+0];
          shift++;
        }
      }
      tmp_vect1[0+(0)]=((((int) _n))/(4)+(((((int) _n))%(4))>0));
      tmp_vect2[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect1[0+0])))*(((int) tmp_vect1[0+0]))))/(((int) tmp_vect1[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect1[0+0])))*(((int) tmp_vect1[0+0]))))%(((int) tmp_vect1[0+0])))>0));
      s_cont=TRUE;
      for (i0=0; i0<(1); i0++) s[i0]=0;
      do {
        c[0+(0)]=(((((int) tmp_vect1[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect1[0+0]))));
        sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect1[0+0]))+((int) s[0+0]))%(4));
        const3[0]=(((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0])));
        const4[0]=(((int) ip[0+0]));
        const5[0]=(((int) bp[0+0])+((int) ip[0+0]));
        tl_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const3[i0]<const4[i0]) tl_in=FALSE;
          if (const3[i0]>=const5[i0]) out=TRUE;
        }
        const6[0]=(((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0]))+((int) tmp_vect1[0+0]));
        br_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const6[i0]<const4[i0]) out=TRUE;
          if (const6[i0]>=const5[i0]) br_in=FALSE;
        }
        if (out) {
          ipp[0+(0)]=(0);
          lpp[0+(0)]=(0);
          bpp[0+(0)]=(0);
        }         else if (tl_in&&br_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0]))+((int) lp[0+0]));
          bpp[0+(0)]=(((3)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+((-3)*(((int) sp2[0+0])))*(((int) tmp_vect1[0+0]))+((int) tmp_vect1[0+0]));
        } else if (tl_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0]))+((int) lp[0+0]));
          bpp[0+(0)]=(((-1)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect1[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
        } else if (br_in) {
          ipp[0+(0)]=(((int) ip[0+0]));
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect1[0+0]))+((int) tmp_vect1[0+0]));
        } else {
          ipp[0+(0)]=(((int) ip[0+0]));
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=(((int) bp[0+0]));
        }
        sp_sp2[0+(0)];
        if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
          shift=_A2+(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) lpp[0+0]));
          offset0=_A+(((-1)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect1[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==p_) {
          RECV(buffer0,(((int) bpp[0+0]))*sizeof(float),sp_);
          shift=_A2+(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) lpp[0+0]));
          offset0=buffer0+0;
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==sp_) {
          shift=buffer0+0;
          offset0=_A+(((-1)*(((int) tmp_vect1[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect1[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)= *(offset0);
            offset0+=(1);
            shift++;
          }
          SEND(buffer0,(((int) bpp[0+0]))*sizeof(float),p_);
        }
        s[0+(0)]++;
        if (s[0+(0)]==tmp_vect2[0+(0)]) s_cont=FALSE;
      } while (s_cont);
      tmp_vect3[0+(0)]=(((int) tmp_vect1[0+0]));
      tmp_vect4[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect3[0+0])))*(((int) tmp_vect3[0+0]))))/(((int) tmp_vect3[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect3[0+0])))*(((int) tmp_vect3[0+0]))))%(((int) tmp_vect3[0+0])))>0));
      s_cont=TRUE;
      for (i0=0; i0<(1); i0++) s[i0]=0;
      do {
        c[0+(0)]=(((((int) tmp_vect3[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect3[0+0]))));
        sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect3[0+0]))+((int) s[0+0]))%(4));
        const7[0]=(((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0])));
        const8[0]=(((int) ip[0+0])+2);
        const9[0]=(((int) bp[0+0])+((int) ip[0+0])+2);
        tl_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const7[i0]<const8[i0]) tl_in=FALSE;
          if (const7[i0]>=const9[i0]) out=TRUE;
        }
        const10[0]=(((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0]))+((int) tmp_vect3[0+0]));
        br_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const10[i0]<const8[i0]) out=TRUE;
          if (const10[i0]>=const9[i0]) br_in=FALSE;
        }
        if (out) {
          ipp[0+(0)]=(0);
          lpp[0+(0)]=(0);
          bpp[0+(0)]=(0);
        }         else if (tl_in&&br_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0]))+((int) lp[0+0])+-2);
          bpp[0+(0)]=(((3)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+((-3)*(((int) sp2[0+0])))*(((int) tmp_vect3[0+0]))+((int) tmp_vect3[0+0]));
        } else if (tl_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0]))+((int) lp[0+0])+-2);
          bpp[0+(0)]=(((-1)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect3[0+0]))+((int) bp[0+0])+((int) ip[0+0])+2);
        } else if (br_in) {
          ipp[0+(0)]=(((int) ip[0+0])+2);
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect3[0+0]))+((int) tmp_vect3[0+0])+-2);
        } else {
          ipp[0+(0)]=(((int) ip[0+0])+2);
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=(((int) bp[0+0]));
        }
        sp_sp2[0+(0)];
        if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
          shift=_A2+(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) lpp[0+0]));
          offset0=_A+(((-1)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect3[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)+= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==p_) {
          RECV(buffer0,(((int) bpp[0+0]))*sizeof(float),sp_);
          shift=_A2+(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+((int) lpp[0+0]));
          offset0=buffer0+0;
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)+= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==sp_) {
          shift=buffer0+0;
          offset0=_A+(((-1)*(((int) tmp_vect3[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect3[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)= *(offset0);
            offset0+=(1);
            shift++;
          }
          SEND(buffer0,(((int) bpp[0+0]))*sizeof(float),p_);
        }
        s[0+(0)]++;
        if (s[0+(0)]==tmp_vect4[0+(0)]) s_cont=FALSE;
      } while (s_cont);
      p[0+(0)]++;
      if (p[0+(0)]==4) p_cont=FALSE;
    } while (p_cont);
    free(buffer);


/*******
<1.000000>A=(b take (<1.000000> drop A)) * m_lambda + A2
********/

    tmp_vect5[0+(0)]=(((int) tmp_vect3[0+0]));
    buffer=(float *) malloc(((((int) _b[0+0])))*sizeof(float));
    for (i0=0; i0<(1); i0++) p[i0]=0;
    p_cont=TRUE;
    do {
            const11[0]=((((int) p[0+0]))*(((int) tmp_vect5[0+0])));
      const13[0]=(((int) _b[0+0])+1);
      tl_in=TRUE;
      for (i0=0; i0<(1); i0++) {
        if (const11[i0]<const12[i0]) tl_in=FALSE;
        if (const11[i0]>=const13[i0]) out=TRUE;
      }
      const14[0]=((((int) p[0+0]))*(((int) tmp_vect5[0+0]))+((int) tmp_vect5[0+0]));
      br_in=TRUE;
      for (i0=0; i0<(1); i0++) {
        if (const14[i0]<const12[i0]) out=TRUE;
        if (const14[i0]>=const13[i0]) br_in=FALSE;
      }
      if (tl_in&&br_in) {
        ip[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect5[0+0]))+-1);
        lp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect5[0+0])));
        bp[0+(0)]=(((int) tmp_vect5[0+0]));
      } else if (tl_in) {
        ip[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect5[0+0]))+-1);
        lp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect5[0+0])));
        bp[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect5[0+0]))+((int) _b[0+0])+1);
      } else if (br_in) {
        ip[0+(0)]=(0);
        lp[0+(0)]=(1);
        bp[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect5[0+0]))+((int) tmp_vect5[0+0])+-1);
      } else {
        ip[0+(0)]=(0);
        lp[0+(0)]=(0);
        bp[0+(0)]=(0);
      }
      p_=p[0+(0)];
      if (MY_PROC()==p_) {
        shift=_A+(((-1)*(((int) p[0+0])))*(((int) tmp_vect5[0+0]))+((int) lp[0+0]));
        for (i0=0; i0<bp[0+(0)]; i0++) {
          *(shift)*= _m_lambda[0+0];
          shift++;
        }
      }
      tmp_vect6[0+(0)]=(((int) tmp_vect0[0+0]));
      tmp_vect7[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))/(((int) tmp_vect6[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))%(((int) tmp_vect6[0+0])))>0));
      s_cont=TRUE;
      for (i0=0; i0<(1); i0++) s[i0]=0;
      do {
        c[0+(0)]=(((((int) tmp_vect6[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect6[0+0]))));
        sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect6[0+0]))+((int) s[0+0]))%(4));
        const15[0]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
        const16[0]=(((int) bp[0+0])+((int) ip[0+0]));
        tl_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const15[i0]<ip[i0]) tl_in=FALSE;
          if (const15[i0]>=const16[i0]) out=TRUE;
        }
        const17[0]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
        br_in=TRUE;
        for (i0=0; i0<(1); i0++) {
          if (const17[i0]<ip[i0]) out=TRUE;
          if (const17[i0]>=const16[i0]) br_in=FALSE;
        }
        if (out) {
          ipp[0+(0)]=(0);
          lpp[0+(0)]=(0);
          bpp[0+(0)]=(0);
        }         else if (tl_in&&br_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) lp[0+0]));
          bpp[0+(0)]=(((3)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-3)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
        } else if (tl_in) {
          ipp[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          lpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) lp[0+0]));
          bpp[0+(0)]=(((-1)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
        } else if (br_in) {
          ipp[0+(0)]=(((int) ip[0+0]));
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
        } else {
          ipp[0+(0)]=(((int) ip[0+0]));
          lpp[0+(0)]=(((int) lp[0+0]));
          bpp[0+(0)]=(((int) bp[0+0]));
        }
        sp_sp2[0+(0)];
        if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
          shift=_A+(((-1)*(((int) p[0+0])))*(((int) tmp_vect5[0+0]))+((int) lpp[0+0]));
          offset0=_A2+(((-1)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)+= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==p_) {
          RECV(buffer0,(((int) bpp[0+0]))*sizeof(float),sp_);
          shift=_A+(((-1)*(((int) p[0+0])))*(((int) tmp_vect5[0+0]))+((int) lpp[0+0]));
          offset0=buffer0+0;
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)+= *(offset0);
            offset0+=(1);
            shift++;
          }
        } else if (MY_PROC()==sp_) {
          shift=buffer0+0;
          offset0=_A2+(((-1)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-4)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+((int) ipp[0+0]));
          for (i0=0; i0<bpp[0+(0)]; i0++) {
            *(shift)= *(offset0);
            offset0+=(1);
            shift++;
          }
          SEND(buffer0,(((int) bpp[0+0]))*sizeof(float),p_);
        }
        s[0+(0)]++;
        if (s[0+(0)]==tmp_vect7[0+(0)]) s_cont=FALSE;
      } while (s_cont);
      p[0+(0)]++;
      if (p[0+(0)]==4) p_cont=FALSE;
    } while (p_cont);
    free(buffer);


  }
  free(_A2);
}


