heat3d(int _i, int _n, double _A[], double _lambda[])

{
  double *offset0;
  double *offset1;
  double *offset2;
  double *offset3;
  double *offset4;
  double *offset5;
  double *offset6;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _b[3];
  double _m_lambda[1];
  double consta0[3];
  double consta1[3];
  double *_A2;
  double _t[1];
  int scalar4;
  int scalar5;
  int scalar6;
  int scalar7;
  int scalar8;
  int scalar9;
  int scalar10;
  int scalar11;

/*******
m_lambda=nsix * lambda + one
********/

  shift=_m_lambda+0;
  offset1=_lambda+0;
  *(shift)= -6.000000;
  *(shift)*= *(offset1);
  *(shift)+= 1.000000;


/*******
b=<n n n> - <2.000000 2.000000 2.000000>
********/

  shift=_b+0;
  consta0[0]=(((int) _n));
  consta0[1]=(((int) _n));
  consta0[2]=(((int) _n));
  offset0=consta0+0;
  consta1[0]=2.000000;
  consta1[1]=2.000000;
  consta1[2]=2.000000;
  offset1=consta1+0;
  for (i0=0; i0<(3); i0++) {
    *(shift)= *(offset0);
    *(shift)-= *(offset1);
    offset1+=(1);
    offset0+=(1);
    shift++;
  }


  _A2=(double *) get_mem(((((int) _b[0+0]))*(((int) _b[1+0]))*(((int) _b[2+0])))*sizeof(double));

  for (_t[0]=0; _t[0]<(((int) _i)); _t[0]++) {
/*******
A2=((b take (<1.000000 2.000000 1.000000> drop A)) + (b take (<1.000000 0.000000 1.000000> drop A)) + (b take (<1.000000 1.000000 2.000000> drop A)) + (b take (<1.000000 1.000000 0.000000> drop A)) + (b take (<2.000000 1.000000 1.000000> drop A)) + (b take (<0.000000 1.000000 1.000000> drop A))) * lambda
********/

    shift=_A2+0*(int) (((int) _b[1+0]))+0*(int) (((int) _b[2+0]))+0;
    offset0=_A+1*(int) ((((int) _n))*(((int) _n)))+2*(int) (((int) _n))+1;
    scalar0=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar1=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    offset1=_A+1*(int) ((((int) _n))*(((int) _n)))+0*(int) (((int) _n))+1;
    scalar2=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar3=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    offset2=_A+1*(int) ((((int) _n))*(((int) _n)))+1*(int) (((int) _n))+2;
    scalar4=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar5=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    offset3=_A+1*(int) ((((int) _n))*(((int) _n)))+1*(int) (((int) _n))+0;
    scalar6=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar7=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    offset4=_A+2*(int) ((((int) _n))*(((int) _n)))+1*(int) (((int) _n))+1;
    scalar8=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar9=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    offset5=_A+0*(int) ((((int) _n))*(((int) _n)))+1*(int) (((int) _n))+1;
    scalar10=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar11=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    for (i0=0; i0<(int) _b[0+(0)]; i0++) {
      for (i1=0; i1<(int) _b[1+(0)]; i1++) {
        for (i2=0; i2<(int) _b[2+(0)]; i2++) {
          *(shift)= *(offset0);
          *(shift)+= *(offset1);
          *(shift)+= *(offset2);
          *(shift)+= *(offset3);
          *(shift)+= *(offset4);
          *(shift)+= *(offset5);
          *(shift)*= _lambda[0+0];
          offset5+=(1);
          offset4+=(1);
          offset3+=(1);
          offset2+=(1);
          offset1+=(1);
          offset0+=(1);
          shift++;
        }
        offset5+=((int) scalar10);
        offset4+=((int) scalar8);
        offset3+=((int) scalar6);
        offset2+=((int) scalar4);
        offset1+=((int) scalar2);
        offset0+=((int) scalar0);
        shift+=0;
      }
      offset5+=((int) scalar11);
      offset4+=((int) scalar9);
      offset3+=((int) scalar7);
      offset2+=((int) scalar5);
      offset1+=((int) scalar3);
      offset0+=((int) scalar1);
      shift+=0;
    }


/*******
<1.000000 1.000000 1.000000> pdrop A=(b take (<1.000000 1.000000 1.000000> drop A)) * m_lambda + A2
********/

    shift=_A+1*(int) (((int) _n))+1*(int) (((int) _n))+1;
    offset1=_A2+0*(int) ((((int) _b[2+0]))*(((int) _b[1+0])))+0*(int) (((int) _b[2+0]))+0;
    scalar0=(((int) _n)+(-1)*(((int) _b[2+0])));
    scalar1=(((-1)*(((int) _n)))*(((int) _b[1+0]))+(((int) _n))*(((int) _n)));
    for (i0=0; i0<(((int) _b[0+0])); i0++) {
      for (i1=0; i1<(((int) _b[1+0])); i1++) {
        for (i2=0; i2<(((int) _b[2+0])); i2++) {
          *(shift)*= _m_lambda[0+0];
          *(shift)+= *(offset1);
          offset1+=(1);
          shift++;
        }
        offset1+=0;
        shift+=((int) scalar0);
      }
      offset1+=0;
      shift+=((int) scalar1);
    }


  }
  free(_A2);
}
