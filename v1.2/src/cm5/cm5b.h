#include <cm/cmmd.h>

#define SEND(ptr,size,who) \
  CMMD_send(who,DEFAULT_TAG,ptr,size)
#define RECV(ptr,size,who) \
  CMMD_receive(who,DEFAULT_TAG,ptr,size)

#define SEND_HOST(ptr,size) \
  CMMD_send(host_node,DEFAULT_TAG,ptr,size)
#define RECV_HOST(ptr,size) \
  CMMD_receive(host_node,DEFAULT_TAG,ptr,size)

#define HOST_SEND(ptr,size,who) \
  CMMD_send(who,DEFAULT_TAG,ptr,size)
#define HOST_RECV(ptr,size,who) \
  CMMD_receive(who,DEFAULT_TAG,ptr,size)

#define WAIT

#define HOST_INIT(n_procs) \
  if (n_procs>CMMD_partition_size()) \
    return(0);

#define NODE_INIT(n_procs) \
  my_node=CMMD_self_address();\
  host_node=CMMD_host_node();\
  if (my_node>n_procs) return(0);

#define MY_PROC() my_node
#define DEFAULT_TAG 0

static int my_node,host_node;
