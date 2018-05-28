SUBROUTINE TEST ( )
USE MOALIB

! MOA
! Variable declarations
!
  INTEGER, DIMENSION (0:4-1) :: A
  INTEGER  , DIMENSION (0:4-1) :: consta0
  INTEGER, DIMENSION (0:4-1) :: B
  INTEGER  , DIMENSION (0:4-1) :: consta1
  INTEGER, DIMENSION (0:4-1) :: C
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0

  ! MOA
  ! array assignment
  !

  shift=0
  consta0 (0) =1.000000
  consta0 (1) =2.000000
  consta0 (2) =3.000000
  consta0 (3) =4.000000
  offset0=0
  DO i0 = 0, 4-1
    A(shift)=consta0(offset0)
    offset0=offset0+1
    shift=shift+1
  END DO


  ! MOA
  ! array assignment
  !

  shift=0
  consta1 (0) =5.000000
  consta1 (1) =6.000000
  consta1 (2) =7.000000
  consta1 (3) =8.000000
  offset0=0
  DO i0 = 0, 4-1
    B(shift)=consta1(offset0)
    offset0=offset0+1
    shift=shift+1
  END DO


  ! MOA
  ! array assignment
  !

  shift=0
  offset0=0
  DO i0 = 0, 4-1
    C(shift)=B(offset0)
    offset0=offset0+1
    shift=shift+1
  END DO


END SUBROUTINE 
