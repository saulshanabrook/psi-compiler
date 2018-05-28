#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  double *offset1;
  int i0;
  int i1;
  double *shift;
  double _tvec[]={3.000000, 3.000000};
  double _dvec[]={1.000000, 1.000000};
  double _jvec[]={0.000000, 2.000000};
  double _ones[]={1.000000, 1.000000};
  double _xold[]={0.000000, 1.000000, 2.000000, 3.000000, 4.000000,
    5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
    10.000000, 11.000000, 12.000000, 13.000000, 14.000000,
    15.000000, 16.000000, 17.000000, 18.000000, 19.000000,
    20.000000, 21.000000, 22.000000, 23.000000, 24.000000};
  double _fives[]={5.000000, 5.000000, 5.000000, 5.000000, 5.000000,
    5.000000, 5.000000, 5.000000, 5.000000};
  double _ishp[2];
  double tmp_vect0[1];
  double _i[1];
  int scalar0;
  double tmp_vect1[scalar0];
  double tmp_vect2[1];
  int scalar1;
  int scalar2;
  int scalar3;
  int scalar4;
  double tmp_vect3[scalar4];
   const0[2];
  int scalar5;
  double tmp_vect4[scalar5];
  int scalar6;
  double tmp_vect5[scalar6];
  int scalar7;
  double tmp_vect6[scalar7];
  double tmp_vect7[1];
  int scalar8;
  int scalar9;
  int scalar10;
  int scalar11;
  double tmp_vect8[scalar11];
  int scalar12;
  double tmp_vect9[scalar12];
  int scalar13;
  double tmp_vect10[scalar13];
  int scalar14;
  double tmp_vect11[scalar14];
  int scalar15;
  double tmp_vect12[scalar15];
  double tmp_vect13[scalar14];
  int scalar16;
  double tmp_vect14[scalar16];
  int scalar17;
  double tmp_vect15[scalar17];
  int scalar18;
  double tmp_vect16[scalar18];
  int scalar19;
  double tmp_vect17[scalar19];
  int scalar20;
  double tmp_vect18[scalar20];
  double _d[1];
  double consta0[2];
  double consta1[2];
  double _ivec[2];
  double _res[3*3];
  int scalar21;
  int scalar22;
  double _j[1];
  double consta2[1];
  int consta2[1];
  int scalar23;

  scalar0=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))));
  scalar1=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))));
  scalar2=((2)-(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))));
  scalar3=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+scalar1);
  scalar4=(2+(scalar1+scalar2)-(2));
  for (i=0; i<2; i++)  tmp_vect3[i+0]=fabs(_ishp[i+0]);
  const0[0]=5;
  const0[1]=5;
  for (i=0; i<((scalar1)-(min(scalar1,2))); i++)  tmp_vect3[i+2]=const0[i+(min(scalar1,2))];
  scalar5=((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(scalar1,2)));
  scalar6=((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(scalar1,2)));
  for (i=0; i<(scalar6); i++)  tmp_vect5[i+2]=tmp_vect1[i+(min(scalar1,2))];
  for (i=0; i<(scalar6); i++)  tmp_vect4[i+0]=fabs(tmp_vect5[i+0]);
  for (i=0; i<(scalar5); i++)  tmp_vect3[i+0]%=tmp_vect4[i+0];
  for (i=0; i<((scalar2)-(max(2,scalar1))); i++)  tmp_vect3[i+(max(scalar3,2)+2)]=const0[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+max(2,scalar1))];
  scalar7=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))));
  scalar8=(min(scalar1,2));
  scalar9=(min(scalar2,(2)-(scalar8)));
  scalar10=((scalar4)-(2));
  scalar11=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+(2+scalar10)-(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))));
  for (i=0; i<(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))); i++)  tmp_vect8[i+0]=tmp_vect6[i+0];
  scalar12=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))));
  for (i=0; i<(scalar12); i++)  tmp_vect9[i+0]=(tmp_vect6[i+0]>0);
  for (i=0; i<(scalar12); i++)  tmp_vect8[i+0]%=tmp_vect9[i+0];
  scalar13=(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))));
  for (i=0; i<(min(2,scalar13)); i++)  tmp_vect10[i+0]=_ishp[i+0];
  scalar14=(min(2,scalar13));
  for (i=0; i<(min(scalar8,scalar14)); i++)  tmp_vect11[i+0]=const0[i+0];
  scalar15=(min(scalar8,scalar14));
  for (i=0; i<(scalar15); i++)  tmp_vect12[i+0]=fabs(tmp_vect1[i+0]);
  for (i=0; i<(scalar15); i++)  tmp_vect11[i+0]%=tmp_vect12[i+0];
  for (i=0; i<(min(scalar9,(scalar14)-(scalar15))); i++)  tmp_vect11[i+(scalar3)]=const0[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))];
  for (i=0; i<(scalar14); i++)  tmp_vect10[i+0]%=tmp_vect11[i+0];
  for (i=0; i<(scalar14); i++)  tmp_vect13[i+0]=(_ishp[i+0]<0);
  for (i=0; i<(scalar14); i++)  tmp_vect10[i+0]%=tmp_vect13[i+0];
  for (i=0; i<(min(scalar10,(scalar13)-(scalar14))); i++)  tmp_vect10[i+2]=0;
  for (i=0; i<(scalar13); i++)  tmp_vect8[i+0]%=tmp_vect10[i+0];
  for (i=0; i<((2)-(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))))); i++)  tmp_vect8[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+scalar12)]=_ishp[i+(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))))];
  scalar16=((2)-(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))));
  for (i=0; i<((scalar8)-(min(scalar8,min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))))); i++)  tmp_vect14[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+scalar12)]=const0[i+(min(scalar8,min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))))];
  scalar17=((scalar8)-(min(scalar8,min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))))));
  scalar18=((scalar8)-(min(scalar8,min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))))));
  for (i=0; i<(scalar18); i++)  tmp_vect16[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+scalar12)]=tmp_vect1[i+(min(scalar8,min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))))];
  for (i=0; i<(scalar18); i++)  tmp_vect15[i+0]=fabs(tmp_vect16[i+0]);
  for (i=0; i<(scalar17); i++)  tmp_vect14[i+0]%=tmp_vect15[i+0];
  for (i=0; i<((scalar9)-(max(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))),scalar8))); i++)  tmp_vect14[i+(max(scalar3,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))+scalar12)]=const0[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+max(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))),scalar8))];
  for (i=0; i<(scalar16); i++)  tmp_vect8[i+0]%=tmp_vect14[i+0];
  scalar19=((2)-(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))));
  scalar20=((2)-(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))));
  for (i=0; i<(scalar20); i++)  tmp_vect18[i+(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))+scalar12)]=_ishp[i+(min(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0])))))];
  for (i=0; i<(scalar20); i++)  tmp_vect17[i+0]=(tmp_vect18[i+0]<0);
  for (i=0; i<(scalar19); i++)  tmp_vect8[i+0]%=tmp_vect17[i+0];
  for (i=0; i<((scalar10)-(max(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),2))); i++)  tmp_vect8[i+(max(2,abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))+scalar12)]=0;
