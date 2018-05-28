PROGRAM opsmain 
	REAL, DIMENSION (0:23) :: in1 = (/ 0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11 /)
	REAL, DIMENSION (0:23) :: in2 = (/ 11,10,9,8,7,6,5,4,3,2,1,0,11,10,9,8,7,6,5,4,3,2,1,0 /)
	REAL, DIMENSION (0:23) :: in3 = (/ 5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,1,1,1,1 /)
	REAL, DIMENSION (0:23) :: out
	INTERFACE
		SUBROUTINE do_ops (mdat, cdat, in1, in2, in3, out)
			CHARACTER(LEN=*) :: mdat, cdat
			REAL, DIMENSION (0:) :: in1, in2, in3, out
		END SUBROUTINE do_ops
	END INTERFACE

	CALL do_ops ("opsm.dat", "opsf.dat", in1, in2, in3, out)
END PROGRAM opsmain

SUBROUTINE do_ops (mdat, cdat, in1, in2, in3, out)
	CHARACTER(LEN=*) :: mdat, cdat
	REAL, DIMENSION (0:) :: in1, in2, in3, out
	INTEGER :: i, j, k

	INTERFACE 
		SUBROUTINE ADD_SUB1(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB1
	END INTERFACE

	INTERFACE 
		SUBROUTINE ADD_SUB2(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB2
	END INTERFACE

	INTERFACE 
		SUBROUTINE ADD_SUB3(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB3
	END INTERFACE

	INTERFACE 
		SUBROUTINE ADD_SUB1_F90(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB1_F90
	END INTERFACE

	INTERFACE 
		SUBROUTINE ADD_SUB2_F90(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB2_F90
	END INTERFACE

	INTERFACE 
		SUBROUTINE ADD_SUB3_F90(f90_in1, f90_in2, f90_in3, f90_out)
			REAL, DIMENSION (0:) :: f90_in1
			REAL, DIMENSION (0:) :: f90_in2
			REAL, DIMENSION (0:) :: f90_in3
			REAL, DIMENSION (0:) :: f90_out
		END SUBROUTINE ADD_SUB3_F90
	END INTERFACE


	OPEN (1, FILE=mdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")

	PRINT *, "HERE"
	CALL ADD_SUB1 (in1, in2, in3, out)
	PRINT *, "HERE"
	WRITE (1,"(6(4F8.3, /))") out
	WRITE (1,"(A)") ""

	PRINT *, "HERE"
	CALL ADD_SUB2 (in1, in2, in3, out)
	PRINT *, "HERE"
	WRITE (1,"(6(4F8.3, /))") out
	WRITE (1,"(A)") ""

	PRINT *, "HERE"
	CALL ADD_SUB3 (in1, in2, in3, out)
	PRINT *, "HERE"
	DO i=0, 1
		DO j=0, 2
			WRITE (1,"(4F8.3)") out(i*12+j*4:i*12+j*4+3)
		END DO
	END DO

	CLOSE (1)

	OPEN (1, FILE=cdat, STATUS="REPLACE", ACCESS="SEQUENTIAL", ACTION="WRITE")
!	if ((fout = fopen (mdat, "w"))==NULL)
!	{
!		printf("Cannot opsn %s.\n",mdat)
!		exit(0)
!	}

	PRINT *, "HERE"
	CALL ADD_SUB1_F90 (in1, in2, in3, out)
	PRINT *, "HERE"
	DO i=0, 1
		DO j=0, 2
			WRITE (1,"(4F8.3)") out(i*12+j*4:i*12+j*4+3)
		END DO
	END DO
	WRITE (1,"(A)") ""

	PRINT *, "HERE"
	CALL ADD_SUB2_F90 (in1, in2, in3, out)
	PRINT *, "HERE"
	DO i=0, 1
		DO j=0, 2
			WRITE (1,"(4F8.3)") out(i*12+j*4:i*12+j*4+3)
		END DO
	END DO
	WRITE (1,"(A)") ""

	PRINT *, "HERE"
	CALL ADD_SUB3_F90 (in1, in2, in3, out)
	PRINT *, "HERE"
	DO i=0, 1
		DO j=0, 2
			WRITE (1,"(4F8.3)") out(i*12+j*4:i*12+j*4+3)
		END DO
	END DO

	CLOSE (1)

END SUBROUTINE do_ops

