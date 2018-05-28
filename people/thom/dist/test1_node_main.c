#include <stdio.h>
#include "mpimac.h"

printout2(double *what)
{
  int i, j;
  char fname[20];

  sprintf (fname, "mmout%d.dat", my_node);
  out = fopen (fname, "w");

  fprintf (fout, "processor %d\n\n", my_node);
  for (i=0; i<(4; i++) {
    for (j=0; j<4; j++) 
      fprintf (out, "%4lg ",what[i*4+j]);
    printf ("\n");
  }
  fclose (fname);
}

main (int argc, char *argv[])
{
  int i, j, k, l;
  double in1[4*4], in2[4*4], out1[4*4];

  l=0;
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
        in1[i*4+j]=(double)(l);
        in2[i*4+j]=(double)(l);
        l++;
      }
    }
  }

  test1(argc, argv, in1, in2, out1);
}
