#include <stdio.h>
#include <stdlib.h>
 
#include "/software/all/mpi/include/mpi.h"
#include <f90.h>
 
extern int my_node;

void printout (float a[100])
{
  int i,j;

  printf ("in printout\n");
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf ("%4lg ", a[i*10+j]);
    }
    printf ("\n");
  }
}

void main (int argc, char *argv[])
{
  float a[100], b[100];
  int i;
  Dope1 dopea, dopeb;

/*  MPI_Init (&argc, &argv);
   MPI_Comm_rank (MPI_COMM_WORLD, &my_node); */

  if (my_node == 0) {
    for (i = 0; i < 100; i++) {
      b[i] = (float) i;
    }
  }

  if (my_node == 0) {
    printf ("array a:\n\n");
    printout (a);
    printf ("array b:\n\n");
    printout (b);
  }
  printf ("here in the beginning....\n");
  dopea.addr = (Pointer)a;
  printf ("here in the beginning....\n");
  dopea.offset = 0;
  printf ("here in the beginning....\n");
  dopea.dim[0].extent=99;
  printf ("here in the beginning....\n");
  dopea.dim[0].mult=1;
  printf ("here in the beginning....\n");
  dopea.dim[0].lower=0;
  printf ("here in the beginning....\n");
  dopeb.addr = (Pointer)b;
  printf ("here in the beginning....\n");
  dopeb.offset = 0;
  printf ("here in the beginning....\n");
  dopeb.dim[0].extent=99;
  printf ("here in the beginning....\n");
  dopeb.dim[0].mult=1;
  printf ("here in the beginning....\n");
  dopeb.dim[0].lower=0;
  printf ("node %d starting test\n", my_node);
  test_ (&dopea, &dopeb);
  printf ("node %d ending test\n", my_node);
  if (my_node == 0) {
    printf ("array a:\n\n");
    printout (a);
    printf ("array b:\n\n");
    printout (b);
  }
}