/*******
d= dim res
********/

  shift=_d+0;
  *(shift)= 2.000000;


/*******
ishp=( shp res) - <2.000000 2.000000>
********/

  shift=_ishp+0;
  consta0[0]=3;
  consta0[1]=3;
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


/*******
ivec= iota d
********/

  shift=_ivec+0;
  for (i0=0; i0<0+(int) _d[0]; i0++) {
    *(shift)= i0;
    shift++;
  }


/*******
res=ishp take (ones drop xold)
********/

  shift=_res+0*3+0;
  offset0=_xold+(1+(((int) _ishp[0])+4)*(((((int) _ishp[0]))<0)))*5+(1+(((int) _ishp[0])+4)*(((((int) _ishp[0]))<0)));
  scalar21=((5)-(abs(((int) _ishp[0]))));
  scalar22=((3)-(abs(((int) _ishp[0]))));
  for (i0=0; i0<(abs(((int) _ishp[0]))); i0++) {
    for (i1=0; i1<(abs(((int) _ishp[0]))); i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
    offset0+=scalar21;
    shift+=scalar22;
  }


  for (_i[0]=0; _i[0]<((int) _d[0]); _i[0]++) {
    for (_j[0]=0; _j[0]<2; _j[0]++) {
/*******
res=res + (ishp take (((i take ones) cat ((j psi jvec) cat ((i + <1.000000>) drop ones))) drop xold))
********/

      shift=tmp_vect0+0;
      offset0=_i+0;
      consta2[0]=1.000000;
      offset1=consta2+0;
      *(shift)= *(offset0);
      *(shift)+= *(offset1);
      shift=tmp_vect1+0;
      offset0=_ones+((((int) _i[0])+2)*(((((int) _i[0]))<0)));
      for (i0=0; i0<(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))); i0++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      shift=tmp_vect1+(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0]))));
      offset0=_jvec+(int) _j[0];
      *(shift)= *(offset0);
      shift=tmp_vect2+0;
      offset0=_i+0;
      offset1=consta2+0;
      *(shift)= *(offset0);
      *(shift)+= *(offset1);
      shift=tmp_vect1+(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))+min((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))),1));
      offset0=_ones+((((int) tmp_vect2[0]))*(((((int) tmp_vect2[0]))>0)));
      for (i0=0; i0<(((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))))-(min((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))),1))); i0++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      shift=_res+0*3+0;
      scalar21=((scalar4)-(2));
      offset0=_res+0*3+0;
      scalar22=((-1)*(((int) tmp_vect3[0]))+3);
      scalar23=((-1)*(((int) tmp_vect3[0]))+3);
      for (i0=0; i0<(int) tmp_vect3[0]; i0++) {
        for (i1=0; i1<(int) tmp_vect3[1]; i1++) {
          *(shift)= *(offset0);
          offset0+=1;
          shift+=1;
        }
        offset0+=scalar22;
        shift+=((int) scalar23);
      }
      shift=tmp_vect6+0;
      offset0=_ones+((((int) _i[0])+2)*(((((int) _i[0]))<0)));
      for (i0=0; i0<(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))); i0++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      shift=tmp_vect6+(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0]))));
      offset0=_jvec+(int) _j[0];
      *(shift)= *(offset0);
      shift=tmp_vect7+0;
      offset0=_i+0;
      offset1=consta2+0;
      *(shift)= *(offset0);
      *(shift)+= *(offset1);
      shift=tmp_vect6+(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))+min((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))),1));
      offset0=_ones+((((int) tmp_vect7[0]))*(((((int) tmp_vect7[0]))>0)));
      for (i0=0; i0<(((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))))-(min((abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))))-(min(abs(((int) _i[0]))+1+(2)-(abs(((int) tmp_vect0[0]))),abs(((int) _i[0])))),1))); i0++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      shift=_res+0*3+0;
      scalar21=((scalar11)-(2));
      offset0=_xold+(int) tmp_vect8[0+scalar21]*5+(int) tmp_vect8[1+scalar21];
      scalar22=((-1)*(((int) tmp_vect3[0]))+5);
      scalar23=((-1)*(((int) tmp_vect3[0]))+3);
      for (i0=0; i0<(int) tmp_vect3[0]; i0++) {
        for (i1=0; i1<(int) tmp_vect3[1]; i1++) {
          *(shift)+= *(offset0);
          offset0+=1;
          shift+=1;
        }
        offset0+=scalar22;
        shift+=scalar23;
      }


    }
  }
/*******
take=(dvec drop xold)
********/

  shift=_tvec+0;
  offset0=_xold+1*5+1;
  for (i0=0; i0<4; i0++) {
    for (i1=0; i1<4; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
    offset0+=1;
  }


}


res()

{
  double *shift;

}


