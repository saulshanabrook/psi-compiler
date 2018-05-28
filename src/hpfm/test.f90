USE MOALIB

USE NETWORK

SUBROUTINE test ()
INTEGER ::D 

! MOA
! Variable declarations
!
  REAL, DIMENSION (:), ALLOCATABLE :: B
  INTEGER, DIMENSION (0:100-1) :: A
  INTEGER, DIMENSION (0:1-1) :: tmp_vect0
  INTEGER, DIMENSION (0:1-1) :: tmp_vect1
  INTEGER, DIMENSION (0:1-1) :: tmp_vect2
  INTEGER, DIMENSION (0:1-1) :: tmp_vect3
  INTEGER, DIMENSION (0:1-1) :: tmp_vect4
  INTEGER, DIMENSION (0:1-1) :: tmp_vect5
  INTEGER, DIMENSION (0:1-1) :: tmp_vect6
  INTEGER, DIMENSION (0:1-1) :: tmp_vect7
  INTEGER, DIMENSION (0:1-1) :: tmp_vect8
  INTEGER, DIMENSION (0:1-1) :: tmp_vect9
  INTEGER, DIMENSION (0:1-1) :: tmp_vect10
  INTEGER, DIMENSION (0:1-1) :: tmp_vect11
  INTEGER, DIMENSION (0:1-1) :: tmp_vect12
  INTEGER, DIMENSION (0:1-1) :: tmp_vect13
  INTEGER, DIMENSION (0:1-1) :: tmp_vect14
  INTEGER, DIMENSION (0:1-1) :: tmp_vect15
  INTEGER, DIMENSION (0:1-1) :: tmp_vect16
  INTEGER :: j_cont,p_cont,s_cont,out
  INTEGER :: p_,sp_,mode,offset
  INTEGER, DIMENSION (0:0) :: p
  INTEGER, DIMENSION (0:0) :: c
  INTEGER, DIMENSION (0:0) :: s
  INTEGER, DIMENSION (0:0) :: sp2
  INTEGER, DIMENSION (0:0) :: ip
  INTEGER, DIMENSION (0:0) :: lp
  INTEGER, DIMENSION (0:0) :: bp
  INTEGER, DIMENSION (0:0) :: ipp
  INTEGER, DIMENSION (0:0) :: lpp
  INTEGER, DIMENSION (0:0) :: bpp
  TYPE BUF
    REAL, DIMENSION (:), POINTER :: store
  END TYPE BUF
  TYPE(BUF), DIMENSION (0:3) :: buffer0r, buffer0s
  INTEGER :: shift
  INTEGER :: offset0
  INTEGER :: i0

  NODE_INIT(4);

  !  Communications for Initial Data

  ALLOCATE (B(0:26-1))

! Procedure body

