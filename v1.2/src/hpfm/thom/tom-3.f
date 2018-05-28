      INTEGER A(10,10)
      INTEGER A1(1,1)
      INTEGER I,J
 
      DO 20 I=0,1
        DO 30 J=0,1
          A1 (I,J) = A(I,J) * B(I,J)
30      CONTINUE
20    CONTINUE
      END
