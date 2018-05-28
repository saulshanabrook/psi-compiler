# line 1 "network.f90"
#include <f90.h>
# line 1 "network.f90"
extern void network_MP_recv();
extern void network_MP_node_cleanup();
extern Integer network_MP_my_proc();
extern void network_MP_wait();
extern void network_MP_host_cleanup();
extern void network_MP_recv_host();
extern void network_MP_send_host();
extern void network_MP_send();
extern void network_MP_host_send();
extern void network_MP_node_init();
extern void network_MP_host_recv();
extern void network_MP_host_init();
# line 1 "network.f90"
# line 73 "network.f90"
# line 69 "network.f90"
void network_MP_wait()
{
extern void mpi_wait_();
# line 69 "network.f90"
# line 71 "network.f90"
mpi_wait_();
# line 72 "network.f90"
}
# line 65 "network.f90"
void network_MP_node_cleanup()
{
extern void mpi_finalize_();
# line 65 "network.f90"
# line 67 "network.f90"
mpi_finalize_();
# line 68 "network.f90"
}
# line 61 "network.f90"
void network_MP_node_init()
{
extern void mpi_node_init_();
# line 61 "network.f90"
# line 63 "network.f90"
mpi_node_init_();
# line 64 "network.f90"
}
# line 57 "network.f90"
void network_MP_host_cleanup()
{
extern void mpi_finalize_();
# line 57 "network.f90"
# line 59 "network.f90"
mpi_finalize_();
# line 60 "network.f90"
}
# line 53 "network.f90"
void network_MP_host_init()
{
extern void mpi_host_init_();
# line 53 "network.f90"
# line 55 "network.f90"
mpi_host_init_();
# line 56 "network.f90"
}
# line 46 "network.f90"
void network_MP_host_recv(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
extern void mpi_recv_();
Dope1 ptr_;
# line 46 "network.f90"
# line 48 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 48 "network.f90"
# line 49 "network.f90"
# line 50 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 50 "network.f90"
ptmp1 = atmp1.addr;
# line 50 "network.f90"
ptmp2 = ptr_.addr;
# line 50 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 50 "network.f90"
mpi_recv_(atmp1.addr,size_,proc_);
# line 52 "network.f90"
ptmp3 = ptr_.addr;
# line 52 "network.f90"
ptmp4 = atmp1.addr;
# line 52 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 52 "network.f90"
}
# line 39 "network.f90"
void network_MP_host_send(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
Dope1 ptr_;
extern void mpi_send_();
# line 39 "network.f90"
# line 41 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 41 "network.f90"
# line 42 "network.f90"
# line 43 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 43 "network.f90"
ptmp1 = atmp1.addr;
# line 43 "network.f90"
ptmp2 = ptr_.addr;
# line 43 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 43 "network.f90"
mpi_send_(atmp1.addr,size_,proc_);
# line 45 "network.f90"
ptmp3 = ptr_.addr;
# line 45 "network.f90"
ptmp4 = atmp1.addr;
# line 45 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 45 "network.f90"
}
# line 32 "network.f90"
void network_MP_recv_host(ptr_dummy,size_)
     Dope1 *ptr_dummy;
     Integer *size_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
extern void mpi_recv_();
Dope1 ptr_;
# line 32 "network.f90"
# line 34 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 34 "network.f90"
# line 35 "network.f90"
# line 36 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 36 "network.f90"
ptmp1 = atmp1.addr;
# line 36 "network.f90"
ptmp2 = ptr_.addr;
# line 36 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 36 "network.f90"
mpi_recv_(atmp1.addr,size_,(tmp1 = 0 , &tmp1));
# line 38 "network.f90"
ptmp3 = ptr_.addr;
# line 38 "network.f90"
ptmp4 = atmp1.addr;
# line 38 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 38 "network.f90"
}
# line 25 "network.f90"
void network_MP_send_host(ptr_dummy,size_)
     Dope1 *ptr_dummy;
     Integer *size_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
Dope1 ptr_;
extern void mpi_send_();
# line 25 "network.f90"
# line 27 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 27 "network.f90"
# line 28 "network.f90"
# line 29 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 29 "network.f90"
ptmp1 = atmp1.addr;
# line 29 "network.f90"
ptmp2 = ptr_.addr;
# line 29 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 29 "network.f90"
mpi_send_(atmp1.addr,size_,(tmp1 = 0 , &tmp1));
# line 31 "network.f90"
ptmp3 = ptr_.addr;
# line 31 "network.f90"
ptmp4 = atmp1.addr;
# line 31 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 31 "network.f90"
}
# line 18 "network.f90"
void network_MP_recv(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
extern void mpi_recv_();
Dope1 ptr_;
# line 18 "network.f90"
# line 20 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 20 "network.f90"
# line 21 "network.f90"
# line 22 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 22 "network.f90"
ptmp1 = atmp1.addr;
# line 22 "network.f90"
ptmp2 = ptr_.addr;
# line 22 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 22 "network.f90"
mpi_recv_(atmp1.addr,size_,proc_);
# line 24 "network.f90"
ptmp3 = ptr_.addr;
# line 24 "network.f90"
ptmp4 = atmp1.addr;
# line 24 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 24 "network.f90"
}
# line 11 "network.f90"
void network_MP_send(ptr_dummy,size_,proc_)
     Dope1 *ptr_dummy;
     Integer *size_;
     Integer *proc_;
{
Integer tmp1;
ArrayTemp_Real atmp1;
Real *ptmp1;
char *ptmp2;
char *ptmp3;
Real *ptmp4;
Dope1 ptr_;
extern void mpi_send_();
# line 11 "network.f90"
# line 13 "network.f90"
assume_shape((Pointer)&ptr_,(Pointer)ptr_dummy,1,1);
# line 13 "network.f90"
# line 14 "network.f90"
# line 15 "network.f90"
atmp1 = mkatmp_r(1,ptr_.dim[0].extent);
# line 15 "network.f90"
ptmp1 = atmp1.addr;
# line 15 "network.f90"
ptmp2 = ptr_.addr;
# line 15 "network.f90"
for(tmp1=0; tmp1<atmp1.extent[0]; tmp1++ )  {  *ptmp1++ =  *((Real *)ptmp2);
ptmp2 += ptr_.dim[0].mult;
}
# line 15 "network.f90"
mpi_send_(atmp1.addr,size_,proc_);
# line 17 "network.f90"
ptmp3 = ptr_.addr;
# line 17 "network.f90"
ptmp4 = atmp1.addr;
# line 17 "network.f90"
for(tmp1=0; tmp1<ptr_.dim[0].extent; tmp1++ )  {  *((Real *)ptmp3) =  *ptmp4;
ptmp4++;
ptmp3 += ptr_.dim[0].mult;
}
freevec_r(atmp1);
# line 17 "network.f90"
}
# line 7 "network.f90"
Integer network_MP_my_proc()
{
Integer tmp1;
auto Integer network_MP_my_procresult;
extern Integer mpi_my_node_();
# line 7 "network.f90"
# line 9 "network.f90"
network_MP_my_procresult = mpi_my_node_();
# line 10 "network.f90"
return network_MP_my_procresult;
# line 10 "network.f90"
}
