#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  double *shift;
  double _v[]={2.000000, 4.000000, 6.000000, 8.000000, 10.000000};
  int forall_i0[1];
  int forall_i1[1];
  double _res[5*5];

/*******
res=v ( +  omega <0.000000 0.000000> ) omega <0.000000 1.000000> v
********/

  for (forall_i0[0]=0; forall_i0[0]<0+5; forall_i0[0]++) {
    for (forall_i1[0]=0; forall_i1[0]<0+5; forall_i1[0]++) {
      shift=_res+(forall_i1[0]*5)+forall_i0[0];
      offset0=_v+forall_i0[0];
      *(shift)= *(offset0);
      shift=_res+(forall_i1[0]*5)+forall_i0[0];
      offset0=_v+forall_i1[0];
      *(shift)+= *(offset0);
      printf("%f \n ", *(shift));
    }
  }


}


