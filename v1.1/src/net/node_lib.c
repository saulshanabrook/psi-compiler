#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#ifndef NEXT
#include <unistd.h>
#include <malloc.h>
#endif

#include "ap.h"

#include "moalib.e"

struct sockaddr_in my_sin;
int daemon_sd;
static ap_t **cows;
static int n_procs;
static deja_vu=FALSE;
int my_proc_no;


/* prototypes */
void node_cleanup();


fatal(char *str)

{
  printf("Fatal error: %s.\n",str);
  exit(1);
}


int bind_sin(int port)
     
{
  int sd;
  struct hostent      *hp;
  
  if ((sd=socket(AF_INET,SOCK_STREAM,0))==-1) {
    perror("bind_sin");
    fatal("Could'nt connect to the host");
  }
  
  /* clear sin structure */
  memset(&my_sin,0,sizeof(my_sin));
  
  my_sin.sin_port=port;

  /* address type 
     my_sin.sin_family=hp->h_addrtype; */
  
  if (bind(sd,(struct sockaddr *) &my_sin,sizeof(my_sin))==-1) {
    perror("bind sin");
    fatal("Could'nt bind socket");
  }
  
  return(sd);
}


do_connect(int cow)
     
{
  int sd,bool=1,i;
  long id;
  char *id_buf;
  struct hostent *hp;
  struct sockaddr_in my_sin;
  
  sd=socket(PF_INET,SOCK_STREAM,0);
  
  /* get IP address */
  if ((hp=gethostbyname(cows[cow]->name))==NULL) {
    perror("do_connect");
    fatal("Gethostbyname failed");
  }
  
  
  /* clear my_sin structure */
  memset(&my_sin,0,sizeof(my_sin));
  
  /* load the IP address into my_sin */
  memcpy(&(my_sin.sin_addr),hp->h_addr,hp->h_length);
  
  my_sin.sin_port=cows[cow]->port;
  
  /* address type */
  my_sin.sin_family=hp->h_addrtype;
  
  while (connect(sd,(struct sockaddr *) &my_sin,sizeof(my_sin))!=0) {
    if (errno!=ETIMEDOUT) {
      perror("do_connect");
      do {
	sd=socket(PF_INET,SOCK_STREAM,0);
	close(sd);
      } while (connect(sd,(struct sockaddr *) &my_sin,sizeof(my_sin))!=0);
      fatal("Could'nt connect to node processor");
    }
  }

  if (setsockopt(sd,IPPROTO_TCP,TCP_NODELAY,(char *) &bool,sizeof(int))==-1) {
    puts("Warning: could'nt set TCP_NODELAY true");
  }
  cows[cow]->sd=sd;

  /* send the receiver my id number */
  id=htonl(my_proc_no);
  id_buf=(char *) (&id);
  for (i=0; i<sizeof(id); i+=write(sd,id_buf+i,sizeof(id)-i));
}


/* await_connect - listens for a socket connection */

await_connect(int cow)
     
{
  int ns,i;
  int bool=1;
  long id,tmp_id;
  char *id_buf;
  packet_t packet;
  
  do {
    if ((ns=accept(daemon_sd,0,0))==-1) fatal("lost connection");
    
    if (setsockopt(ns,IPPROTO_TCP,TCP_NODELAY,(char *) &bool,sizeof(int))==-1) {
      puts("could'nt set TCP_NODELAY true");
    }
    
    id_buf=(char *) (&tmp_id);
    for (i=0; i<sizeof(tmp_id); i+=read(ns,id_buf+i,sizeof(tmp_id)-i));
    id=(int) ntohl(tmp_id);
    
    cows[id+1]->sd=ns;
  } while ((id+1)!=cow);
}


int await_host()
     
{
  int ns,i;
  int bool=1;
  long id,tmp_id;
  char *id_buf;
  packet_t packet;
  
  listen(daemon_sd,5);
    
  if ((ns=accept(daemon_sd,0,0))==-1) fatal("lost connection");
    
  if (setsockopt(ns,IPPROTO_TCP,TCP_NODELAY,(char *) &bool,sizeof(int))==-1) {
    puts("could'nt set TCP_NODELAY true");
  }
  
  return(ns);
}


