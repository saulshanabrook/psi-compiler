#include <mpi.h>


#define MY_PROC() my_proc_no

#define SEND(ptr,size,proc) MPI_Send(ptr,size/sizeof(double),MPI_DOUBLE,proc,0,MPI_COMM_WORLD)
#define RECV(ptr,size,proc) MPI_Recv(ptr,size/sizeof(double),MPI_DOUBLE,proc,0,MPI_COMM_WORLD,&status)

#define SEND_HOST(ptr,size) MPI_Send(ptr,size/sizeof(double),MPI_DOUBLE,0,0,MPI_COMM_WORLD)
#define RECV_HOST(ptr,size) MPI_Recv(ptr,size/sizeof(double),MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status)

#define HOST_SEND(ptr,size,proc) MPI_Send(ptr,size/sizeof(double),MPI_DOUBLE,proc,0,MPI_COMM_WORLD)
#define HOST_RECV(ptr,size,proc) MPI_Recv(ptr,size/sizeof(double),MPI_DOUBLE,proc,0,MPI_COMM_WORLD,&status)

#define HOST_INIT(argc,argv) MPI_Init(&argc,&argv)
#define HOST_CLEANUP() MPI_Finalize()
#define NODE_INIT(argc,argv) MPI_Init(&argc,&argv);   \
	MPI_Comm_rank (MPI_COMM_WORLD, &my_proc_no)
#define NODE_CLEANUP() MPI_Finalize()

#define WAIT

MPI_Status status;
static int my_proc_no;

