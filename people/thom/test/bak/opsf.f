SUBROUTINE ADD_SUB1_F90 (in1, in2, in3, out)
	REAL, DIMENSION (0:) :: in1, in2, in3, out
	INTEGER :: I

	DO I = 0, 23
		out(I) = in1(I) + in2(I) + in3(I)
	END DO	
END SUBROUTINE ADD_SUB1_F90

SUBROUTINE ADD_SUB2_F90 (in1, in2, in3, out)
	REAL, DIMENSION (0:) :: in1, in2, in3, out
	INTEGER :: I

	DO I = 0, 23
		out(I) = in1(I) * in2(I) - in3(I)
	END DO	
END SUBROUTINE ADD_SUB2_F90

SUBROUTINE ADD_SUB3_F90 (in1, in2, in3, out)
	REAL, DIMENSION (0:) :: in1, in2, in3, out
	REAL, DIMENSION (0:23) :: temp
	INTEGER :: I

	DO I = 0, 23
		temp(I) = in2(I) * in3(I) 
	END DO	
	DO I = 0, 23
		OUT(I) = ((in1(I) - 4) * in3(I) + 25) * temp(I) / in3(I) - in2(I)
	END DO	
END SUBROUTINE ADD_SUB3_F90


