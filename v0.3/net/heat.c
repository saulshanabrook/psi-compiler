#include <stdlib.h>
#include "moalib.e"

#include "uni.h"

heat1d()

{
  float *offset0;
  float *offset1;
  float *offset2;
  int i0;
  int i1;
  int i2;
  float *shift;
  int _i;
  int _n;
  float *_A;
  float *_lambda;
  float _b[1];
  float _m_lambda[1];
  float _ntwo[1];
  float _one[1];
  float consta0[1];
  float consta1[1];
  float *_A2;
  float _t[1];
  float tmp_vect0[1];
  float tmp_vect1[1];
  float tmp_vect2[1];
  float tmp_vect3[1];
  float tmp_vect4[1];
  float tmp_vect5[1];
  float tmp_vect6[1];
  float tmp_vect7[1];
  float tmp_vect8[1];
  float tmp_vect9[1];
  float tmp_vect10[1];
  float tmp_vect11[1];
  float tmp_vect12[1];
  float tmp_vect13[1];
  float tmp_vect14[1];
  float tmp_vect15[1];
  float tmp_vect16[1];
  float tmp_vect17[1];
  float tmp_vect18[1];
  float tmp_vect19[1];
  float tmp_vect20[1];
  float tmp_vect21[1];
  float tmp_vect22[1];
  float tmp_vect23[1];
  float tmp_vect24[1];
  float tmp_vect25[1];
  float tmp_vect26[1];
  float tmp_vect27[1];
  float tmp_vect28[1];
  float tmp_vect29[1];
  float tmp_vect30[1];
  float tmp_vect31[1];
  float tmp_vect32[1];
  float tmp_vect33[1];
  float tmp_vect34[1];
  float tmp_vect35[1];
  float tmp_vect36[1];
  float tmp_vect37[1];
  float tmp_vect38[1];
  float tmp_vect39[1];
  float tmp_vect40[1];
  float tmp_vect41[1];
  float tmp_vect42[1];
  float tmp_vect43[1];
  float tmp_vect44[1];
  float tmp_vect45[1];
  float tmp_vect46[1];
  float tmp_vect47[1];
  float tmp_vect48[1];
  float tmp_vect49[1];
  float const0[]={1};
  float tmp_vect50[1];
  float tmp_vect51[1];
  float tmp_vect52[1];
  float tmp_vect53[1];
  float tmp_vect54[1];
  float tmp_vect55[1];
  float tmp_vect56[1];
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
  float *buffer0r[4],*buffer0s[4];

  NODE_INIT(4);

  RECV_HOST(&_i,sizeof(int)); 
_i=1;

  RECV_HOST(&_n,sizeof(int)); 
_n=32;

  _lambda=(float *) get_mem(sizeof(float));
  RECV_HOST(_lambda,sizeof(float)); 

  /* Communications for Initial Data */

  _A=(float *) get_mem(((((int) _n))/(4)+(((((int) _n))%(4))>0))*sizeof(float));
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


  _A2=(float *) get_mem((((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0)))*sizeof(float));

  for (_t[0]=0; _t[0]<(((int) _i)); _t[0]++) {
/*******
A2=((b take (<0.000000> drop A)) + (b take (<2.000000> drop A))) * lambda
********/

    tmp_vect0[0+(0)]=((((int) _b[0+0]))/(4)+(((((int) _b[0+0]))%(4))>0));
    for (mode=0; mode<2; mode++) {
printf("mode=%d\n",mode);
      for (i0=0; i0<(1); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect1[0+(0)]=(0);
        tmp_vect2[0+(0)]=(((int) _b[0+0]));
        tmp_vect3[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect4[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect5[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect6[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect7[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
printf("x1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect1[i0]);
printf(">\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect2[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect3[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect4[i0]);
printf(">\n");
        out=FALSE;
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect3[i0]>=tmp_vect2[i0]) out=TRUE;
        }
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect4[i0]<tmp_vect1[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          lp[0+(0)]=(0);
          bp[0+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect5[0+0]))>0))*(((int) tmp_vect5[0+0])));
          lp[0+(0)]=((((((int) tmp_vect5[0+0]))>0))*(((int) tmp_vect5[0+0]))+((int) tmp_vect1[0+0]));
          bp[0+(0)]=(((((((int) tmp_vect6[0+0]))>0))*(((int) tmp_vect7[0+0]))+((int) tmp_vect4[0+0]))-(((int) lp[0+0])));
        }
printf("ip:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ip[i0]);
printf(">\n");
printf("lp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lp[i0]);
printf(">\n");
printf("bp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bp[i0]);
printf(">\n");
        p_=p[0+(0)];
        tmp_vect8[0+(0)]=((((int) _n))/(4)+(((((int) _n))%(4))>0));
        tmp_vect9[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect8[0+0])))*(((int) tmp_vect8[0+0]))))/(((int) tmp_vect8[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect8[0+0])))*(((int) tmp_vect8[0+0]))))%(((int) tmp_vect8[0+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(1); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect8[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect8[0+0]))));
          sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect8[0+0]))+((int) s[0+0]))%(4));
          tmp_vect10[0+(0)]=(((int) ip[0+0]));
          tmp_vect11[0+(0)]=(((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect12[0+(0)]=(((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0])));
          tmp_vect13[0+(0)]=(((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0]));
          tmp_vect14[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0])));
          tmp_vect15[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0]));
          tmp_vect16[0+(0)]=(((-4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect8[0+0]))+(-1)*(((int) tmp_vect8[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
printf("x1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect10[i0]);
printf(">\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect11[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect12[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect13[i0]);
printf(">\n");
          out=FALSE;
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect12[i0]>=tmp_vect11[i0]) out=TRUE;
          }
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect13[i0]<tmp_vect10[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            lpp[0+(0)]=(0);
            bpp[0+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect14[0+0]))>0))*(((int) tmp_vect14[0+0]))+((int) tmp_vect10[0+0]));
            lpp[0+(0)]=((((((int) tmp_vect14[0+0]))>0))*(((int) tmp_vect14[0+0]))+((int) lp[0+0]));
            bpp[0+(0)]=(((((((int) tmp_vect15[0+0]))>0))*(((int) tmp_vect16[0+0]))+((int) tmp_vect13[0+0]))-(((int) ipp[0+0])));
          }
