#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  double *shift;
  int forall_i0[1];
  int forall_i1[1];
  int forall_i2[1];
  double _a4[10*30];
  double _fish[10*30];
  double _b5[10*30];

/*******
a4=(<15.000000> drop ((<15.000000> drop fish) cat (<15.000000> take fish))) cat (<15.000000> take ((<15.000000> drop fish) cat (<15.000000> take fish)))
********/

  shift=_a4+0*30+0;
  offset0=_fish+10*30+0;
  for (i0=0; i0<10; i0++) {
    for (i1=0; i1<30; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


/*******
fish=(<5.000000> drop  omega <1.000000 1.000000> b5) cat  omega <1.000000 1.000000> (<5.000000> take  omega <1.000000 1.000000> b5)
********/

  for (forall_i2[0]=0; forall_i2[0]<0+10; forall_i2[0]++) {
    forall_i0[0]=forall_i2[0];
    shift=_fish+forall_i0[0]*30+0;
    offset0=_b5+forall_i0[0]*30+5;
    for (i1=0; i1<25; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
    forall_i1[0]=forall_i2[0];
    shift=_fish+forall_i1[0]*30+25;
    offset0=_b5+forall_i1[0]*30+0;
    for (i1=0; i1<5; i1++) {
      *(shift)= *(offset0);
      offset0+=1;
      shift+=1;
    }
  }


}


