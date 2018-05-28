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


static ap_t **nodes;
static int n_nodes;
static deja_vu=FALSE;
static int daemon_sd=-1;              /* daemon socket discriptor */
static struct sockaddr_in daemon_my_sin; /* my_sin structure for the daemon */


/* prototypes */
void host_cleanup();


fatal(char *str)

{
  printf("Fatal error: %s.\n",str);
  exit(1);
}


/* write_rec - sends a record with the length preceding it */

int write_rec(int fd,
	      void *inbuf,
	      long len)

{
  int i;
  char *buf;
  int size;
  
  buf=(char *) inbuf;
  
  len=htonl(len);
  for (i=0; i<sizeof(len); i+=write(fd,&len+i,sizeof(len)-i));
  for (i=0; i<len; i+=size) {
    size=write(fd,buf+i,len-i);
    if (size<0) {
      perror("write_rec");
      break;
    }
  }  
}


int cow_write(int cow, void *buf, long len)

{
  if (cow>n_nodes)
    fatal("Attempt to write to non-existing processor");
  
  write_rec(nodes[cow]->sd,buf,len);
}


/* read_rec - reads a record preceded by its length */

int read_rec(int fd,
             void *inbuf,
             long nbyte)
     
{
  long len;
  int i,v;
  char *buf;
  
  buf=(char *) inbuf;
  
  /*for (i=0; i<sizeof(len); i+=read(fd,&len+i,sizeof(len)-i)); */
  i=0;
  while (i<sizeof(len)) {
    while ((v=read(fd,&len+i,sizeof(len)-i))==-1);
    i+=v;
  }
  
  len=ntohl(len);
  if (len<=nbyte)  {
    i=0;
    while (i<len) {
      while ((v=read(fd,buf+i,len-i))==-1);
      i+=v;
    }
  }
  /* for (i=0; i<len; i+=read(fd,buf+i,len-i)); */
  else return(-1);
  return(len);
}


int cow_read(int cow, void *buf, long len)

{
  if (cow>=n_nodes) 
    fatal("Attempt to write to non-existing processor");
  
  read_rec(nodes[cow]->sd,buf,len);
}


/* bind - binds a socket descriptor to listen for connections
   to the local machine. Returns TRUE on error. */

int bind_sin()
     
{
  struct hostent      *hp;
  int foo=1;
  
  if ((daemon_sd=socket(AF_INET,SOCK_STREAM,0))==-1) {
    perror("bind");
    return(TRUE);
  }
  
  setsockopt(daemon_sd,SOL_SOCKET,SO_REUSEADDR,(char *) &foo,sizeof foo);
  
  /* clear my_sin structure */
  memset(&daemon_my_sin,0,sizeof(daemon_my_sin));
  
  daemon_my_sin.sin_port=NETPORT;
  
  /* address type 
     daemon_my_sin.sin_family=hp->h_addrtype; */
  
  if (bind(daemon_sd,(struct sockaddr *) &daemon_my_sin,sizeof(daemon_my_sin))==-1) {
    perror("bind");
    return(TRUE);
  }
  
  return(FALSE);
}


/********************* export procedures *********************/

/* attach_ap - attempts to attach to a named machine.  A pointer
   to an attacthed processor is returned or NULL on error. */

ap_t *attach_ap(char *name,int port,int id)
     
{
  int bool=1;
  ap_t *new_ap;
  struct hostent      *hp;
  struct sockaddr_in  my_sin;
  packet_t packet;

  new_ap=(ap_t *) get_mem(sizeof(ap_t));
  
  strcpy(new_ap->name,name);
  new_ap->id=id;
  new_ap->port=port;
  
  /* open a new socket */
  if ((new_ap->sd=socket(AF_INET,SOCK_STREAM,0))==-1) {
    perror("attach_ap");
    return(NULL);
  }
  
  /* get the host information */
  if ((hp=gethostbyname(name))==NULL) {
    perror("attach_ap");
    return(NULL);
  }
  
  /* clear my_sin structure */
  memset(&my_sin,0,sizeof(my_sin));
  
  /* load the IP address into my_sin */
  memcpy(&(my_sin.sin_addr),hp->h_addr,hp->h_length);
  
  my_sin.sin_port=new_ap->port;  /* socket port number */
  
  /* address type */
  my_sin.sin_family=hp->h_addrtype;
  
  /* connect to processor element */
  if (connect(new_ap->sd,(struct sockaddr *) &my_sin,sizeof(my_sin))==-1) {
    return(NULL);
  }

  /*
    if (setsockopt(new_ap->sd,IPPROTO_TCP,TCP_NODELAY,(char *) &bool,sizeof(int))==-1) {
    puts("Could not set TCP_NODELAY option");
    }
    */

  return(new_ap);
}