printf("ipp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ipp[i0]);
printf(">\n");
printf("lpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lpp[i0]);
printf(">\n");
printf("bpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bpp[i0]);
printf(">\n");
          sp_=sp2[0+(0)];
printf("p=%d\n",p_);
printf("sp=%d\n",sp_);
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect3[0+0]))+((int) lpp[0+0]));
              offset0=_A+((-1)*(((int) tmp_vect12[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)= *(offset0);
                offset0+=(1);
                shift++;
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*sizeof(float),sp_);
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect3[0+0]))+((int) lpp[0+0]));
              offset0=buffer0r[sp_]+0;
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)= *(offset0);
                offset0+=(1);
                shift++;
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              shift=buffer0s[sp_]+0;
              offset0=_A+((-1)*(((int) tmp_vect12[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)= *(offset0);
                offset0+=(1);
                shift++;
              }
              SEND(buffer0s[sp_],(((int) bpp[0+0]))*sizeof(float),p_);
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[0+(0)]++;
          if (s[0+(0)]==tmp_vect9[0+(0)]) s_cont=FALSE;
        } while (s_cont);
        p[0+(0)]++;
        if (p[0+(0)]==4) p_cont=FALSE;
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
printf("mode=%d\n",mode);
      for (i0=0; i0<(1); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect17[0+(0)]=(((int) _b[0+0]));
        tmp_vect18[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect19[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect20[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect21[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect22[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
printf("x1:0\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect17[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect18[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect19[i0]);
printf(">\n");
        out=FALSE;
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect18[i0]>=tmp_vect17[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          lp[0+(0)]=(0);
          bp[0+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect20[0+0]))>0))*(((int) tmp_vect20[0+0])));
          lp[0+(0)]=((((((int) tmp_vect20[0+0]))>0))*(((int) tmp_vect20[0+0])));
          bp[0+(0)]=(((((((int) tmp_vect21[0+0]))>0))*(((int) tmp_vect22[0+0]))+((int) tmp_vect19[0+0]))-(((int) lp[0+0])));
        }
printf("ip:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ip[i0]);
printf(">\n");
printf("lp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lp[i0]);
printf(">\n");
printf("bp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bp[i0]);
printf(">\n");
        p_=p[0+(0)];
        tmp_vect23[0+(0)]=(((((int) ip[0+0])+2+((int) bp[0+0]))-(((((int) ip[0+0])+2)/(((int) tmp_vect8[0+0])))*(((int) tmp_vect8[0+0]))))/(((int) tmp_vect8[0+0]))+((((((int) ip[0+0])+2+((int) bp[0+0]))-(((((int) ip[0+0])+2)/(((int) tmp_vect8[0+0])))*(((int) tmp_vect8[0+0]))))%(((int) tmp_vect8[0+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(1); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect8[0+0]))*(((int) s[0+0]))+((int) ip[0+0])+2)/((4)*(((int) tmp_vect8[0+0]))));
          sp2[0+(0)]=(((((int) ip[0+0])+2)/(((int) tmp_vect8[0+0]))+((int) s[0+0]))%(4));
          tmp_vect24[0+(0)]=(((int) ip[0+0])+2);
          tmp_vect25[0+(0)]=(((int) bp[0+0])+((int) ip[0+0])+2);
          tmp_vect26[0+(0)]=(((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0])));
          tmp_vect27[0+(0)]=(((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0]));
          tmp_vect28[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0]))+-2);
          tmp_vect29[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0])+-2);
          tmp_vect30[0+(0)]=(((-4)*(((int) tmp_vect8[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect8[0+0]))+(-1)*(((int) tmp_vect8[0+0]))+((int) bp[0+0])+((int) ip[0+0])+2);
printf("x1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect24[i0]);
printf(">\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect25[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect26[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect27[i0]);
printf(">\n");
          out=FALSE;
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect26[i0]>=tmp_vect25[i0]) out=TRUE;
          }
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect27[i0]<tmp_vect24[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            lpp[0+(0)]=(0);
            bpp[0+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect28[0+0]))>0))*(((int) tmp_vect28[0+0]))+((int) tmp_vect24[0+0]));
            lpp[0+(0)]=((((((int) tmp_vect28[0+0]))>0))*(((int) tmp_vect28[0+0]))+((int) lp[0+0]));
            bpp[0+(0)]=(((((((int) tmp_vect29[0+0]))>0))*(((int) tmp_vect30[0+0]))+((int) tmp_vect27[0+0]))-(((int) ipp[0+0])));
          }
printf("ipp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ipp[i0]);
printf(">\n");
printf("lpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lpp[i0]);
printf(">\n");
printf("bpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bpp[i0]);
printf(">\n");
          sp_=sp2[0+(0)];
printf("p=%d\n",p_);
printf("sp=%d\n",sp_);
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect18[0+0]))+((int) lpp[0+0]));
              offset0=_A+((-1)*(((int) tmp_vect26[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)+= *(offset0);
                offset0+=(1);
                shift++;
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*sizeof(float),sp_);
            }
            if (mode==1) {
              shift=_A2+((-1)*(((int) tmp_vect18[0+0]))+((int) lpp[0+0]));
              offset0=buffer0r[sp_]+0;
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)+= *(offset0);
                offset0+=(1);
                shift++;
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              shift=buffer0s[sp_]+0;
              offset0=_A+((-1)*(((int) tmp_vect26[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)= *(offset0);
                offset0+=(1);
                shift++;
              }
              SEND(buffer0s[sp_],(((int) bpp[0+0]))*sizeof(float),p_);
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[0+(0)]++;
          if (s[0+(0)]==tmp_vect23[0+(0)]) s_cont=FALSE;
        } while (s_cont);
        p[0+(0)]++;
        if (p[0+(0)]==4) p_cont=FALSE;
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
printf("mode=%d\n",mode);
      for (i0=0; i0<(1); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect31[0+(0)]=(((int) _b[0+0]));
        tmp_vect32[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect33[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect34[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect0[0+0])));
        tmp_vect35[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
        tmp_vect36[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) _b[0+0]));
printf("x1:0\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect31[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect32[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect33[i0]);
printf(">\n");
        out=FALSE;
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect32[i0]>=tmp_vect31[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          lp[0+(0)]=(0);
          bp[0+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect34[0+0]))>0))*(((int) tmp_vect34[0+0])));
          lp[0+(0)]=((((((int) tmp_vect34[0+0]))>0))*(((int) tmp_vect34[0+0])));
          bp[0+(0)]=(((((((int) tmp_vect35[0+0]))>0))*(((int) tmp_vect36[0+0]))+((int) tmp_vect33[0+0]))-(((int) lp[0+0])));
        }
