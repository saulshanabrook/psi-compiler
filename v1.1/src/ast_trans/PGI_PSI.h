/* 
   PGI_PSI.h -- this file contains prototypes for those functions that the
   PGI compiler will use as drivers for the PSI compiler.  PGI will interpret
   the opcode for each of its ASTs and call the appropriate module.
*/
void PGI_PSI_INIT(void);
void PGI_PSI_PLUS(void);
void PGI_PSI_MINUS(void);
void PGI_PSI_TIMES(void);
void PGI_PSI_DIVIDE(void);
void PGI_PSI_NOP(void);
void PGI_PSI_ABS(void);
void PGI_PSI_CONS(char *name, float psi_val);
void PGI_PSI_SCALAR(char *name);
void PGI_PSI_ARRAY(char *name, int dim, int []);


void PGI_PSI_CONCAT(int);
void PGI_PSI_CSHIFT(int, int);
void PGI_PSI_DOTPROD(void);
void PGI_PSI_INDEX(int, int [], int [], int []);
