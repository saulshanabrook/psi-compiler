#include <stdio.h>
#include <stdlib.h>


main ()
{
  int i, j, k, l;
  double in1[40*40], in2[40*40], out1[40*40];

  l=0;
  for (i=0; i<40; i++) {
    for (j=0; j<40; j++) {
        in1[i*40+j]=(double)(l);
        in2[i*40+j]=(double)(l);
        l++;
    }
  }

  test1(in1, out1);
}