! MOA
! array assignment
!

  shift=0
  offset0=2
  DO i0 = 0, 100-1
    A(shift)=A(offset0)
    offset0=offset0+((1))
    shift=shift+1
  END DO
  DO mode=0, 1
    tmp_vect0(0+((0)))=((26))
    tmp_vect1(0+((0)))=((((102))-((((2))/((INT (tmp_vect0(0+0)))))*((INT (tmp_vect0(0+0))))))/((INT (tmp_vect0(0+0))))+((MOD(((102))-((((2))/((INT (tmp_vect0(0+0)))))*((INT (tmp_vect0(0+0))))),(INT (tmp_vect0(0+0)))))>0))
    s_cont=TRUE
    DO i0=0, ((1))-1
      s(i0)=0
    END DO
    DO
      c(0+((0)))=((((INT (tmp_vect0(0+0))))*((INT (s(0+0))))+(2))/(((4))*((INT (tmp_vect0(0+0))))))
      sp2(0+((0)))=(MOD(((2))/((INT (tmp_vect0(0+0))))+(INT (s(0+0))),(4)))
      tmp_vect2(0+((0)))=((2))
      tmp_vect3(0+((0)))=((102))
      tmp_vect4(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0)))))
      tmp_vect5(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0))))
      tmp_vect6(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(-2))
      tmp_vect7(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0)))+(-102))
      tmp_vect8(0+((0)))=((((-4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+(((-1))*((INT (sp2(0+0)))))*((INT (tmp_vect0(0+0))))+((-1))*((INT (tmp_vect0(0+0))))+(102))
      out=FALSE
      DO i0 = 0, ((1))-1
        IF (tmp_vect4(i0)>=tmp_vect3(i0)) out=TRUE
      END DO
      DO i0 = 0, ((1))-1
        IF (tmp_vect5(i0)<tmp_vect2(i0)) out=TRUE
      END DO
      IF (out) THEN
        ipp(0+((0)))=((0))
        lpp(0+((0)))=((0))
        bpp(0+((0)))=((0))
      ELSE
        ipp(0+((0)))=(((((INT (tmp_vect6(0+0))))>0))*((INT (tmp_vect6(0+0))))+(INT (tmp_vect2(0+0))))
        lpp(0+((0)))=(((((INT (tmp_vect6(0+0))))>0))*((INT (tmp_vect6(0+0)))))
        bpp(0+((0)))=((((((INT (tmp_vect7(0+0))))>0))*((INT (tmp_vect8(0+0))))+(INT (tmp_vect5(0+0))))-((INT (ipp(0+0)))))
      END IF
      sp_=INT (sp2(0+((0))))
      IF (MY_PROC()==sp_) THEN
        IF (mode==1) THEN
          shift=INT (lpp(0+((0))))
          offset0=(((-1))*((INT (tmp_vect4(0+0))))+(INT (ipp(0+0))))
          DO i0 = 0, INT (bpp(0+((0))))-1
            A(shift)=A(shift)+B(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
        END IF
      ELSE
        IF (mode==0) THEN
          ALLOCATE (buffer0r(sp_)%store(0:((INT (bpp(0+0))))-1))
          RECV(buffer0r(sp_)%store,((INT (bpp(0+0)))),sp_)
        END IF
        IF (mode==1) THEN
          shift=INT (lpp(0+((0))))
          offset0=0
          DO i0 = 0, INT (bpp(0+((0))))-1
            A(shift)=A(shift)+buffer0r(sp_)%store(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
          DEALLOCATE(buffer0r(sp_)%store)
        END IF
      END IF
      IF (MY_PROC()==sp_) THEN
        IF (mode==0) THEN
          ALLOCATE (buffer0s(sp_)%store(0:((INT (bpp(0+0))))-1))
          shift=0
          offset0=(((-1))*((INT (tmp_vect4(0+0))))+(INT (ipp(0+0))))
          DO i0 = 0, INT (bpp(0+((0))))-1
            buffer0s(sp_)%store(shift)=B(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
          DO i0=0, 3
            IF (i0/=mp) SEND(buffer0s(sp_)%store,((INT (bpp(0+0)))),i0)
          END IF
        END DO
        END IF
        IF (mode==1) THEN
          DEALLOCATE(buffer0s(sp_)%store)
        END IF
      END IF
      s(0+((0)))=s(0+((0)))+1
      IF (s(0+((0)))>=tmp_vect1(0+((0)))) s_cont=FALSE
      IF (s_cont /= 0) EXIT
    END DO
    IF (mode==0) WAIT
  END DO

  DO mode=0, 1
    tmp_vect9(0+((0)))=((((106))-((((6))/((INT (tmp_vect0(0+0)))))*((INT (tmp_vect0(0+0))))))/((INT (tmp_vect0(0+0))))+((MOD(((106))-((((6))/((INT (tmp_vect0(0+0)))))*((INT (tmp_vect0(0+0))))),(INT (tmp_vect0(0+0)))))>0))
    s_cont=TRUE
    DO i0=0, ((1))-1
      s(i0)=0
    END DO
    DO
      c(0+((0)))=((((INT (tmp_vect0(0+0))))*((INT (s(0+0))))+(6))/(((4))*((INT (tmp_vect0(0+0))))))
      sp2(0+((0)))=(MOD(((6))/((INT (tmp_vect0(0+0))))+(INT (s(0+0))),(4)))
      tmp_vect10(0+((0)))=((6))
      tmp_vect11(0+((0)))=((106))
      tmp_vect12(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0)))))
      tmp_vect13(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0))))
      tmp_vect14(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(-6))
      tmp_vect15(0+((0)))=((((4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+((INT (sp2(0+0))))*((INT (tmp_vect0(0+0))))+(INT (tmp_vect0(0+0)))+(-106))
      tmp_vect16(0+((0)))=((((-4))*((INT (tmp_vect0(0+0)))))*((INT (c(0+0))))+(((-1))*((INT (sp2(0+0)))))*((INT (tmp_vect0(0+0))))+((-1))*((INT (tmp_vect0(0+0))))+(106))
      out=FALSE
      DO i0 = 0, ((1))-1
        IF (tmp_vect12(i0)>=tmp_vect11(i0)) out=TRUE
      END DO
      DO i0 = 0, ((1))-1
        IF (tmp_vect13(i0)<tmp_vect10(i0)) out=TRUE
      END DO
      IF (out) THEN
        ipp(0+((0)))=((0))
        lpp(0+((0)))=((0))
        bpp(0+((0)))=((0))
      ELSE
        ipp(0+((0)))=(((((INT (tmp_vect14(0+0))))>0))*((INT (tmp_vect14(0+0))))+(INT (tmp_vect10(0+0))))
        lpp(0+((0)))=(((((INT (tmp_vect14(0+0))))>0))*((INT (tmp_vect14(0+0)))))
        bpp(0+((0)))=((((((INT (tmp_vect15(0+0))))>0))*((INT (tmp_vect16(0+0))))+(INT (tmp_vect13(0+0))))-((INT (ipp(0+0)))))
      END IF
      sp_=INT (sp2(0+((0))))
      IF (MY_PROC()==sp_) THEN
        IF (mode==1) THEN
          shift=INT (lpp(0+((0))))
          offset0=(((-1))*((INT (tmp_vect12(0+0))))+(INT (ipp(0+0))))
          DO i0 = 0, INT (bpp(0+((0))))-1
            A(shift)=A(shift)+B(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
        END IF
      ELSE
        IF (mode==0) THEN
          ALLOCATE (buffer0r(sp_)%store(0:((INT (bpp(0+0))))-1))
          RECV(buffer0r(sp_)%store,((INT (bpp(0+0)))),sp_)
        END IF
        IF (mode==1) THEN
          shift=INT (lpp(0+((0))))
          offset0=0
          DO i0 = 0, INT (bpp(0+((0))))-1
            A(shift)=A(shift)+buffer0r(sp_)%store(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
          DEALLOCATE(buffer0r(sp_)%store)
        END IF
      END IF
      IF (MY_PROC()==sp_) THEN
        IF (mode==0) THEN
          ALLOCATE (buffer0s(sp_)%store(0:((INT (bpp(0+0))))-1))
          shift=0
          offset0=(((-1))*((INT (tmp_vect12(0+0))))+(INT (ipp(0+0))))
          DO i0 = 0, INT (bpp(0+((0))))-1
            buffer0s(sp_)%store(shift)=B(offset0)
            offset0=offset0+((1))
            shift=shift+1
          END DO
          DO i0=0, 3
            IF (i0/=mp) SEND(buffer0s(sp_)%store,((INT (bpp(0+0)))),i0)
          END IF
        END DO
        END IF
        IF (mode==1) THEN
          DEALLOCATE(buffer0s(sp_)%store)
        END IF
      END IF
      s(0+((0)))=s(0+((0)))+1
      IF (s(0+((0)))>=tmp_vect9(0+((0)))) s_cont=FALSE
      IF (s_cont /= 0) EXIT
    END DO
    IF (mode==0) WAIT
  END DO



END SUBROUTINE test 
