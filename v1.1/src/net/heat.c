#include <stdlib.h>
#include "moalib.e"

#include "network.h"

#include "picl.h"

heat2d()

{
  double *offset0;
  double *offset1;
  double *offset2;
  int i0;
  int i1;
  int i2;
  double *shift;
  int _i;
  int _n;
  double *_A;
  double *_lambda;
    double _b[2];
    double _m_lambda[1];
  double consta0[2];
  double consta1[2];
  double *_A2;
  double _t[1];
  int tmp_vect0[2];
  int tmp_vect1[2];
  int tmp_vect2[2];
  int tmp_vect3[2];
  int tmp_vect4[2];
  int tmp_vect5[2];
  int tmp_vect6[2];
  int tmp_vect7[2];
  int tmp_vect8[2];
  int tmp_vect9[2];
  int tmp_vect10[2];
  int tmp_vect11[2];
  int tmp_vect12[2];
  int tmp_vect13[2];
  int tmp_vect14[2];
  int scalar0;
  int scalar1;
  int tmp_vect15[2];
  int tmp_vect16[2];
  int tmp_vect17[2];
  int tmp_vect18[2];
  int tmp_vect19[2];
  int tmp_vect20[2];
  int tmp_vect21[2];
  int tmp_vect22[2];
  int tmp_vect23[2];
  int tmp_vect24[2];
  int tmp_vect25[2];
  int tmp_vect26[2];
  int tmp_vect27[2];
  int tmp_vect28[2];
  int tmp_vect29[2];
  int tmp_vect30[2];
  int tmp_vect31[2];
  int tmp_vect32[2];
  int tmp_vect33[2];
  int tmp_vect34[2];
  int tmp_vect35[2];
  int tmp_vect36[2];
  int tmp_vect37[2];
  int tmp_vect38[2];
  int tmp_vect39[2];
  int tmp_vect40[2];
  int tmp_vect41[2];
  int tmp_vect42[2];
  int tmp_vect43[2];
  int tmp_vect44[2];
  int tmp_vect45[2];
  int tmp_vect46[2];
  int tmp_vect47[2];
  int tmp_vect48[2];
  int tmp_vect49[2];
  int tmp_vect50[2];
  int tmp_vect51[2];
  int tmp_vect52[2];
  int tmp_vect53[2];
  int tmp_vect54[2];
  int tmp_vect55[2];
  int tmp_vect56[2];
  int tmp_vect57[2];
  int tmp_vect58[2];
  int tmp_vect59[2];
  int tmp_vect60[2];
  int tmp_vect61[2];
  int tmp_vect62[2];
  int tmp_vect63[2];
  int tmp_vect64[2];
  int tmp_vect65[2];
  int tmp_vect66[2];
  int tmp_vect67[2];
  int const0[]={1,1};
  int tmp_vect68[2];
  int tmp_vect69[2];
  int tmp_vect70[2];
  int tmp_vect71[2];
  int tmp_vect72[2];
  int tmp_vect73[2];
  int tmp_vect74[2];
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
  double *buffer0r[4],*buffer0s[4];

  NODE_INIT(4);

  TRACE_START("heat");
  START_RECV();
  RECV_HOST(&_i,sizeof(int)); 
  END_RECV(-1,sizeof(int));

  START_RECV();
  RECV_HOST(&_n,sizeof(int)); 
  END_RECV(-1,sizeof(int));

  START_RECV();
  _lambda=(double *) get_mem(sizeof(double));
  RECV_HOST(_lambda,sizeof(double)); 
  END_RECV(-1,sizeof(double));

  /* Communications for Initial Data */

  _A=(double *) get_mem(((((int) _n))/(4)+(((((int) _n))%(4))>0))*(((int) _n))*sizeof(double));
    i1=((((int) _n))/(4)+(((((int) _n))%(4))>0))*(((int) _n));
  RECV_HOST(_A,i1*sizeof(double));

/* Procedure body */

/*******
m_lambda=nfour * lambda +  + one
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
  consta0[0]=(((int) _n));
  consta0[1]=(((int) _n));
  offset0=consta0+0;
  consta1[0]=2.000000;
  consta1[1]=2.000000;
  offset1=consta1+0;
  for (i0=0; i0<(2); i0++) {
    *(shift)= *(offset0);
    *(shift)-= *(offset1);
    offset1+=1;
    offset0+=1;
    shift+=1;
  }


  _A2=(double *) get_mem((((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0))*(((int) _b[1+0])))*sizeof(double));

  for (_t[0]=0; _t[0]<(((int) _i)); _t[0]++) {
/*******
A2=((b take (<1.000000 2.000000> drop A)) +  + (b take (<1.000000 0.000000> drop A)) +  + (b take (<2.000000 1.000000> drop A)) +  + (b take (<0.000000 1.000000> drop A))) * lambda
********/

    tmp_vect0[0+(0)]=((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0));
    tmp_vect0[1+(0)]=(((int) _b[1+0]));
    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect1[0+(0)]=(0);
        tmp_vect1[1+(0)]=(0);
        tmp_vect2[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect2[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0])));
        tmp_vect3[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect3[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect4[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect4[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect5[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
        tmp_vect5[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) _b[1+0]));
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect2[i0]>=_b[i0]) out=TRUE;
        }
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect3[i0]<tmp_vect1[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          ip[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          lp[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0])))+((int) tmp_vect1[0+0]));
          lp[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0])))+((int) tmp_vect1[1+0]));
          bp[0+(0)]=(((((((int) tmp_vect4[0+0]))>0))*(((int) tmp_vect5[0+0]))+((int) tmp_vect3[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect4[1+0]))>0))*(((int) tmp_vect5[1+0]))+((int) tmp_vect3[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        tmp_vect6[0+(0)]=((((int) _n))/(4)+(((((int) _n))%(4))>0));
        tmp_vect6[1+(0)]=(((int) _n));
        tmp_vect7[0+(0)]=(((((int) ip[0+0])+1+((int) bp[0+0]))-(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))/(((int) tmp_vect6[0+0]))+((((((int) ip[0+0])+1+((int) bp[0+0]))-(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))%(((int) tmp_vect6[0+0])))>0));
        tmp_vect7[1+(0)]=(((((int) ip[1+0])+2+((int) bp[1+0]))-(((((int) ip[1+0])+2)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))/(((int) tmp_vect6[1+0]))+((((((int) ip[1+0])+2+((int) bp[1+0]))-(((((int) ip[1+0])+2)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))%(((int) tmp_vect6[1+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(2); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect6[0+0]))*(((int) s[0+0]))+((int) ip[0+0])+1)/((4)*(((int) tmp_vect6[0+0]))));
          c[1+(0)]=(((((int) tmp_vect6[1+0]))*(((int) s[1+0]))+((int) ip[1+0])+2)/(((int) tmp_vect6[1+0])));
          sp2[0+(0)]=(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0]))+((int) s[0+0]))%(4));
          sp2[1+(0)]=(((((int) ip[1+0])+2)/(((int) tmp_vect6[1+0]))+((int) s[1+0]))%(1));
          tmp_vect8[0+(0)]=(((int) ip[0+0])+1);
          tmp_vect8[1+(0)]=(((int) ip[1+0])+2);
          tmp_vect9[0+(0)]=(((int) bp[0+0])+((int) ip[0+0])+1);
          tmp_vect9[1+(0)]=(((int) bp[1+0])+((int) ip[1+0])+2);
          tmp_vect10[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          tmp_vect10[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0])));
          tmp_vect11[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
          tmp_vect11[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
          tmp_vect12[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+-1);
          tmp_vect12[1+(0)]=((-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+-2);
          tmp_vect13[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0])+-1);
          tmp_vect13[1+(0)]=((-1)*(((int) bp[1+0]))+(-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0])+-2);
          tmp_vect14[0+(0)]=(((-4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) bp[0+0])+((int) ip[0+0])+1);
          tmp_vect14[1+(0)]=(((-1)*(((int) tmp_vect6[1+0])))*(((int) c[1+0]))+((-1)*(((int) sp2[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) bp[1+0])+((int) ip[1+0])+2);
          out=FALSE;
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect10[i0]>=tmp_vect9[i0]) out=TRUE;
          }
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect11[i0]<tmp_vect8[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            ipp[1+(0)]=(0);
            lpp[0+(0)]=(0);
            lpp[1+(0)]=(0);
            bpp[0+(0)]=(0);
            bpp[1+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect12[0+0]))>0))*(((int) tmp_vect12[0+0]))+((int) tmp_vect8[0+0]));
            ipp[1+(0)]=((((((int) tmp_vect12[1+0]))>0))*(((int) tmp_vect12[1+0]))+((int) tmp_vect8[1+0]));
            lpp[0+(0)]=((((((int) tmp_vect12[0+0]))>0))*(((int) tmp_vect12[0+0]))+((int) lp[0+0]));
            lpp[1+(0)]=((((((int) tmp_vect12[1+0]))>0))*(((int) tmp_vect12[1+0]))+((int) lp[1+0]));
            bpp[0+(0)]=(((((((int) tmp_vect13[0+0]))>0))*(((int) tmp_vect14[0+0]))+((int) tmp_vect11[0+0]))-(((int) ipp[0+0])));
            bpp[1+(0)]=(((((((int) tmp_vect13[1+0]))>0))*(((int) tmp_vect14[1+0]))+((int) tmp_vect11[1+0]))-(((int) ipp[1+0])));
          }
          sp_=(int) sp2[0+(0)]*(int) 1+(int) sp2[1+(0)];
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect2[0+0]))+((int) lpp[0+0]))*(int) (int) tmp_vect0[1+(0)]+((-1)*(((int) tmp_vect2[1+0]))+((int) lpp[1+0]));
              offset0=_A+((-1)*(((int) tmp_vect10[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect10[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              scalar1=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=((int) scalar1);
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              START_RECV();
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double),sp_);
              END_RECV(sp_,(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double));
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect2[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect2[1+0]))+((int) lpp[1+0]));
              offset0=buffer0r[sp_]+0*(int) (((int) bpp[1+0]))+0;
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=0;
                shift+=((int) scalar0);
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              shift=buffer0s[sp_]+0*(int) (int) bpp[1+(0)]+0;
              offset0=_A+((-1)*(((int) tmp_vect10[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect10[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=0;
              }
              START_SEND(p_,sizeof(double)*((((int) bpp[1+0]))*(((int) bpp[0+0]))));
              SEND(buffer0s[sp_],((((int) bpp[1+0]))*(((int) bpp[0+0])))*sizeof(double),p_);
              END_SEND();
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[1+(0)]++;
          if (s[1+(0)]>=tmp_vect7[1+(0)]) {
            s[1+(0)]=0;
            s[0+(0)]++;
            if (s[0+(0)]>=tmp_vect7[0+(0)]) s_cont=FALSE;
            }
        } while (s_cont);
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect15[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect15[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0])));
        tmp_vect16[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect16[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect17[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect17[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect18[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
        tmp_vect18[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) _b[1+0]));
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect15[i0]>=_b[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          ip[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          lp[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          lp[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          bp[0+(0)]=(((((((int) tmp_vect17[0+0]))>0))*(((int) tmp_vect18[0+0]))+((int) tmp_vect16[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect17[1+0]))>0))*(((int) tmp_vect18[1+0]))+((int) tmp_vect16[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        tmp_vect19[0+(0)]=(((((int) ip[0+0])+1+((int) bp[0+0]))-(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))/(((int) tmp_vect6[0+0]))+((((((int) ip[0+0])+1+((int) bp[0+0]))-(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))%(((int) tmp_vect6[0+0])))>0));
        tmp_vect19[1+(0)]=(((((int) ip[1+0])+((int) bp[1+0]))-(((((int) ip[1+0]))/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))/(((int) tmp_vect6[1+0]))+((((((int) ip[1+0])+((int) bp[1+0]))-(((((int) ip[1+0]))/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))%(((int) tmp_vect6[1+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(2); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect6[0+0]))*(((int) s[0+0]))+((int) ip[0+0])+1)/((4)*(((int) tmp_vect6[0+0]))));
          c[1+(0)]=(((((int) tmp_vect6[1+0]))*(((int) s[1+0]))+((int) ip[1+0]))/(((int) tmp_vect6[1+0])));
          sp2[0+(0)]=(((((int) ip[0+0])+1)/(((int) tmp_vect6[0+0]))+((int) s[0+0]))%(4));
          sp2[1+(0)]=(((((int) ip[1+0]))/(((int) tmp_vect6[1+0]))+((int) s[1+0]))%(1));
          tmp_vect20[0+(0)]=(((int) ip[0+0])+1);
          tmp_vect20[1+(0)]=(((int) ip[1+0]));
          tmp_vect21[0+(0)]=(((int) bp[0+0])+((int) ip[0+0])+1);
          tmp_vect21[1+(0)]=(((int) bp[1+0])+((int) ip[1+0]));
          tmp_vect22[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          tmp_vect22[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0])));
          tmp_vect23[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
          tmp_vect23[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
          tmp_vect24[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+-1);
          tmp_vect24[1+(0)]=((-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0])));
          tmp_vect25[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0])+-1);
          tmp_vect25[1+(0)]=((-1)*(((int) bp[1+0]))+(-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
          tmp_vect26[0+(0)]=(((-4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) bp[0+0])+((int) ip[0+0])+1);
          tmp_vect26[1+(0)]=(((-1)*(((int) tmp_vect6[1+0])))*(((int) c[1+0]))+((-1)*(((int) sp2[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) bp[1+0])+((int) ip[1+0]));
          out=FALSE;
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect22[i0]>=tmp_vect21[i0]) out=TRUE;
          }
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect23[i0]<tmp_vect20[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            ipp[1+(0)]=(0);
            lpp[0+(0)]=(0);
            lpp[1+(0)]=(0);
            bpp[0+(0)]=(0);
            bpp[1+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect24[0+0]))>0))*(((int) tmp_vect24[0+0]))+((int) tmp_vect20[0+0]));
            ipp[1+(0)]=((((((int) tmp_vect24[1+0]))>0))*(((int) tmp_vect24[1+0]))+((int) tmp_vect20[1+0]));
            lpp[0+(0)]=((((((int) tmp_vect24[0+0]))>0))*(((int) tmp_vect24[0+0]))+((int) lp[0+0]));
            lpp[1+(0)]=((((((int) tmp_vect24[1+0]))>0))*(((int) tmp_vect24[1+0]))+((int) lp[1+0]));
            bpp[0+(0)]=(((((((int) tmp_vect25[0+0]))>0))*(((int) tmp_vect26[0+0]))+((int) tmp_vect23[0+0]))-(((int) ipp[0+0])));
            bpp[1+(0)]=(((((((int) tmp_vect25[1+0]))>0))*(((int) tmp_vect26[1+0]))+((int) tmp_vect23[1+0]))-(((int) ipp[1+0])));
          }
          sp_=(int) sp2[0+(0)]*(int) 1+(int) sp2[1+(0)];
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect15[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect15[1+0]))+((int) lpp[1+0]));
              offset0=_A+((-1)*(((int) tmp_vect22[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect22[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              scalar1=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=((int) scalar1);
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              START_RECV();
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double),sp_);
              END_RECV(sp_,(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double));
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect15[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect15[1+0]))+((int) lpp[1+0]));
              offset0=buffer0r[sp_]+0*(int) (((int) bpp[1+0]))+0;
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=0;
                shift+=((int) scalar0);
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              shift=buffer0s[sp_]+0*(int) (int) bpp[1+(0)]+0;
              offset0=_A+((-1)*(((int) tmp_vect22[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect22[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=0;
              }
              START_SEND(p_,sizeof(double)*((((int) bpp[1+0]))*(((int) bpp[0+0]))));
              SEND(buffer0s[sp_],((((int) bpp[1+0]))*(((int) bpp[0+0])))*sizeof(double),p_);
              END_SEND();
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[1+(0)]++;
          if (s[1+(0)]>=tmp_vect19[1+(0)]) {
            s[1+(0)]=0;
            s[0+(0)]++;
            if (s[0+(0)]>=tmp_vect19[0+(0)]) s_cont=FALSE;
            }
        } while (s_cont);
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect27[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect27[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0])));
        tmp_vect28[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect28[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect29[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect29[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect30[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
        tmp_vect30[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) _b[1+0]));
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect27[i0]>=_b[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          ip[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          lp[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          lp[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          bp[0+(0)]=(((((((int) tmp_vect29[0+0]))>0))*(((int) tmp_vect30[0+0]))+((int) tmp_vect28[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect29[1+0]))>0))*(((int) tmp_vect30[1+0]))+((int) tmp_vect28[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        tmp_vect31[0+(0)]=(((((int) ip[0+0])+2+((int) bp[0+0]))-(((((int) ip[0+0])+2)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))/(((int) tmp_vect6[0+0]))+((((((int) ip[0+0])+2+((int) bp[0+0]))-(((((int) ip[0+0])+2)/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))%(((int) tmp_vect6[0+0])))>0));
        tmp_vect31[1+(0)]=(((((int) ip[1+0])+1+((int) bp[1+0]))-(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))/(((int) tmp_vect6[1+0]))+((((((int) ip[1+0])+1+((int) bp[1+0]))-(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))%(((int) tmp_vect6[1+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(2); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect6[0+0]))*(((int) s[0+0]))+((int) ip[0+0])+2)/((4)*(((int) tmp_vect6[0+0]))));
          c[1+(0)]=(((((int) tmp_vect6[1+0]))*(((int) s[1+0]))+((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])));
          sp2[0+(0)]=(((((int) ip[0+0])+2)/(((int) tmp_vect6[0+0]))+((int) s[0+0]))%(4));
          sp2[1+(0)]=(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0]))+((int) s[1+0]))%(1));
          tmp_vect32[0+(0)]=(((int) ip[0+0])+2);
          tmp_vect32[1+(0)]=(((int) ip[1+0])+1);
          tmp_vect33[0+(0)]=(((int) bp[0+0])+((int) ip[0+0])+2);
          tmp_vect33[1+(0)]=(((int) bp[1+0])+((int) ip[1+0])+1);
          tmp_vect34[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          tmp_vect34[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0])));
          tmp_vect35[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
          tmp_vect35[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
          tmp_vect36[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+-2);
          tmp_vect36[1+(0)]=((-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+-1);
          tmp_vect37[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0])+-2);
          tmp_vect37[1+(0)]=((-1)*(((int) bp[1+0]))+(-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0])+-1);
          tmp_vect38[0+(0)]=(((-4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) bp[0+0])+((int) ip[0+0])+2);
          tmp_vect38[1+(0)]=(((-1)*(((int) tmp_vect6[1+0])))*(((int) c[1+0]))+((-1)*(((int) sp2[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) bp[1+0])+((int) ip[1+0])+1);
          out=FALSE;
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect34[i0]>=tmp_vect33[i0]) out=TRUE;
          }
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect35[i0]<tmp_vect32[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            ipp[1+(0)]=(0);
            lpp[0+(0)]=(0);
            lpp[1+(0)]=(0);
            bpp[0+(0)]=(0);
            bpp[1+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect36[0+0]))>0))*(((int) tmp_vect36[0+0]))+((int) tmp_vect32[0+0]));
            ipp[1+(0)]=((((((int) tmp_vect36[1+0]))>0))*(((int) tmp_vect36[1+0]))+((int) tmp_vect32[1+0]));
            lpp[0+(0)]=((((((int) tmp_vect36[0+0]))>0))*(((int) tmp_vect36[0+0]))+((int) lp[0+0]));
            lpp[1+(0)]=((((((int) tmp_vect36[1+0]))>0))*(((int) tmp_vect36[1+0]))+((int) lp[1+0]));
            bpp[0+(0)]=(((((((int) tmp_vect37[0+0]))>0))*(((int) tmp_vect38[0+0]))+((int) tmp_vect35[0+0]))-(((int) ipp[0+0])));
            bpp[1+(0)]=(((((((int) tmp_vect37[1+0]))>0))*(((int) tmp_vect38[1+0]))+((int) tmp_vect35[1+0]))-(((int) ipp[1+0])));
          }
          sp_=(int) sp2[0+(0)]*(int) 1+(int) sp2[1+(0)];
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect27[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect27[1+0]))+((int) lpp[1+0]));
              offset0=_A+((-1)*(((int) tmp_vect34[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect34[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              scalar1=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=((int) scalar1);
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              START_RECV();
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double),sp_);
              END_RECV(sp_,(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double));
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect27[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect27[1+0]))+((int) lpp[1+0]));
              offset0=buffer0r[sp_]+0*(int) (((int) bpp[1+0]))+0;
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=0;
                shift+=((int) scalar0);
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              shift=buffer0s[sp_]+0*(int) (int) bpp[1+(0)]+0;
              offset0=_A+((-1)*(((int) tmp_vect34[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect34[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=0;
              }
              START_SEND(p_,sizeof(double)*((((int) bpp[1+0]))*(((int) bpp[0+0]))));
              SEND(buffer0s[sp_],((((int) bpp[1+0]))*(((int) bpp[0+0])))*sizeof(double),p_);
              END_SEND();
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[1+(0)]++;
          if (s[1+(0)]>=tmp_vect31[1+(0)]) {
            s[1+(0)]=0;
            s[0+(0)]++;
            if (s[0+(0)]>=tmp_vect31[0+(0)]) s_cont=FALSE;
            }
        } while (s_cont);
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect39[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect39[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0])));
        tmp_vect40[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect40[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect41[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect41[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect42[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
        tmp_vect42[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) _b[1+0]));
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect39[i0]>=_b[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          ip[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          lp[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          lp[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          bp[0+(0)]=(((((((int) tmp_vect41[0+0]))>0))*(((int) tmp_vect42[0+0]))+((int) tmp_vect40[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect41[1+0]))>0))*(((int) tmp_vect42[1+0]))+((int) tmp_vect40[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        tmp_vect43[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))/(((int) tmp_vect6[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect6[0+0])))*(((int) tmp_vect6[0+0]))))%(((int) tmp_vect6[0+0])))>0));
        tmp_vect43[1+(0)]=(((((int) ip[1+0])+1+((int) bp[1+0]))-(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))/(((int) tmp_vect6[1+0]))+((((((int) ip[1+0])+1+((int) bp[1+0]))-(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])))*(((int) tmp_vect6[1+0]))))%(((int) tmp_vect6[1+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(2); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect6[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect6[0+0]))));
          c[1+(0)]=(((((int) tmp_vect6[1+0]))*(((int) s[1+0]))+((int) ip[1+0])+1)/(((int) tmp_vect6[1+0])));
          sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect6[0+0]))+((int) s[0+0]))%(4));
          sp2[1+(0)]=(((((int) ip[1+0])+1)/(((int) tmp_vect6[1+0]))+((int) s[1+0]))%(1));
          tmp_vect44[0+(0)]=(((int) ip[0+0]));
          tmp_vect44[1+(0)]=(((int) ip[1+0])+1);
          tmp_vect45[0+(0)]=(((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect45[1+(0)]=(((int) bp[1+0])+((int) ip[1+0])+1);
          tmp_vect46[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          tmp_vect46[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0])));
          tmp_vect47[0+(0)]=(((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
          tmp_vect47[1+(0)]=((((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
          tmp_vect48[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0])));
          tmp_vect48[1+(0)]=((-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+-1);
          tmp_vect49[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
          tmp_vect49[1+(0)]=((-1)*(((int) bp[1+0]))+(-1)*(((int) ip[1+0]))+(((int) tmp_vect6[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0])+-1);
          tmp_vect50[0+(0)]=(((-4)*(((int) tmp_vect6[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect50[1+(0)]=(((-1)*(((int) tmp_vect6[1+0])))*(((int) c[1+0]))+((-1)*(((int) sp2[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) bp[1+0])+((int) ip[1+0])+1);
          out=FALSE;
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect46[i0]>=tmp_vect45[i0]) out=TRUE;
          }
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect47[i0]<tmp_vect44[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            ipp[1+(0)]=(0);
            lpp[0+(0)]=(0);
            lpp[1+(0)]=(0);
            bpp[0+(0)]=(0);
            bpp[1+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect48[0+0]))>0))*(((int) tmp_vect48[0+0]))+((int) tmp_vect44[0+0]));
            ipp[1+(0)]=((((((int) tmp_vect48[1+0]))>0))*(((int) tmp_vect48[1+0]))+((int) tmp_vect44[1+0]));
            lpp[0+(0)]=((((((int) tmp_vect48[0+0]))>0))*(((int) tmp_vect48[0+0]))+((int) lp[0+0]));
            lpp[1+(0)]=((((((int) tmp_vect48[1+0]))>0))*(((int) tmp_vect48[1+0]))+((int) lp[1+0]));
            bpp[0+(0)]=(((((((int) tmp_vect49[0+0]))>0))*(((int) tmp_vect50[0+0]))+((int) tmp_vect47[0+0]))-(((int) ipp[0+0])));
            bpp[1+(0)]=(((((((int) tmp_vect49[1+0]))>0))*(((int) tmp_vect50[1+0]))+((int) tmp_vect47[1+0]))-(((int) ipp[1+0])));
          }
          sp_=(int) sp2[0+(0)]*(int) 1+(int) sp2[1+(0)];
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect39[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect39[1+0]))+((int) lpp[1+0]));
              offset0=_A+((-1)*(((int) tmp_vect46[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect46[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              scalar1=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=((int) scalar1);
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              START_RECV();
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double),sp_);
              END_RECV(sp_,(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double));
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect39[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect39[1+0]))+((int) lpp[1+0]));
              offset0=buffer0r[sp_]+0*(int) (((int) bpp[1+0]))+0;
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=0;
                shift+=((int) scalar0);
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              shift=buffer0s[sp_]+0*(int) (int) bpp[1+(0)]+0;
              offset0=_A+((-1)*(((int) tmp_vect46[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect46[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=0;
              }
              START_SEND(p_,sizeof(double)*((((int) bpp[1+0]))*(((int) bpp[0+0]))));
              SEND(buffer0s[sp_],((((int) bpp[1+0]))*(((int) bpp[0+0])))*sizeof(double),p_);
              END_SEND();
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[1+(0)]++;
          if (s[1+(0)]>=tmp_vect43[1+(0)]) {
            s[1+(0)]=0;
            s[0+(0)]++;
            if (s[0+(0)]>=tmp_vect43[0+(0)]) s_cont=FALSE;
            }
        } while (s_cont);
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect51[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect51[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0])));
        tmp_vect52[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect52[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect53[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect53[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
        tmp_vect54[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
        tmp_vect54[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) _b[1+0]));
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect51[i0]>=_b[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          ip[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          lp[0+(0)]=(((((((int) p[0+0]))*(((int) tmp_vect0[0+0])))>0))*((((int) p[0+0]))*(((int) tmp_vect0[0+0]))));
          lp[1+(0)]=(((((((int) p[1+0]))*(((int) tmp_vect0[1+0])))>0))*((((int) p[1+0]))*(((int) tmp_vect0[1+0]))));
          bp[0+(0)]=(((((((int) tmp_vect53[0+0]))>0))*(((int) tmp_vect54[0+0]))+((int) tmp_vect52[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect53[1+0]))>0))*(((int) tmp_vect54[1+0]))+((int) tmp_vect52[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        if (MY_PROC()==p_) {
          if (mode==1) {
            shift=_A2+((-1)*(((int) tmp_vect51[0+0]))+((int) lp[0+0]))*(int) (int) tmp_vect0[1+(0)]+((-1)*(((int) tmp_vect51[1+0]))+((int) lp[1+0]));
            scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bp[1+0])));
            for (i0=0; i0<(int) bp[0+(0)]; i0++) {
              for (i1=0; i1<(int) bp[1+(0)]; i1++) {
                *(shift)*= _lambda[0+0];
                shift+=1;
              }
              shift+=((int) scalar0);
            }
          }
        }
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }



/*******
<1.000000 1.000000> pdrop A=(b take (<1.000000 1.000000> drop A)) * m_lambda +  + A2
********/

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect55[0+(0)]=(1);
        tmp_vect55[1+(0)]=(1);
        tmp_vect56[0+(0)]=(((int) _b[0+0])+1);
        tmp_vect56[1+(0)]=(((int) _b[1+0])+1);
        tmp_vect57[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0])));
        tmp_vect57[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0])));
        tmp_vect58[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
        tmp_vect58[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
        tmp_vect59[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0]))+-1);
        tmp_vect59[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0]))+-1);
        tmp_vect60[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0])+-1);
        tmp_vect60[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0])+-1);
        tmp_vect61[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) _b[0+0])+1);
        tmp_vect61[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) _b[1+0])+1);
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect57[i0]>=tmp_vect56[i0]) out=TRUE;
        }
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect58[i0]<tmp_vect55[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect59[0+0]))>0))*(((int) tmp_vect59[0+0])));
          ip[1+(0)]=((((((int) tmp_vect59[1+0]))>0))*(((int) tmp_vect59[1+0])));
          lp[0+(0)]=((((((int) tmp_vect59[0+0]))>0))*(((int) tmp_vect59[0+0]))+((int) tmp_vect55[0+0]));
          lp[1+(0)]=((((((int) tmp_vect59[1+0]))>0))*(((int) tmp_vect59[1+0]))+((int) tmp_vect55[1+0]));
          bp[0+(0)]=(((((((int) tmp_vect60[0+0]))>0))*(((int) tmp_vect61[0+0]))+((int) tmp_vect58[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect60[1+0]))>0))*(((int) tmp_vect61[1+0]))+((int) tmp_vect58[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        if (MY_PROC()==p_) {
          if (mode==1) {
            shift=_A+((-1)*(((int) tmp_vect57[0+0]))+((int) lp[0+0]))*(int) (int) tmp_vect6[1+(0)]+((-1)*(((int) tmp_vect57[1+0]))+((int) lp[1+0]));
            scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bp[1+0])));
            for (i0=0; i0<(int) bp[0+(0)]; i0++) {
              for (i1=0; i1<(int) bp[1+(0)]; i1++) {
                *(shift)*= _m_lambda[0+0];
                shift+=1;
              }
              shift+=((int) scalar0);
            }
          }
        }
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
      for (i0=0; i0<(2); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect62[0+(0)]=(((int) _b[0+0])+1);
        tmp_vect62[1+(0)]=(((int) _b[1+0])+1);
        tmp_vect63[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0])));
        tmp_vect63[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0])));
        tmp_vect64[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0]));
        tmp_vect64[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0]));
        tmp_vect65[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect6[0+0]))+-1);
        tmp_vect65[1+(0)]=((((int) p[1+0]))*(((int) tmp_vect6[1+0]))+-1);
        tmp_vect66[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect6[0+0]))+((int) tmp_vect6[0+0])+-1);
        tmp_vect66[1+(0)]=((-1)*(((int) _b[1+0]))+(((int) p[1+0]))*(((int) tmp_vect6[1+0]))+((int) tmp_vect6[1+0])+-1);
        tmp_vect67[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect6[0+0]))+(-1)*(((int) tmp_vect6[0+0]))+((int) _b[0+0])+1);
        tmp_vect67[1+(0)]=(((-1)*(((int) p[1+0])))*(((int) tmp_vect6[1+0]))+(-1)*(((int) tmp_vect6[1+0]))+((int) _b[1+0])+1);
        out=FALSE;
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect63[i0]>=tmp_vect62[i0]) out=TRUE;
        }
        for (i0=0; i0<(2); i0++) {
          if (tmp_vect64[i0]<const0[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          ip[1+(0)]=(0);
          lp[0+(0)]=(0);
          lp[1+(0)]=(0);
          bp[0+(0)]=(0);
          bp[1+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect65[0+0]))>0))*(((int) tmp_vect65[0+0])));
          ip[1+(0)]=((((((int) tmp_vect65[1+0]))>0))*(((int) tmp_vect65[1+0])));
          lp[0+(0)]=((((((int) tmp_vect65[0+0]))>0))*(((int) tmp_vect65[0+0]))+1);
          lp[1+(0)]=((((((int) tmp_vect65[1+0]))>0))*(((int) tmp_vect65[1+0]))+1);
          bp[0+(0)]=(((((((int) tmp_vect66[0+0]))>0))*(((int) tmp_vect67[0+0]))+((int) tmp_vect64[0+0]))-(((int) lp[0+0])));
          bp[1+(0)]=(((((((int) tmp_vect66[1+0]))>0))*(((int) tmp_vect67[1+0]))+((int) tmp_vect64[1+0]))-(((int) lp[1+0])));
        }
        p_=(int) p[0+(0)]*(int) 1+(int) p[1+(0)];
        tmp_vect68[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect0[0+0])))*(((int) tmp_vect0[0+0]))))/(((int) tmp_vect0[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect0[0+0])))*(((int) tmp_vect0[0+0]))))%(((int) tmp_vect0[0+0])))>0));
        tmp_vect68[1+(0)]=(((((int) ip[1+0])+((int) bp[1+0]))-(((((int) ip[1+0]))/(((int) tmp_vect0[1+0])))*(((int) tmp_vect0[1+0]))))/(((int) tmp_vect0[1+0]))+((((((int) ip[1+0])+((int) bp[1+0]))-(((((int) ip[1+0]))/(((int) tmp_vect0[1+0])))*(((int) tmp_vect0[1+0]))))%(((int) tmp_vect0[1+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(2); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect0[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect0[0+0]))));
          c[1+(0)]=(((((int) tmp_vect0[1+0]))*(((int) s[1+0]))+((int) ip[1+0]))/(((int) tmp_vect0[1+0])));
          sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect0[0+0]))+((int) s[0+0]))%(4));
          sp2[1+(0)]=(((((int) ip[1+0]))/(((int) tmp_vect0[1+0]))+((int) s[1+0]))%(1));
          tmp_vect69[0+(0)]=(((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect69[1+(0)]=(((int) bp[1+0])+((int) ip[1+0]));
          tmp_vect70[0+(0)]=(((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0])));
          tmp_vect70[1+(0)]=((((int) tmp_vect0[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect0[1+0])));
          tmp_vect71[0+(0)]=(((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
          tmp_vect71[1+(0)]=((((int) tmp_vect0[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
          tmp_vect72[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0])));
          tmp_vect72[1+(0)]=((-1)*(((int) ip[1+0]))+(((int) tmp_vect0[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect0[1+0])));
          tmp_vect73[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
          tmp_vect73[1+(0)]=((-1)*(((int) bp[1+0]))+(-1)*(((int) ip[1+0]))+(((int) tmp_vect0[1+0]))*(((int) c[1+0]))+(((int) sp2[1+0]))*(((int) tmp_vect0[1+0]))+((int) tmp_vect0[1+0]));
          tmp_vect74[0+(0)]=(((-4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect74[1+(0)]=(((-1)*(((int) tmp_vect0[1+0])))*(((int) c[1+0]))+((-1)*(((int) sp2[1+0])))*(((int) tmp_vect0[1+0]))+(-1)*(((int) tmp_vect0[1+0]))+((int) bp[1+0])+((int) ip[1+0]));
          out=FALSE;
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect70[i0]>=tmp_vect69[i0]) out=TRUE;
          }
          for (i0=0; i0<(2); i0++) {
            if (tmp_vect71[i0]<ip[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            ipp[1+(0)]=(0);
            lpp[0+(0)]=(0);
            lpp[1+(0)]=(0);
            bpp[0+(0)]=(0);
            bpp[1+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect72[0+0]))>0))*(((int) tmp_vect72[0+0]))+((int) ip[0+0]));
            ipp[1+(0)]=((((((int) tmp_vect72[1+0]))>0))*(((int) tmp_vect72[1+0]))+((int) ip[1+0]));
            lpp[0+(0)]=((((((int) tmp_vect72[0+0]))>0))*(((int) tmp_vect72[0+0]))+((int) lp[0+0]));
            lpp[1+(0)]=((((((int) tmp_vect72[1+0]))>0))*(((int) tmp_vect72[1+0]))+((int) lp[1+0]));
            bpp[0+(0)]=(((((((int) tmp_vect73[0+0]))>0))*(((int) tmp_vect74[0+0]))+((int) tmp_vect71[0+0]))-(((int) ipp[0+0])));
            bpp[1+(0)]=(((((((int) tmp_vect73[1+0]))>0))*(((int) tmp_vect74[1+0]))+((int) tmp_vect71[1+0]))-(((int) ipp[1+0])));
          }
          sp_=(int) sp2[0+(0)]*(int) 1+(int) sp2[1+(0)];
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A+((-1)*(((int) tmp_vect63[0+0]))+((int) lpp[0+0]))*(int) (int) tmp_vect6[1+(0)]+((-1)*(((int) tmp_vect63[1+0]))+((int) lpp[1+0]));
              offset0=_A2+((-1)*(((int) tmp_vect70[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect70[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              scalar1=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=((int) scalar1);
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              START_RECV();
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double),sp_);
              END_RECV(sp_,(((int) bpp[0+0]))*(((int) bpp[1+0]))*sizeof(double));
            }
            if (mode==1) {
              shift=_A+((-1)*(((int) tmp_vect63[0+0]))+((int) lpp[0+0]))*(int) (((int) tmp_vect6[1+0]))+((-1)*(((int) tmp_vect63[1+0]))+((int) lpp[1+0]));
              offset0=buffer0r[sp_]+0*(int) (((int) bpp[1+0]))+0;
              scalar0=(((int) tmp_vect6[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)+= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=0;
                shift+=((int) scalar0);
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(double *) get_mem(((((int) bpp[0+0]))*(((int) bpp[1+0])))*sizeof(double));
              shift=buffer0s[sp_]+0*(int) (int) bpp[1+(0)]+0;
              offset0=_A2+((-1)*(((int) tmp_vect70[0+0]))+((int) ipp[0+0]))*(int) (((int) tmp_vect0[1+0]))+((-1)*(((int) tmp_vect70[1+0]))+((int) ipp[1+0]));
              scalar0=(((int) tmp_vect0[1+0])+(-1)*(((int) bpp[1+0])));
              for (i0=0; i0<(int) bpp[0+(0)]; i0++) {
                for (i1=0; i1<(int) bpp[1+(0)]; i1++) {
                  *(shift)= *(offset0);
                  offset0+=1;
                  shift+=1;
                }
                offset0+=((int) scalar0);
                shift+=0;
              }
              START_SEND(p_,sizeof(double)*((((int) bpp[1+0]))*(((int) bpp[0+0]))));
              SEND(buffer0s[sp_],((((int) bpp[1+0]))*(((int) bpp[0+0])))*sizeof(double),p_);
              END_SEND();
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[1+(0)]++;
          if (s[1+(0)]>=tmp_vect68[1+(0)]) {
            s[1+(0)]=0;
            s[0+(0)]++;
            if (s[0+(0)]>=tmp_vect68[0+(0)]) s_cont=FALSE;
            }
        } while (s_cont);
        p[1+(0)]++;
        if (p[1+(0)]>=1) {
          p[1+(0)]=0;
          p[0+(0)]++;
          if (p[0+(0)]>=4) p_cont=FALSE;
          }
      } while (p_cont);
      if (mode==0) WAIT;
    }



  }
  free(_A2);
  TRACE_END();
}


