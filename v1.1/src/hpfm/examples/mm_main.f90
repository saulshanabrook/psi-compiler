PROGRAM example
  INTERFACE
   SUBROUTINE multiply(m,n,p,A,B,C)
     INTEGER :: m,n,p
     REAL, DIMENSION (m,n) :: A
     REAL, DIMENSION (n,p) :: B
     REAL, DIMENSION (m,p) :: C
    END SUBROUTINE
  END INTERFACE

  REAL, DIMENSION (0:3) :: A,B,C

  A=(/ 1.0, 3.0, 5.0, 2.0 /)
  B=(/ 9.0, 8.0, 4.0, 7.0 /)

  CALL multiply (2,2,2,A,B,C)

  PRINT *,C
END PROGRAM