printf("ip:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ip[i0]);
printf(">\n");
printf("lp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lp[i0]);
printf(">\n");
printf("bp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bp[i0]);
printf(">\n");
        p_=p[0+(0)];
printf("p=%d\n",p_);
printf("sp=%d\n",sp_);
        if (MY_PROC()==p_) {
          if (mode==1) {
            shift=_A2+((-1)*(((int) tmp_vect32[0+0]))+((int) lp[0+0]));
            for (i0=0; i0<bp[0+(0)]; i0++) {
              *(shift)*= _lambda[0+0];
              shift++;
            }
          }
        }
        p[0+(0)]++;
        if (p[0+(0)]==4) p_cont=FALSE;
      } while (p_cont);
      if (mode==0) WAIT;
    }



/*******
<1.000000> pdrop A=(b take (<1.000000> drop A)) * m_lambda + A2
********/

    for (mode=0; mode<2; mode++) {
printf("mode=%d\n",mode);
      for (i0=0; i0<(1); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect37[0+(0)]=(1);
        tmp_vect38[0+(0)]=(((int) _b[0+0])+1);
        tmp_vect39[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0])));
        tmp_vect40[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0]));
        tmp_vect41[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0]))+-1);
        tmp_vect42[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0])+-1);
        tmp_vect43[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect8[0+0]))+(-1)*(((int) tmp_vect8[0+0]))+((int) _b[0+0])+1);
