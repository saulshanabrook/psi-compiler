#include <stdio.h>
#include <stdlib.h>

main ()
{
  int i, j, k, l;
  double in1[20*30*10], in2[20*30*10], out1[20*30*10];

  l=0;
  for (i=0; i<20; i++) {
    for (j=0; j<30; j++) {
      for (k=0; k<10; k++) {
        in1[i*300+j*10+k]=(double)(l);
        in2[i*300+j*10+k]=(double)(l);
        l++;
      }
    }
  }

  test3(in1, in2, out1);
}
