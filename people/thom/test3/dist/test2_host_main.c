#include <stdio.h>
#include <stdlib.h>

main ()
{
  int i, j, k, l;
  double in1[100], out1[100];

  l=0;
  for (j=0; j<1; j++) {
    for (k=0; k<100; k++) {
      in1[j*100+k]=(double)(l);
      l++;
    }
  }
  for (i=0; i<1; i++) {
    for (j=0; j<100; j++) {
      printf ("%5lg", in1[i*100+j]);
    }
  }
  test2(in1, out1);
}
