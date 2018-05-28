# line 1 "tom-2.f90"
#include <f90.h>
# line 1 "tom-2.f90"
void test_(a_,b_)
     Integer a_[100];
     Integer b_[100];
{
Integer tmp1;
Integer tmp2;
Integer *ptmp1;
char *ptmp2;
char *ptmp3;
Dope2 section1;
Dope2 section2;
auto Integer a1_[1];
auto Integer c_;
auto Integer d_;
# line 1 "tom-2.f90"
# line 2 "tom-2.f90"
# line 3 "tom-2.f90"
# line 4 "tom-2.f90"
# line 5 "tom-2.f90"
section1.addr = (Pointer)a_;
# line 5 "tom-2.f90"
section1.addr += 4*(1 - 1);
# line 5 "tom-2.f90"
section1.dim[0].extent = 0;
# line 5 "tom-2.f90"
section1.dim[0].mult = 4;
# line 5 "tom-2.f90"
section1.offset = -(section1.dim[0].mult);
# line 5 "tom-2.f90"
section1.dim[0].lower = 1;
# line 5 "tom-2.f90"
section1.addr += 40*(1 - 1);
# line 5 "tom-2.f90"
section1.dim[1].extent = 0;
# line 5 "tom-2.f90"
section1.dim[1].mult = 40;
# line 5 "tom-2.f90"
section1.offset -= section1.dim[1].mult;
# line 5 "tom-2.f90"
section1.dim[1].lower = 1;
# line 5 "tom-2.f90"
section2.addr = (Pointer)b_;
# line 5 "tom-2.f90"
section2.addr += 4*(1 - 1);
# line 5 "tom-2.f90"
section2.dim[0].extent = 0;
# line 5 "tom-2.f90"
section2.dim[0].mult = 4;
# line 5 "tom-2.f90"
section2.offset = -(section2.dim[0].mult);
# line 5 "tom-2.f90"
section2.dim[0].lower = 1;
# line 5 "tom-2.f90"
section2.addr += 40*(1 - 1);
# line 5 "tom-2.f90"
section2.dim[1].extent = 0;
# line 5 "tom-2.f90"
section2.dim[1].mult = 40;
# line 5 "tom-2.f90"
section2.offset -= section2.dim[1].mult;
# line 5 "tom-2.f90"
section2.dim[1].lower = 1;
# line 5 "tom-2.f90"
ptmp1 = a1_;
# line 5 "tom-2.f90"
ptmp2 = section1.addr;
# line 5 "tom-2.f90"
ptmp3 = section2.addr;
# line 5 "tom-2.f90"
for(tmp2=0; tmp2<0; tmp2++ )  { for(tmp1=0; tmp1<0; tmp1++ )  {  *ptmp1++ = ( *((Integer *)ptmp2)* *((Integer *)ptmp3));
ptmp2 += section1.dim[0].mult;
ptmp3 += section2.dim[0].mult;
}
ptmp2 += section1.dim[1].mult - section1.dim[0].mult*section1.dim[0].extent;
ptmp3 += section2.dim[1].mult - section2.dim[0].mult*section2.dim[0].extent;
}
# line 7 "tom-2.f90"
}
