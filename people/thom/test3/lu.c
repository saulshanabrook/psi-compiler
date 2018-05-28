#include <stdlib.h>
#include "moalib.e"

LU(int _n, double _a[])

{
  double *offset0;
  double *offset1;
  int i0;
  int i1;
  double *shift;
  double _ni[1];
  int forall_i0[1];
  double _i1[1];
  double tmp_vect0[1];
  double tmp_vect1[2];
  int forall_i1[1];
  double tmp_vect2[2];
  int forall_i2[1];
  int forall_i3[1];
  double tmp_vect3[2];
  double tmp_vect4[1];
  double _n1[1];
  double consta0[1];
  double consta1[1];
  double _i[1];
  double consta2[1];
  double consta3[1];
  double *_c;
  double *temp1;
  int scalar0;

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
i1=i +  + <1.000000>
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


    _c=(double *) get_mem(((((int) _ni[0+0])))*sizeof(double));

/*******
c=(<i> psi  omega <1.000000 1.000000> (i1 drop a)) / (<i i> psi a)
********/

    for (forall_i0[0]=0; forall_i0[0]<0+((-1)*(((int) _i1[0+0]))+((int) _n)); forall_i0[0]++) {
      shift=_c+(int) forall_i0[0+(0)];
      offset0=_a+(((int) forall_i0[0+0])+((int) _i1[0+0]))*(int) (((int) _n))+(((int) _i[0]));
      *(shift)= *(offset0);
    }
    shift=tmp_vect0+0;
    offset0=_a+(((int) _i[0]))*(int) (((int) _n))+(((int) _i[0]));
    *(shift)= *(offset0);
    shift=_c+0;
    for (i0=0; i0<((-1)*(((int) _i1[0+0]))+((int) _n)); i0++) {
      *(shift)/= tmp_vect0[0+0];
      shift+=1;
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
      temp1=(double *) get_mem((((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))))*sizeof(double));
      for (forall_i1[0]=(((int) forall_i3[0+0])); forall_i1[0]<(((int) forall_i3[0+0]))+(1); forall_i1[0]++) {
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i1[0+0]))-(((int) forall_i3[0+0])))*(int) (((int) _n))+(0);
        offset0=_a+(((int) forall_i1[0+0])+((int) _i1[0]))*(int) (((int) _n))+(0);
        scalar0=((((int) _n))-(min(min(((int) _n),((int) tmp_vect1[0+1])+1),((int) tmp_vect1[0+1]))));
        for (i1=0; i1<(min(min(((int) _n),((int) tmp_vect1[0+1])+1),((int) tmp_vect1[0+1]))); i1++) {
          *(shift)= *(offset0);
          offset0+=1;
          shift+=1;
        }
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i1[0+0]))-(((int) forall_i3[0+0])))*(int) (((int) _n))+(min(min(((int) _n),((int) tmp_vect1[0+1])+1),((int) tmp_vect1[0+1])));
        offset0=_c+(int) forall_i1[0+(0)];
        *(shift)= *(offset0);
      }
      shift=tmp_vect3+0;
      offset0=_i1+0;
      *(shift)= *(offset0);
      shift=tmp_vect3+1;
      offset0=_i1+0;
      *(shift)= *(offset0);
      shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0]))*(int) (((int) _n))+(min(((int) _n),((int) tmp_vect1[0+1])+1));
      offset0=_a+(((int) forall_i3[0+0])+((int) tmp_vect3[0+0]))*(int) (((int) _n))+(((int) tmp_vect3[1+0]));
      scalar0=((((int) _n))-((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))));
      for (i1=0; i1<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i1++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      for (forall_i2[0]=(((int) forall_i3[0+0])); forall_i2[0]<(((int) forall_i3[0+0]))+(1); forall_i2[0]++) {
        shift=tmp_vect4+0;
        offset0=_c+(int) forall_i2[0+(0)];
        *(shift)= *(offset0);
        shift=temp1+0;
        for (i0=0; i0<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i0++) {
          *(shift)= tmp_vect4[0+0];
          shift+=1;
        }
        shift=temp1+0;
        offset0=_a+(((int) _i[0]))*(int) (((int) _n))+(((int) _i1[0+0]));
        scalar0=((((int) _n))-((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))));
        for (i1=0; i1<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i1++) {
          *(shift)*= *(offset0);
          offset0+=1;
          shift+=1;
        }
        shift=_a+(min(((int) _i1[0])+((int) _ni[0+0]),((int) _i1[0]))+((int) forall_i3[0+0])+(((int) forall_i2[0+0]))-(((int) forall_i3[0+0])))*(int) (((int) _n))+(min(((int) _n),((int) tmp_vect1[0+1])+1));
        offset0=temp1+0;
        for (i0=0; i0<((((int) _n))-(min(((int) _n),((int) tmp_vect1[0+1])+1))); i0++) {
          *(shift)-= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      free(temp1);
    }


    free(_c);
  }
}


