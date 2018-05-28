SUBROUTINE TEST ( )
USE MOALIB

! MOA
! Variable declarations
!
  INTEGER, DIMENSION (0:4-1) :: C
  INTEGER, DIMENSION (0:8-1) :: B
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0

  ! MOA
  ! array assignment
  !

  shift=0
  offset0=4
  DO i0 = 0, 4-1
    C(shift)=B(offset0)
    offset0=offset0+1
    shift=shift+1
  END DO


END SUBROUTINE 
