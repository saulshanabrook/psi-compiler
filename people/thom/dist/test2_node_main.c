#include <stdio.h>

printout(double what[])
{
  int i, j;

  for (i=0; i<3; i++) {
    for (j=0; j<300; j++) 
      printf ("%4lg ",what[i*300+j]);
    printf ("\n");
  }
}

main ()
{
  test2();
}
