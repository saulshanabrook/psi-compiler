#include <stdio.h>

printout(double what[])
{
  int i, j;

  for (i=0; i<1; i++) {
    for (j=0; j<25; j++) 
      printf ("%4lg ",what[i*25+j]);
    printf ("\n");
  }
}

main ()
{
  test2();
}
