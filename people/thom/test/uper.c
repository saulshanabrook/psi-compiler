#include <stdlib.h>
#include "moalib.e"

one_to_two(double _in[], double _out[])

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[2];
  int forall_i3[2];
  int forall_i4[3];
  double _mid1[10*5*5];
  int *temp1;
  double _mid2[10*10*5];
  int scalar0;
  int *temp2;
  double _mid3[10*10*10];

/*******
mid1=in cat  omega <2.000000 2.000000> (in +  + ((<1.000000> drop in) cat (<1.000000> take in)))
********/

  for (forall_i0[0]=0; forall_i0[0]<0+5; forall_i0[0]++) {
    shift=_mid1+(((int) forall_i0[0+0]))*(int) 25+(0)*(int) 5+(0);
    offset0=_in+(((int) forall_i0[0+0]))*(int) 25+(0)*(int) 5+(0);
    for (i1=0; i1<5; i1++) {
      for (i2=0; i2<5; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_mid1+(((int) forall_i0[0+0]))*(int) 125+(5)*(int) 5+(0);
    offset0=_in+(((int) forall_i0[0+0]))*(int) 25+(0)*(int) 5+(0);
    for (i1=0; i1<5; i1++) {
      for (i2=0; i2<5; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
    }
    shift=_mid1+(((int) forall_i0[0+0]))*(int) 125+(5)*(int) 5+(0);
    offset0=_in+(1+min(((int) forall_i0[0+0]),4))*(int) 25+(0)*(int) 5+(0);
    for (i0=0; i0<(min(1,(4)-(min(((int) forall_i0[0+0]),4)))); i0++) {
      for (i1=0; i1<(5); i1++) {
        for (i2=0; i2<(5); i2++) {
          *(shift)+= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      offset0+=20;
      shift+=-25;
    }
    shift=_mid1+(((int) forall_i0[0+0])+min(1,(4)-(min(((int) forall_i0[0+0]),4))))*(int) 125+(5)*(int) 5+(0);
    offset0=_in+((((int) forall_i0[0+0]))-(min(((int) forall_i0[0+0]),4)))*(int) 25+(0)*(int) 5+(0);
    for (i0=0; i0<((1)-(min(1,(4)-(min(((int) forall_i0[0+0]),4))))); i0++) {
      for (i1=0; i1<(5); i1++) {
        for (i2=0; i2<(5); i2++) {
          *(shift)+= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      offset0+=20;
      shift+=-25;
    }
  }


/*******
mid2=mid1 cat  omega <1.000000 1.000000> (mid1 +  + ((<0.000000 1.000000> drop mid1) cat  omega <2.000000 2.000000> (<5.000000 1.000000> take mid1)))
********/

  for (forall_i2[0]=0; forall_i2[0]<0+5; forall_i2[0]++) {
    for (forall_i2[1]=0; forall_i2[1]<0+5; forall_i2[1]++) {
      temp1=(int *) get_mem((5)*sizeof(int));
      shift=_mid2+(((int) forall_i2[0+0]))*(int) 50+(((int) forall_i2[1+0]))*(int) 5+(0);
      offset0=_mid1+(((int) forall_i2[0+0]))*(int) 25+(((int) forall_i2[1+0]))*(int) 5+(0);
      for (i2=0; i2<5; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      shift=_mid2+(((int) forall_i2[0+0]))*(int) 250+(((int) forall_i2[1+0]))*(int) 5+(5);
      offset0=_mid1+(((int) forall_i2[0+0]))*(int) 25+(((int) forall_i2[1+0]))*(int) 5+(0);
      for (i2=0; i2<5; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      for (forall_i1[0]=(((int) forall_i2[0+0])); forall_i1[0]<(((int) forall_i2[0+0]))+1; forall_i1[0]++) {
        shift=temp1+0*(int) 5+0;
        offset0=_mid1+(((int) forall_i1[0+0]))*(int) 25+(1+min(((int) forall_i2[1+0]),4))*(int) 5+(0);
        scalar0=((25)-((5)*(min(1,(4)-(min(((int) forall_i2[1+0]),4))))));
        for (i1=0; i1<(min(1,(4)-(min(((int) forall_i2[1+0]),4)))); i1++) {
          for (i2=0; i2<(5); i2++) {
            *(shift)= *(offset0);
            offset0+=1;
            shift+=1;
          }
          offset0+=0;
        }
        shift=temp1+(min(1,(4)-(min(((int) forall_i2[1+0]),4))))*(int) 5+(0);
        offset0=_mid1+(((int) forall_i1[0+0]))*(int) 25+((((int) forall_i2[1+0]))-(min(((int) forall_i2[1+0]),4)))*(int) 5+(0);
        scalar0=((25)-((5)*((1)-(min(1,(4)-(min(((int) forall_i2[1+0]),4)))))));
        for (i1=0; i1<((1)-(min(1,(4)-(min(((int) forall_i2[1+0]),4))))); i1++) {
          for (i2=0; i2<(5); i2++) {
            *(shift)= *(offset0);
            offset0+=1;
            shift+=1;
          }
          offset0+=0;
        }
        shift=_mid2+(((int) forall_i1[0+0]))*(int) 250+(((int) forall_i2[0+1]))*(int) 5+(5);
        offset0=temp1+0*(int) 5+0;
        for (i1=0; i1<(5); i1++) {
          *(shift)+= *(offset0);
          offset0+=1;
          shift+=1;
        }
      }
      free(temp1);
    }
  }


/*******
mid3=mid2 cat  omega <0.000000 0.000000> (mid2 +  + ((<0.000000 0.000000 1.000000> drop mid2) cat  omega <1.000000 1.000000> (<5.000000 5.000000 1.000000> take mid2)))
********/

  for (forall_i4[0]=0; forall_i4[0]<0+5; forall_i4[0]++) {
    for (forall_i4[1]=0; forall_i4[1]<0+5; forall_i4[1]++) {
      for (forall_i4[2]=0; forall_i4[2]<0+5; forall_i4[2]++) {
        temp2=(int *) get_mem((1)*sizeof(int));
        shift=_mid3+(int) forall_i4[0+(0)]*(int) 100+(int) forall_i4[1+(0)]*(int) 10+(int) forall_i4[2+(0)];
        offset0=_mid2+(int) forall_i4[0+(0)]*(int) 50+(int) forall_i4[1+(0)]*(int) 5+(int) forall_i4[2+(0)];
        *(shift)= *(offset0);
        shift=_mid3+(((int) forall_i4[0+0]))*(int) 1000+(((int) forall_i4[1+0]))*(int) 10+(((int) forall_i4[0+2])+1);
        offset0=_mid2+(int) forall_i4[0+(0)]*(int) 50+(int) forall_i4[1+(0)]*(int) 5+(int) forall_i4[2+(0)];
        *(shift)= *(offset0);
        for (forall_i3[0]=(int) forall_i4[0+(0)]; forall_i3[0]<(int) forall_i4[0+(0)]+1; forall_i3[0]++) {
          for (forall_i3[1]=(int) forall_i4[1+(0)]; forall_i3[1]<(int) forall_i4[1+(0)]+1; forall_i3[1]++) {
            shift=temp2+0;
            offset0=_mid2+(((int) forall_i3[0+0]))*(int) 50+(((int) forall_i3[1+0]))*(int) 5+(1+min(((int) forall_i4[0+2]),4));
            scalar0=((5)-(min(1,(4)-(min(((int) forall_i4[0+2]),4)))));
            for (i2=0; i2<(min(1,(4)-(min(((int) forall_i4[0+2]),4)))); i2++) {
              *(shift)= *(offset0);
              offset0+=1;
              shift+=0;
            }
            shift=temp2+(min(1,(4)-(min(((int) forall_i4[0+2]),4))));
            offset0=_mid2+(((int) forall_i3[0+0]))*(int) 50+(((int) forall_i3[1+0]))*(int) 5+((((int) forall_i4[0+2]))-(min(((int) forall_i4[0+2]),4)));
            scalar0=((5)-((1)-(min(1,(4)-(min(((int) forall_i4[0+2]),4))))));
            for (i2=0; i2<((1)-(min(1,(4)-(min(((int) forall_i4[0+2]),4))))); i2++) {
              *(shift)= *(offset0);
              offset0+=1;
              shift+=0;
            }
            shift=_mid3+(((int) forall_i3[0+0]))*(int) 1000+(((int) forall_i3[1+0]))*(int) 10+(((int) forall_i4[0+2])+1);
            offset0=temp2+0;
            *(shift)+= *(offset0);
          }
        }
        free(temp2);
      }
    }
  }


/*******
out=<-1.000000 -1.000000 -1.000000> drop mid3
********/

  shift=_out+0*(int) 81+0*(int) 9+0;
  offset0=_mid3+0*(int) 100+0*(int) 10+0;
  for (i0=0; i0<9; i0++) {
    for (i1=0; i1<9; i1++) {
      for (i2=0; i2<9; i2++) {
        *(shift)= *(offset0);
        offset0+=1;
        shift+=1;
      }
      offset0+=1;
    }
    offset0+=10;
  }


}


