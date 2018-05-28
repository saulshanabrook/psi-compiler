SUBROUTINE ADD_SUB1(f90_in1, f90_in2, f90_in3, f90_out)
  REAL, DIMENSION (0:) :: f90_in1
  REAL, DIMENSION (0:) :: f90_in2
  REAL, DIMENSION (0:) :: f90_in3
  REAL, DIMENSION (0:) :: f90_out
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0
  INTEGER :: i1
  INTEGER :: i2

! MOA
! out=in1
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_out(shift)=f90_in1(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! out=out +  + in2
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_out(shift)=f90_out(shift)+f90_in2(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! out=out +  + in3
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_out(shift)=f90_out(shift)+f90_in3(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


END SUBROUTINE ADD_SUB1


SUBROUTINE ADD_SUB2(f90_in1, f90_in2, f90_in3, f90_out)
  REAL, DIMENSION (0:) :: f90_in1
  REAL, DIMENSION (0:) :: f90_in2
  REAL, DIMENSION (0:) :: f90_in3
  REAL, DIMENSION (0:) :: f90_out
  INTEGER, DIMENSION (0:2*3*4-1) :: f90_temp
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0
  INTEGER :: i1
  INTEGER :: i2

! MOA
! temp=in1
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_temp(shift)=f90_in1(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! temp=temp * in2
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_temp(shift)=f90_temp(shift)*f90_in2(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! temp=temp - in3
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_temp(shift)=f90_temp(shift)-f90_in3(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! out=temp
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_out(shift)=f90_temp(offset0)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


END SUBROUTINE ADD_SUB2


SUBROUTINE ADD_SUB3(f90_in1, f90_in2, f90_in3, f90_out)
  REAL, DIMENSION (0:) :: f90_in1
  REAL, DIMENSION (0:) :: f90_in2
  REAL, DIMENSION (0:) :: f90_in3
  REAL, DIMENSION (0:) :: f90_out
  INTEGER, DIMENSION (0:2*3*4-1) :: f90_temp
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: offset1
  INTEGER :: offset2
  INTEGER :: offset3
  INTEGER :: offset4
  INTEGER :: offset5
  INTEGER :: offset6
  INTEGER :: i0
  INTEGER :: i1
  INTEGER :: i2

! MOA
! temp=in2 * in3
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  offset1=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_temp(shift)=f90_in2(offset0)
        f90_temp(shift)=f90_temp(shift)*f90_in3(offset1)
        offset1=offset1+(1)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


! MOA
! out=in1 - four * in3 +  + tfive * temp / in3 - in2
!

  shift=0* INT (((2)))+0* INT (((3)))+0
  offset0=0* INT (2)+0* INT (6)+0
  offset2=0* INT (2)+0* INT (6)+0
  offset4=0* INT (2)+0* INT (6)+0
  offset5=0* INT (2)+0* INT (6)+0
  offset6=0* INT (2)+0* INT (6)+0
  DO i0 = 0, ((4))-1
    DO i1 = 0, ((3))-1
      DO i2 = 0, ((2))-1
        f90_out(shift)=f90_in1(offset0)
        f90_out(shift)=f90_out(shift)-4.000000
        f90_out(shift)=f90_out(shift)*f90_in3(offset2)
        f90_out(shift)=f90_out(shift)+25.000000
        f90_out(shift)=f90_out(shift)*f90_temp(offset4)
        f90_out(shift)=f90_out(shift)/f90_in3(offset5)
        f90_out(shift)=f90_out(shift)-f90_in2(offset6)
        offset6=offset6+(1)
        offset5=offset5+(1)
        offset4=offset4+(1)
        offset2=offset2+(1)
        offset0=offset0+(1)
        shift=shift+(1)
      END DO
    END DO
  END DO


END SUBROUTINE ADD_SUB3


