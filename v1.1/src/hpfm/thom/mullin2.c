# line 1 "mullin2.f90"
#include <f90.h>
extern Integer moalib_MP_max();
extern Integer moalib_MP_min();
# line 1 "mullin2.f90"
void test_()
{
register Integer i0_;
auto Integer a_[4];
auto Integer b_[4];
auto Integer consta0_[4];
auto Integer consta1_[4];
auto Integer c_[4];
auto Integer shift_;
auto Integer offset0_;
# line 1 "mullin2.f90"
# line 2 "mullin2.f90"
# line 3 "mullin2.f90"
# line 8 "mullin2.f90"
# line 9 "mullin2.f90"
# line 10 "mullin2.f90"
# line 11 "mullin2.f90"
# line 12 "mullin2.f90"
# line 13 "mullin2.f90"
# line 14 "mullin2.f90"
# line 15 "mullin2.f90"
shift_ = 0;
# line 21 "mullin2.f90"
consta0_[1*(0) + 0] = 1.000000000e+00f;
# line 22 "mullin2.f90"
consta0_[1*(1) + 0] = 2.000000000e+00f;
# line 23 "mullin2.f90"
consta0_[1*(2) + 0] = 3.000000000e+00f;
# line 24 "mullin2.f90"
consta0_[1*(3) + 0] = 4.000000000e+00f;
# line 25 "mullin2.f90"
offset0_ = 0;
# line 26 "mullin2.f90"
for(i0_ = 0;i0_ <= 3;i0_++) {
# line 27 "mullin2.f90"
a_[1*(shift_) + 0] = consta0_[1*(offset0_) + 0];
# line 28 "mullin2.f90"
offset0_ = offset0_ + 1;
# line 29 "mullin2.f90"
shift_ = shift_ + 1;
# line 30 "mullin2.f90"
}
# line 31 "mullin2.f90"
shift_ = 0;
# line 38 "mullin2.f90"
consta1_[1*(0) + 0] = 5.000000000e+00f;
# line 39 "mullin2.f90"
consta1_[1*(1) + 0] = 6.000000000e+00f;
# line 40 "mullin2.f90"
consta1_[1*(2) + 0] = 7.000000000e+00f;
# line 41 "mullin2.f90"
consta1_[1*(3) + 0] = 8.000000000e+00f;
# line 42 "mullin2.f90"
offset0_ = 0;
# line 43 "mullin2.f90"
for(i0_ = 0;i0_ <= 3;i0_++) {
# line 44 "mullin2.f90"
b_[1*(shift_) + 0] = consta1_[1*(offset0_) + 0];
# line 45 "mullin2.f90"
offset0_ = offset0_ + 1;
# line 46 "mullin2.f90"
shift_ = shift_ + 1;
# line 47 "mullin2.f90"
}
# line 48 "mullin2.f90"
shift_ = 0;
# line 55 "mullin2.f90"
offset0_ = 0;
# line 56 "mullin2.f90"
for(i0_ = 0;i0_ <= 3;i0_++) {
# line 57 "mullin2.f90"
c_[1*(shift_) + 0] = b_[1*(offset0_) + 0];
# line 58 "mullin2.f90"
offset0_ = offset0_ + 1;
# line 59 "mullin2.f90"
shift_ = shift_ + 1;
# line 60 "mullin2.f90"
}
# line 61 "mullin2.f90"
}
