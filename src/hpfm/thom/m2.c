# line 1 "m2.f90"
#include <f90.h>
# line 1 "m2.f90"
void test_()
{
Integer tmp1;
Real tmp2;
ArrayTemp_Integer atmp1;
ArrayTemp_Integer atmp2;
Integer *ptmp1;
Integer *ptmp2;
char *ptmp3;
Dope1 section1;
static Integer  aconst1[4] = { 1,2,3,4,};
static Integer  aconst2[4] = { 5,6,7,8,};
auto Integer a_[4];
auto Integer b_[4];
auto Integer c_[4];
auto Integer d_[8];
extern Real concat_();
# line 1 "m2.f90"
# line 2 "m2.f90"
# line 3 "m2.f90"
# line 4 "m2.f90"
ptmp1 = a_;
# line 4 "m2.f90"
ptmp2 = aconst1;
# line 4 "m2.f90"
for(tmp1=0; tmp1<4; tmp1++ )  {  *ptmp1++ =  *ptmp2;
ptmp2++;
}
# line 6 "m2.f90"
ptmp1 = b_;
# line 6 "m2.f90"
ptmp2 = aconst2;
# line 6 "m2.f90"
for(tmp1=0; tmp1<4; tmp1++ )  {  *ptmp1++ =  *ptmp2;
ptmp2++;
}
# line 7 "m2.f90"
atmp2 = mkatmp_i(1,4);
# line 7 "m2.f90"
section1.addr = (Pointer)a_;
# line 7 "m2.f90"
section1.dim[0].extent = 4;
# line 7 "m2.f90"
section1.dim[0].mult = 4;
# line 7 "m2.f90"
section1.dim[0].lower = 1;
# line 7 "m2.f90"
section1.dim[0].lower = 1;
# line 7 "m2.f90"
section1.offset = -4;
# line 7 "m2.f90"
cshift_a(1,(Dope7*)&section1,4,1,(Pointer)atmp2.addr,4);
# line 7 "m2.f90"
tmp2 = concat_(atmp2.addr,b_);
# line 7 "m2.f90"
freevec_i(atmp2);
# line 7 "m2.f90"
ptmp1 = d_;
# line 7 "m2.f90"
for(tmp1=0; tmp1<8; tmp1++ )   *ptmp1++ = tmp2;
# line 9 "m2.f90"
section1.addr = (Pointer)d_;
# line 9 "m2.f90"
section1.addr += 4*(5 - 1);
# line 9 "m2.f90"
section1.dim[0].extent = 4;
# line 9 "m2.f90"
section1.dim[0].mult = 4;
# line 9 "m2.f90"
section1.offset = -(section1.dim[0].mult);
# line 9 "m2.f90"
section1.dim[0].lower = 1;
# line 9 "m2.f90"
ptmp1 = c_;
# line 9 "m2.f90"
ptmp3 = section1.addr;
# line 9 "m2.f90"
for(tmp1=0; tmp1<4; tmp1++ )  {  *ptmp1++ =  *((Integer *)ptmp3);
ptmp3 += section1.dim[0].mult;
}
# line 10 "m2.f90"
}
