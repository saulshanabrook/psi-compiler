program test1
  real, allocatable, dimension (:,:) :: a
  integer :: i

  allocate (a(0:10,0:10))
  i = 3
  call func (a, i)
end
