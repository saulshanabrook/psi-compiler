#define MY_PROC() my_proc_no

#define SEND(ptr,size,proc) printf("sending to %d\n",proc);
#define RECV(ptr,size,proc) printf("receiving from %d\n",proc);

#define SEND_HOST(ptr,size) printf("sending to host\n");
#define RECV_HOST(ptr,size) printf("receiving from host\n");

#define HOST_SEND(ptr,size,proc) printf("sending to %d\n",proc);
#define HOST_RECV(ptr,size,proc) printf("receiving from %d\n",proc);

#define HOST_INIT(procs) 
#define NODE_INIT(procs) \
printf("Processor #:");\
scanf("%d",&my_proc_no)

#define WAIT

int my_proc_no;