printf("x1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect37[i0]);
printf(">\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect38[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect39[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect40[i0]);
printf(">\n");
        out=FALSE;
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect39[i0]>=tmp_vect38[i0]) out=TRUE;
        }
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect40[i0]<tmp_vect37[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          lp[0+(0)]=(0);
          bp[0+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect41[0+0]))>0))*(((int) tmp_vect41[0+0])));
          lp[0+(0)]=((((((int) tmp_vect41[0+0]))>0))*(((int) tmp_vect41[0+0]))+((int) tmp_vect37[0+0]));
          bp[0+(0)]=(((((((int) tmp_vect42[0+0]))>0))*(((int) tmp_vect43[0+0]))+((int) tmp_vect40[0+0]))-(((int) lp[0+0])));
        }
printf("ip:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ip[i0]);
printf(">\n");
printf("lp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lp[i0]);
printf(">\n");
printf("bp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bp[i0]);
printf(">\n");
        p_=p[0+(0)];
printf("p=%d\n",p_);
printf("sp=%d\n",sp_);
        if (MY_PROC()==p_) {
          if (mode==1) {
            shift=_A+((-1)*(((int) tmp_vect39[0+0]))+((int) lp[0+0]));
            for (i0=0; i0<bp[0+(0)]; i0++) {
              *(shift)*= _m_lambda[0+0];
              shift++;
            }
          }
        }
        p[0+(0)]++;
        if (p[0+(0)]==4) p_cont=FALSE;
      } while (p_cont);
      if (mode==0) WAIT;
    }

    for (mode=0; mode<2; mode++) {
printf("mode=%d\n",mode);
      for (i0=0; i0<(1); i0++) p[i0]=0;
      p_cont=TRUE;
      do {
        tmp_vect44[0+(0)]=(((int) _b[0+0])+1);
        tmp_vect45[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0])));
        tmp_vect46[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0]));
        tmp_vect47[0+(0)]=((((int) p[0+0]))*(((int) tmp_vect8[0+0]))+-1);
        tmp_vect48[0+(0)]=((-1)*(((int) _b[0+0]))+(((int) p[0+0]))*(((int) tmp_vect8[0+0]))+((int) tmp_vect8[0+0])+-1);
        tmp_vect49[0+(0)]=(((-1)*(((int) p[0+0])))*(((int) tmp_vect8[0+0]))+(-1)*(((int) tmp_vect8[0+0]))+((int) _b[0+0])+1);
