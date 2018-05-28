#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct event_s {
  long type;
  long sec,usec;
  long arg1,arg2,arg3,arg4;
  struct event_s *next;
} event_t;

typedef struct proc_s {
  long node;
  long cnt;
  event_t *events;
  struct proc_s *next;
} proc_t;

proc_t *procs;


void *get_mem(int size)

{
  void *ret;

  if (size==0) {
    puts("Internal error: get_mem");
    exit(1);
  }
  if ((ret=(void *) malloc(size))==NULL) {
    puts("Out of memory!");
    exit(1);
  }

  return(ret);
}


cmp_clock(event_t *e1, event_t *e2)

{
  int ret;

  if (e1->sec<e2->sec)
    ret=-1;
  else if (e1->sec>e2->sec)
    ret=1;
  else
    ret=0;

  if (ret==0) {
    if (e1->usec<e2->usec)
      ret=-1;
    else if (e1->usec>e2->usec)
      ret=1;
  }

  return(ret);
}


event_t *insert_event(event_t *list, event_t *new)

{
  event_t *last,*ret;
  
  ret=list;

  last=NULL;
  while ((list!=NULL)&&(cmp_clock(list,new)<=0)) {
    last=list;
    list=list->next;
  }

  if (last==NULL) {
    ret=new;
    new->next=NULL;
  } else {
    new->next=last->next;
    last->next=new;
  }

  return(ret);
}


read_ntr(char *filename)

{
  FILE *fd;
  long tmp;
  char buf[256];
  event_t *new;
  proc_t *proc;
  
  if ((fd=fopen(filename,"rt"))==NULL) {
    printf("Could'nt open %s\n",filename);
    exit(1);
  }
  
  printf("loading %s...\n",filename);

  proc=(proc_t *) get_mem(sizeof(proc_t));
  proc->events=NULL;
  fgets(buf,256,fd);
  while (!feof(fd)) {
    new=(event_t *) get_mem(sizeof(event_t));

    sscanf(buf," %ld",&(new->type));
    
    switch (new->type) {
    case 1:
      sscanf(buf," %ld %ld %ld %ld %ld %ld %ld ",&tmp,&(new->sec),&(new->usec),
	    &(proc->node),&(new->arg1),&(new->arg2),&(new->arg3));
      break;
    case 4:
      sscanf(buf," %ld %ld %ld %ld %ld %ld %ld ",&tmp,&(new->sec),&(new->usec),
	    &tmp,&(new->arg1),&(new->arg2),&(new->arg3));
      break;
    case 7:
      sscanf(buf," %ld %ld %ld %ld %ld ",&tmp,&(new->sec),&(new->usec),
	    &tmp,&(new->arg1));
      break;
    case 8:
      sscanf(buf," %ld %ld %ld %ld %ld %ld %ld ",&tmp,&(new->sec),&(new->usec),
	    &tmp,&(new->arg1),&(new->arg2),&(new->arg3));
      break;
    case 11:
      sscanf(buf," %ld %ld %ld %ld %ld %ld %ld %ld ",&tmp,&(new->sec),
	     &(new->usec),&tmp,&(new->arg1),&(new->arg2),&(new->arg3),
	     &(new->arg4));
      break;
    case 19:
      sscanf(buf," %ld %ld %ld %ld %ld ",&tmp,&(new->sec),&(new->usec),
	    &tmp,&(new->arg1));
      break;
    default:
      printf("Error in input file %s\n",filename);
    }
    proc->events=insert_event(proc->events,new);

    fgets(buf,256,fd);
  }

  proc->next=procs;
  procs=proc;
  
  fclose(fd);
}


event_t *find_receive(long num, long from, event_t *list)

{
  while ((list!=NULL)&&(num>0)) {
    if ((list->type==8)&&(list->arg1==from))
      num--;
    if (num>0)
      list=list->next;
  }

  return(list);
}


inc_clock(event_t *list, long sec, long usec)

{
  while (list!=NULL) {
    list->sec+=sec;
    list->usec+=usec;
    if (list->usec<0) {
      list->sec--;
      list->usec+=1000000;
    } else if (list->usec>=1000000) {
      list->sec++;
      list->usec-=1000000;
    }
    list=list->next;
  }
}


int resolve()

{
  int ret;
  long cnt;
  event_t *node,*match;
  proc_t *pnode,*dest;
  
  ret=FALSE;
  pnode=procs;
  while (pnode!=NULL) {
    dest=procs;
    while (dest!=NULL) {
      dest->cnt=0;
      dest=dest->next;
    }

    node=pnode->events;

    do {
      while ((node!=NULL)&&(node->type!=4)) node=node->next;
      if (node!=NULL) {
	dest=procs;
	while ((dest!=NULL)&&(dest->node!=node->arg1)) dest=dest->next;

	dest->cnt++;
	match=find_receive(dest->cnt,pnode->node,dest->events);
	
	if (cmp_clock(match,node)<=0) {
	  ret=TRUE;
	  inc_clock(dest->events,node->sec-match->sec,
		    node->usec-match->usec+1);
	}
	
	node=node->next;
      }
    } while (node!=NULL);

    pnode=pnode->next;
  }

  return(ret);
}


resolve_all()

{
  int cnt;
  
  cnt=0;
  while (resolve()) cnt++;
  
  printf("complete in %d passes\n",cnt);
}


print_event(FILE *fd, event_t *e, long node)

{
  switch (e->type) {
  case 7:
  case 19:
    fprintf(fd,"%ld %ld %ld %ld %ld\n",e->type,e->sec,e->usec,node,e->arg1);
    break;
  case 1:
  case 4:
  case 8:
    fprintf(fd,"%ld %ld %ld %ld %ld %ld %ld\n",e->type,e->sec,e->usec,node,
	    e->arg1,e->arg2,e->arg3);
    break;
  case 11:
    fprintf(fd,"%ld %ld %ld %ld %ld %ld %ld %ld\n",e->type,e->sec,e->usec,node,
	    e->arg1,e->arg2,e->arg3,e->arg4);
    break;
  }
}


dump_events(char *filename)

{
  FILE *fd;
  long node_num;
  event_t *junk,*next;
  proc_t *node;

  if ((fd=fopen(filename,"wt"))==NULL) {
    printf("Could'nt create %s\n",filename);
    exit(1);
  }
  
  do {
    next=NULL;
    node=procs;

    /* find the first event available on any node */
    while ((node!=NULL)&&(next==NULL)) {
      next=node->events;
      node_num=node->node;
      node=node->next;
    }
    
    /* compare next with the first event available on all nodes
       and pick the earliest event */
    while (node!=NULL) {
      if (node->events!=NULL) {
	if (cmp_clock(node->events,next)<0) {
	  next=node->events;
	  node_num=node->node;
	}
      }
      node=node->next;
    }

    if (next!=NULL) {
      /* print the earliest event */
      print_event(fd,next,node_num);
      
      /* find and delete the event */
      node=procs;
      while ((node!=NULL)&&(node->node!=node_num)) node=node->next;
      junk=node->events;
      node->events=node->events->next;
      free(junk);
    }
  } while (next!=NULL);

  fclose(fd);
}


main(int argc, char *argv[])

{
  int i;

  if (argc<2) {
    printf("usage: maketrf trf_file ntr_file1 ... ntr_fileN\n");
    exit(1);
  }

  procs=NULL;
  for (i=2; i<argc; i++) {
    read_ntr(argv[i]);
  }

  printf("processing events\n");
  resolve_all();

  dump_events(argv[1]);
}
