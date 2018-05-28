PROGRAM scalarmain
        REAL, DIMENSION (0:4) :: in1 = (/ 7,8,9,10,11 /)
        REAL, DIMENSION (0:23) :: in2 = (/ 11,10,9,8,7,6,5,4,3,2,1,0,11,10,9,8,7,6,5,4,3,2,1,0 /)
        REAL, DIMENSION (0:23) :: in3 = (/ 5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,1,1,1,1 /)
        INTERFACE
                SUBROUTINE do_scalars (mdat, cdat, in1, in2, in3)
                        CHARACTER(LEN=*) :: mdat, cdat
                        REAL, DIMENSION (0:) :: in1, in2, in3
                END SUBROUTINE do_scalars
        END INTERFACE

        CALL do_scalars ("scalarm.dat", "scalarf.dat", in1, in2, in3)
END PROGRAM scalarmain

SUBROUTINE do_scalars (mdat, cdat, in1, in2, in3)
    CHARACTER(LEN=*) :: mdat, cdat
    REAL, DIMENSION (0:) :: in1, in2, in3
    REAL, DIMENSION (0:5) :: out1, out2
    REAL, DIMENSION (0:1) :: out3
    REAL, DIMENSION (0:23) :: out4
    REAL, DIMENSION (0:35) :: out5


    INTERFACE
        SUBROUTINE SCALARCAT_M(f90_in1, f90_out1, f90_out2, f90_out3)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out1
            REAL, DIMENSION (0:) :: f90_out2
            REAL, DIMENSION (0:) :: f90_out3
        END SUBROUTINE SCALARCAT_M
    END INTERFACE

    INTERFACE
        SUBROUTINE SCALAROPS_M(f90_in1, f90_out1)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out1
        END SUBROUTINE SCALAROPS_M
    END INTERFACE

    INTERFACE
        SUBROUTINE SCALAROPS2_M(f90_in1, f90_in2, f90_out1)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_in2
            REAL, DIMENSION (0:) :: f90_out1
        END SUBROUTINE SCALAROPS2_M
    END INTERFACE

    INTERFACE
        SUBROUTINE SCALARCAT_F90(f90_in1, f90_out1, f90_out2, f90_out3)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out1
            REAL, DIMENSION (0:) :: f90_out2
            REAL, DIMENSION (0:) :: f90_out3
        END SUBROUTINE SCALARCAT_F90
    END INTERFACE

    INTERFACE
        SUBROUTINE SCALAROPS_F90(f90_in1, f90_out1)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_out1
        END SUBROUTINE SCALAROPS_F90
    END INTERFACE

    INTERFACE
        SUBROUTINE SCALAROPS2_F90(f90_in1, f90_in2, f90_out1)
            REAL, DIMENSION (0:) :: f90_in1
            REAL, DIMENSION (0:) :: f90_in2
            REAL, DIMENSION (0:) :: f90_out1
        END SUBROUTINE SCALAROPS2_F90
    END INTERFACE

    OPEN (1, FILE=mdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")

    PRINT *, "HERE"
    CALL SCALARCAT_M (in1, out1, out2, out3)
    PRINT *, "HERE"
    WRITE (1,"(6F8.3)") out1
    WRITE (1,"(A)") ""
    WRITE (1,"(6F8.3)") out2
    WRITE (1,"(A)") ""
    WRITE (1,"(2F8.3)") out3
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL SCALAROPS_M (in2, out4)
    PRINT *, "HERE"
    WRITE (1,"(6(4F8.3, /))") out4
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL SCALAROPS2_M (in2, in3, out5)
    PRINT *, "HERE"
    WRITE (1,"(9(4F8.3, /))") out4
    WRITE (1,"(A)") ""

    CLOSE (1)
    OPEN (1, FILE=cdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")

    PRINT *, "HERE"
    CALL SCALARCAT_F90 (in1, out1, out2, out3)
    PRINT *, "HERE"
    WRITE (1,"(6F8.3)") out1
    WRITE (1,"(A)") ""
    WRITE (1,"(6F8.3)") out2
    WRITE (1,"(A)") ""
    WRITE (1,"(2F8.3)") out3
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL SCALAROPS_F90 (in2, out4)
    PRINT *, "HERE"
    WRITE (1,"(6(4F8.3, /))") out4
    WRITE (1,"(A)") ""

    PRINT *, "HERE"
    CALL SCALAROPS2_F90 (in2, in3, out5)
    PRINT *, "HERE"
    WRITE (1,"(9(4F8.3, /))") out4
    WRITE (1,"(A)") ""

    CLOSE (1)
END SUBROUTINE do_scalars
