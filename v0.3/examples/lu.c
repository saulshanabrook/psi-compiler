#include <stdlib.h>
#include "moalib.e"

LU(int _n, float _a[])

{
  float *offset0;
  float *offset1;
  int i0;
  int i1;
  float *shift;
  float _ni[1];
  int forall_i0[1];
  float _i1[1];
  float tmp_vect0[1];
  float tmp_vect1[2];
  int forall_i1[1];
  float tmp_vect2[2];
  int forall_i2[1];
  int forall_i3[1];
  float tmp_vect3[2];
  float tmp_vect4[1];
  float _n1[1];
  float consta0[1];
  float consta1[1];
  float _i[1];
  float consta2[1];
  float consta3[1];
  float *_c;
  float *temp0;
  float *temp1;

/*******
n1=<n> - <1.000000>
********/

  shift=_n1+0;
  consta0[0]=(((int) _n));
  offset0=consta0+0;
  consta1[0]=1.000000;
  offset1=consta1+0;
  *(shift)= *(offset0);
  *(shift)-= *(offset1);


  for (_i[0]=0; _i[0]<(((int) _n1[0])); _i[0]++) {
/*******
i1=i + <1.000000>
********/

    shift=_i1+0;
    offset0=_i+0;
    consta2[0]=1.000000;
    offset1=consta2+0;
    *(shift)= *(offset0);
    *(shift)+= *(offset1);


/*******
ni=<n> - i1
********/

    shift=_ni+0;
    consta3[0]=(((int) _n));
    offset0=consta3+0;
    offset1=_i1+0;
    *(shift)= *(offset0);
    *(shift)-= *(offset1);


    _c=(float *) malloc(((((int) _ni[0+0])))*sizeof(float));

/*******
c=(<i> psi  omega <1.000000 1.000000> (i1 drop a)) / (<i i> psi a)
********/

    for (forall_i0[0]=0; forall_i0[0]<0+((-1)*(((int) _i1[0+0]))+((int) _n)); forall_i0[0]++) {
      shift=_c+forall_i0[0+(0)];
      offset0=_a+(((int) forall_i0[0+0])+((int) _i1[0+0]))*(((int) _n))+(((int) _i[0]));
      *(shift)= *(offset0);
    }
    shift=tmp_vect0+0;
    offset0=_a+(((int) _i[0]))*(((int) _n))+(((int) _i[0]));
    *(shift)= *(offset0);
    shift=_c+0;
    for (i0=0; i0<((-1)*(((int) _i1[0+0]))+((int) _n)); i0++) {
      *(shift)/= tmp_vect0[0+0];
      shift++;
    }


/*******
a=(<i1> take a) cat ((((ni cat i) take (<i1> drop a)) cat  omega <1.000000 0.000000> c) cat  omega <1.000000 1.000000> (((i1 cat i1) drop a) - (c *  omega <0.000000 1.000000> (i1 drop (<i> psi a)))))
********/

    shift=tmp_vect1+0;
    offset0=_ni+0;
    *(shift)= *(offset0);
    shift=tmp_vect1+1;
    offset0=_i+0;
    *(shift)= *(offset0);
    shift=tmp_vect2+0;
    offset0=_i1+0;
    *(shift)= *(offset0);
    shift=tmp_vect2+1;
    offset0=_i1+0;
    *(shift)= *(offset0);
    for (forall_i3[0]=0; forall_i3[0]<0+((((int) _i1[0])+((int) _ni[0+0]))-(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0])))); forall_i3[0]++) {
      for (forall_i1[0]=(((int) forall_i3[0+0])); forall_i1[0]<(((int) forall_i3[0+0]))+(1); forall_i1[0]++) {
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i1[0+0]))-(((int) forall_i3[0+0])))*(((int) _n))+(0);
        offset0=_a+(((int) forall_i1[0+0])+((int) _i1[0]))*(((int) _n))+(0);
        for (i1=0; i1<(min(min(((int) _n),((int) tmp_vect1[0+1])+1),((int) tmp_vect1[0+1]))); i1++) {
          *(shift)= *(offset0);
          offset0+=(1);
          shift++;
        }
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i1[0+0]))-(((int) forall_i3[0+0])))*(((int) _n))+(min(min(((int) _n),((int) tmp_vect1[0+1])+1),((int) tmp_vect1[0+1])));
        offset0=_c+forall_i1[0+(0)];
        *(shift)= *(offset0);
      }
      shift=tmp_vect3+0;
      offset0=_i1+0;
      *(shift)= *(offset0);
      shift=tmp_vect3+1;
      offset0=_i1+0;
      *(shift)= *(offset0);
      shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0]))*(((int) _n))+(min(((int) _n),((int) tmp_vect1[0+1])+1));
      offset0=_a+(((int) forall_i3[0+0])+((int) tmp_vect3[0+0]))*(((int) _n))+(((int) tmp_vect3[1+0]));
      for (i1=0; i1<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i1++) {
        *(shift)= *(offset0);
        offset0+=(1);
        shift++;
      }
      for (forall_i2[0]=(((int) forall_i3[0+0])); forall_i2[0]<(((int) forall_i3[0+0]))+(1); forall_i2[0]++) {
        temp0=(float *) malloc(((((int) _n))*(((int) _n)))*sizeof(float));
        temp1=(float *) malloc((((-1)*(((int) _i1[0+0]))+((int) _n)))*sizeof(float));
        shift=tmp_vect4+0;
        offset0=_c+forall_i2[0+(0)];
        *(shift)= *(offset0);
        shift=temp1+0;
        for (i0=0; i0<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i0++) {
          *(shift)= tmp_vect4[0+0];
          shift++;
        }
        shift=temp1+0;
        offset0=_a+(((int) _i[0]))*(((int) _n))+(((int) _i1[0+0]));
        for (i1=0; i1<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i1++) {
          *(shift)*= *(offset0);
          offset0+=(1);
          shift++;
        }
        shift=temp0+0*(((int) _n))+0;
        offset0=temp1+0;
        for (i0=0; i0<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i0++) {
          *(shift)= *(offset0);
          offset0+=(1);
          shift++;
        }
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i2[0+0]))-(((int) forall_i3[0+0])))*(((int) _n))+(min(((int) _n),((int) tmp_vect1[0+1])+1));
        offset0=temp0+0*(((int) _n))+0;
        for (i1=0; i1<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i1++) {
          *(shift)-= *(offset0);
          offset0+=(1);
          shift++;
        }
        free(temp1);
        free(temp0);
      }
    }


    free(_c);
  }
}


