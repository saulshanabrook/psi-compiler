SUBROUTINE ADD_SUB1()
  REAL, DIMENSION (:), ALLOCATABLE :: f90_in1
  REAL, DIMENSION (:), ALLOCATABLE :: f90_in2
  REAL, DIMENSION (:), ALLOCATABLE :: f90_in3
  REAL, DIMENSION (:), ALLOCATABLE :: f90_out
  INTEGER, DIMENSION (0:3-1) :: tmp_vect0
  INTEGER, DIMENSION (0:3-1) :: tmp_vect1
  INTEGER, DIMENSION (0:3-1) :: tmp_vect2
  INTEGER, DIMENSION (0:3-1) :: tmp_vect3
  INTEGER, DIMENSION (0:3-1) :: tmp_vect4
  INTEGER, DIMENSION (0:3-1) :: tmp_vect5
  INTEGER, DIMENSION (0:3-1) :: tmp_vect6
  INTEGER, DIMENSION (0:3-1) :: tmp_vect7
  INTEGER, DIMENSION (0:3-1) :: tmp_vect8
  INTEGER, DIMENSION (0:3-1) :: tmp_vect9
  INTEGER, DIMENSION (0:3-1) :: tmp_vect10
  INTEGER, DIMENSION (0:3-1) :: tmp_vect11
  INTEGER, DIMENSION (0:3-1) :: tmp_vect12
  INTEGER, DIMENSION (0:3-1) :: tmp_vect13
  INTEGER, DIMENSION (0:3-1) :: tmp_vect14
  INTEGER :: scalar0
  INTEGER :: scalar1
  INTEGER :: scalar2
  INTEGER :: scalar3
  INTEGER, DIMENSION (0:3-1) :: tmp_vect15
  INTEGER, DIMENSION (0:3-1) :: tmp_vect16
  INTEGER, DIMENSION (0:3-1) :: tmp_vect17
  INTEGER, DIMENSION (0:3-1) :: tmp_vect18
  INTEGER, DIMENSION (0:3-1) :: tmp_vect19
  INTEGER, DIMENSION (0:3-1) :: tmp_vect20
  INTEGER, DIMENSION (0:3-1) :: tmp_vect21
  INTEGER, DIMENSION (0:3-1) :: tmp_vect22
  INTEGER, DIMENSION (0:3-1) :: tmp_vect23
  INTEGER, DIMENSION (0:3-1) :: tmp_vect24
  INTEGER, DIMENSION (0:3-1) :: tmp_vect25
  INTEGER, DIMENSION (0:3-1) :: tmp_vect26
  INTEGER, DIMENSION (0:3-1) :: tmp_vect27
  INTEGER :: j_cont,p_cont,s_cont,out
  INTEGER :: p_,sp_,mode,offset
  INTEGER, DIMENSION (0:2) :: p
  INTEGER, DIMENSION (0:2) :: c
  INTEGER, DIMENSION (0:2) :: s
  INTEGER, DIMENSION (0:2) :: sp2
  INTEGER, DIMENSION (0:2) :: ip
  INTEGER, DIMENSION (0:2) :: lp
  INTEGER, DIMENSION (0:2) :: bp
  INTEGER, DIMENSION (0:2) :: ipp
  INTEGER, DIMENSION (0:2) :: lpp
  INTEGER, DIMENSION (0:2) :: bpp
  TYPE BUF
    REAL, DIMENSION (:), POINTER :: store
  END TYPE BUF
  TYPE(BUF), DIMENSION (0:9) :: buffer0r, buffer0s
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0
  INTEGER :: i1
  INTEGER :: i2

! NODE_INIT(10);

  !  Communications for Initial Data

  ALLOCATE (f90_out(0:3*30*40-1))
  i1=3*30*40
  RECV_HOST(f90_out,i1)
  ALLOCATE (f90_in1(0:3*30*40-1))
  i1=3*30*40
  RECV_HOST(f90_in1,i1)
  ALLOCATE (f90_in3(0:3*30*40-1))
  i1=3*30*40
  RECV_HOST(f90_in3,i1)

! Procedure body

