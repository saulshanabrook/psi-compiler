extern int my_proc_no;
/*
extern int host_init(int min_procs);
*/
extern int node_init();
extern int cow_write(int cow, void *buf, long len);
extern int cow_read(int cow, void *buf, long len);

int scottt_my_proc_ ()
{
  return (my_proc_no);
}

void scottt_send_(float *ptr, int size, int proc)
{
   cow_write((proc)+1,(void *) (ptr),size);
}

void scottt_recv_(float *ptr, int size, int proc)
{
  cow_read((proc)+1,(void *) (ptr),size);
}

void scottt_send_host_ (float *ptr, int size)
{
  cow_write(0,(void *) (ptr),size);
}

void scottt_recv_host_ (float *ptr, int size)
{
  cow_read(0,(void *) (ptr),size);
}

void scottt_host_send_ (float *ptr, int size, int proc)
{
  cow_write(proc,(void *) (ptr),size);
}

void scottt_host_recv_ (float *ptr, int size, int proc)
{
  cow_read(proc,(void *) (ptr),size);
}

/*
void scottt_host_init_ (int procs)
{
  host_init (procs);
}

void scottt_host_cleanup_ ()
{
  host_cleanup ();
}
*/

void scottt_node_init_ (int procs)
{
  node_init (procs);
}

void scottt_node_cleanup_ ()
{
  node_cleanup ();
}

void scottt_wait_ ()
{
}
