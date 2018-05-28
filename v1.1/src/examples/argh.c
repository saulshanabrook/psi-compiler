#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  int i1;
  int i2;
  double *shift;
  double _foo[]={0.000000, 0.000000, 0.000000, 1.000000, 0.000000,
    2.000000, 0.000000, 3.000000, 0.000000, 4.000000,
    1.000000, 0.000000, 1.000000, 1.000000, 1.000000,
    2.000000, 1.000000, 3.000000, 1.000000, 4.000000};
  int forall_i0[2];
  int forall_i1[2];
  int tmp_vect0[2];
  int tmp_vect1[2];
  double *temp1;
  double _goat[2*5];
  double _duck[2*5];

/*******
goat=((( iota ( shp duck))) psi  omega <1.000000 2.000000> duck) + (( iota ( shp (duck))) psi  omega <1.000000 2.000000> duck)
********/

  temp1=(double *) get_mem((1)*sizeof(double));
  for (forall_i0[0]=0; forall_i0[0]<0+2; forall_i0[0]++) {
    for (forall_i0[1]=0; forall_i0[1]<0+5; forall_i0[1]++) {
      shift=tmp_vect0+0;
      *(shift)= forall_i0[0];
      shift++;
      *(shift)= forall_i0[0];
      shift++;
      shift=_goat+forall_i0[0]*5+forall_i0[1];
      offset0=_duck+tmp_vect0[0]*5+tmp_vect0[1];
      *(shift)= *(offset0);
    }
  }
  for (forall_i1[0]=0; forall_i1[0]<0+2; forall_i1[0]++) {
    for (forall_i1[1]=0; forall_i1[1]<0+5; forall_i1[1]++) {
      shift=tmp_vect1+0;
      *(shift)= forall_i1[0];
      shift++;
      *(shift)= forall_i1[0];
      shift++;
      shift=temp1+0;
      offset0=_duck+tmp_vect1[0]*5+tmp_vect1[1];
      *(shift)= *(offset0);
      shift=_goat+forall_i1[0]*5+forall_i1[1];
      offset0=temp1+0;
      *(shift)+= *(offset0);
    }
  }
  free(temp1);


}


