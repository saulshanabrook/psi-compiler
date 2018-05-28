#include <stdlib.h>
#include <stdio.h>

printout2(double *what, int node)
{
  FILE *fout;
  int i, j, k;
  char fname[20];

  sprintf (fname, "mmout%d.dat", node);
  fout = fopen (fname, "w");

  fprintf (fout, "processor %d:\n\n", node);
  for (i=0; i<10; i++) {
    for (j=0; j<10; j++) {
      for (k = 0; k < 4; k++)
        fprintf (fout, "%4lg ",what[i*40+j*4+k]);
      fprintf (fout, "\n");
    }
  }
  fclose (fout);
}

main (int argc, char *argv[])
{
  int i, j, k, l;
  double in1[4*4], in2[4*4], out1[4*4];

  printf ("%d\n", argc);
  for (i = 0; i < (argc - 1); i++)
    printf ("%s\n", argv[i+1]);
  
  l=0;
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      in1[i*4+j]=(double)(l);
      in2[i*4+j]=(double)(l);
      l++;
    }
  }

  test1();
}
