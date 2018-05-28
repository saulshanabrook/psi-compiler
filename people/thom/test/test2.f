SUBROUTINE omega_red(f90_in1, f90_out1)
  REAL, DIMENSION (0:) :: f90_in1
  REAL, DIMENSION (0:) :: f90_out1
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0
  INTEGER :: i1

! MOA
! out1=(<3.000000> drop in1) cat (<3.000000> take in1)
!

  shift=0* INT (((10)))+0
  offset0=0* INT (10)+3
  DO i0 = 0, 10-1
    DO i1 = 0, 7-1
      f90_out1(shift)=f90_in1(offset0)
      offset0=offset0+(1)
      shift=shift+(1)
    END DO
    offset0=offset0+(3)
  END DO
  shift=0* INT (10)+7
  offset0=0* INT (10)+0
  DO i0 = 0, 10-1
    DO i1 = 0, 3-1
      f90_out1(shift)=f90_in1(offset0)
      offset0=offset0+(1)
      shift=shift+(1)
    END DO
    offset0=offset0+(7)
  END DO


END SUBROUTINE omega_red