/* write_rec - sends a record with the length preceding it */

int write_rec(int sd,
	      void *buf,
	      long len)

{
  int i,size;
  char *data_buf,*len_buf;
  
  len=htonl(len);
  len_buf=(char *) (&len);
  for (i=0; i<sizeof(len); i+=write(sd,len_buf+i,sizeof(len)-i));
  data_buf=(char *) buf;
  i=0;
  while (i<len) {
    size=write(sd,data_buf+i,len-i);
    i+=size;
  }
}


int cow_write(int cow, void *buf, long len)

{
  if (cow>n_procs)
    fatal("Attempt to write to non-existing processor");
  
  if (cows[cow]->sd==-1) {
    do_connect(cow);
  }
  
  write_rec(cows[cow]->sd,buf,len);
}


/* read_rec - reads a record preceded by its length */

int read_rec(int sd,
	     void *buf,
	     long nbyte)

{
  long rec_len;
  int size,i,len;
  char *data_buf,*len_buf;

  len_buf=(char *) (&rec_len);
  for (i=0; i<sizeof(rec_len); i+=read(sd,len_buf+i,sizeof(rec_len)-i));
  len=(int) ntohl(rec_len);

  if (len>nbyte) {
    puts("overflow in read_rec");
    len=nbyte;
  }

  data_buf=(char *) buf;
  i=0;
  while (i<len) {
    size=read(sd,data_buf+i,len-i);
    i+=size;
  }

  return(len);
}


int cow_read(int cow, void *buf, long len)

{
  if (cow>n_procs) 
    fatal("Attempt to read from non-existing processor");
  
  if (cows[cow]->sd==-1) {
    await_connect(cow);
  }
  
  read_rec(cows[cow]->sd,buf,len);
}


int node_init()

{
  int sd;
  packet_t packet;
  int i,pid,friends;
  int my_port;

  if (deja_vu) return(TRUE);
  deja_vu=TRUE;
  atexit(node_cleanup);

/*  signal(SIGINT,disconnect); */
  daemon_sd=bind_sin(NETPORT);
  sd=await_host();

  read_rec(sd,&packet,sizeof(packet_t));
  if (packet.cmd!=CLUSTER_SIZE) {
    fatal("Host to node protocol error");
  } else {    
    friends=packet.arg;
    my_port=NETPORT;
    for (i=1; i<friends; i++) {
      pid=fork();
      if (pid==0) {
	my_port+=i;
	daemon_sd=bind_sin(my_port);
	sd=await_host();
	break;
      } else if (pid==-1) {
	fatal("Could'nt fork new process");
      }
    }
  }

  read_rec(sd,&packet,sizeof(packet_t));
  if (packet.cmd!=SET_ID) {
    fatal("Host to node protocol error");
  } else {
    my_proc_no=packet.arg;
    n_procs=packet.arg2;
  }

  cows=(ap_t **) get_mem((n_procs+1)*sizeof(ap_t *));

  cows[0]=(ap_t *) get_mem(sizeof(ap_t));
  cows[0]->sd=sd;

  for (i=1; i<=n_procs; i++) {
    cows[i]=(ap_t *) get_mem(sizeof(ap_t));
    cows[i]->id=i-1;
    cows[i]->sd=-1;
    cow_read(0,cows[i]->name,sizeof(cows[i]->name));
    cow_read(0,&(cows[i]->port),sizeof(cows[i]->port));
  }

#ifndef QUIET
  printf("Processor %d of %d on port %d, with %d local processors.\n",
	 my_proc_no,n_procs,my_port,friends);
  printf("Network configuration:\n");
  for (i=1; i<=n_procs; i++) {
    printf("%s on port %d is processor %d.\n",cows[i]->name,cows[i]->port,i-1);
  }
#endif

  return(TRUE);
}


void node_cleanup()

{
  int i;

  for (i=1; i<=n_procs; i++) {
    if (cows[i]->sd>=0)
      close(cows[i]->sd);
  }
  close(daemon_sd);
}
