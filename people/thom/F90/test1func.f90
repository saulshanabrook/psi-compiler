subroutine func (a, i)
  real, dimension (0:10,0:10) :: a
  integer :: i
  a(i,i) = 5
end subroutine func