!
! out=in1
!

  tmp_vect0(0+((0)))=((3))
  tmp_vect0(1+((0)))=((30))
  tmp_vect0(2+((0)))=((40))
  DO mode=0, 1
    DO i0 = 0, ((3))-1
      p(i0)=0
    END DO
    p_cont=TRUE
    DO
      tmp_vect1(0+((0)))=((0))
      tmp_vect1(1+((0)))=((0))
      tmp_vect1(2+((0)))=((0))
      tmp_vect2(0+((0)))=((20))
      tmp_vect2(1+((0)))=((30))
      tmp_vect2(2+((0)))=((40))
      tmp_vect3(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))
      tmp_vect3(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))
      tmp_vect3(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))
      tmp_vect4(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0))))
      tmp_vect4(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))+(INT (tmp_vect0(1+0))))
      tmp_vect4(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))+(INT (tmp_vect0(2+0))))
      tmp_vect5(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0)))+(-20))
      tmp_vect5(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))+(INT (tmp_vect0(1+0)))+(-30))
      tmp_vect5(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))+(INT (tmp_vect0(2+0)))+(-40))
      tmp_vect6(0+((0)))=((((-1))*((INT (p(0+0)))))*((INT (tmp_vect0(0+0))))+((-1))*((INT (tmp_vect0(0+0))))+(20))
      tmp_vect6(1+((0)))=((((-1))*((INT (p(1+0)))))*((INT (tmp_vect0(1+0))))+((-1))*((INT (tmp_vect0(1+0))))+(30))
      tmp_vect6(2+((0)))=((((-1))*((INT (p(2+0)))))*((INT (tmp_vect0(2+0))))+((-1))*((INT (tmp_vect0(2+0))))+(40))
      out=FALSE
      DO i0 = 0, ((3))-1
        IF (tmp_vect3(i0)>=tmp_vect2(i0)) out=TRUE
      END DO
      DO i0 = 0, ((3))-1
        IF (tmp_vect4(i0)<tmp_vect1(i0)) out=TRUE
      END DO
      IF (out) THEN
        ip(0+((0)))=((0))
        ip(1+((0)))=((0))
        ip(2+((0)))=((0))
        lp(0+((0)))=((0))
        lp(1+((0)))=((0))
        lp(2+((0)))=((0))
        bp(0+((0)))=((0))
        bp(1+((0)))=((0))
        bp(2+((0)))=((0))
       ELSE
        ip(0+((0)))=((((((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))>0))*(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))))
        ip(1+((0)))=((((((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))>0))*(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))))
        ip(2+((0)))=((((((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))>0))*(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))))
        lp(0+((0)))=((((((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))>0))*(((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))+(INT (tmp_vect1(0+0))))
        lp(1+((0)))=((((((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))>0))*(((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))+(INT (tmp_vect1(1+0))))
        lp(2+((0)))=((((((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))>0))*(((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))+(INT (tmp_vect1(2+0))))
        bp(0+((0)))=((((((INT (tmp_vect5(0+0))))>0))*((INT (tmp_vect6(0+0))))+(INT (tmp_vect4(0+0))))-((INT (lp(0+0)))))
        bp(1+((0)))=((((((INT (tmp_vect5(1+0))))>0))*((INT (tmp_vect6(1+0))))+(INT (tmp_vect4(1+0))))-((INT (lp(1+0)))))
        bp(2+((0)))=((((((INT (tmp_vect5(2+0))))>0))*((INT (tmp_vect6(2+0))))+(INT (tmp_vect4(2+0))))-((INT (lp(2+0)))))
      END IF
      p_=INT (p(0+((0))))* INT (1)+INT (p(1+((0))))* INT (1)+INT (p(2+((0))))
      tmp_vect7(0+((0)))=((3))
      tmp_vect7(1+((0)))=((30))
      tmp_vect7(2+((0)))=((40))
      tmp_vect8(0+((0)))=((((INT (ip(0+0)))+(INT (bp(0+0))))-((((INT (ip(0+0))))/((INT (tmp_vect7(0+0)))))*((INT (tmp_vect7(0+0))))))/((INT (tmp_vect7(0+0))))+((MOD(((INT (ip(0+0)))+(INT (bp(0+0))))-((((INT (ip(0+0))))/((INT (tmp_vect7(0+0)))))*((INT (tmp_vect7(0+0))))),(INT (tmp_vect7(0+0)))))>0))
      tmp_vect8(1+((0)))=((((INT (ip(1+0)))+(INT (bp(1+0))))-((((INT (ip(1+0))))/((INT (tmp_vect7(1+0)))))*((INT (tmp_vect7(1+0))))))/((INT (tmp_vect7(1+0))))+((MOD(((INT (ip(1+0)))+(INT (bp(1+0))))-((((INT (ip(1+0))))/((INT (tmp_vect7(1+0)))))*((INT (tmp_vect7(1+0))))),(INT (tmp_vect7(1+0)))))>0))
      tmp_vect8(2+((0)))=((((INT (ip(2+0)))+(INT (bp(2+0))))-((((INT (ip(2+0))))/((INT (tmp_vect7(2+0)))))*((INT (tmp_vect7(2+0))))))/((INT (tmp_vect7(2+0))))+((MOD(((INT (ip(2+0)))+(INT (bp(2+0))))-((((INT (ip(2+0))))/((INT (tmp_vect7(2+0)))))*((INT (tmp_vect7(2+0))))),(INT (tmp_vect7(2+0)))))>0))
      s_cont=TRUE
      DO i0=0, ((3))-1
        s(i0)=0
      END DO
      DO
        c(0+((0)))=((((INT (tmp_vect7(0+0))))*((INT (s(0+0))))+(INT (ip(0+0))))/(((10))*((INT (tmp_vect7(0+0))))))
        c(1+((0)))=((((INT (tmp_vect7(1+0))))*((INT (s(1+0))))+(INT (ip(1+0))))/((INT (tmp_vect7(1+0)))))
        c(2+((0)))=((((INT (tmp_vect7(2+0))))*((INT (s(2+0))))+(INT (ip(2+0))))/((INT (tmp_vect7(2+0)))))
        sp2(0+((0)))=(MOD(((INT (ip(0+0))))/((INT (tmp_vect7(0+0))))+(INT (s(0+0))),(10)))
        sp2(1+((0)))=(MOD(((INT (ip(1+0))))/((INT (tmp_vect7(1+0))))+(INT (s(1+0))),(1)))
        sp2(2+((0)))=(MOD(((INT (ip(2+0))))/((INT (tmp_vect7(2+0))))+(INT (s(2+0))),(1)))
        tmp_vect9(0+((0)))=((INT (bp(0+0)))+(INT (ip(0+0))))
        tmp_vect9(1+((0)))=((INT (bp(1+0)))+(INT (ip(1+0))))
        tmp_vect9(2+((0)))=((INT (bp(2+0)))+(INT (ip(2+0))))
        tmp_vect10(0+((0)))=((((10))*((INT (tmp_vect7(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect7(0+0)))))
        tmp_vect10(1+((0)))=(((INT (tmp_vect7(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect7(1+0)))))
        tmp_vect10(2+((0)))=(((INT (tmp_vect7(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect7(2+0)))))
        tmp_vect11(0+((0)))=((((10))*((INT (tmp_vect7(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect7(0+0))))+(INT (tmp_vect7(0+0))))
        tmp_vect11(1+((0)))=(((INT (tmp_vect7(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect7(1+0))))+(INT (tmp_vect7(1+0))))
        tmp_vect11(2+((0)))=(((INT (tmp_vect7(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect7(2+0))))+(INT (tmp_vect7(2+0))))
        tmp_vect12(0+((0)))=(((-1))*((INT (ip(0+0))))+(((10))*((INT (tmp_vect7(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect7(0+0)))))
        tmp_vect12(1+((0)))=(((-1))*((INT (ip(1+0))))+((INT (tmp_vect7(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect7(1+0)))))
        tmp_vect12(2+((0)))=(((-1))*((INT (ip(2+0))))+((INT (tmp_vect7(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect7(2+0)))))
        tmp_vect13(0+((0)))=(((-1))*((INT (bp(0+0))))+((-1))*((INT (ip(0+0))))+(((10))*((INT (tmp_vect7(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect7(0+0))))+(INT (tmp_vect7(0+0))))
        tmp_vect13(1+((0)))=(((-1))*((INT (bp(1+0))))+((-1))*((INT (ip(1+0))))+((INT (tmp_vect7(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect7(1+0))))+(INT (tmp_vect7(1+0))))
        tmp_vect13(2+((0)))=(((-1))*((INT (bp(2+0))))+((-1))*((INT (ip(2+0))))+((INT (tmp_vect7(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect7(2+0))))+(INT (tmp_vect7(2+0))))
        tmp_vect14(0+((0)))=((((-10))*((INT (tmp_vect7(0+0)))))*((INT (c(0+0))))+(((-1))*((INT (sp2(0+0)))))*((INT (tmp_vect7(0+0))))+((-1))*((INT (tmp_vect7(0+0))))+(INT (bp(0+0)))+(INT (ip(0+0))))
        tmp_vect14(1+((0)))=((((-1))*((INT (tmp_vect7(1+0)))))*((INT (c(1+0))))+(((-1))*((INT (sp2(1+0)))))*((INT (tmp_vect7(1+0))))+((-1))*((INT (tmp_vect7(1+0))))+(INT (bp(1+0)))+(INT (ip(1+0))))
        tmp_vect14(2+((0)))=((((-1))*((INT (tmp_vect7(2+0)))))*((INT (c(2+0))))+(((-1))*((INT (sp2(2+0)))))*((INT (tmp_vect7(2+0))))+((-1))*((INT (tmp_vect7(2+0))))+(INT (bp(2+0)))+(INT (ip(2+0))))
        out=FALSE
        DO i0 = 0, ((3))-1
          IF (tmp_vect10(i0)>=tmp_vect9(i0)) out=TRUE
        END DO
        DO i0 = 0, ((3))-1
          IF (tmp_vect11(i0)<ip(i0)) out=TRUE
        END DO
        IF (out) THEN
          ipp(0+((0)))=((0))
          ipp(1+((0)))=((0))
          ipp(2+((0)))=((0))
          lpp(0+((0)))=((0))
          lpp(1+((0)))=((0))
          lpp(2+((0)))=((0))
          bpp(0+((0)))=((0))
          bpp(1+((0)))=((0))
          bpp(2+((0)))=((0))
        ELSE
          ipp(0+((0)))=(((((INT (tmp_vect12(0+0))))>0))*((INT (tmp_vect12(0+0))))+(INT (ip(0+0))))
          ipp(1+((0)))=(((((INT (tmp_vect12(1+0))))>0))*((INT (tmp_vect12(1+0))))+(INT (ip(1+0))))
          ipp(2+((0)))=(((((INT (tmp_vect12(2+0))))>0))*((INT (tmp_vect12(2+0))))+(INT (ip(2+0))))
          lpp(0+((0)))=(((((INT (tmp_vect12(0+0))))>0))*((INT (tmp_vect12(0+0))))+(INT (lp(0+0))))
          lpp(1+((0)))=(((((INT (tmp_vect12(1+0))))>0))*((INT (tmp_vect12(1+0))))+(INT (lp(1+0))))
          lpp(2+((0)))=(((((INT (tmp_vect12(2+0))))>0))*((INT (tmp_vect12(2+0))))+(INT (lp(2+0))))
          bpp(0+((0)))=((((((INT (tmp_vect13(0+0))))>0))*((INT (tmp_vect14(0+0))))+(INT (tmp_vect11(0+0))))-((INT (ipp(0+0)))))
          bpp(1+((0)))=((((((INT (tmp_vect13(1+0))))>0))*((INT (tmp_vect14(1+0))))+(INT (tmp_vect11(1+0))))-((INT (ipp(1+0)))))
          bpp(2+((0)))=((((((INT (tmp_vect13(2+0))))>0))*((INT (tmp_vect14(2+0))))+(INT (tmp_vect11(2+0))))-((INT (ipp(2+0)))))
        END IF
        sp_=INT (sp2(0+((0))))* INT (1)+INT (sp2(1+((0))))* INT (1)+INT (sp2(2+((0))))
        IF ((MY_PROC()==p_) .AND. (MY_PROC()==sp_)) THEN
          IF (mode==1) THEN
            shift=(((-1))*((INT (tmp_vect3(0+0))))+(INT (lpp(0+0))))* INT (INT (tmp_vect0(1+((0)))))+(((-1))*((INT (tmp_vect3(1+0))))+(INT (lpp(1+0))))* INT (INT (tmp_vect0(2+((0)))))+(((-1))*((INT (tmp_vect3(2+0))))+(INT (lpp(2+0))))
            offset0=(((-1))*((INT (tmp_vect10(0+0))))+(INT (ipp(0+0))))* INT ((((INT (tmp_vect7(2+0))))*((INT (tmp_vect7(1+0))))))+(((-1))*((INT (tmp_vect10(1+0))))+(INT (ipp(1+0))))* INT (((INT (tmp_vect7(2+0)))))+(((-1))*((INT (tmp_vect10(2+0))))+(INT (ipp(2+0))))
            scalar0=((INT (tmp_vect7(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect7(2+0))))*((INT (tmp_vect7(1+0))))+(((-1))*((INT (tmp_vect7(2+0)))))*((INT (bpp(1+0)))));
            scalar2=((INT (tmp_vect0(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar3=(((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))+(((-1))*((INT (tmp_vect0(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  f90_out(shift)=f90_in1(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(INT (scalar0))
                shift=shift+(INT (scalar2))
              END DO
              offset0=offset0+(INT (scalar1))
              shift=shift+(INT (scalar3))
            END DO
          END IF
        ELSE IF (MY_PROC()==p_) THEN
          IF (mode==0) THEN
            ALLOCATE (buffer0r(sp_)%store(0:((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0))))-1))
            RECV(buffer0r(sp_)%store,((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0)))),sp_)
          END IF
          IF (mode==1) THEN
            shift=(((-1))*((INT (tmp_vect3(0+0))))+(INT (lpp(0+0))))* INT ((((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))))+(((-1))*((INT (tmp_vect3(1+0))))+(INT (lpp(1+0))))* INT (((INT (tmp_vect0(2+0)))))+(((-1))*((INT (tmp_vect3(2+0))))+(INT (lpp(2+0))))
            offset0=0* INT ((((INT (bpp(2+0))))*((INT (bpp(1+0))))))+0* INT (((INT (bpp(2+0)))))+0
            scalar0=((INT (tmp_vect0(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))+(((-1))*((INT (tmp_vect0(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  f90_out(shift)=buffer0r(sp_)%store(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(0)
                shift=shift+(INT (scalar0))
              END DO
              offset0=offset0+(0)
              shift=shift+(INT (scalar1))
            END DO
            DEALLOCATE(buffer0r(sp_)%store)
          END IF
        ELSE IF (MY_PROC()==sp_) THEN
          IF (mode==0) THEN
            ALLOCATE (buffer0s(sp_)%store(0:((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0))))-1))
            shift=0* INT (INT (bpp(1+((0)))))+0* INT (INT (bpp(2+((0)))))+0
            offset0=(((-1))*((INT (tmp_vect10(0+0))))+(INT (ipp(0+0))))* INT ((((INT (tmp_vect7(2+0))))*((INT (tmp_vect7(1+0))))))+(((-1))*((INT (tmp_vect10(1+0))))+(INT (ipp(1+0))))* INT (((INT (tmp_vect7(2+0)))))+(((-1))*((INT (tmp_vect10(2+0))))+(INT (ipp(2+0))))
            scalar0=((INT (tmp_vect7(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect7(2+0))))*((INT (tmp_vect7(1+0))))+(((-1))*((INT (tmp_vect7(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  buffer0s(sp_)%store(shift)=f90_in1(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(INT (scalar0))
                shift=shift+(0)
              END DO
              offset0=offset0+(INT (scalar1))
              shift=shift+(0)
            END DO
            SEND(buffer0s(sp_)%store,((((INT (bpp(2+0))))*((INT (bpp(1+0)))))*((INT (bpp(0+0))))),p_)
          END IF
          IF (mode==1) THEN
            DEALLOCATE(buffer0s(sp_)%store)
          END IF
        END IF
        s(2+((0)))=s(2+((0)))+1
        IF (s(2+((0)))>=tmp_vect8(2+((0)))) THEN
          s(2+((0)))=0
          s(1+((0)))=s(1+((0)))+1
          IF (s(1+((0)))>=tmp_vect8(1+((0)))) THEN
            s(1+((0)))=0
            s(0+((0)))=s(0+((0)))+1
            IF (s(0+((0)))>=tmp_vect8(0+((0)))) s_cont=FALSE
          END IF
        END IF
        IF (s_cont /= 0) EXIT
      END DO
      p(2+((0)))=p(2+((0)))+1
      IF (p(2+((0)))>=1) THEN
        p(2+((0)))=0
        p(1+((0)))=p(1+((0)))+1
        IF (p(1+((0)))>=1) THEN
          p(1+((0)))=0
          p(0+((0)))=p(0+((0)))+1
          IF (p(0+((0)))>=10) p_cont=FALSE
        END IF
      END IF
      IF (p_cont /= 0) EXIT
    END DO
    IF (mode==0) WAIT
  END DO



!
! out=out +  + in3
!

  DO mode=0, 1
    DO i0 = 0, ((3))-1
      p(i0)=0
    END DO
    p_cont=TRUE
    DO
      tmp_vect15(0+((0)))=((20))
      tmp_vect15(1+((0)))=((30))
      tmp_vect15(2+((0)))=((40))
      tmp_vect16(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))
      tmp_vect16(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))
      tmp_vect16(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))
      tmp_vect17(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0))))
      tmp_vect17(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))+(INT (tmp_vect0(1+0))))
      tmp_vect17(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))+(INT (tmp_vect0(2+0))))
      tmp_vect18(0+((0)))=(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0)))+(-20))
      tmp_vect18(1+((0)))=(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))+(INT (tmp_vect0(1+0)))+(-30))
      tmp_vect18(2+((0)))=(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))+(INT (tmp_vect0(2+0)))+(-40))
      tmp_vect19(0+((0)))=((((-1))*((INT (p(0+0)))))*((INT (tmp_vect0(0+0))))+((-1))*((INT (tmp_vect0(0+0))))+(20))
      tmp_vect19(1+((0)))=((((-1))*((INT (p(1+0)))))*((INT (tmp_vect0(1+0))))+((-1))*((INT (tmp_vect0(1+0))))+(30))
      tmp_vect19(2+((0)))=((((-1))*((INT (p(2+0)))))*((INT (tmp_vect0(2+0))))+((-1))*((INT (tmp_vect0(2+0))))+(40))
      out=FALSE
      DO i0 = 0, ((3))-1
        IF (tmp_vect16(i0)>=tmp_vect15(i0)) out=TRUE
      END DO
      IF (out) THEN
        ip(0+((0)))=((0))
        ip(1+((0)))=((0))
        ip(2+((0)))=((0))
        lp(0+((0)))=((0))
        lp(1+((0)))=((0))
        lp(2+((0)))=((0))
        bp(0+((0)))=((0))
        bp(1+((0)))=((0))
        bp(2+((0)))=((0))
       ELSE
        ip(0+((0)))=((((((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))>0))*(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))))
        ip(1+((0)))=((((((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))>0))*(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))))
        ip(2+((0)))=((((((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))>0))*(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))))
        lp(0+((0)))=((((((INT (p(0+0))))*((INT (tmp_vect0(0+0)))))>0))*(((INT (p(0+0))))*((INT (tmp_vect0(0+0))))))
        lp(1+((0)))=((((((INT (p(1+0))))*((INT (tmp_vect0(1+0)))))>0))*(((INT (p(1+0))))*((INT (tmp_vect0(1+0))))))
        lp(2+((0)))=((((((INT (p(2+0))))*((INT (tmp_vect0(2+0)))))>0))*(((INT (p(2+0))))*((INT (tmp_vect0(2+0))))))
        bp(0+((0)))=((((((INT (tmp_vect18(0+0))))>0))*((INT (tmp_vect19(0+0))))+(INT (tmp_vect17(0+0))))-((INT (lp(0+0)))))
        bp(1+((0)))=((((((INT (tmp_vect18(1+0))))>0))*((INT (tmp_vect19(1+0))))+(INT (tmp_vect17(1+0))))-((INT (lp(1+0)))))
        bp(2+((0)))=((((((INT (tmp_vect18(2+0))))>0))*((INT (tmp_vect19(2+0))))+(INT (tmp_vect17(2+0))))-((INT (lp(2+0)))))
      END IF
      p_=INT (p(0+((0))))* INT (1)+INT (p(1+((0))))* INT (1)+INT (p(2+((0))))
      tmp_vect20(0+((0)))=((3))
      tmp_vect20(1+((0)))=((30))
      tmp_vect20(2+((0)))=((40))
      tmp_vect21(0+((0)))=((((INT (ip(0+0)))+(INT (bp(0+0))))-((((INT (ip(0+0))))/((INT (tmp_vect20(0+0)))))*((INT (tmp_vect20(0+0))))))/((INT (tmp_vect20(0+0))))+((MOD(((INT (ip(0+0)))+(INT (bp(0+0))))-((((INT (ip(0+0))))/((INT (tmp_vect20(0+0)))))*((INT (tmp_vect20(0+0))))),(INT (tmp_vect20(0+0)))))>0))
      tmp_vect21(1+((0)))=((((INT (ip(1+0)))+(INT (bp(1+0))))-((((INT (ip(1+0))))/((INT (tmp_vect20(1+0)))))*((INT (tmp_vect20(1+0))))))/((INT (tmp_vect20(1+0))))+((MOD(((INT (ip(1+0)))+(INT (bp(1+0))))-((((INT (ip(1+0))))/((INT (tmp_vect20(1+0)))))*((INT (tmp_vect20(1+0))))),(INT (tmp_vect20(1+0)))))>0))
      tmp_vect21(2+((0)))=((((INT (ip(2+0)))+(INT (bp(2+0))))-((((INT (ip(2+0))))/((INT (tmp_vect20(2+0)))))*((INT (tmp_vect20(2+0))))))/((INT (tmp_vect20(2+0))))+((MOD(((INT (ip(2+0)))+(INT (bp(2+0))))-((((INT (ip(2+0))))/((INT (tmp_vect20(2+0)))))*((INT (tmp_vect20(2+0))))),(INT (tmp_vect20(2+0)))))>0))
      s_cont=TRUE
      DO i0=0, ((3))-1
        s(i0)=0
      END DO
      DO
        c(0+((0)))=((((INT (tmp_vect20(0+0))))*((INT (s(0+0))))+(INT (ip(0+0))))/(((10))*((INT (tmp_vect20(0+0))))))
        c(1+((0)))=((((INT (tmp_vect20(1+0))))*((INT (s(1+0))))+(INT (ip(1+0))))/((INT (tmp_vect20(1+0)))))
        c(2+((0)))=((((INT (tmp_vect20(2+0))))*((INT (s(2+0))))+(INT (ip(2+0))))/((INT (tmp_vect20(2+0)))))
        sp2(0+((0)))=(MOD(((INT (ip(0+0))))/((INT (tmp_vect20(0+0))))+(INT (s(0+0))),(10)))
        sp2(1+((0)))=(MOD(((INT (ip(1+0))))/((INT (tmp_vect20(1+0))))+(INT (s(1+0))),(1)))
        sp2(2+((0)))=(MOD(((INT (ip(2+0))))/((INT (tmp_vect20(2+0))))+(INT (s(2+0))),(1)))
        tmp_vect22(0+((0)))=((INT (bp(0+0)))+(INT (ip(0+0))))
        tmp_vect22(1+((0)))=((INT (bp(1+0)))+(INT (ip(1+0))))
        tmp_vect22(2+((0)))=((INT (bp(2+0)))+(INT (ip(2+0))))
        tmp_vect23(0+((0)))=((((10))*((INT (tmp_vect20(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect20(0+0)))))
        tmp_vect23(1+((0)))=(((INT (tmp_vect20(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect20(1+0)))))
        tmp_vect23(2+((0)))=(((INT (tmp_vect20(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect20(2+0)))))
        tmp_vect24(0+((0)))=((((10))*((INT (tmp_vect20(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect20(0+0))))+(INT (tmp_vect20(0+0))))
        tmp_vect24(1+((0)))=(((INT (tmp_vect20(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect20(1+0))))+(INT (tmp_vect20(1+0))))
        tmp_vect24(2+((0)))=(((INT (tmp_vect20(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect20(2+0))))+(INT (tmp_vect20(2+0))))
        tmp_vect25(0+((0)))=(((-1))*((INT (ip(0+0))))+(((10))*((INT (tmp_vect20(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect20(0+0)))))
        tmp_vect25(1+((0)))=(((-1))*((INT (ip(1+0))))+((INT (tmp_vect20(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect20(1+0)))))
        tmp_vect25(2+((0)))=(((-1))*((INT (ip(2+0))))+((INT (tmp_vect20(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect20(2+0)))))
        tmp_vect26(0+((0)))=(((-1))*((INT (bp(0+0))))+((-1))*((INT (ip(0+0))))+(((10))*((INT (tmp_vect20(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect20(0+0))))+(INT (tmp_vect20(0+0))))
        tmp_vect26(1+((0)))=(((-1))*((INT (bp(1+0))))+((-1))*((INT (ip(1+0))))+((INT (tmp_vect20(1+0))))*((INT (c(1+0))))+((INT (sp2(1+0))))*((INT (tmp_vect20(1+0))))+(INT (tmp_vect20(1+0))))
        tmp_vect26(2+((0)))=(((-1))*((INT (bp(2+0))))+((-1))*((INT (ip(2+0))))+((INT (tmp_vect20(2+0))))*((INT (c(2+0))))+((INT (sp2(2+0))))*((INT (tmp_vect20(2+0))))+(INT (tmp_vect20(2+0))))
        tmp_vect27(0+((0)))=((((-10))*((INT (tmp_vect20(0+0)))))*((INT (c(0+0))))+(((-1))*((INT (sp2(0+0)))))*((INT (tmp_vect20(0+0))))+((-1))*((INT (tmp_vect20(0+0))))+(INT (bp(0+0)))+(INT (ip(0+0))))
        tmp_vect27(1+((0)))=((((-1))*((INT (tmp_vect20(1+0)))))*((INT (c(1+0))))+(((-1))*((INT (sp2(1+0)))))*((INT (tmp_vect20(1+0))))+((-1))*((INT (tmp_vect20(1+0))))+(INT (bp(1+0)))+(INT (ip(1+0))))
        tmp_vect27(2+((0)))=((((-1))*((INT (tmp_vect20(2+0)))))*((INT (c(2+0))))+(((-1))*((INT (sp2(2+0)))))*((INT (tmp_vect20(2+0))))+((-1))*((INT (tmp_vect20(2+0))))+(INT (bp(2+0)))+(INT (ip(2+0))))
        out=FALSE
        DO i0 = 0, ((3))-1
          IF (tmp_vect23(i0)>=tmp_vect22(i0)) out=TRUE
        END DO
        DO i0 = 0, ((3))-1
          IF (tmp_vect24(i0)<ip(i0)) out=TRUE
        END DO
        IF (out) THEN
          ipp(0+((0)))=((0))
          ipp(1+((0)))=((0))
          ipp(2+((0)))=((0))
          lpp(0+((0)))=((0))
          lpp(1+((0)))=((0))
          lpp(2+((0)))=((0))
          bpp(0+((0)))=((0))
          bpp(1+((0)))=((0))
          bpp(2+((0)))=((0))
        ELSE
          ipp(0+((0)))=(((((INT (tmp_vect25(0+0))))>0))*((INT (tmp_vect25(0+0))))+(INT (ip(0+0))))
          ipp(1+((0)))=(((((INT (tmp_vect25(1+0))))>0))*((INT (tmp_vect25(1+0))))+(INT (ip(1+0))))
          ipp(2+((0)))=(((((INT (tmp_vect25(2+0))))>0))*((INT (tmp_vect25(2+0))))+(INT (ip(2+0))))
          lpp(0+((0)))=(((((INT (tmp_vect25(0+0))))>0))*((INT (tmp_vect25(0+0))))+(INT (lp(0+0))))
          lpp(1+((0)))=(((((INT (tmp_vect25(1+0))))>0))*((INT (tmp_vect25(1+0))))+(INT (lp(1+0))))
          lpp(2+((0)))=(((((INT (tmp_vect25(2+0))))>0))*((INT (tmp_vect25(2+0))))+(INT (lp(2+0))))
          bpp(0+((0)))=((((((INT (tmp_vect26(0+0))))>0))*((INT (tmp_vect27(0+0))))+(INT (tmp_vect24(0+0))))-((INT (ipp(0+0)))))
          bpp(1+((0)))=((((((INT (tmp_vect26(1+0))))>0))*((INT (tmp_vect27(1+0))))+(INT (tmp_vect24(1+0))))-((INT (ipp(1+0)))))
          bpp(2+((0)))=((((((INT (tmp_vect26(2+0))))>0))*((INT (tmp_vect27(2+0))))+(INT (tmp_vect24(2+0))))-((INT (ipp(2+0)))))
        END IF
        sp_=INT (sp2(0+((0))))* INT (1)+INT (sp2(1+((0))))* INT (1)+INT (sp2(2+((0))))
        IF ((MY_PROC()==p_) .AND. (MY_PROC()==sp_)) THEN
          IF (mode==1) THEN
            shift=(((-1))*((INT (tmp_vect16(0+0))))+(INT (lpp(0+0))))* INT (INT (tmp_vect0(1+((0)))))+(((-1))*((INT (tmp_vect16(1+0))))+(INT (lpp(1+0))))* INT (INT (tmp_vect0(2+((0)))))+(((-1))*((INT (tmp_vect16(2+0))))+(INT (lpp(2+0))))
            offset0=(((-1))*((INT (tmp_vect23(0+0))))+(INT (ipp(0+0))))* INT ((((INT (tmp_vect20(2+0))))*((INT (tmp_vect20(1+0))))))+(((-1))*((INT (tmp_vect23(1+0))))+(INT (ipp(1+0))))* INT (((INT (tmp_vect20(2+0)))))+(((-1))*((INT (tmp_vect23(2+0))))+(INT (ipp(2+0))))
            scalar0=((INT (tmp_vect20(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect20(2+0))))*((INT (tmp_vect20(1+0))))+(((-1))*((INT (tmp_vect20(2+0)))))*((INT (bpp(1+0)))));
            scalar2=((INT (tmp_vect0(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar3=(((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))+(((-1))*((INT (tmp_vect0(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  f90_out(shift)=f90_out(shift)+f90_in3(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(INT (scalar0))
                shift=shift+(INT (scalar2))
              END DO
              offset0=offset0+(INT (scalar1))
              shift=shift+(INT (scalar3))
            END DO
          END IF
        ELSE IF (MY_PROC()==p_) THEN
          IF (mode==0) THEN
            ALLOCATE (buffer0r(sp_)%store(0:((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0))))-1))
            RECV(buffer0r(sp_)%store,((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0)))),sp_)
          END IF
          IF (mode==1) THEN
            shift=(((-1))*((INT (tmp_vect16(0+0))))+(INT (lpp(0+0))))* INT ((((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))))+(((-1))*((INT (tmp_vect16(1+0))))+(INT (lpp(1+0))))* INT (((INT (tmp_vect0(2+0)))))+(((-1))*((INT (tmp_vect16(2+0))))+(INT (lpp(2+0))))
            offset0=0* INT ((((INT (bpp(2+0))))*((INT (bpp(1+0))))))+0* INT (((INT (bpp(2+0)))))+0
            scalar0=((INT (tmp_vect0(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect0(2+0))))*((INT (tmp_vect0(1+0))))+(((-1))*((INT (tmp_vect0(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  f90_out(shift)=f90_out(shift)+buffer0r(sp_)%store(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(0)
                shift=shift+(INT (scalar0))
              END DO
              offset0=offset0+(0)
              shift=shift+(INT (scalar1))
            END DO
            DEALLOCATE(buffer0r(sp_)%store)
          END IF
        ELSE IF (MY_PROC()==sp_) THEN
          IF (mode==0) THEN
            ALLOCATE (buffer0s(sp_)%store(0:((INT (bpp(0+0))))*((INT (bpp(1+0))))*((INT (bpp(2+0))))-1))
            shift=0* INT (INT (bpp(1+((0)))))+0* INT (INT (bpp(2+((0)))))+0
            offset0=(((-1))*((INT (tmp_vect23(0+0))))+(INT (ipp(0+0))))* INT ((((INT (tmp_vect20(2+0))))*((INT (tmp_vect20(1+0))))))+(((-1))*((INT (tmp_vect23(1+0))))+(INT (ipp(1+0))))* INT (((INT (tmp_vect20(2+0)))))+(((-1))*((INT (tmp_vect23(2+0))))+(INT (ipp(2+0))))
            scalar0=((INT (tmp_vect20(2+0)))+((-1))*((INT (bpp(2+0)))));
            scalar1=(((INT (tmp_vect20(2+0))))*((INT (tmp_vect20(1+0))))+(((-1))*((INT (tmp_vect20(2+0)))))*((INT (bpp(1+0)))));
            DO i0 = 0, INT (bpp(0+((0))))-1
              DO i1 = 0, INT (bpp(1+((0))))-1
                DO i2 = 0, INT (bpp(2+((0))))-1
                  buffer0s(sp_)%store(shift)=f90_in3(offset0)
                  offset0=offset0+((1))
                  shift=shift+1
                END DO
                offset0=offset0+(INT (scalar0))
                shift=shift+(0)
              END DO
              offset0=offset0+(INT (scalar1))
              shift=shift+(0)
            END DO
            SEND(buffer0s(sp_)%store,((((INT (bpp(2+0))))*((INT (bpp(1+0)))))*((INT (bpp(0+0))))),p_)
          END IF
          IF (mode==1) THEN
            DEALLOCATE(buffer0s(sp_)%store)
          END IF
        END IF
        s(2+((0)))=s(2+((0)))+1
        IF (s(2+((0)))>=tmp_vect21(2+((0)))) THEN
          s(2+((0)))=0
          s(1+((0)))=s(1+((0)))+1
          IF (s(1+((0)))>=tmp_vect21(1+((0)))) THEN
            s(1+((0)))=0
            s(0+((0)))=s(0+((0)))+1
            IF (s(0+((0)))>=tmp_vect21(0+((0)))) s_cont=FALSE
          END IF
        END IF
        IF (s_cont /= 0) EXIT
      END DO
      p(2+((0)))=p(2+((0)))+1
      IF (p(2+((0)))>=1) THEN
        p(2+((0)))=0
        p(1+((0)))=p(1+((0)))+1
        IF (p(1+((0)))>=1) THEN
          p(1+((0)))=0
          p(0+((0)))=p(0+((0)))+1
          IF (p(0+((0)))>=10) p_cont=FALSE
        END IF
      END IF
      IF (p_cont /= 0) EXIT
    END DO
    IF (mode==0) WAIT
  END DO



END SUBROUTINE ADD_SUB1


