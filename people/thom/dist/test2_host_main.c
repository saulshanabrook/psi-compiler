#include <stdio.h>
#include <stdlib.h>

main ()
{
  int i, j, k, l;
  double in1[9*300], out1[9*300];

  l=0;
  for (j=0; j<9; j++) {
    for (k=0; k<300; k++) {
      in1[j*300+k]=(double)(l);
      l++;
    }
  }
  for (i=0; i<9; i++) {
    for (j=0; j<300; j++) {
      printf ("%5lg", in1[i*300+j]);
    }
  }
  test2(in1, out1);
}
