! network.f90 - This module contains some utility functions used at run time
!     by the F90 procedures generated by the PSI Compiler

MODULE NETWORK

CONTAINS

FUNCTION MY_PROC ()
  MY_PROC = SCOTTT_MY_PROC ()
END FUNCTION

SUBROUTINE SEND (PTR, SIZE, PROC)
  REAL, DIMENSION (:) :: PTR 
  INTEGER :: SIZE, PROC

  call SCOTTT_SEND (PTR, SIZE, PROC);
END SUBROUTINE

SUBROUTINE RECV (PTR, SIZE, PROC)
  REAL, DIMENSION (:) :: PTR 
  INTEGER :: SIZE, PROC

  call SCOTTT_RECV (PTR, SIZE, PROC)
END SUBROUTINE

SUBROUTINE NODE_INIT ()
  call SCOTTT_NODE_INIT ()
END SUBROUTINE 

SUBROUTINE NODE_CLEANUP ()
  call SCOTTT_NODE_CLEANUP ()
END SUBROUTINE

SUBROUTINE WAIT ()
  call SCOTTT_WAIT ()
END SUBROUTINE

END MODULE
