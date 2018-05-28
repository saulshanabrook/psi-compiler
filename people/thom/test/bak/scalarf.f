SUBROUTINE SCALARCAT_F90 (in1, out1, out2, out3)
    REAL, DIMENSION (0:) :: in1, out1, out2, out3
    INTEGER :: I

	DO I = 0, 4
        out1(I) = in1(I)
    END DO
    out1(5) = 5
	DO I = 0, 4
        out2(I+1) = in1(I)
    END DO
    out2(0) = 5
    out3(0)=5
    out3(0)=5
END SUBROUTINE SCALARCAT_F90

SUBROUTINE SCALAROPS_F90 (in1, out1)
    REAL, DIMENSION (0:) :: in1, out1
    INTEGER :: I

	DO I = 0, 23
        out1(I) = in1(I) + 5
    END DO
END SUBROUTINE SCALAROPS_F90

SUBROUTINE SCALAROPS2_F90 (in1, in2, out1)
    REAL, DIMENSION (0:) :: in1, in2, out1
    INTEGER :: I

	DO I = 0, 23
        out1(I) = in1(I) + 5
    END DO
	DO I = 0, 11
        out1(I+24) = in2(I) + 5
    END DO
END SUBROUTINE SCALAROPS2_F90

