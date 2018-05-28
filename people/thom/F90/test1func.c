# line 1 "test1func.f90"
#include <f90.h>
# line 1 "test1func.f90"
void func_(a_,i_)
     Real a_[121];
     Integer *i_;
{
# line 1 "test1func.f90"
# line 2 "test1func.f90"
# line 3 "test1func.f90"
# line 4 "test1func.f90"
if (( *i_)<0 || ( *i_)>10) {
# line 4 "test1func.f90"
badsub1(1,"A",( *i_),0,10);
# line 4 "test1func.f90"
} else if (( *i_)<0 || ( *i_)>10) {
# line 4 "test1func.f90"
badsub1(2,"A",( *i_),0,10);
# line 4 "test1func.f90"
}
# line 4 "test1func.f90"
a_[1*( *i_) + 11*( *i_) + 0] = 5;
# line 5 "test1func.f90"
}
