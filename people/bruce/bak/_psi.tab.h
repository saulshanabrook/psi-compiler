typedef union {
  unsigned int wval;
  signed int swval;
  double fval;
  char *cval;

  ident_t *ident;
  statement_t *statement;
  reduced_t *reduced;
  parser_t *parser;
  vect_t *loc;
  op_t *op;
  s_expr_t *s_expr;
} YYSTYPE;
#define	FOR1	258
#define	NAME1	259
#define	NUMBER1	260
#define	ARRAY1	261
#define	GLOBAL1	262
#define	INT1	263
#define	FLOAT1	264
#define	PSI1	265
#define	TAKE1	266
#define	DROP1	267
#define	CAT1	268
#define	PDROP1	269
#define	PTAKE1	270
#define	CONST1	271
#define	IOTA1	272
#define	DIM1	273
#define	SHP1	274
#define	TAU1	275
#define	RAV1	276
#define	LTE1	277
#define	RED1	278
#define	OMEGA1	279
#define	TRACE1	280
#define	PROCS1	281
#define	ARCH1	282
#define	HOSTNAME1	283
#define	PICL1	284
#define	UNEG	285


extern YYSTYPE yylval;
