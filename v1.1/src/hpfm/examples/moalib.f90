! moalib.c - This module contains some utility functions used at run time
!     by the F90 procedures generated by the PSI Compiler

MODULE MOALIB

CONTAINS

FUNCTION min(a, b)
  INTEGER a,b

  IF (a<b) THEN
    min= a
  ELSE
    min= b
  END IF
END FUNCTION


FUNCTION max(a, b)
  INTEGER a,b

  IF (a<b) THEN
    max= a
  ELSE
    max= b
  END IF
END FUNCTION


END MODULE