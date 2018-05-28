# line 1 "tom5.f90"
#include <f90.h>
extern void mpi_recv_();
extern void mpinet_MP_recv();
extern void mpinet_MP_recv_host();
extern void mpinet_MP_host_cleanup();
extern void mpinet_MP_node_cleanup();
extern void mpinet_MP_send();
extern void mpi_init_();
extern void mpinet_MP_host_init();
extern void mpi_recv_();
extern Integer mpinet_MP_my_proc();
extern void mpinet_MP_send_host();
extern void mpinet_MP_wait();
extern void mpinet_MP_host_recv();
extern void mpinet_MP_host_send();
extern void mpi_init_();
extern void mpinet_MP_node_init();
extern void mpi_send_();
extern void mpi_send_();
extern Integer moalib_MP_min();
extern Integer moalib_MP_max();
# line 1 "tom5.f90"
void test_(a_,b_)
     Dope1 *a_;
     Dope1 *b_;
{
Integer tmp1;
Dope1 section1;
auto Integer i2_;
auto Real *dist_a_;
auto BoundsInfo dist_a_info;
auto Real *dist_b_;
auto BoundsInfo dist_b_info;
auto Integer p__;
auto Integer offset_;
auto Logical p_cont_;
auto Integer p_[3];
auto Integer shift_;
auto Integer offset0_;
register Integer i0_;
auto Integer i1_;
# line 1 "tom5.f90"
# line 2 "tom5.f90"
dist_a_ = 0;
# line 2 "tom5.f90"
dist_b_ = 0;
# line 2 "tom5.f90"
# line 3 "tom5.f90"
# line 4 "tom5.f90"
# line 9 "tom5.f90"
# line 10 "tom5.f90"
# line 11 "tom5.f90"
# line 12 "tom5.f90"
# line 13 "tom5.f90"
# line 14 "tom5.f90"
# line 15 "tom5.f90"
# line 16 "tom5.f90"
# line 17 "tom5.f90"
# line 18 "tom5.f90"
# line 19 "tom5.f90"
# line 20 "tom5.f90"
mpinet_MP_node_init();
# line 22 "tom5.f90"
if (mpinet_MP_my_proc()>0) {
# line 25 "tom5.f90"
dist_a_info = make_info(1,0,24);
# line 25 "tom5.f90"
if (dist_a_) crash("ALLOCATABLE array %s has already been ALLOCATEd","DIST_A");
# line 25 "tom5.f90"
dist_a_ = ((Real *)Allocate_i(dist_a_info,4,(Integer*)0));
# line 25 "tom5.f90"
;
# line 25 "tom5.f90"
}
# line 26 "tom5.f90"
i1_ = 25;
# line 27 "tom5.f90"
if (mpinet_MP_my_proc()==0) {
# line 28 "tom5.f90"
i0_ = 100;
# line 29 "tom5.f90"
for(i2_ = 0;i2_ <= 0;i2_++) {
# line 30 "tom5.f90"
p_[1*(i2_) + 0] = 0;
# line 31 "tom5.f90"
}
# line 32 "tom5.f90"
p_[1*(0) + 0] = 1;
# line 33 "tom5.f90"
p_cont_ = 1;
# line 34 "tom5.f90"
for(;;){
# line 35 "tom5.f90"
p__ = p_[1*(0) + 0];
# line 36 "tom5.f90"
offset_ = (25*(p_[1*(0) + 0]));
# line 37 "tom5.f90"
section1.addr = a_->addr;
# line 37 "tom5.f90"
section1.offset = 0;
# line 37 "tom5.f90"
tmp1 = offset_;
# line 37 "tom5.f90"
section1.addr += a_->dim[0].mult*(tmp1 - a_->dim[0].lower);
# line 37 "tom5.f90"
section1.dim[0].mult = a_->dim[0].mult;
# line 37 "tom5.f90"
section1.dim[0].extent = offset_ + i1_ - 1 - tmp1 + 1;
# line 37 "tom5.f90"
if (section1.dim[0].extent<0) section1.dim[0].extent = 0;
# line 37 "tom5.f90"
section1.offset = -(section1.dim[0].mult);
# line 37 "tom5.f90"
section1.dim[0].lower = 1;
# line 37 "tom5.f90"
mpinet_MP_send(&section1,&i2_,&p__);
# line 38 "tom5.f90"
p_[1*(0) + 0] = p_[1*(0) + 0] + 1;
# line 39 "tom5.f90"
if (p_[1*(0) + 0]>=4) {
# line 39 "tom5.f90"
p_cont_ = 0;
# line 39 "tom5.f90"
}
# line 40 "tom5.f90"
if (!(p_cont_)) {
# line 40 "tom5.f90"
goto CONSTRUCT_1_EXIT;
# line 40 "tom5.f90"
}
# line 41 "tom5.f90"
}
CONSTRUCT_1_EXIT:;
# line 42 "tom5.f90"
} else {
# line 43 "tom5.f90"
section1.addr = (Pointer)dist_a_;
# line 43 "tom5.f90"
section1.offset = 4*dist_a_info.offset;
# line 43 "tom5.f90"
section1.dim[0].extent = dist_a_info.dim[0].extent;
# line 43 "tom5.f90"
section1.dim[0].mult = 4*dist_a_info.dim[0].mult;
# line 43 "tom5.f90"
section1.dim[0].lower = 1;
# line 43 "tom5.f90"
mpinet_MP_recv(&section1,&i1_,(tmp1 = 0 , &tmp1));
# line 44 "tom5.f90"
section1.addr = (Pointer)dist_a_;
# line 44 "tom5.f90"
section1.offset = 4*dist_a_info.offset;
# line 44 "tom5.f90"
section1.dim[0].extent = dist_a_info.dim[0].extent;
# line 44 "tom5.f90"
section1.dim[0].mult = 4*dist_a_info.dim[0].mult;
# line 44 "tom5.f90"
section1.dim[0].lower = 1;
# line 44 "tom5.f90"
 *a_ = section1;
# line 45 "tom5.f90"
}
# line 46 "tom5.f90"
if (mpinet_MP_my_proc()>0) {
# line 46 "tom5.f90"
dist_b_info = make_info(1,0,24);
# line 46 "tom5.f90"
if (dist_b_) crash("ALLOCATABLE array %s has already been ALLOCATEd","DIST_B");
# line 46 "tom5.f90"
dist_b_ = ((Real *)Allocate_i(dist_b_info,4,(Integer*)0));
# line 46 "tom5.f90"
;
# line 46 "tom5.f90"
}
# line 47 "tom5.f90"
i1_ = 25;
# line 48 "tom5.f90"
if (mpinet_MP_my_proc()==0) {
# line 49 "tom5.f90"
i0_ = 100;
# line 50 "tom5.f90"
for(i2_ = 0;i2_ <= 0;i2_++) {
# line 51 "tom5.f90"
p_[1*(i2_) + 0] = 0;
# line 52 "tom5.f90"
}
# line 53 "tom5.f90"
p_[1*(0) + 0] = 1;
# line 54 "tom5.f90"
p_cont_ = 1;
# line 55 "tom5.f90"
for(;;){
# line 56 "tom5.f90"
p__ = p_[1*(0) + 0];
# line 57 "tom5.f90"
offset_ = (25*(p_[1*(0) + 0]));
# line 58 "tom5.f90"
section1.addr = b_->addr;
# line 58 "tom5.f90"
section1.offset = 0;
# line 58 "tom5.f90"
tmp1 = offset_;
# line 58 "tom5.f90"
section1.addr += b_->dim[0].mult*(tmp1 - b_->dim[0].lower);
# line 58 "tom5.f90"
section1.dim[0].mult = b_->dim[0].mult;
# line 58 "tom5.f90"
section1.dim[0].extent = offset_ + i1_ - 1 - tmp1 + 1;
# line 58 "tom5.f90"
if (section1.dim[0].extent<0) section1.dim[0].extent = 0;
# line 58 "tom5.f90"
section1.offset = -(section1.dim[0].mult);
# line 58 "tom5.f90"
section1.dim[0].lower = 1;
# line 58 "tom5.f90"
mpinet_MP_send(&section1,&i2_,&p__);
# line 59 "tom5.f90"
p_[1*(0) + 0] = p_[1*(0) + 0] + 1;
# line 60 "tom5.f90"
if (p_[1*(0) + 0]>=4) {
# line 60 "tom5.f90"
p_cont_ = 0;
# line 60 "tom5.f90"
}
# line 61 "tom5.f90"
if (!(p_cont_)) {
# line 61 "tom5.f90"
goto CONSTRUCT_2_EXIT;
# line 61 "tom5.f90"
}
# line 62 "tom5.f90"
}
CONSTRUCT_2_EXIT:;
# line 63 "tom5.f90"
} else {
# line 64 "tom5.f90"
section1.addr = (Pointer)dist_b_;
# line 64 "tom5.f90"
section1.offset = 4*dist_b_info.offset;
# line 64 "tom5.f90"
section1.dim[0].extent = dist_b_info.dim[0].extent;
# line 64 "tom5.f90"
section1.dim[0].mult = 4*dist_b_info.dim[0].mult;
# line 64 "tom5.f90"
section1.dim[0].lower = 1;
# line 64 "tom5.f90"
mpinet_MP_recv(&section1,&i1_,(tmp1 = 0 , &tmp1));
# line 65 "tom5.f90"
section1.addr = (Pointer)dist_b_;
# line 65 "tom5.f90"
section1.offset = 4*dist_b_info.offset;
# line 65 "tom5.f90"
section1.dim[0].extent = dist_b_info.dim[0].extent;
# line 65 "tom5.f90"
section1.dim[0].mult = 4*dist_b_info.dim[0].mult;
# line 65 "tom5.f90"
section1.dim[0].lower = 1;
# line 65 "tom5.f90"
 *b_ = section1;
# line 66 "tom5.f90"
}
# line 67 "tom5.f90"
shift_ = 0;
# line 75 "tom5.f90"
offset0_ = 0;
# line 76 "tom5.f90"
for(i0_ = 0;i0_ <= 24;i0_++) {
# line 77 "tom5.f90"
 *((Real *)(a_->addr + (a_->dim[0].mult*(shift_) + a_->offset))) =  *((Real *)(b_->addr + (b_->dim[0].mult*(offset0_) + b_->offset)));
# line 78 "tom5.f90"
offset0_ = offset0_ + 1;
# line 79 "tom5.f90"
shift_ = shift_ + 1;
# line 80 "tom5.f90"
}
# line 81 "tom5.f90"
i1_ = 25;
# line 86 "tom5.f90"
if (mpinet_MP_my_proc()==0) {
# line 87 "tom5.f90"
i0_ = 100;
# line 88 "tom5.f90"
for(i2_ = 0;i2_ <= 0;i2_++) {
# line 89 "tom5.f90"
p_[1*(i2_) + 0] = 0;
# line 90 "tom5.f90"
}
# line 91 "tom5.f90"
p_[1*(0) + 0] = 1;
# line 92 "tom5.f90"
p_cont_ = 1;
# line 93 "tom5.f90"
for(;;){
# line 94 "tom5.f90"
p__ = p_[1*(0) + 0];
# line 95 "tom5.f90"
offset_ = (25*(p_[1*(0) + 0]));
# line 96 "tom5.f90"
section1.addr = a_->addr;
# line 96 "tom5.f90"
section1.offset = 0;
# line 96 "tom5.f90"
tmp1 = offset_;
# line 96 "tom5.f90"
section1.addr += a_->dim[0].mult*(tmp1 - a_->dim[0].lower);
# line 96 "tom5.f90"
section1.dim[0].mult = a_->dim[0].mult;
# line 96 "tom5.f90"
section1.dim[0].extent = offset_ + i1_ - 1 - tmp1 + 1;
# line 96 "tom5.f90"
if (section1.dim[0].extent<0) section1.dim[0].extent = 0;
# line 96 "tom5.f90"
section1.offset = -(section1.dim[0].mult);
# line 96 "tom5.f90"
section1.dim[0].lower = 1;
# line 96 "tom5.f90"
mpinet_MP_recv(&section1,&i2_,&p__);
# line 97 "tom5.f90"
p_[1*(0) + 0] = p_[1*(0) + 0] + 1;
# line 98 "tom5.f90"
if (p_[1*(0) + 0]>=4) {
# line 98 "tom5.f90"
p_cont_ = 0;
# line 98 "tom5.f90"
}
# line 99 "tom5.f90"
if (!(p_cont_)) {
# line 99 "tom5.f90"
goto CONSTRUCT_3_EXIT;
# line 99 "tom5.f90"
}
# line 100 "tom5.f90"
}
CONSTRUCT_3_EXIT:;
# line 101 "tom5.f90"
} else {
# line 102 "tom5.f90"
mpinet_MP_send(a_,&i1_,(tmp1 = 0 , &tmp1));
# line 103 "tom5.f90"
}
# line 104 "tom5.f90"
mpinet_MP_node_cleanup();
# line 105 "tom5.f90"
i1_ = 25;
# line 106 "tom5.f90"
if (mpinet_MP_my_proc()==0) {
# line 107 "tom5.f90"
i0_ = 100;
# line 108 "tom5.f90"
for(i2_ = 0;i2_ <= 0;i2_++) {
# line 109 "tom5.f90"
p_[1*(i2_) + 0] = 0;
# line 110 "tom5.f90"
}
# line 111 "tom5.f90"
p_[1*(0) + 0] = 1;
# line 112 "tom5.f90"
p_cont_ = 1;
# line 113 "tom5.f90"
for(;;){
# line 114 "tom5.f90"
p__ = p_[1*(0) + 0];
# line 115 "tom5.f90"
offset_ = (25*(p_[1*(0) + 0]));
# line 116 "tom5.f90"
section1.addr = b_->addr;
# line 116 "tom5.f90"
section1.offset = 0;
# line 116 "tom5.f90"
tmp1 = offset_;
# line 116 "tom5.f90"
section1.addr += b_->dim[0].mult*(tmp1 - b_->dim[0].lower);
# line 116 "tom5.f90"
section1.dim[0].mult = b_->dim[0].mult;
# line 116 "tom5.f90"
section1.dim[0].extent = offset_ + i1_ - 1 - tmp1 + 1;
# line 116 "tom5.f90"
if (section1.dim[0].extent<0) section1.dim[0].extent = 0;
# line 116 "tom5.f90"
section1.offset = -(section1.dim[0].mult);
# line 116 "tom5.f90"
section1.dim[0].lower = 1;
# line 116 "tom5.f90"
mpinet_MP_recv(&section1,&i2_,&p__);
# line 117 "tom5.f90"
p_[1*(0) + 0] = p_[1*(0) + 0] + 1;
# line 118 "tom5.f90"
if (p_[1*(0) + 0]>=4) {
# line 118 "tom5.f90"
p_cont_ = 0;
# line 118 "tom5.f90"
}
# line 119 "tom5.f90"
if (!(p_cont_)) {
# line 119 "tom5.f90"
goto CONSTRUCT_4_EXIT;
# line 119 "tom5.f90"
}
# line 120 "tom5.f90"
}
CONSTRUCT_4_EXIT:;
# line 121 "tom5.f90"
} else {
# line 122 "tom5.f90"
mpinet_MP_send(b_,&i1_,(tmp1 = 0 , &tmp1));
# line 123 "tom5.f90"
}
# line 124 "tom5.f90"
mpinet_MP_node_cleanup();
ROUTINE_END:if (dist_a_) Deallocate_i((Pointer)dist_a_,dist_a_info,4,(Integer*)0);
dist_a_ = 0;
if (dist_b_) Deallocate_i((Pointer)dist_b_,dist_b_info,4,(Integer*)0);
dist_b_ = 0;
# line 125 "tom5.f90"
}
