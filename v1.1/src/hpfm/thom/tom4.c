# line 1 "tom4.f90"
#include <f90.h>
extern Integer moalib_MP_max();
extern Integer moalib_MP_min();
# line 1 "tom4.f90"
void test_(a_,b_,c_,d_,e_)
     Real *a_;
     Integer b_[100];
     Real *c_;
     Integer *d_;
     Integer e_[100];
{
Integer tmp1;
Real tmp2;
Real tmp3;
Integer tmp4;
Integer tmp5;
Integer tmp6;
Integer tmp7;
Integer *ptmp1;
Integer *ptmp2;
register Integer i1_;
auto Integer tmp_vect1_[1];
auto Integer forall_i3_[1];
auto Integer tmp_vect0_[1];
auto Integer forall_i4_[1];
auto Real temp2_[10];
auto Integer forall_i5_[1];
auto Integer tempf901_[100];
auto Integer forall_i0_[1];
auto Integer forall_i6_[1];
auto Integer shift_;
auto Integer tempf900_[100];
auto Integer forall_i1_[1];
auto Integer offset0_;
auto Real temp1_[10];
auto Integer forall_i7_[1];
auto Integer forall_i2_[1];
register Integer i0_;
# line 1 "tom4.f90"
# line 2 "tom4.f90"
# line 3 "tom4.f90"
# line 4 "tom4.f90"
# line 9 "tom4.f90"
# line 10 "tom4.f90"
# line 11 "tom4.f90"
# line 12 "tom4.f90"
# line 13 "tom4.f90"
# line 14 "tom4.f90"
# line 15 "tom4.f90"
# line 16 "tom4.f90"
# line 17 "tom4.f90"
# line 18 "tom4.f90"
# line 19 "tom4.f90"
# line 20 "tom4.f90"
# line 21 "tom4.f90"
# line 22 "tom4.f90"
# line 23 "tom4.f90"
# line 24 "tom4.f90"
# line 25 "tom4.f90"
# line 26 "tom4.f90"
# line 27 "tom4.f90"
# line 28 "tom4.f90"
ptmp1 = tempf900_;
# line 28 "tom4.f90"
ptmp2 = b_;
# line 28 "tom4.f90"
for(tmp1=0; tmp1<100; tmp1++ )  { tmp3 = (float)ipowr( *ptmp2, *a_);
 *ptmp1++ = (tmp3>=0.0f ? tmp3 : -(tmp3));
ptmp2++;
}
# line 34 "tom4.f90"
forall_i2_[1*(0) + 0] = 0;
# line 35 "tom4.f90"
for(;;){
# line 36 "tom4.f90"
if (forall_i2_[1*(0) + 0]==10) {
# line 36 "tom4.f90"
goto CONSTRUCT_1_EXIT;
# line 36 "tom4.f90"
}
# line 37 "tom4.f90"
shift_ = (forall_i2_[1*(0) + 0]) + 0;
# line 38 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 39 "tom4.f90"
b_[1*(shift_) + 0] = 0.000000000e+00f;
# line 40 "tom4.f90"
}
# line 41 "tom4.f90"
forall_i3_[1*(0) + 0] = 0;
# line 42 "tom4.f90"
for(;;){
# line 43 "tom4.f90"
if (forall_i3_[1*(0) + 0]==10) {
# line 43 "tom4.f90"
goto CONSTRUCT_2_EXIT;
# line 43 "tom4.f90"
}
# line 44 "tom4.f90"
forall_i0_[1*(0) + 0] = (forall_i2_[1*(0) + 0]);
# line 45 "tom4.f90"
for(;;){
# line 46 "tom4.f90"
if (forall_i0_[1*(0) + 0]==(forall_i2_[1*(0) + 0]) + 1) {
# line 46 "tom4.f90"
goto CONSTRUCT_3_EXIT;
# line 46 "tom4.f90"
}
# line 47 "tom4.f90"
forall_i1_[1*(0) + 0] = (forall_i3_[1*(0) + 0]);
# line 48 "tom4.f90"
for(;;){
# line 49 "tom4.f90"
if (forall_i1_[1*(0) + 0]==(forall_i3_[1*(0) + 0]) + 1) {
# line 49 "tom4.f90"
goto CONSTRUCT_4_EXIT;
# line 49 "tom4.f90"
}
# line 50 "tom4.f90"
shift_ = 0;
# line 51 "tom4.f90"
offset0_ = (3 + moalib_MP_min(&forall_i0_[1*(0) + 0],(tmp4 = 7 , &tmp4))) + (forall_i1_[1*(0) + 0])*10;
# line 52 "tom4.f90"
tmp1 = (moalib_MP_min((tmp5 = 1 , &tmp5),(tmp6 = 7 - (moalib_MP_min(&forall_i0_[1*(0) + 0],(tmp7 = 7 , &tmp7))) , &tmp6))) - 1;
# line 52 "tom4.f90"
for(i1_ = 0;i1_ <= tmp1;i1_++) {
# line 53 "tom4.f90"
tmp_vect0_[1*(shift_) + 0] = e_[1*(offset0_) + 0];
# line 54 "tom4.f90"
offset0_ = offset0_ + 1;
# line 55 "tom4.f90"
}
# line 56 "tom4.f90"
shift_ = 0;
# line 57 "tom4.f90"
offset0_ = ((forall_i0_[1*(0) + 0]) - (moalib_MP_min(&forall_i0_[1*(0) + 0],(tmp4 = 7 , &tmp4)))) + (forall_i1_[1*(0) + 0])*10;
# line 58 "tom4.f90"
tmp1 = (1 - (moalib_MP_min((tmp5 = 1 , &tmp5),(tmp6 = 7 - (moalib_MP_min(&forall_i0_[1*(0) + 0],(tmp7 = 7 , &tmp7))) , &tmp6)))) - 1;
# line 58 "tom4.f90"
for(i1_ = 0;i1_ <= tmp1;i1_++) {
# line 59 "tom4.f90"
tmp_vect0_[1*(shift_) + 0] = e_[1*(offset0_) + 0];
# line 60 "tom4.f90"
offset0_ = offset0_ + 1;
# line 61 "tom4.f90"
}
# line 62 "tom4.f90"
shift_ = 0;
# line 63 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 64 "tom4.f90"
temp1_[1*(shift_) + 0] = tmp_vect0_[1*(0) + 0];
# line 65 "tom4.f90"
shift_ = shift_ + 1;
# line 66 "tom4.f90"
}
# line 67 "tom4.f90"
shift_ = 0;
# line 68 "tom4.f90"
offset0_ = (forall_i1_[1*(0) + 0]) + 0;
# line 69 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 70 "tom4.f90"
temp1_[1*(shift_) + 0] = temp1_[1*(shift_) + 0]*tempf900_[1*(offset0_) + 0];
# line 71 "tom4.f90"
offset0_ = offset0_ + 10;
# line 72 "tom4.f90"
shift_ = shift_ + 1;
# line 73 "tom4.f90"
}
# line 74 "tom4.f90"
forall_i1_[1*(0) + 0] = forall_i1_[1*(0) + 0] + 1;
# line 75 "tom4.f90"
}
CONSTRUCT_4_EXIT:;
# line 76 "tom4.f90"
forall_i0_[1*(0) + 0] = forall_i0_[1*(0) + 0] + 1;
# line 77 "tom4.f90"
}
CONSTRUCT_3_EXIT:;
# line 78 "tom4.f90"
shift_ = (forall_i2_[1*(0) + 0]) + 0;
# line 79 "tom4.f90"
offset0_ = 0;
# line 80 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 81 "tom4.f90"
b_[1*(shift_) + 0] = b_[1*(shift_) + 0] + temp1_[1*(offset0_) + 0];
# line 82 "tom4.f90"
offset0_ = offset0_ + 1;
# line 83 "tom4.f90"
}
# line 84 "tom4.f90"
forall_i3_[1*(0) + 0] = forall_i3_[1*(0) + 0] + 1;
# line 85 "tom4.f90"
}
CONSTRUCT_2_EXIT:;
# line 86 "tom4.f90"
forall_i2_[1*(0) + 0] = forall_i2_[1*(0) + 0] + 1;
# line 87 "tom4.f90"
}
CONSTRUCT_1_EXIT:;
# line 88 "tom4.f90"
ptmp1 = tempf901_;
# line 88 "tom4.f90"
ptmp2 = b_;
# line 88 "tom4.f90"
for(tmp1=0; tmp1<100; tmp1++ )  { tmp3 = (float)ipowr( *ptmp2, *a_);
 *ptmp1++ = (tmp3>=0.0f ? tmp3 : -(tmp3));
ptmp2++;
}
# line 95 "tom4.f90"
forall_i6_[1*(0) + 0] = 0;
# line 96 "tom4.f90"
for(;;){
# line 97 "tom4.f90"
if (forall_i6_[1*(0) + 0]==10) {
# line 97 "tom4.f90"
goto CONSTRUCT_5_EXIT;
# line 97 "tom4.f90"
}
# line 98 "tom4.f90"
shift_ = (forall_i6_[1*(0) + 0]) + 0;
# line 99 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 100 "tom4.f90"
b_[1*(shift_) + 0] = 0.000000000e+00f;
# line 101 "tom4.f90"
}
# line 102 "tom4.f90"
forall_i7_[1*(0) + 0] = 0;
# line 103 "tom4.f90"
for(;;){
# line 104 "tom4.f90"
if (forall_i7_[1*(0) + 0]==10) {
# line 104 "tom4.f90"
goto CONSTRUCT_6_EXIT;
# line 104 "tom4.f90"
}
# line 105 "tom4.f90"
forall_i4_[1*(0) + 0] = (forall_i6_[1*(0) + 0]);
# line 106 "tom4.f90"
for(;;){
# line 107 "tom4.f90"
if (forall_i4_[1*(0) + 0]==(forall_i6_[1*(0) + 0]) + 1) {
# line 107 "tom4.f90"
goto CONSTRUCT_7_EXIT;
# line 107 "tom4.f90"
}
# line 108 "tom4.f90"
forall_i5_[1*(0) + 0] = (forall_i7_[1*(0) + 0]);
# line 109 "tom4.f90"
for(;;){
# line 110 "tom4.f90"
if (forall_i5_[1*(0) + 0]==(forall_i7_[1*(0) + 0]) + 1) {
# line 110 "tom4.f90"
goto CONSTRUCT_8_EXIT;
# line 110 "tom4.f90"
}
# line 111 "tom4.f90"
shift_ = 0;
# line 112 "tom4.f90"
offset0_ = (forall_i4_[1*(0) + 0]) + (forall_i5_[1*(0) + 0])*10;
# line 113 "tom4.f90"
tmp_vect1_[1*(shift_) + 0] = tempf901_[1*(offset0_) + 0];
# line 114 "tom4.f90"
shift_ = 0;
# line 115 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 116 "tom4.f90"
temp2_[1*(shift_) + 0] = tmp_vect1_[1*(0) + 0];
# line 117 "tom4.f90"
shift_ = shift_ + 1;
# line 118 "tom4.f90"
}
# line 119 "tom4.f90"
shift_ = 0;
# line 120 "tom4.f90"
offset0_ = (forall_i5_[1*(0) + 0]) + 0;
# line 121 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 122 "tom4.f90"
temp2_[1*(shift_) + 0] = temp2_[1*(shift_) + 0]*e_[1*(offset0_) + 0];
# line 123 "tom4.f90"
offset0_ = offset0_ + 10;
# line 124 "tom4.f90"
shift_ = shift_ + 1;
# line 125 "tom4.f90"
}
# line 126 "tom4.f90"
forall_i5_[1*(0) + 0] = forall_i5_[1*(0) + 0] + 1;
# line 127 "tom4.f90"
}
CONSTRUCT_8_EXIT:;
# line 128 "tom4.f90"
forall_i4_[1*(0) + 0] = forall_i4_[1*(0) + 0] + 1;
# line 129 "tom4.f90"
}
CONSTRUCT_7_EXIT:;
# line 130 "tom4.f90"
shift_ = (forall_i6_[1*(0) + 0]) + 0;
# line 131 "tom4.f90"
offset0_ = 0;
# line 132 "tom4.f90"
for(i0_ = 0;i0_ <= 9;i0_++) {
# line 133 "tom4.f90"
b_[1*(shift_) + 0] = b_[1*(shift_) + 0] + temp2_[1*(offset0_) + 0];
# line 134 "tom4.f90"
offset0_ = offset0_ + 1;
# line 135 "tom4.f90"
}
# line 136 "tom4.f90"
forall_i7_[1*(0) + 0] = forall_i7_[1*(0) + 0] + 1;
# line 137 "tom4.f90"
}
CONSTRUCT_6_EXIT:;
# line 138 "tom4.f90"
forall_i6_[1*(0) + 0] = forall_i6_[1*(0) + 0] + 1;
# line 139 "tom4.f90"
}
CONSTRUCT_5_EXIT:;
# line 140 "tom4.f90"
}
