#include <stdlib.h>
#include <stdlib.h>

main (int argc, char *argv[])
{
  int i, j, k;
  double in1[40*40], out1[40*40];
 
  k = 0; 
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 40 ; J++) {
      in1[i*40+j] = (double) k;
      k++
    }
  }

  test1 (argc, argv, in1, out1);
}

