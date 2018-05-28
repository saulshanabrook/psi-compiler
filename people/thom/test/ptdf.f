SUBROUTINE TAKE1_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out
        INTEGER :: I

        DO I = 0, 11
                out(I) = in1(2*I)
        END DO
END SUBROUTINE TAKE1_F90

SUBROUTINE DROP1_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out
        INTEGER :: I

        DO I = 0, 11
                out(I) = in1(I*2+1)
        END DO
END SUBROUTINE DROP1_F90

SUBROUTINE TAKE2_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out

        out(0) = in1(2)
END SUBROUTINE TAKE2_F90

SUBROUTINE DROP2_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out

        out(0) = in1(2)
END SUBROUTINE DROP2_F90

SUBROUTINE PTD1_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out
        INTEGER :: I

        DO I = 0, 3
                out(I) = in1(I*6+5)
        END DO
END SUBROUTINE PTD1_F90

SUBROUTINE PSI1_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out
        INTEGER :: I

        DO I = 0, 11
                out(I) = in1(2*I+1)
        END DO
END SUBROUTINE PSI1_F90

SUBROUTINE PSI2_F90 (in1, out)
        REAL, DIMENSION (0:) :: in1, out
        INTEGER :: I

        DO I = 0, 3
                out(I) = in1(I*6+5)
        END DO
END SUBROUTINE PSI2_F90
