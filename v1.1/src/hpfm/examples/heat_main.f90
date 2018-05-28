PROGRAM example
  INTERFACE
    SUBROUTINE heat2d(n,A,L)
      INTEGER :: n
      REAL, DIMENSION (n,n) :: A
      REAL, DIMENSION (1) :: L
    END SUBROUTINE
  END INTERFACE

  INTEGER :: i,j
  REAL, DIMENSION (0:8*8-1) :: A
  REAL, DIMENSION (1) :: L
  REAL :: SP

! lambda 
  L(1)=0.25

! grid spacing
  SP=2*3.141592653589793/8
! initialize with 2d sin
  DO i=1, 6
    DO j=1, 6
      A(i*8+j)=SIN(i*SP-3.141592653589793)*SIN(j*SP-3.141592653589793)
    END DO
  END DO
! set boundry to 0
  DO i=0, 7
    A(i)=0.0
    A(7*8+i)=0.0
    A(i*8)=0.0
    A(i*8+7)=0.0
  END DO

! caclulate finite difference for 50 iterations
  DO i=1, 200
    CALL heat2d (8,A,L)
  END DO

  PRINT *,A
END PROGRAM
