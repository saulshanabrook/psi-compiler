# line 1 "test1.f90"
#include <f90.h>
# line 1 "test1.f90"
int main(argc,argv)
     int argc; char *argv[];
{
auto Real *a_;
auto BoundsInfo a_info;
auto Integer i_;
extern void func_();
f90_init(argc,argv);
# line 1 "test1.f90"
# line 2 "test1.f90"
a_ = 0;
# line 2 "test1.f90"
# line 3 "test1.f90"
# line 4 "test1.f90"
a_info = make_info(2,0,10,0,10);
# line 4 "test1.f90"
if (a_) crash("ALLOCATABLE array %s has already been ALLOCATEd","A");
# line 4 "test1.f90"
a_ = ((Real *)Allocate_i(a_info,4,(Integer*)0));
# line 4 "test1.f90"
;
# line 6 "test1.f90"
i_ = 3;
# line 7 "test1.f90"
func_(a_,&i_);
ROUTINE_END:if (a_) Deallocate_i((Pointer)a_,a_info,4,(Integer*)0);
a_ = 0;
# line 8 "test1.f90"
f90_finish(0);
# line 8 "test1.f90"
}
