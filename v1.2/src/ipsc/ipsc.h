#include <cube.h>
 
#define SEND(ptr,size,who) \
  csend(my_node, ptr, size, who, 0)
 
#define RECV(ptr,size,who) \
  crecv(who, ptr, size)
 
#define SEND_HOST(ptr,size) \
  csend(0, ptr, size, host_node)
 
#define RECV_HOST(ptr,size) \
  crecv(0, ptr, size)
 
#define HOST_SEND(ptr,size,who) \
  csend(my_node, ptr, size, who)
 
#define HOST_RECV(ptr,size,who) \
  crecv(who, ptr, size)
 
#define WAIT { }
 
/*  gsync() */
 
#define HOST_INIT(n_procs) \
   if (n_procs > numnodes()) return(0);
 
#define NODE_INIT(n_procs) \
  my_node=mynode();  \
  host_node=0;       \
  if (my_node > n_procs) return(0);
 
#define MY_PROC() my_node
#define DEFAULT_TAG 0
 
static int my_node,host_node;

