#include <stdio.h>
#include <sys/time.h>

#define TRACE_START(filename) \
  sprintf(trace_name,"%s%d.ntr",filename,my_proc_no+1); \
  trace_fd=fopen(trace_name,"wt"); \
  set_trace_time(); \
  fprintf(trace_fd,"1 %d %d %d 0 0 0\n",trace_sec,trace_usec,my_proc_no+1)

#define TRACE_END() \
  get_trace_time(); \
  fprintf(trace_fd,"19 %d %d %d 0\n",trace_sec,trace_usec,my_proc_no+1); \
  fclose(trace_fd)

#define START_SEND(dest,len) \
  get_trace_time(); \
  start_idle(); \
  fprintf(trace_fd,"11 %d %d %d %d %d %d %d\n",trace_sec,trace_usec, \
	  my_proc_no+1, busy_sec,busy_usec,idle_sec,idle_usec); \
  fprintf(trace_fd,"4 %d %d %d %d 1 %d\n",trace_sec,trace_usec,my_proc_no+1, \
	  dest+1,len)

#define END_SEND() \
  get_trace_time(); \
  end_idle(); \
  fprintf(trace_fd,"11 %d %d %d %d %d %d %d\n",trace_sec,trace_usec, \
	  my_proc_no+1,busy_sec,busy_usec,idle_sec,idle_usec)

#define START_RECV() \
  get_trace_time(); \
  start_idle(); \
  fprintf(trace_fd,"11 %d %d %d %d %d %d %d\n",trace_sec,trace_usec, \
	  my_proc_no+1,busy_sec,busy_usec,idle_sec,idle_usec); \
  fprintf(trace_fd,"7 %d %d %d 1\n",trace_sec,trace_usec,my_proc_no+1)

#define END_RECV(from,len) \
  get_trace_time(from,len); \
  end_idle(); \
  fprintf(trace_fd,"8 %d %d %d %d 1 %d\n",trace_sec,trace_usec,my_proc_no+1, \
	  from+1,len); \
  fprintf(trace_fd,"11 %d %d %d %d %d %d %d\n",trace_sec,trace_usec, \
	  my_proc_no+1,busy_sec,busy_usec,idle_sec,idle_usec)


FILE *trace_fd;
char trace_name[256];
long start_sec,start_usec;
long trace_sec,trace_usec;
long last_sec,last_usec;
long busy_sec,busy_usec;
long idle_sec,idle_usec;

set_trace_time()

{
  struct timeval now;

  gettimeofday(&now);
  start_sec=now.tv_sec;
  start_usec=now.tv_usec;
  trace_sec=0;
  trace_usec=0;
  last_sec=0;
  last_usec=0;
  busy_sec=0;
  busy_usec=0;
  idle_sec=0;
  idle_usec=0;
}

get_trace_time()

{
  struct timeval now;

  gettimeofday(&now);
  last_sec=trace_sec;
  last_usec=trace_usec;
  trace_sec=now.tv_sec-start_sec;
  trace_usec=now.tv_usec-start_usec;
  if (trace_usec<0) {
    trace_sec--;
    trace_usec+=1000000;
  }
}


/* to be called immediately after get_trace_time */
start_idle()

{
  busy_sec+=trace_sec-last_sec;
  busy_usec+=trace_usec-last_usec;
  if (busy_usec<0) {
    busy_sec--;
    busy_usec+=1000000;
  } else if (busy_usec>=1000000) {
    busy_sec++;
    busy_usec-=1000000;
  }
}


/* to be called immediately after get_trace_time */
end_idle()

{
  idle_sec+=trace_sec-last_sec;
  idle_usec+=trace_usec-last_usec;
  if (idle_usec<0) {
    idle_sec--;
    idle_usec+=1000000;
  } else if (idle_usec>=1000000) {
    idle_sec++;
    idle_usec-=1000000;
  }
}
