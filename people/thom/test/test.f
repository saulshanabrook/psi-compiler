SUBROUTINE omega_red(f90_in1, f90_out1)
  REAL, DIMENSION (0:) :: f90_in1
  REAL, DIMENSION (0:) :: f90_out1
  INTEGER, DIMENSION (0:0) :: forall_i0
  INTEGER, DIMENSION (0:0) :: forall_i1
  INTEGER, DIMENSION (0:0) :: forall_i2
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0
  INTEGER :: i1

! MOA
! out1=(<3.000000> drop  omega <1.000000 1.000000> in1) cat  omega <1.000000 1.000000> (<3.000000> take  omega <1.000000 1.000000> in1)
!

  forall_i2(0)=0
  DO
    IF (forall_i2(0) == 0+10) EXIT
    forall_i0(0)=((INT (forall_i2(0+0))))
    DO
      IF (forall_i0(0) == ((INT (forall_i2(0+0))))+1) EXIT
      shift=((0))* INT (((10)))+((INT (forall_i0(0+0))))
      offset0=((3))* INT (10)+((INT (forall_i0(0+0))))
      DO i0 = 0, 7-1
        f90_out1(shift)=f90_in1(offset0)
        offset0=offset0+(10)
      END DO
      forall_i0(0)=forall_i0(0)+1
    END DO
    forall_i1(0)=((INT (forall_i2(0+0))))
    DO
      IF (forall_i1(0) == ((INT (forall_i2(0+0))))+1) EXIT
      shift=((7))* INT (10)+((INT (forall_i1(0+0))))
      offset0=((0))* INT (10)+((INT (forall_i1(0+0))))
      DO i0 = 0, 3-1
        f90_out1(shift)=f90_in1(offset0)
        offset0=offset0+(10)
      END DO
      forall_i1(0)=forall_i1(0)+1
    END DO
    forall_i2(0)=forall_i2(0)+1
  END DO


END SUBROUTINE omega_red


