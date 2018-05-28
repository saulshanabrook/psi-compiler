#define MY_PROC() my_proc_no

#define SEND(ptr,size,proc) cow_write((proc)+1,(void *) (ptr),size)
#define RECV(ptr,size,proc) cow_read((proc)+1,(void *) (ptr),size);

#define SEND_HOST(ptr,size) cow_write(0,(void *) (ptr),size)
#define RECV_HOST(ptr,size) cow_read(0,(void *) (ptr),size);

#define HOST_SEND(ptr,size,proc) cow_write(proc,(void *) (ptr),size)
#define HOST_RECV(ptr,size,proc) cow_read(proc,(void *) (ptr),size);

#define HOST_INIT(procs) host_init(procs)
#define HOST_CLEANUP() host_cleanup()
#define NODE_INIT(procs) node_init()
#define NODE_CLEANUP() node_cleanup()

#define WAIT

extern int my_proc_no;
extern int host_init(int min_procs);
extern int node_init();
extern int cow_write(int cow, void *buf, long len);
extern int cow_read(int cow, void *buf, long len);
