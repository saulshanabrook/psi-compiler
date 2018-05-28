
/*  A Bison parser, made from _psi.y.omega with Bison version GNU Bison version 1.22
  */

#define YYBISON 1  /* Identify Bison output.  */

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
#define	OMEGAB	286
#define	OMEGAU	287

#line 1 "_psi.y.omega"

/* This is inserted in resulting .C file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"
#include "ops.h"
 
#include "code.e"
#include "part.e"
#include "dist.e"
#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
#include "moa_func.e"
#include "_psi.sem.h"

extern char expr_str[1024];
extern int line_num;
extern int vector_const2_num;
extern op_t *op;
FILE *cfile;

#line 28 "_psi.y.omega"
typedef union {
  int ival;
  double dval;
  char *cval;

  ident_t *ident;
  statement_t *statement;
  reduced_t *reduced;
  parser_t *parser;
  vect_t *loc;
  op_t *op;
  s_expr_t *s_expr;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		236
#define	YYFLAG		-32768
#define	YYNTBASE	50

#define YYTRANSLATE(x) ((unsigned)(x) <= 287 ? yytranslate[x] : 90)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    38,     2,     2,     2,    47,
    48,    32,    30,    46,    31,     2,    33,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    45,    42,
    44,    43,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    35,     2,    49,    41,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    39,     2,    40,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    34,    36,    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     2,     7,     8,    11,    15,    19,    23,    27,
    28,    29,    37,    38,    41,    44,    47,    52,    53,    62,
    63,    72,    77,    90,   101,   103,   106,   109,   112,   113,
   117,   121,   125,   126,   128,   129,   132,   133,   134,   139,
   140,   146,   147,   150,   152,   154,   156,   160,   165,   174,
   183,   193,   199,   201,   202,   205,   207,   209,   212,   215,
   216,   219,   221,   222,   223,   229,   233,   237,   241,   245,
   249,   253,   257,   261,   265,   269,   273,   276,   279,   282,
   285,   288,   291,   294,   298,   302,   306,   310,   313,   317,
   319,   322,   325,   328,   331,   333,   335,   337,   339,   341,
   343,   345,   347,   349,   351,   357,   365,   371
};

static const short yyrhs[] = {    -1,
     0,    51,    53,    52,    58,     0,     0,    38,    25,     0,
    38,    26,     5,     0,    38,    27,     4,     0,    38,    28,
     4,     0,    38,    29,     4,     0,     0,     0,    55,    71,
    39,    67,    56,    73,    40,     0,     0,    54,    57,     0,
    54,    57,     0,     8,     4,     0,     6,     4,    41,     5,
     0,     0,     6,     4,    41,     5,    60,    42,    79,    43,
     0,     0,     6,     4,    41,     5,    62,    42,    79,    43,
     0,     6,     4,    41,     5,     0,    16,     6,     4,    41,
     5,    42,    79,    43,    44,    42,    78,    43,     0,    16,
     6,     4,    41,     5,    42,    79,    43,    44,    63,     0,
     5,     0,    30,     5,     0,    31,     5,     0,     7,     4,
     0,     0,    61,    45,    65,     0,    64,    45,    65,     0,
    61,    45,    65,     0,     0,    66,     0,     0,    59,    69,
     0,     0,     0,    46,    70,    59,    69,     0,     0,     4,
    47,    72,    68,    48,     0,     0,    74,    73,     0,    75,
     0,    76,     0,    77,     0,    39,    73,    40,     0,     4,
    44,    83,    45,     0,    42,    78,    43,    14,     4,    44,
    83,    45,     0,    42,    78,    43,    10,     4,    44,    83,
    45,     0,     3,    47,    83,    22,    83,    42,    83,    48,
    74,     0,     4,    47,    83,    48,    45,     0,    79,     0,
     0,    80,    82,     0,     5,     0,     4,     0,    30,     5,
     0,    31,     5,     0,     0,    81,    82,     0,     4,     0,
     0,     0,    47,    84,    83,    85,    48,     0,    42,    78,
    43,     0,    83,    30,    83,     0,    83,    31,    83,     0,
    83,    32,    83,     0,    83,    33,    83,     0,    83,    10,
    83,     0,    83,    11,    83,     0,    83,    12,    83,     0,
    83,    13,    83,     0,    83,    14,    83,     0,    83,    15,
    83,     0,    30,    83,     0,    31,    83,     0,    17,    83,
     0,    18,    83,     0,    19,    83,     0,    20,    83,     0,
    21,    83,     0,    30,    23,    83,     0,    31,    23,    83,
     0,    32,    23,    83,     0,    33,    23,    83,     0,    88,
    83,     0,    83,    89,    83,     0,    21,     0,    30,    23,
     0,    31,    23,     0,    32,    23,     0,    33,    23,     0,
    30,     0,    31,     0,    33,     0,    32,     0,    10,     0,
    11,     0,    12,     0,    13,     0,    14,     0,    15,     0,
    86,    24,    42,    78,    43,     0,    35,    88,    49,    24,
    42,    78,    43,     0,    87,    24,    42,    79,    43,     0,
    35,    89,    49,    24,    42,    79,    43,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   105,   108,   110,   113,   114,   115,   116,   117,   118,   121,
   124,   128,   132,   133,   136,   140,   142,   144,   145,   147,
   149,   150,   155,   159,   165,   167,   168,   170,   174,   175,
   177,   180,   185,   186,   188,   189,   192,   193,   193,   196,
   199,   202,   204,   208,   210,   211,   212,   215,   218,   220,
   224,   229,   235,   240,   243,   246,   248,   249,   250,   253,
   254,   257,   261,   264,   266,   267,   270,   272,   274,   276,
   278,   280,   282,   284,   286,   288,   291,   293,   295,   297,
   299,   301,   303,   305,   307,   309,   311,   313,   315,   319,
   321,   322,   323,   324,   327,   329,   330,   331,   332,   333,
   334,   335,   336,   337,   340,   343,   347,   350
};

static const char * const yytname[] = {   "$","error","$illegal.","FOR1","NAME1",
"NUMBER1","ARRAY1","GLOBAL1","INT1","FLOAT1","PSI1","TAKE1","DROP1","CAT1","PDROP1",
"PTAKE1","CONST1","IOTA1","DIM1","SHP1","TAU1","RAV1","LTE1","RED1","OMEGA1",
"TRACE1","PROCS1","ARCH1","HOSTNAME1","PICL1","'+'","'-'","'*'","'/'","UNEG",
"'['","OMEGAB","OMEGAU","'$'","'{'","'}'","'^'","'<'","'>'","'='","';'","','",
"'('","')'","']'","executable_program","@1","@2","directives_opt","procedure_mand",
"@3","@4","procedure_opt","procedure_list","arg_dec","@5","var_dec","@6","anynumber",
"global_dec","var_dec_statement_cont","var_dec_statement_mand","var_dec_statement_opt",
"arg_list_opt","arg_list_cont","@7","declaration","@8","statement_base_opt",
"statement_base_mand","assignment","for_statement","procedure_call","vector_const_ident_base",
"vector_const2_base","@9","vector_const2_mand","vector_const2_opt","expression",
"@10","@11","unary_op","binary_op","omega_unop","omega_binop",""
};
#endif

static const short yyr1[] = {     0,
    51,    52,    50,    53,    53,    53,    53,    53,    53,    55,
    56,    54,    57,    57,    58,    59,    59,    60,    59,    62,
    61,    61,    61,    61,    63,    63,    63,    64,    65,    65,
    65,    66,    67,    67,    68,    68,    69,    70,    69,    72,
    71,    73,    73,    74,    74,    74,    74,    75,    75,    75,
    76,    77,    78,    80,    79,    81,    81,    81,    81,    82,
    82,    83,    84,    85,    83,    83,    83,    83,    83,    83,
    83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
    83,    83,    83,    83,    83,    83,    83,    83,    83,    86,
    86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
    87,    87,    87,    87,    88,    88,    89,    89
};

static const short yyr2[] = {     0,
     0,     0,     4,     0,     2,     3,     3,     3,     3,     0,
     0,     7,     0,     2,     2,     2,     4,     0,     8,     0,
     8,     4,    12,    10,     1,     2,     2,     2,     0,     3,
     3,     3,     0,     1,     0,     2,     0,     0,     4,     0,
     5,     0,     2,     1,     1,     1,     3,     4,     8,     8,
     9,     5,     1,     0,     2,     1,     1,     2,     2,     0,
     2,     1,     0,     0,     5,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
     2,     2,     2,     3,     3,     3,     3,     2,     3,     1,
     2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     5,     7,     5,     7
};

static const short yydefact[] = {     1,
     4,     0,     2,     5,     0,     0,     0,     0,    10,     6,
     7,     8,     9,    10,     0,     3,    10,    15,     0,     0,
    14,    40,    33,    35,     0,     0,     0,    34,    11,     0,
     0,    37,     0,     0,     0,    29,    42,     0,    16,    38,
    36,    41,     0,     0,     0,     0,     0,    32,     0,     0,
    42,    54,     0,    42,    44,    45,    46,     0,     0,    20,
     0,    28,    29,    29,     0,     0,     0,     0,     0,    53,
    60,    12,    43,    17,    37,     0,     0,    30,    31,    62,
     0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
    54,    63,     0,     0,     0,     0,     0,    47,     0,    57,
    56,     0,     0,    60,    55,     0,    39,    54,    54,    79,
    80,    81,    82,    83,    91,    77,    92,    78,    93,    94,
    90,     0,     0,     0,     0,     0,     0,     0,    99,   100,
   101,   102,   103,   104,     0,    95,    96,    98,    97,     0,
     0,     0,     0,    88,    48,     0,     0,     0,    58,    59,
    61,    54,     0,     0,    84,    85,    86,    87,    91,    92,
    93,    94,     0,    66,    64,    71,    72,    73,    74,    75,
    76,     0,    67,    68,    69,    70,    99,   100,   101,   102,
   103,   104,    95,    96,    98,    97,     0,     0,    89,    54,
    52,     0,     0,     0,    21,     0,     0,     0,     0,     0,
    54,     0,     0,     0,    19,     0,    54,    65,     0,     0,
     0,   105,     0,     0,    25,     0,     0,    54,    24,     0,
     0,    54,   107,    50,    49,    26,    27,     0,   106,    51,
     0,    23,   108,     0,     0,     0
};

static const short yydefgoto[] = {   234,
     1,     9,     3,    17,    15,    37,    18,    16,    32,   106,
    46,    76,   219,    47,    48,    28,    29,    33,    41,    59,
    20,    24,    53,    54,    55,    56,    57,    69,    70,    71,
   104,   105,    93,   128,   198,    94,   141,    95,   142
};

static const short yypact[] = {-32768,
   -12,    30,-32768,-32768,    27,    33,    39,    42,-32768,-32768,
-32768,-32768,-32768,    48,    46,-32768,    48,-32768,    13,    36,
-32768,-32768,    22,     6,    57,    75,     7,-32768,-32768,    78,
    79,    38,    37,    45,    83,    24,     2,    47,-32768,-32768,
-32768,-32768,    84,    49,    94,    54,    55,-32768,    56,    -5,
     2,-32768,    62,     2,-32768,-32768,-32768,   103,     6,    65,
   106,-32768,    24,    24,   130,   130,   130,    72,    70,-32768,
     5,-32768,-32768,    73,    38,    77,    80,-32768,-32768,-32768,
   130,   130,   130,   130,   130,    74,   122,    91,    97,    -8,
-32768,-32768,   264,    99,   130,   180,   168,-32768,    -3,-32768,
-32768,   119,   120,     5,-32768,    85,-32768,-32768,-32768,    93,
    93,    93,    93,    93,   130,    93,   130,    93,   130,   130,
-32768,   107,   108,   109,   112,    87,   101,   130,   130,   130,
   130,   130,   130,   130,   130,   130,   130,   130,   130,   291,
   132,   130,   104,-32768,-32768,   113,   155,   162,-32768,-32768,
-32768,-32768,   124,   125,    93,    93,    93,    93,-32768,-32768,
-32768,-32768,   146,-32768,   297,    93,    93,    93,    93,    93,
    93,   258,    93,    93,    93,    93,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   126,   129,-32768,-32768,
-32768,   152,   153,   131,-32768,   158,   134,   160,   130,   149,
-32768,   171,   130,   130,-32768,     3,-32768,-32768,   174,   175,
   176,-32768,   216,   222,-32768,   213,   215,-32768,-32768,   178,
     2,-32768,-32768,-32768,-32768,-32768,-32768,   181,-32768,-32768,
   195,-32768,-32768,   223,   239,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,   231,-32768,-32768,   224,-32768,   183,-32768,
   220,-32768,-32768,-32768,    16,-32768,-32768,-32768,   169,-32768,
-32768,-32768,    23,    29,-32768,-32768,-32768,   -89,  -105,-32768,
-32768,   141,   -66,-32768,-32768,-32768,-32768,   166,   118
};


#define	YYLAST		332


static const short yytable[] = {    96,
    97,   127,   153,   154,    49,    50,   147,   215,   100,   101,
   148,    30,   121,    31,   110,   111,   112,   113,   114,   116,
   118,   122,   123,   124,   125,     2,    90,    25,   144,    25,
    45,    10,   216,   217,   102,   103,    11,    26,    66,    26,
    51,    67,    12,    52,   218,    13,   194,   -13,   155,    19,
   156,    36,   157,   158,     4,     5,     6,     7,     8,    22,
    34,   165,   166,   167,   168,   169,   170,   171,   172,   173,
   174,   175,   176,    68,    23,   189,    73,    80,    78,    79,
    35,    38,    39,    40,    42,    43,    44,    58,    60,    61,
    81,    82,    83,    84,    85,   211,   115,    62,    63,    64,
   202,    72,    65,    86,    87,    88,    89,    74,    90,   -22,
    77,    98,    99,   119,   -18,    91,   231,   220,   108,   120,
    92,   109,   143,   149,   150,    80,   152,   140,   228,   159,
   160,   161,   209,    80,   162,   163,   213,   214,    81,    82,
    83,    84,    85,   164,   117,   190,    81,    82,    83,    84,
    85,    86,    87,    88,    89,   188,    90,   191,   192,    86,
    87,    88,    89,    91,    90,   193,   195,   196,    92,   197,
   201,    91,   210,   205,   200,   207,    92,   129,   130,   131,
   132,   133,   134,   129,   130,   131,   132,   133,   134,   129,
   130,   131,   132,   133,   134,   203,   204,   136,   137,   138,
   139,   206,   140,   136,   137,   138,   139,   208,   140,   136,
   137,   138,   139,   212,   140,   146,   222,   226,   223,   227,
   229,   221,   235,   232,   145,   129,   130,   131,   132,   133,
   134,   129,   130,   131,   132,   133,   134,   233,   236,    14,
    21,    75,    27,   107,   151,   136,   137,   138,   139,   230,
   140,   136,   137,   138,   139,   126,   140,   187,     0,     0,
   224,     0,     0,     0,     0,     0,   225,   129,   130,   131,
   132,   133,   134,   129,   130,   131,   132,   133,   134,     0,
     0,     0,     0,     0,     0,   135,     0,   136,   137,   138,
   139,     0,   140,   136,   137,   138,   139,     0,   140,   199,
   177,   178,   179,   180,   181,   182,   129,   130,   131,   132,
   133,   134,     0,     0,     0,     0,     0,     0,     0,     0,
   183,   184,   185,   186,     0,   140,   136,   137,   138,   139,
     0,   140
};

static const short yycheck[] = {    66,
    67,    91,   108,   109,     3,     4,    10,     5,     4,     5,
    14,     6,    21,     8,    81,    82,    83,    84,    85,    86,
    87,    30,    31,    32,    33,    38,    35,     6,    95,     6,
     7,     5,    30,    31,    30,    31,     4,    16,    44,    16,
    39,    47,     4,    42,    42,     4,   152,     0,   115,     4,
   117,    45,   119,   120,    25,    26,    27,    28,    29,    47,
     4,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,    51,    39,   142,    54,     4,    63,    64,
     6,     4,     4,    46,    48,    41,     4,    41,     5,    41,
    17,    18,    19,    20,    21,   201,    23,     4,    45,    45,
   190,    40,    47,    30,    31,    32,    33,     5,    35,    45,
     5,    40,    43,    23,    42,    42,   222,   207,    42,    23,
    47,    42,    24,     5,     5,     4,    42,    35,   218,    23,
    23,    23,   199,     4,    23,    49,   203,   204,    17,    18,
    19,    20,    21,    43,    23,    42,    17,    18,    19,    20,
    21,    30,    31,    32,    33,    24,    35,    45,     4,    30,
    31,    32,    33,    42,    35,     4,    43,    43,    47,    24,
    42,    42,    24,    43,    49,    42,    47,    10,    11,    12,
    13,    14,    15,    10,    11,    12,    13,    14,    15,    10,
    11,    12,    13,    14,    15,    44,    44,    30,    31,    32,
    33,    44,    35,    30,    31,    32,    33,    48,    35,    30,
    31,    32,    33,    43,    35,    48,    42,     5,    43,     5,
    43,    48,     0,    43,    45,    10,    11,    12,    13,    14,
    15,    10,    11,    12,    13,    14,    15,    43,     0,     9,
    17,    59,    23,    75,   104,    30,    31,    32,    33,   221,
    35,    30,    31,    32,    33,    90,    35,   140,    -1,    -1,
    45,    -1,    -1,    -1,    -1,    -1,    45,    10,    11,    12,
    13,    14,    15,    10,    11,    12,    13,    14,    15,    -1,
    -1,    -1,    -1,    -1,    -1,    22,    -1,    30,    31,    32,
    33,    -1,    35,    30,    31,    32,    33,    -1,    35,    42,
    10,    11,    12,    13,    14,    15,    10,    11,    12,    13,
    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    30,    31,    32,    33,    -1,    35,    30,    31,    32,    33,
    -1,    35
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/lib/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 184 "/usr/local/lib/bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 106 "_psi.y.omega"
{ executable_header(); ;
    break;}
case 2:
#line 108 "_psi.y.omega"
{ executable_post_declaration(); ;
    break;}
case 3:
#line 110 "_psi.y.omega"
{ executable_footer(); ;
    break;}
case 5:
#line 114 "_psi.y.omega"
{directive_trace(); ;
    break;}
case 6:
#line 115 "_psi.y.omega"
{ directive_procs(yyvsp[0].ival);;
    break;}
case 7:
#line 116 "_psi.y.omega"
{directive_arch(yyvsp[0].cval);;
    break;}
case 8:
#line 117 "_psi.y.omega"
{directive_hostname(yyvsp[0].cval);;
    break;}
case 9:
#line 118 "_psi.y.omega"
{directive_picl(yyvsp[0].cval);;
    break;}
case 10:
#line 122 "_psi.y.omega"
{procedure_header();;
    break;}
case 11:
#line 126 "_psi.y.omega"
{ procedure_post_declaration(); ;
    break;}
case 12:
#line 129 "_psi.y.omega"
{ procedure_footer(yyvsp[-1].statement); ;
    break;}
case 16:
#line 141 "_psi.y.omega"
{ arg_dec_int(yyvsp[0].cval); ;
    break;}
case 17:
#line 142 "_psi.y.omega"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].ival); 
	 yyval.ident = arg_dec_array_3(yyvsp[-2].cval, yyvsp[1].ident); ;
    break;}
case 18:
#line 144 "_psi.y.omega"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].ival); ;
    break;}
case 19:
#line 145 "_psi.y.omega"
{ yyval.ident = arg_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ival,yyvsp[-4].ival,yyvsp[-3].ident); ;
    break;}
case 20:
#line 148 "_psi.y.omega"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].ival); ;
    break;}
case 21:
#line 149 "_psi.y.omega"
{ yyval.ident = var_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ival,yyvsp[-4].ival,yyvsp[-3].ident); ;
    break;}
case 22:
#line 150 "_psi.y.omega"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].ival); 
	 yyval.ident = var_dec_array_3(yyvsp[-2].cval,yyvsp[1].ident); ;
    break;}
case 23:
#line 158 "_psi.y.omega"
{ yyval.ident=const_dec_array_3(yyvsp[-9].cval,const_dec_array_2(yyvsp[-5].ival,yyvsp[-7].ival,const_dec_array(yyvsp[-9].cval,yyvsp[-7].ival))); ;
    break;}
case 24:
#line 162 "_psi.y.omega"
{ yyval.ident=const_dec_array_4(yyvsp[-7].cval,const_dec_array_2(yyvsp[-3].ival,yyvsp[-5].ival,const_dec_array(yyvsp[-7].cval,yyvsp[-5].ival)),yyvsp[0].ival); ;
    break;}
case 25:
#line 166 "_psi.y.omega"
{ yyval.ival = yyvsp[0].ival ;
    break;}
case 26:
#line 167 "_psi.y.omega"
{ yyval.ival = yyvsp[0].ival ;
    break;}
case 27:
#line 168 "_psi.y.omega"
{ yyval.ival = 0 - yyvsp[0].ival ;
    break;}
case 28:
#line 171 "_psi.y.omega"
{ yyval.ident = global_dec(yyvsp[0].cval); ;
    break;}
case 29:
#line 174 "_psi.y.omega"
{ yyval.ident = NULL; ;
    break;}
case 33:
#line 185 "_psi.y.omega"
{ yyval.ident = NULL; ;
    break;}
case 35:
#line 188 "_psi.y.omega"
{ yyval.ident = NULL; ;
    break;}
case 37:
#line 192 "_psi.y.omega"
{ yyval.ident = NULL; ;
    break;}
case 38:
#line 193 "_psi.y.omega"
{dual_fprintf(","); ;
    break;}
case 39:
#line 193 "_psi.y.omega"
{ yyval.ident = yyvsp[-1].ident; ;
    break;}
case 40:
#line 197 "_psi.y.omega"
{ declaration_name(yyvsp[-1].cval);;
    break;}
case 41:
#line 199 "_psi.y.omega"
{  declaration_footer(); ;
    break;}
case 42:
#line 203 "_psi.y.omega"
{ yyval.statement=NULL;
    break;}
case 43:
#line 205 "_psi.y.omega"
{ yyval.statement=yyvsp[-1].statement; yyvsp[-1].statement->next=yyvsp[0].statement; collect_garbage(NULL,save_list,NULL); ;
    break;}
case 44:
#line 209 "_psi.y.omega"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 45:
#line 210 "_psi.y.omega"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 46:
#line 211 "_psi.y.omega"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 47:
#line 212 "_psi.y.omega"
{ yyval.statement=yyvsp[-1].statement ;
    break;}
case 48:
#line 217 "_psi.y.omega"
{ yyval.statement=assignment_normal(yyvsp[-3].cval,yyvsp[-1].parser);;
    break;}
case 49:
#line 219 "_psi.y.omega"
{ yyval.statement=assignment_pdrop(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 50:
#line 221 "_psi.y.omega"
{ yyval.statement=assignment_psi(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 51:
#line 226 "_psi.y.omega"
{ yyval.statement = for_statement(yyvsp[-6].parser,yyvsp[-4].parser,yyvsp[-2].parser,yyvsp[0].statement); ;
    break;}
case 52:
#line 232 "_psi.y.omega"
{ yyval.statement = do_procedure_call (yyvsp[-4].cval, yyvsp[-2].parser); ;
    break;}
case 53:
#line 237 "_psi.y.omega"
{ yyval.ident = vector_const2_ident(); ;
    break;}
case 54:
#line 241 "_psi.y.omega"
{ vector_const2_init(); ;
    break;}
case 55:
#line 243 "_psi.y.omega"
{yyval.ival=vector_const2_num; vector_const2_footer(); ;
    break;}
case 56:
#line 247 "_psi.y.omega"
{ yyval.ival = vector_const2_number(yyvsp[0].ival);;
    break;}
case 57:
#line 248 "_psi.y.omega"
{ yyval.ival = vector_const2_name(yyvsp[0].cval); ;
    break;}
case 58:
#line 249 "_psi.y.omega"
{ yyval.ival = vector_const2_number(yyvsp[0].ival); ;
    break;}
case 59:
#line 250 "_psi.y.omega"
{ yyval.ival = vector_const2_number(-yyvsp[0].ival); ;
    break;}
case 60:
#line 253 "_psi.y.omega"
{ yyval.ival = 0; ;
    break;}
case 61:
#line 254 "_psi.y.omega"
{ yyval.ival = yyvsp[-1].ival + yyvsp[0].ival; ;
    break;}
case 62:
#line 258 "_psi.y.omega"
{ yyval.parser=expression_name(yyvsp[0].cval); ;
    break;}
case 63:
#line 262 "_psi.y.omega"
{ sprintf (expr_str+strlen(expr_str),"%c",'('); ;
    break;}
case 64:
#line 264 "_psi.y.omega"
{ sprintf (expr_str+strlen(expr_str),"%c",')'); ;
    break;}
case 65:
#line 266 "_psi.y.omega"
{ yyval.parser = yyvsp[-2].parser; ;
    break;}
case 66:
#line 268 "_psi.y.omega"
{ yyval.parser=psi_access(yyvsp[-1].ident); ;
    break;}
case 67:
#line 271 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," + ",yyvsp[0].parser,psi_plus);;
    break;}
case 68:
#line 273 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," - ",yyvsp[0].parser,psi_minus);;
    break;}
case 69:
#line 275 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," * ",yyvsp[0].parser,psi_times);;
    break;}
case 70:
#line 277 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," / ",yyvsp[0].parser,psi_div);;
    break;}
case 71:
#line 279 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," psi ",yyvsp[0].parser,psi_psi);;
    break;}
case 72:
#line 281 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," take ",yyvsp[0].parser,psi_take);;
    break;}
case 73:
#line 283 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," drop ",yyvsp[0].parser,psi_drop);;
    break;}
case 74:
#line 285 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," cat ",yyvsp[0].parser,psi_cat);;
    break;}
case 75:
#line 287 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," pdrop ",yyvsp[0].parser,psi_pdrop);;
    break;}
case 76:
#line 289 "_psi.y.omega"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," ptake ",yyvsp[0].parser,psi_ptake);;
    break;}
case 77:
#line 292 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" + ", yyvsp[0].parser,psi_plus); ;
    break;}
case 78:
#line 294 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" - ", yyvsp[0].parser,psi_minus); ;
    break;}
case 79:
#line 296 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" iota ", yyvsp[0].parser,psi_iota); ;
    break;}
case 80:
#line 298 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" dim ", yyvsp[0].parser,psi_dim); ;
    break;}
case 81:
#line 300 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" shp ", yyvsp[0].parser,psi_shp); ;
    break;}
case 82:
#line 302 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" tau ", yyvsp[0].parser,psi_tau); ;
    break;}
case 83:
#line 304 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" rav ", yyvsp[0].parser,psi_rav); ;
    break;}
case 84:
#line 306 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" +red ", yyvsp[0].parser,psi_red_plus); ;
    break;}
case 85:
#line 308 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" -red ", yyvsp[0].parser,psi_red_minus); ;
    break;}
case 86:
#line 310 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" *red ", yyvsp[0].parser,psi_red_times); ;
    break;}
case 87:
#line 312 "_psi.y.omega"
{ yyval.parser = expression_unary_operator(" /red ", yyvsp[0].parser,psi_red_div); ;
    break;}
case 88:
#line 314 "_psi.y.omega"
{ yyval.parser = omega_unary (yyvsp[-1].op, yyvsp[0].parser); ;
    break;}
case 89:
#line 316 "_psi.y.omega"
{ yyval.parser = omega_binary (yyvsp[-2].parser, yyvsp[-1].op, yyvsp[0].parser); ;
    break;}
case 90:
#line 320 "_psi.y.omega"
{ yyval.op = set_opt (psi_rav, " rav "); ;
    break;}
case 91:
#line 321 "_psi.y.omega"
{ yyval.op = set_opt (psi_red_plus, " + red "); ;
    break;}
case 92:
#line 322 "_psi.y.omega"
{ yyval.op = set_opt (psi_red_minus, " - red "); ;
    break;}
case 93:
#line 323 "_psi.y.omega"
{ yyval.op = set_opt (psi_red_times, " * red "); ;
    break;}
case 94:
#line 324 "_psi.y.omega"
{ yyval.op = set_opt (psi_red_divide, " / red "); ;
    break;}
case 95:
#line 328 "_psi.y.omega"
{ yyval.op = set_opt (psi_plus, " + "); ;
    break;}
case 96:
#line 329 "_psi.y.omega"
{ yyval.op = set_opt (psi_minus, " - "); ;
    break;}
case 97:
#line 330 "_psi.y.omega"
{ yyval.op = set_opt (psi_divide, " / "); ;
    break;}
case 98:
#line 331 "_psi.y.omega"
{ yyval.op = set_opt (psi_times, " * "); ;
    break;}
case 99:
#line 332 "_psi.y.omega"
{ yyval.op = set_opt (psi_psi, " psi "); ;
    break;}
case 100:
#line 333 "_psi.y.omega"
{ yyval.op = set_opt (psi_take, " take "); ;
    break;}
case 101:
#line 334 "_psi.y.omega"
{ yyval.op = set_opt (psi_drop, " drop "); ;
    break;}
case 102:
#line 335 "_psi.y.omega"
{ yyval.op = set_opt (psi_cat, " cat "); ;
    break;}
case 103:
#line 336 "_psi.y.omega"
{ yyval.op = set_opt (psi_pdrop, " pdrop "); ;
    break;}
case 104:
#line 337 "_psi.y.omega"
{ yyval.op = set_opt (psi_ptake, " ptake "); ;
    break;}
case 105:
#line 342 "_psi.y.omega"
{ yyval.op = omega_no_bracket (yyvsp[-4].op, yyvsp[-1].ident); ;
    break;}
case 106:
#line 344 "_psi.y.omega"
{ yyval.op = omega_yes_bracket (yyvsp[-5].op, yyvsp[-1].ident); ;
    break;}
case 107:
#line 349 "_psi.y.omega"
{ yyval.op = omega_no_bracket (yyvsp[-4].op, yyvsp[-1].ival); ;
    break;}
case 108:
#line 351 "_psi.y.omega"
{ yyval.op = omega_yes_bracket (yyvsp[-5].op, yyvsp[-1].ival); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 465 "/usr/local/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 354 "_psi.y.omega"


yyerror (char *s)
{ 
	printf ("Error line %d:  %s\n", line_num, s);
	return (0);
}
