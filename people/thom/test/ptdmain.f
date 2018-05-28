PROGRAM ptdmain
    REAL, DIMENSION (0:23) :: in1 = (/ 5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,4,2,9,7/)
    INTERFACE
        SUBROUTINE do_ptd (mdat, cdat, in1)
            CHARACTER(LEN=*) :: mdat, cdat
            REAL, DIMENSION (0:) :: in1
        END SUBROUTINE do_ptd
    END INTERFACE

    CALL do_ptd ("ptdm.dat", "ptdf.dat", in1)
END PROGRAM ptdmain

SUBROUTINE do_ptd (mdat, cdat, in1)
    CHARACTER(LEN=*) :: mdat, cdat
    REAL, DIMENSION (0:) :: in1
	REAL :: out1 (0:11), out2 (0:0), out3 (0:3), out4 (0:11)
    INTEGER :: j

    INTERFACE 
        SUBROUTINE TAKE1_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE TAKE1_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE DROP_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE DROP_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE TAKE2_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE TAKE2_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE DROP2_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE DROP2_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE PTD1_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PTD1_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE PSI1_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PSI1_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE PSI2_M(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PSI2_M
    END INTERFACE

    INTERFACE 
        SUBROUTINE TAKE1_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE TAKE1_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE DROP1_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE DROP1_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE TAKE2_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE TAKE2_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE DROP2_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE DROP2_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE PTD1_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PTD1_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE PSI1_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PSI1_F90
    END INTERFACE

    INTERFACE 
        SUBROUTINE PSI2_F90(f90_in1, f90_out)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out
        END SUBROUTINE PSI2_F90
    END INTERFACE

    OPEN (1, FILE=mdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")

    PRINT *, "HERE"
    CALL TAKE1_M (in1, out1)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out1(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL DROP_M (in1, out1)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out1(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    CALL TAKE2_M (in1, out2)
    WRITE (1,"(F8.3)") out2(0)
    WRITE (1,"(A)") ""

    CALL DROP2_M (in1, out2)
    WRITE (1,"(F8.3)") out2(0)
    WRITE (1,"(A)") ""

    CALL PTD1_M (in1, out3)
    WRITE (1,"(4F8.3)") out3(0:3)
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL PSI1_M (in1, out4)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out4(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    CALL PSI2_M (in1, out3)
    WRITE (1,"(4F8.3)") out3(0:3)
    WRITE (1,"(A)") ""


    OPEN (1, FILE=cdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")

    PRINT *, "HERE"
    CALL TAKE1_F90 (in1, out1)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out1(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL DROP1_F90 (in1, out1)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out1(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    CALL TAKE2_F90 (in1, out2)
    WRITE (1,"(F8.3)") out2(0)
    WRITE (1,"(A)") ""

    CALL DROP2_F90 (in1, out2)
    WRITE (1,"(F8.3)") out2(0)
    WRITE (1,"(A)") ""

    CALL PTD1_F90 (in1, out3)
    WRITE (1,"(4F8.3)") out3(0:3)
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL PSI1_F90 (in1, out4)
    PRINT *, "HERE"
    DO j=0, 2
        WRITE (1,"(4F8.3)") out4(j*4:j*4+3)
    END DO
    WRITE (1,"(A)") ""

    CALL PSI2_F90 (in1, out3)
    WRITE (1,"(4F8.3)") out3(0:3)
    WRITE (1,"(A)") ""

	CLOSE (1)
END SUBROUTINE do_ptd