/* detach_ap - detach from an attached processor 
   effectivly clomy_sing the socket connection. */

detach_ap(ap_t *ap)
     
{
  if (ap->sd>=0) {
    close(ap->sd);
  }
}


/* init_proc_no - tell the attached processor how many local processors
   there are */

int init_multiprocess(ap_t *ap, int no_proc)
     
{
  packet_t packet;
  
  if (ap->sd>0) {
    packet.cmd=CLUSTER_SIZE;
    packet.arg=no_proc;
    if (write_rec(ap->sd,(char *) &packet, sizeof(packet))==-1) {
    return(TRUE);
    }
  }
  else return(TRUE);
  
  return(FALSE);
}


ap_t **find_aps(int num, char **name, int *dim, int *n_procs)

{
  ap_t **ap;
  int cnt,i,proc_no,size,sub_proc_no;
  int last;

  size=0;
  for (i=0; i<num; i++) {
    size+=dim[i];
  }

  ap=(ap_t **) get_mem(size*sizeof(ap_t *));

  cnt=0;
  proc_no=0;
  while (cnt<num) {
#ifndef QUIET
    printf("attempt %s",name[cnt]);
#endif    

    sub_proc_no=0;
    ap[proc_no]=attach_ap(name[cnt],NETPORT,proc_no);
    if (ap[proc_no]!=NULL) {
      last=proc_no;
      init_multiprocess(ap[proc_no],dim[cnt]);
      proc_no++;
      for (i=1, sub_proc_no=1; i<dim[cnt]; i++) {
	if ((ap[proc_no]=
	     attach_ap(name[cnt],NETPORT+sub_proc_no,proc_no))!=NULL) {
#ifndef QUIET
	  printf("(%d)",i);
#endif
	  proc_no++;
	  sub_proc_no++;
	} else {
	  puts("Warning failed to connect multiprocessor.");
	  sub_proc_no=0;
	  proc_no=last;
	  break;
	}
      }
    }
    
#ifndef QUIET
    if (sub_proc_no==0) printf(" - failed.\n");
    else printf(" ok.\n");
#endif
    cnt++;
  }

  *n_procs=proc_no;
  return(ap);
}


free_ap(ap_t **ap, int n_procs)

{
  int i;

  for (i=0; i<n_procs; i++) {
      detach_ap(ap[i]);
  }
}


/* strip - removes leading garbage and places a '\0' at the end of the valid 
     string of characters. */

strip(char *buf,char *name,int *num)
     
{
  char *ch;
  
  ch=buf;
  while ((*ch!='\0')&&(!isalnum(*ch))) ch++;
  while ((*ch!='\0')&&(isalnum(*ch))) {
    *name=*ch;
    *name++;
    ch++;
  }
  *name='\0';
  while ((*ch!='\0')&&(!isalnum(*ch))) ch++;
  *num=atoi(ch);
}


int host_init(int min_procs)

{
  FILE *fp;
  char *names[64];
  int dim[64],i,j,num;
  char buffer[HOSTNAMESZ*2];
  packet_t packet;

  if (deja_vu) return(TRUE);
  deja_vu=TRUE;
  atexit(host_cleanup);
  
  if ((fp=fopen("net.conf","r"))==NULL) {
    printf("Could'nt open configuration file.\n");
    exit(1);
  }

  num=0;
  names[num]=(char *) malloc(sizeof(char)*HOSTNAMESZ);
  while (fgets(buffer,HOSTNAMESZ,fp)!=NULL) {
    strip(buffer,names[num],dim+num);  /* isolate the name string */
    if ((int) strlen(names[num])>0) num++;
    names[num]=(char *) malloc(sizeof(char)*HOSTNAMESZ);
  }

  fclose(fp);
  nodes=find_aps(num,names,dim,&n_nodes);

  for (i=0; i<n_nodes; i++) {
    packet.cmd=SET_ID;
    packet.arg=i;
    packet.arg2=n_nodes;
    write_rec(nodes[i]->sd,&packet,sizeof(packet_t));
  }

  for (i=0; i<n_nodes; i++) {
    for (j=0; j<n_nodes; j++) {
      write_rec(nodes[i]->sd,nodes[j]->name,strlen(nodes[j]->name)+1);
      write_rec(nodes[i]->sd,&(nodes[j]->port),sizeof(nodes[j]->port));
    }
  }

  if (n_nodes<min_procs)
    fatal("Could'nt connect to enough processors");

  return(TRUE);
}


void host_cleanup()

{
  free_ap(nodes,n_nodes);
}
