#include <cm/cmmd.h>

#define SEND(ptr,size,who) \
  CMMD_free_mcb(CMMD_send_async(who,DEFAULT_TAG,ptr,size,NULL))
#define RECV(ptr,size,who) \
  CMMD_free_mcb(CMMD_receive_async(who,DEFAULT_TAG,ptr,size,NULL))

#define SEND_HOST(ptr,size) \
  CMMD_free_mcb(CMMD_send_async(host_node,DEFAULT_TAG,ptr,size,NULL))
#define RECV_HOST(ptr,size) \
  CMMD_free_mcb(CMMD_receive_async(host_node,DEFAULT_TAG,ptr,size,NULL))

#define HOST_SEND(ptr,size,who) \
  CMMD_free_mcb(CMMD_send_async(who,DEFAULT_TAG,ptr,size,NULL))
#define HOST_RECV(ptr,size,who) \
  CMMD_free_mcb(CMMD_receive_async(who,DEFAULT_TAG,ptr,size,NULL))

#define WAIT \
  CMMD_all_msgs_wait()

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
