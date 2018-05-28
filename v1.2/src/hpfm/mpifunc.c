#include <stdio.h>
#include <stdlib.h>

#include "/software/all/mpi/include/mpi.h"

MPI_Status status;
int my_node;

int mpi_my_node_ ()
{
  return (my_node);
}

void mpi_send_ (float **ptr, int *size, int *proc)
{
  MPI_Send (*ptr, *size/sizeof(float), MPI_FLOAT, *proc, 0, MPI_COMM_WORLD);
}

void mpi_recv_ (float **ptr, int *size, int *proc)
{
  MPI_Recv (*ptr, *size/sizeof(float), MPI_FLOAT, *proc, 0, MPI_COMM_WORLD,
    &status);
}

void mpi_init_ (int *argc, char **argv)
{
  printf ("MPI_INIT_ CALLED\n");
  MPI_Init (argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_node);
  printf ("my_node = %d\n", my_node);
}

void mpi_host_init_ ()
{
  MPI_Init (0, NULL);
}

void host_cleanup_ ()
{
  MPI_Finalize ();
}

void mpi_node_init_ ()
{
  char *string;
  char **pointer;
  int *num;
  
  string = (char *) malloc (30); 
  sprintf (string, "hell");
  pointer = &string;
  *num = 1;
  if (my_node == 0) { printf ("here\n"); }
  MPI_Init (num, &pointer);
  if (my_node == 0) { printf ("here\n"); }
  MPI_Comm_rank (MPI_COMM_WORLD, &my_node);
  if (my_node == 0) { printf ("here\n"); }
}

void node_cleanup_ ()
{
  MPI_Finalize ();
}

void mpi_wait_ ()
{
}
