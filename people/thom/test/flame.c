#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  double *offset1;
  double *offset2;
  int i0;
  double *shift;
  double _sh[]={3.000000, 3.000000, 3.000000};
  double _x[]={1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
    1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
    1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
    1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
    1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
    1.000000, 1.000000};
  double _n[1];
  double _xin[27];
  double _i[1];
  double _jcon[1];
  double _jbound[1];
  double _abound[1];
  double _y[1];
  double _k[1];
  double _e[1];
  double _i1[1];
  double _bbound[1];
  double _j[1];
  double _jvar[1];
  double _llim[1];
  double _b[1];
  double _bvar0[1];
  double _bvar1[1];
  double _bvar2[1];
  double _a[1];
  double _ind0[1];
  double _ind1[1];
  double _ind2[1];
  double _index[1];
  double _xnew[27];

/*******
n=four
********/

  shift=_n+0;
  *(shift)= 4.000000;


/*******
xin=x
********/

  shift=_xin+0;
  offset0=_x+0;
  for (i0=0; i0<27; i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


  for (_i[0]=1; _i[0]<(int) _n[0+0]; _i[0]++) {
/*******
jcon=one
********/

    shift=_jcon+0;
    *(shift)= 1.000000;


/*******
jbound=one
********/

    shift=_jbound+0;
    *(shift)= 1.000000;


/*******
abound=one
********/

    shift=_abound+0;
    *(shift)= 1.000000;


/*******
y=(n - one) - i
********/

    shift=_y+0;
    offset0=_n+0;
    offset2=_i+0;
    *(shift)= *(offset0);
    *(shift)-= 1.000000;
    *(shift)-= *(offset2);


    for (_k[0]=0; _k[0]<(int) _i[0+0]; _k[0]++) {
/*******
e=y + k
********/

      shift=_e+0;
      offset0=_y+0;
      offset1=_k+0;
      *(shift)= *(offset0);
      *(shift)+= *(offset1);


/*******
jcon=jcon * (<e> psi sh)
********/

      shift=_jcon+0;
      offset0=_sh+((int) _e[0]);
      *(shift)*= *(offset0);


    }
    for (_k[0]=0; _k[0]<(int) _y[0+0]; _k[0]++) {
/*******
jbound=jbound * (<k> psi sh)
********/

      shift=_jbound+0;
      offset0=_sh+((int) _k[0]);
      *(shift)*= *(offset0);


    }
/*******
i1=i + one
********/

    shift=_i1+0;
    offset0=_i+0;
    *(shift)= *(offset0);
    *(shift)+= 1.000000;


    for (_k[0]=0; _k[0]<((int) _i1[0]); _k[0]++) {
/*******
e=y + one + k
********/

      shift=_e+0;
      offset0=_y+0;
      offset2=_k+0;
      *(shift)= *(offset0);
      *(shift)+= 1.000000;
      *(shift)+= *(offset2);


/*******
abound=abound * (<e> psi sh)
********/

      shift=_abound+0;
      offset0=_sh+((int) _e[0]);
      *(shift)*= *(offset0);


    }
/*******
bbound=<y> psi sh
********/

    shift=_bbound+0;
    offset0=_sh+((int) _y[0]);
    *(shift)= *(offset0);


    for (_j[0]=0; _j[0]<(int) _jbound[0+0]; _j[0]++) {
/*******
jvar=j * jcon
********/

      shift=_jvar+0;
      offset0=_j+0;
      offset1=_jcon+0;
      *(shift)= *(offset0);
      *(shift)*= *(offset1);


/*******
llim=bbound - one
********/

      shift=_llim+0;
      offset0=_bbound+0;
      *(shift)= *(offset0);
      *(shift)-= 1.000000;


      for (_b[0]=0; _b[0]<1; _b[0]++) {
/*******
bvar0=b * abound
********/

        shift=_bvar0+0;
        offset0=_b+0;
        offset1=_abound+0;
        *(shift)= *(offset0);
        *(shift)*= *(offset1);


/*******
bvar1=(b + one) * abound
********/

        shift=_bvar1+0;
        offset0=_b+0;
        offset2=_abound+0;
        *(shift)= *(offset0);
        *(shift)+= 1.000000;
        *(shift)*= *(offset2);


/*******
bvar2=(llim + b) * abound
********/

        shift=_bvar2+0;
        offset0=_llim+0;
        offset1=_b+0;
        offset2=_abound+0;
        *(shift)= *(offset0);
        *(shift)+= *(offset1);
        *(shift)*= *(offset2);


        for (_a[0]=0; _a[0]<(int) _abound[0+0]; _a[0]++) {
/*******
ind0=jvar + bvar0 + a
********/

          shift=_ind0+0;
          offset0=_jvar+0;
          offset1=_bvar0+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind1=jvar + bvar1 + a
********/

          shift=_ind1+0;
          offset0=_jvar+0;
          offset1=_bvar1+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind2=jvar + bvar2 + a
********/

          shift=_ind2+0;
          offset0=_jvar+0;
          offset1=_bvar2+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
index=ind0 - one
********/

          shift=_index+0;
          offset0=_ind0+0;
          *(shift)= *(offset0);
          *(shift)-= 1.000000;


/*******
pdrop drop xnew=(<ind0> psi x) + (<ind1> psi x) + (<ind2> psi x)
********/

          shift=_xnew+(int) _index[0+0];
          offset0=_x+((int) _ind0[0]);
          offset1=_x+((int) _ind1[0]);
          offset2=_x+((int) _ind2[0]);
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


        }
      }
      for (_b[0]=1; _b[0]<(int) _llim[0+0]; _b[0]++) {
/*******
bvar0=b * abound
********/

        shift=_bvar0+0;
        offset0=_b+0;
        offset1=_abound+0;
        *(shift)= *(offset0);
        *(shift)*= *(offset1);


/*******
bvar1=(b + one) * abound
********/

        shift=_bvar1+0;
        offset0=_b+0;
        offset2=_abound+0;
        *(shift)= *(offset0);
        *(shift)+= 1.000000;
        *(shift)*= *(offset2);


/*******
bvar2=b * abound
********/

        shift=_bvar2+0;
        offset0=_b+0;
        offset1=_abound+0;
        *(shift)= *(offset0);
        *(shift)*= *(offset1);


        for (_a[0]=0; _a[0]<(int) _abound[0+0]; _a[0]++) {
/*******
ind0=jvar + bvar0 + a
********/

          shift=_ind0+0;
          offset0=_jvar+0;
          offset1=_bvar0+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind1=jvar + bvar1 + a
********/

          shift=_ind1+0;
          offset0=_jvar+0;
          offset1=_bvar1+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind2=jvar + bvar2 + a
********/

          shift=_ind2+0;
          offset0=_jvar+0;
          offset1=_bvar2+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
index=ind0 - one
********/

          shift=_index+0;
          offset0=_ind0+0;
          *(shift)= *(offset0);
          *(shift)-= 1.000000;


/*******
pdrop drop xnew=(<ind0> psi x) + (<ind1> psi x) + (<ind2> psi x)
********/

          shift=_xnew+(int) _index[0+0];
          offset0=_x+((int) _ind0[0]);
          offset1=_x+((int) _ind1[0]);
          offset2=_x+((int) _ind2[0]);
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


        }
      }
      for (_b[0]=(int) _llim[0+0]; _b[0]<(int) _bbound[0+0]; _b[0]++) {
/*******
bvar0=b * abound
********/

        shift=_bvar0+0;
        offset0=_b+0;
        offset1=_abound+0;
        *(shift)= *(offset0);
        *(shift)*= *(offset1);


/*******
bvar1=(b - llim) * abound
********/

        shift=_bvar1+0;
        offset0=_b+0;
        offset1=_llim+0;
        offset2=_abound+0;
        *(shift)= *(offset0);
        *(shift)-= *(offset1);
        *(shift)*= *(offset2);


/*******
bvar2=b * abound
********/

        shift=_bvar2+0;
        offset0=_b+0;
        offset1=_abound+0;
        *(shift)= *(offset0);
        *(shift)*= *(offset1);


        for (_a[0]=0; _a[0]<(int) _abound[0+0]; _a[0]++) {
/*******
ind0=jvar + bvar0 + a
********/

          shift=_ind0+0;
          offset0=_jvar+0;
          offset1=_bvar0+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind1=jvar + bvar1 + a
********/

          shift=_ind1+0;
          offset0=_jvar+0;
          offset1=_bvar1+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
ind2=jvar + bvar2 + a
********/

          shift=_ind2+0;
          offset0=_jvar+0;
          offset1=_bvar2+0;
          offset2=_a+0;
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


/*******
index=ind0 - one
********/

          shift=_index+0;
          offset0=_ind0+0;
          *(shift)= *(offset0);
          *(shift)-= 1.000000;


/*******
pdrop drop xnew=(<ind0> psi x) + (<ind1> psi x) + (<ind2> psi x)
********/

          shift=_xnew+(int) _index[0+0];
          offset0=_x+((int) _ind0[0]);
          offset1=_x+((int) _ind1[0]);
          offset2=_x+((int) _ind2[0]);
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);


        }
      }
    }
  }
/*******
n=n - one
********/

  shift=_n+0;
  *(shift)-= 1.000000;


/*******
e=n
********/

  shift=_e+0;
  offset0=_n+0;
  *(shift)= *(offset0);


  for (_k[0]=0; _k[0]<1; _k[0]++) {
/*******
n=n * e
********/

    shift=_n+0;
    offset0=_e+0;
    *(shift)*= *(offset0);


  }
/*******
n=n - one
********/

  shift=_n+0;
  *(shift)-= 1.000000;


/*******
xnew=(xnew - xin) / n
********/

  printf ("n=%f\n", _n[0]);
  shift=_xnew+0;
  offset0=_xin+0;
  for (i0=0; i0<27; i0++) {
    *(shift)-= *(offset0);
    *(shift)/= _n[0+0];
    printf ("%4lg\n", *(shift));
    offset0+=1;
    shift+=1;
  }


}


