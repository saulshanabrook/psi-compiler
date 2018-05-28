# line 1 "mpinet.f90"
#include <f90.h>
# line 1 "mpinet.f90"
extern Integer mpinet_MP_my_proc();
extern void mpinet_MP_host_recv();
extern void mpinet_MP_host_cleanup();
extern void mpinet_MP_host_init();
extern void mpi_recv_();
extern void mpi_send_();
extern void mpinet_MP_wait();
extern void mpinet_MP_send();
extern void mpinet_MP_recv();
extern void mpi_send_();
extern void mpinet_MP_send_host();
extern void mpi_recv_();
extern void mpinet_MP_recv_host();
extern void mpi_init_();
extern void mpinet_MP_node_init();
extern void mpinet_MP_host_send();
extern void mpinet_MP_node_cleanup();
extern void mpi_init_();
# line 1 "mpinet.f90"
# line 5 "mpinet.f90"
# line 12 "mpinet.f90"
# line 19 "mpinet.f90"
# line 104 "mpinet.f90"
# line 100 "mpinet.f90"
void mpinet_MP_wait()
{
extern void mpi_wait_();
# line 100 "mpinet.f90"
# line 102 "mpinet.f90"
mpi_wait_();
# line 103 "mpinet.f90"
}
# line 90 "mpinet.f90"
void mpinet_MP_node_cleanup()
{
extern void mpi_finalize_();
# line 90 "mpinet.f90"
# line 98 "mpinet.f90"
mpi_finalize_();
# line 99 "mpinet.f90"
}
# line 87 "mpinet.f90"
void mpinet_MP_node_init()
{
# line 87 "mpinet.f90"
# line 89 "mpinet.f90"
}
# line 77 "mpinet.f90"
void mpinet_MP_host_cleanup()
{
extern void mpi_finalize_();
# line 77 "mpinet.f90"
# line 85 "mpinet.f90"
mpi_finalize_();
# line 86 "mpinet.f90"
}
# line 74 "mpinet.f90"
void mpinet_MP_host_init()
{
# line 74 "mpinet.f90"
# line 76 "mpinet.f90"
}
# line 67 "mpinet.f90"
void mpinet_MP_host_recv(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Dope1 ptr_;
# line 67 "mpinet.f90"
# line 69 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 69 "mpinet.f90"
# line 70 "mpinet.f90"
# line 71 "mpinet.f90"
mpi_recv_(&ptr_,size_,proc_);
# line 73 "mpinet.f90"
}
# line 60 "mpinet.f90"
void mpinet_MP_host_send(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Dope1 ptr_;
# line 60 "mpinet.f90"
# line 62 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 62 "mpinet.f90"
# line 63 "mpinet.f90"
# line 64 "mpinet.f90"
mpi_send_(&ptr_,size_,proc_);
# line 66 "mpinet.f90"
}
# line 53 "mpinet.f90"
void mpinet_MP_recv_host(ptr_dummy,size_)
     Dope1 *ptr_dummy;
     Integer *size_;
{
Integer tmp1;
Dope1 ptr_;
# line 53 "mpinet.f90"
# line 55 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 55 "mpinet.f90"
# line 56 "mpinet.f90"
# line 57 "mpinet.f90"
mpi_recv_(&ptr_,size_,(tmp1 = 0 , &tmp1));
# line 59 "mpinet.f90"
}
# line 46 "mpinet.f90"
void mpinet_MP_send_host(ptr_dummy,size_)
     Dope1 *ptr_dummy;
     Integer *size_;
{
Integer tmp1;
Dope1 ptr_;
# line 46 "mpinet.f90"
# line 48 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 48 "mpinet.f90"
# line 49 "mpinet.f90"
# line 50 "mpinet.f90"
mpi_send_(&ptr_,size_,(tmp1 = 0 , &tmp1));
# line 52 "mpinet.f90"
}
# line 39 "mpinet.f90"
void mpinet_MP_recv(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Dope1 ptr_;
# line 39 "mpinet.f90"
# line 41 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 41 "mpinet.f90"
# line 42 "mpinet.f90"
# line 43 "mpinet.f90"
mpi_recv_(&ptr_,size_,proc_);
# line 45 "mpinet.f90"
}
# line 32 "mpinet.f90"
void mpinet_MP_send(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Dope1 ptr_;
# line 32 "mpinet.f90"
# line 34 "mpinet.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 34 "mpinet.f90"
# line 35 "mpinet.f90"
# line 36 "mpinet.f90"
mpi_send_(&ptr_,size_,proc_);
# line 38 "mpinet.f90"
}
# line 28 "mpinet.f90"
Integer mpinet_MP_my_proc()
{
Integer tmp1;
auto Integer mpinet_MP_my_procresult;
extern Integer mpi_my_node_();
# line 28 "mpinet.f90"
# line 30 "mpinet.f90"
mpinet_MP_my_procresult = mpi_my_node_();
# line 31 "mpinet.f90"
return mpinet_MP_my_procresult;
# line 31 "mpinet.f90"
}