printf("x1:0\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect44[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect45[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect46[i0]);
printf(">\n");
        out=FALSE;
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect45[i0]>=tmp_vect44[i0]) out=TRUE;
        }
        for (i0=0; i0<(1); i0++) {
          if (tmp_vect46[i0]<const0[i0]) out=TRUE;
        }
        if (out) {
          ip[0+(0)]=(0);
          lp[0+(0)]=(0);
          bp[0+(0)]=(0);
        } else {
          ip[0+(0)]=((((((int) tmp_vect47[0+0]))>0))*(((int) tmp_vect47[0+0])));
          lp[0+(0)]=((((((int) tmp_vect47[0+0]))>0))*(((int) tmp_vect47[0+0]))+1);
          bp[0+(0)]=(((((((int) tmp_vect48[0+0]))>0))*(((int) tmp_vect49[0+0]))+((int) tmp_vect46[0+0]))-(((int) lp[0+0])));
        }
printf("ip:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ip[i0]);
printf(">\n");
printf("lp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lp[i0]);
printf(">\n");
printf("bp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bp[i0]);
printf(">\n");
        p_=p[0+(0)];
        tmp_vect50[0+(0)]=(((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect0[0+0])))*(((int) tmp_vect0[0+0]))))/(((int) tmp_vect0[0+0]))+((((((int) ip[0+0])+((int) bp[0+0]))-(((((int) ip[0+0]))/(((int) tmp_vect0[0+0])))*(((int) tmp_vect0[0+0]))))%(((int) tmp_vect0[0+0])))>0));
        s_cont=TRUE;
        for (i0=0; i0<(1); i0++) s[i0]=0;
        do {
          c[0+(0)]=(((((int) tmp_vect0[0+0]))*(((int) s[0+0]))+((int) ip[0+0]))/((4)*(((int) tmp_vect0[0+0]))));
          sp2[0+(0)]=(((((int) ip[0+0]))/(((int) tmp_vect0[0+0]))+((int) s[0+0]))%(4));
          tmp_vect51[0+(0)]=(((int) bp[0+0])+((int) ip[0+0]));
          tmp_vect52[0+(0)]=(((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0])));
          tmp_vect53[0+(0)]=(((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
          tmp_vect54[0+(0)]=((-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0])));
          tmp_vect55[0+(0)]=((-1)*(((int) bp[0+0]))+(-1)*(((int) ip[0+0]))+((4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+(((int) sp2[0+0]))*(((int) tmp_vect0[0+0]))+((int) tmp_vect0[0+0]));
          tmp_vect56[0+(0)]=(((-4)*(((int) tmp_vect0[0+0])))*(((int) c[0+0]))+((-1)*(((int) sp2[0+0])))*(((int) tmp_vect0[0+0]))+(-1)*(((int) tmp_vect0[0+0]))+((int) bp[0+0])+((int) ip[0+0]));
printf("x1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) ip[i0]);
printf(">\n");
printf("x2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect51[i0]);
printf(">\n");
printf("y1:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect52[i0]);
printf(">\n");
printf("y2:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",(int) tmp_vect53[i0]);
printf(">\n");
          out=FALSE;
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect52[i0]>=tmp_vect51[i0]) out=TRUE;
          }
          for (i0=0; i0<(1); i0++) {
            if (tmp_vect53[i0]<ip[i0]) out=TRUE;
          }
          if (out) {
            ipp[0+(0)]=(0);
            lpp[0+(0)]=(0);
            bpp[0+(0)]=(0);
          } else {
            ipp[0+(0)]=((((((int) tmp_vect54[0+0]))>0))*(((int) tmp_vect54[0+0]))+((int) ip[0+0]));
            lpp[0+(0)]=((((((int) tmp_vect54[0+0]))>0))*(((int) tmp_vect54[0+0]))+((int) lp[0+0]));
            bpp[0+(0)]=(((((((int) tmp_vect55[0+0]))>0))*(((int) tmp_vect56[0+0]))+((int) tmp_vect53[0+0]))-(((int) ipp[0+0])));
          }
printf("ipp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",ipp[i0]);
printf(">\n");
printf("lpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",lpp[i0]);
printf(">\n");
printf("bpp:<");
for (i0=0; i0<(1); i0++)
  printf("%d ",bpp[i0]);
printf(">\n");
          sp_=sp2[0+(0)];
printf("p=%d\n",p_);
printf("sp=%d\n",sp_);
          if ((MY_PROC()==p_)&&(MY_PROC()==sp_)) {
            if (mode==1) {
              shift=_A+((-1)*(((int) tmp_vect45[0+0]))+((int) lpp[0+0]));
              offset0=_A2+((-1)*(((int) tmp_vect52[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)+= *(offset0);
                offset0+=(1);
                shift++;
              }
            }
          } else if (MY_PROC()==p_) {
            if (mode==0) {
              buffer0r[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              RECV(buffer0r[sp_],(((int) bpp[0+0]))*sizeof(float),sp_);
            }
            if (mode==1) {
              shift=_A+((-1)*(((int) tmp_vect45[0+0]))+((int) lpp[0+0]));
              offset0=buffer0r[sp_]+0;
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)+= *(offset0);
                offset0+=(1);
                shift++;
              }
              free(buffer0r[sp_]);
            }
          } else if (MY_PROC()==sp_) {
            if (mode==0) {
              buffer0s[sp_]=(float *) get_mem(((((int) bpp[0+0])))*sizeof(float));
              shift=buffer0s[sp_]+0;
              offset0=_A2+((-1)*(((int) tmp_vect52[0+0]))+((int) ipp[0+0]));
              for (i0=0; i0<bpp[0+(0)]; i0++) {
                *(shift)= *(offset0);
                offset0+=(1);
                shift++;
              }
              SEND(buffer0s[sp_],(((int) bpp[0+0]))*sizeof(float),p_);
            }
            if (mode==1) {
              free(buffer0s[sp_]);
            }
          }
          s[0+(0)]++;
          if (s[0+(0)]==tmp_vect50[0+(0)]) s_cont=FALSE;
        } while (s_cont);
        p[0+(0)]++;
        if (p[0+(0)]==4) p_cont=FALSE;
      } while (p_cont);
      if (mode==0) WAIT;
    }



  }
  printout(_i,_n,_A,_lambda);
  free(_A2);
}


