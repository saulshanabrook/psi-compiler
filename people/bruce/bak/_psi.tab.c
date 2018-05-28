
/*  A Bison parser, made from _psi.y with Bison version GNU Bison version 1.22
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

#line 1 "_psi.y"

/* This is inserted in resulting .C file */
#include <stdio.h>
#include <stdlib.h>
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
extern int line_num;
extern op_t *op;
FILE *cfile;

#line 23 "_psi.y"
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



#define	YYFINAL		187
#define	YYFLAG		-32768
#define	YYNTBASE	46

#define YYTRANSLATE(x) ((unsigned)(x) <= 285 ? yytranslate[x] : 80)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    35,     2,     2,     2,    44,
    45,    32,    30,    43,    31,     2,    33,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    42,    39,
    41,    40,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    36,     2,    37,     2,     2,     2,     2,     2,
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
    26,    27,    28,    29,    34
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     2,     7,     8,    11,    15,    19,    23,    27,
    28,    29,    37,    38,    41,    44,    47,    52,    53,    62,
    63,    72,    77,    90,   101,   103,   106,   109,   112,   113,
   117,   121,   125,   126,   128,   129,   132,   133,   134,   139,
   140,   146,   147,   150,   152,   154,   156,   160,   165,   174,
   183,   193,   199,   201,   202,   205,   207,   209,   212,   215,
   216,   219,   221,   225,   229,   233,   237,   241,   245,   249,
   253,   257,   261,   265,   269,   272,   275,   278,   281,   284,
   287,   290,   294,   298,   302
};

static const short yyrhs[] = {    -1,
     0,    47,    49,    48,    54,     0,     0,    35,    25,     0,
    35,    26,     5,     0,    35,    27,     4,     0,    35,    28,
     4,     0,    35,    29,     4,     0,     0,     0,    51,    67,
    36,    63,    52,    69,    37,     0,     0,    50,    53,     0,
    50,    53,     0,     8,     4,     0,     6,     4,    38,     5,
     0,     0,     6,     4,    38,     5,    56,    39,    74,    40,
     0,     0,     6,     4,    38,     5,    58,    39,    74,    40,
     0,     6,     4,    38,     5,     0,    16,     6,     4,    38,
     5,    39,    74,    40,    41,    39,    74,    40,     0,    16,
     6,     4,    38,     5,    39,    74,    40,    41,    59,     0,
     5,     0,    30,     5,     0,    31,     5,     0,     7,     4,
     0,     0,    57,    42,    61,     0,    60,    42,    61,     0,
    57,    42,    61,     0,     0,    62,     0,     0,    55,    65,
     0,     0,     0,    43,    66,    55,    65,     0,     0,     4,
    44,    68,    64,    45,     0,     0,    70,    69,     0,    71,
     0,    72,     0,    73,     0,    36,    69,    37,     0,     4,
    41,    79,    42,     0,    39,    74,    40,    14,     4,    41,
    79,    42,     0,    39,    74,    40,    10,     4,    41,    79,
    42,     0,     3,    44,    79,    22,    79,    39,    79,    45,
    70,     0,     4,    44,    79,    45,    42,     0,    75,     0,
     0,    76,    78,     0,     5,     0,     4,     0,    30,     5,
     0,    31,     5,     0,     0,    77,    78,     0,     4,     0,
    44,    79,    45,     0,    39,    74,    40,     0,    79,    30,
    79,     0,    79,    31,    79,     0,    79,    32,    79,     0,
    79,    33,    79,     0,    79,    10,    79,     0,    79,    11,
    79,     0,    79,    12,    79,     0,    79,    13,    79,     0,
    79,    14,    79,     0,    79,    15,    79,     0,    30,    79,
     0,    31,    79,     0,    17,    79,     0,    18,    79,     0,
    19,    79,     0,    20,    79,     0,    21,    79,     0,    30,
    23,    79,     0,    31,    23,    79,     0,    32,    23,    79,
     0,    33,    23,    79,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    94,    97,    99,   102,   103,   104,   105,   106,   107,   110,
   113,   117,   121,   122,   125,   129,   131,   133,   134,   136,
   138,   139,   144,   148,   154,   156,   157,   159,   163,   164,
   166,   169,   174,   175,   177,   178,   181,   182,   182,   185,
   188,   191,   193,   197,   199,   200,   201,   204,   207,   209,
   213,   218,   224,   229,   232,   235,   237,   238,   239,   242,
   243,   246,   250,   252,   255,   257,   259,   261,   263,   265,
   267,   269,   271,   273,   276,   278,   280,   282,   284,   286,
   288,   290,   292,   294,   296
};

static const char * const yytname[] = {   "$","error","$illegal.","FOR1","NAME1",
"NUMBER1","ARRAY1","GLOBAL1","INT1","FLOAT1","PSI1","TAKE1","DROP1","CAT1","PDROP1",
"PTAKE1","CONST1","IOTA1","DIM1","SHP1","TAU1","RAV1","LTE1","RED1","OMEGA1",
"TRACE1","PROCS1","ARCH1","HOSTNAME1","PICL1","'+'","'-'","'*'","'/'","UNEG",
"'$'","'{'","'}'","'^'","'<'","'>'","'='","';'","','","'('","')'","executable_program",
"@1","@2","directives_opt","procedure_mand","@3","@4","procedure_opt","procedure_list",
"arg_dec","@5","var_dec","@6","anynumber","global_dec","var_dec_statement_cont",
"var_dec_statement_mand","var_dec_statement_opt","arg_list_opt","arg_list_cont",
"@7","declaration","@8","statement_base_opt","statement_base_mand","assignment",
"for_statement","procedure_call","vector_const_ident_base","vector_const2_base",
"@9","vector_const2_mand","vector_const2_opt","expression",""
};
#endif

static const short yyr1[] = {     0,
    47,    48,    46,    49,    49,    49,    49,    49,    49,    51,
    52,    50,    53,    53,    54,    55,    55,    56,    55,    58,
    57,    57,    57,    57,    59,    59,    59,    60,    61,    61,
    61,    62,    63,    63,    64,    64,    65,    66,    65,    68,
    67,    69,    69,    70,    70,    70,    70,    71,    71,    71,
    72,    73,    74,    76,    75,    77,    77,    77,    77,    78,
    78,    79,    79,    79,    79,    79,    79,    79,    79,    79,
    79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
    79,    79,    79,    79,    79
};

static const short yyr2[] = {     0,
     0,     0,     4,     0,     2,     3,     3,     3,     3,     0,
     0,     7,     0,     2,     2,     2,     4,     0,     8,     0,
     8,     4,    12,    10,     1,     2,     2,     2,     0,     3,
     3,     3,     0,     1,     0,     2,     0,     0,     4,     0,
     5,     0,     2,     1,     1,     1,     3,     4,     8,     8,
     9,     5,     1,     0,     2,     1,     1,     2,     2,     0,
     2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
     2,     3,     3,     3,     3
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
     0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
     0,     0,     0,     0,    47,     0,    57,    56,     0,     0,
    60,    55,     0,    39,    54,    54,    77,    78,    79,    80,
    81,     0,    75,     0,    76,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    48,     0,     0,     0,    58,    59,    61,    54,     0,     0,
    82,    83,    84,    85,    64,    63,    69,    70,    71,    72,
    73,    74,     0,    65,    66,    67,    68,    52,     0,     0,
     0,    21,     0,     0,     0,     0,    19,     0,     0,     0,
     0,    25,     0,     0,    54,    24,     0,    50,    49,    26,
    27,     0,    51,    23,     0,     0,     0
};

static const short yydefgoto[] = {   185,
     1,     9,     3,    17,    15,    37,    18,    16,    32,   103,
    46,    76,   176,    47,    48,    28,    29,    33,    41,    59,
    20,    24,    53,    54,    55,    56,    57,    69,    70,    71,
   101,   102,    92
};

static const short yypact[] = {-32768,
   -23,    68,-32768,-32768,    27,    41,    43,    49,-32768,-32768,
-32768,-32768,-32768,    72,    69,-32768,    72,-32768,    32,    46,
-32768,-32768,    18,    34,    73,    82,    59,-32768,-32768,    86,
    87,    66,    67,    75,   110,     7,     0,    83,-32768,-32768,
-32768,-32768,    81,    84,   116,    88,    89,-32768,    79,   -39,
     0,-32768,    90,     0,-32768,-32768,-32768,   120,    34,    95,
   121,-32768,     7,     7,   115,   115,   115,    91,    98,-32768,
    80,-32768,-32768,   100,    66,   101,   102,-32768,-32768,-32768,
   115,   115,   115,   115,   115,    48,    85,   119,   126,-32768,
   115,   243,   192,    -4,-32768,    21,-32768,-32768,   138,   139,
    80,-32768,   111,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   115,-32768,   115,-32768,   115,   115,   112,   150,   115,
   115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
-32768,   109,   149,   151,-32768,-32768,-32768,-32768,   117,   118,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   231,-32768,-32768,-32768,-32768,-32768,   131,   132,
   134,-32768,   135,   115,   115,   115,-32768,    44,   156,   198,
   205,-32768,   170,   172,-32768,-32768,     0,-32768,-32768,-32768,
-32768,   144,-32768,-32768,   178,   179,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,   147,-32768,-32768,   168,-32768,   133,-32768,
   167,-32768,-32768,-32768,   -20,-32768,-32768,-32768,   122,-32768,
-32768,-32768,   -21,    14,-32768,-32768,-32768,   -68,-32768,-32768,
-32768,    92,   -66
};


#define	YYLAST		276


static const short yytable[] = {    93,
    94,    66,    49,    50,    67,   120,   121,   122,   123,   124,
   125,     2,    25,    45,   107,   108,   109,   110,   111,   113,
   115,   118,    26,    25,   119,   127,   128,   129,   130,    68,
   133,    10,    73,    26,   134,    51,   139,   140,    52,    30,
   132,    31,    78,    79,    11,   141,    12,   142,   172,   143,
   144,    80,    13,   147,   148,   149,   150,   151,   152,   153,
   154,   155,   156,   157,    81,    82,    83,    84,    85,   161,
   112,   -13,    19,   173,   174,    22,    34,    86,    87,    88,
    89,    23,   175,    97,    98,    60,    90,    35,    80,    38,
    39,    91,     4,     5,     6,     7,     8,   169,   170,   171,
    36,    81,    82,    83,    84,    85,   182,   114,    40,    99,
   100,    42,    43,    44,    86,    87,    88,    89,    80,    62,
    58,    61,    65,    90,    74,    77,    72,    95,    91,    63,
    64,    81,    82,    83,    84,    85,   -22,    96,   -18,   105,
   106,   116,   135,   136,    86,    87,    88,    89,   117,   138,
   158,   145,   159,    90,   160,    14,   162,   163,    91,   120,
   121,   122,   123,   124,   125,   120,   121,   122,   123,   124,
   125,   165,   166,   167,   180,   168,   181,   186,   187,   127,
   128,   129,   130,   184,    21,   127,   128,   129,   130,    27,
   183,    75,   137,     0,   146,     0,   104,     0,     0,     0,
   177,   120,   121,   122,   123,   124,   125,   120,   121,   122,
   123,   124,   125,     0,   120,   121,   122,   123,   124,   125,
     0,   127,   128,   129,   130,     0,     0,   127,   128,   129,
   130,     0,     0,   131,   127,   128,   129,   130,     0,   178,
   120,   121,   122,   123,   124,   125,   179,     0,     0,     0,
     0,     0,   120,   121,   122,   123,   124,   125,     0,     0,
   127,   128,   129,   130,   126,     0,     0,     0,     0,   164,
     0,     0,   127,   128,   129,   130
};

static const short yycheck[] = {    66,
    67,    41,     3,     4,    44,    10,    11,    12,    13,    14,
    15,    35,     6,     7,    81,    82,    83,    84,    85,    86,
    87,    90,    16,     6,    91,    30,    31,    32,    33,    51,
    10,     5,    54,    16,    14,    36,   105,   106,    39,     6,
    45,     8,    63,    64,     4,   112,     4,   114,     5,   116,
   117,     4,     4,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,    17,    18,    19,    20,    21,   138,
    23,     0,     4,    30,    31,    44,     4,    30,    31,    32,
    33,    36,    39,     4,     5,     5,    39,     6,     4,     4,
     4,    44,    25,    26,    27,    28,    29,   164,   165,   166,
    42,    17,    18,    19,    20,    21,   175,    23,    43,    30,
    31,    45,    38,     4,    30,    31,    32,    33,     4,     4,
    38,    38,    44,    39,     5,     5,    37,    37,    44,    42,
    42,    17,    18,    19,    20,    21,    42,    40,    39,    39,
    39,    23,     5,     5,    30,    31,    32,    33,    23,    39,
    42,    40,     4,    39,     4,     9,    40,    40,    44,    10,
    11,    12,    13,    14,    15,    10,    11,    12,    13,    14,
    15,    41,    41,    40,     5,    41,     5,     0,     0,    30,
    31,    32,    33,    40,    17,    30,    31,    32,    33,    23,
   177,    59,   101,    -1,    45,    -1,    75,    -1,    -1,    -1,
    45,    10,    11,    12,    13,    14,    15,    10,    11,    12,
    13,    14,    15,    -1,    10,    11,    12,    13,    14,    15,
    -1,    30,    31,    32,    33,    -1,    -1,    30,    31,    32,
    33,    -1,    -1,    42,    30,    31,    32,    33,    -1,    42,
    10,    11,    12,    13,    14,    15,    42,    -1,    -1,    -1,
    -1,    -1,    10,    11,    12,    13,    14,    15,    -1,    -1,
    30,    31,    32,    33,    22,    -1,    -1,    -1,    -1,    39,
    -1,    -1,    30,    31,    32,    33
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
#line 95 "_psi.y"
{ executable_header(); ;
    break;}
case 2:
#line 97 "_psi.y"
{ executable_post_declaration(); ;
    break;}
case 3:
#line 99 "_psi.y"
{ executable_footer(); ;
    break;}
case 5:
#line 103 "_psi.y"
{directive_trace(); ;
    break;}
case 6:
#line 104 "_psi.y"
{ directive_procs(yyvsp[0].fval);;
    break;}
case 7:
#line 105 "_psi.y"
{directive_arch(yyvsp[0].cval);;
    break;}
case 8:
#line 106 "_psi.y"
{directive_hostname(yyvsp[0].cval);;
    break;}
case 9:
#line 107 "_psi.y"
{directive_picl(yyvsp[0].cval);;
    break;}
case 10:
#line 111 "_psi.y"
{procedure_header();;
    break;}
case 11:
#line 115 "_psi.y"
{ procedure_post_declaration(); ;
    break;}
case 12:
#line 118 "_psi.y"
{ procedure_footer(yyvsp[-1].statement); ;
    break;}
case 16:
#line 130 "_psi.y"
{ arg_dec_int(yyvsp[0].cval); ;
    break;}
case 17:
#line 131 "_psi.y"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].fval); 
	 yyval.ident = arg_dec_array_3(yyvsp[1].ident); ;
    break;}
case 18:
#line 133 "_psi.y"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].fval); ;
    break;}
case 19:
#line 134 "_psi.y"
{ yyval.ident = arg_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ident,yyvsp[-4].fval,yyvsp[-3].ident); ;
    break;}
case 20:
#line 137 "_psi.y"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].fval); ;
    break;}
case 21:
#line 138 "_psi.y"
{ yyval.ident = var_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ident,yyvsp[-4].fval,yyvsp[-3].ident); ;
    break;}
case 22:
#line 139 "_psi.y"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].fval); 
	 yyval.ident = var_dec_array_3(yyvsp[-2].cval,yyvsp[1].ident); ;
    break;}
case 23:
#line 147 "_psi.y"
{ yyval.ident=const_dec_array_3(const_dec_array_2(yyvsp[-5].ident,yyvsp[-7].fval,const_dec_array(yyvsp[-9].cval,yyvsp[-7].fval))); ;
    break;}
case 24:
#line 151 "_psi.y"
{ yyval.ident=const_dec_array_4(yyvsp[-7].cval,const_dec_array_2(yyvsp[-3].ident,yyvsp[-5].fval,const_dec_array(yyvsp[-7].cval,yyvsp[-5].fval)),yyvsp[0].swval); ;
    break;}
case 25:
#line 155 "_psi.y"
{ yyval.swval = yyvsp[0].fval ;
    break;}
case 26:
#line 156 "_psi.y"
{ yyval.swval = yyvsp[0].fval ;
    break;}
case 27:
#line 157 "_psi.y"
{ yyval.swval = 0 - yyvsp[0].fval ;
    break;}
case 28:
#line 160 "_psi.y"
{ yyval.ident = global_dec(yyvsp[0].cval); ;
    break;}
case 29:
#line 163 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 33:
#line 174 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 35:
#line 177 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 37:
#line 181 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 38:
#line 182 "_psi.y"
{dual_fprintf(","); ;
    break;}
case 39:
#line 182 "_psi.y"
{ yyval.ident = yyvsp[-1].ident; ;
    break;}
case 40:
#line 186 "_psi.y"
{ declaration_name(yyvsp[-1].cval);;
    break;}
case 41:
#line 188 "_psi.y"
{  declaration_footer(); ;
    break;}
case 42:
#line 192 "_psi.y"
{ yyval.statement=NULL;
    break;}
case 43:
#line 194 "_psi.y"
{ yyval.statement=yyvsp[-1].statement; yyvsp[-1].statement->next=yyvsp[0].statement; collect_garbage(NULL,save_list,NULL); ;
    break;}
case 44:
#line 198 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 45:
#line 199 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 46:
#line 200 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 47:
#line 201 "_psi.y"
{ yyval.statement=yyvsp[-1].statement ;
    break;}
case 48:
#line 206 "_psi.y"
{ yyval.statement=assignment_normal(yyvsp[-3].cval,yyvsp[-1].parser);;
    break;}
case 49:
#line 208 "_psi.y"
{ yyval.statement=assignment_pdrop(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 50:
#line 210 "_psi.y"
{ yyval.statement=assignment_psi(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 51:
#line 215 "_psi.y"
{ yyval.statement = for_statement(yyvsp[-6].parser,yyvsp[-4].parser,yyvsp[-2].parser,yyvsp[0].statement); ;
    break;}
case 52:
#line 221 "_psi.y"
{ yyval.statement = do_procedure_call (yyvsp[-4].cval, yyvsp[-2].parser); ;
    break;}
case 53:
#line 226 "_psi.y"
{ yyval.ident = vector_const2_ident(); ;
    break;}
case 54:
#line 230 "_psi.y"
{ vector_const2_init(); ;
    break;}
case 55:
#line 232 "_psi.y"
{yyval.wval=vector_const2_num; vector_const2_footer(); ;
    break;}
case 56:
#line 236 "_psi.y"
{ yyval.wval = vector_const2_number(yyvsp[0].fval);;
    break;}
case 57:
#line 237 "_psi.y"
{ yyval.wval = vector_const2_name(yyvsp[0].cval); ;
    break;}
case 58:
#line 238 "_psi.y"
{ yyval.wval = vector_const2_number(yyvsp[0].fval); ;
    break;}
case 59:
#line 239 "_psi.y"
{ yyval.wval = vector_const2_number(-yyvsp[0].fval); ;
    break;}
case 60:
#line 242 "_psi.y"
{ yyval.wval = 0; ;
    break;}
case 61:
#line 243 "_psi.y"
{ yyval.wval = yyvsp[-1].wval + yyvsp[0].wval; ;
    break;}
case 62:
#line 247 "_psi.y"
{ yyval.parser=expression_name(yyvsp[0].cval); ;
    break;}
case 63:
#line 251 "_psi.y"
{ strcat(expr_str,"("); yyval.parser=yyvsp[-1].parser strcat(expr_str,")");;
    break;}
case 64:
#line 253 "_psi.y"
{ yyval.parser=psi_access(yyvsp[-1].ident); ;
    break;}
case 65:
#line 256 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," + ",yyvsp[0].parser,psi_plus);;
    break;}
case 66:
#line 258 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," - ",yyvsp[0].parser,psi_minus);;
    break;}
case 67:
#line 260 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," * ",yyvsp[0].parser,psi_times);;
    break;}
case 68:
#line 262 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," / ",yyvsp[0].parser,psi_div);;
    break;}
case 69:
#line 264 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," psi ",yyvsp[0].parser,psi_psi);;
    break;}
case 70:
#line 266 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," take ",yyvsp[0].parser,psi_take);;
    break;}
case 71:
#line 268 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," drop ",yyvsp[0].parser,psi_drop);;
    break;}
case 72:
#line 270 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," cat ",yyvsp[0].parser,psi_cat);;
    break;}
case 73:
#line 272 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," pdrop ",yyvsp[0].parser,psi_pdrop);;
    break;}
case 74:
#line 274 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," ptake ",yyvsp[0].parser,psi_ptake);;
    break;}
case 75:
#line 277 "_psi.y"
{ yyval.parser = expression_unary_operator(" + ", yyvsp[0].parser,psi_plus); ;
    break;}
case 76:
#line 279 "_psi.y"
{ yyval.parser = expression_unary_operator(" - ", yyvsp[0].parser,psi_minus); ;
    break;}
case 77:
#line 281 "_psi.y"
{ yyval.parser = expression_unary_operator(" iota ", yyvsp[0].parser,psi_iota); ;
    break;}
case 78:
#line 283 "_psi.y"
{ yyval.parser = expression_unary_operator(" dim ", yyvsp[0].parser,psi_dim); ;
    break;}
case 79:
#line 285 "_psi.y"
{ yyval.parser = expression_unary_operator(" shp ", yyvsp[0].parser,psi_shp); ;
    break;}
case 80:
#line 287 "_psi.y"
{ yyval.parser = expression_unary_operator(" tau ", yyvsp[0].parser,psi_tau); ;
    break;}
case 81:
#line 289 "_psi.y"
{ yyval.parser = expression_unary_operator(" rav ", yyvsp[0].parser,psi_rav); ;
    break;}
case 82:
#line 291 "_psi.y"
{ yyval.parser = expression_unary_operator(" +red ", yyvsp[-1].wval,psi_red_plus); ;
    break;}
case 83:
#line 293 "_psi.y"
{ yyval.parser = expression_unary_operator(" -red ", yyvsp[-1].wval,psi_red_minus); ;
    break;}
case 84:
#line 295 "_psi.y"
{ yyval.parser = expression_unary_operator(" *red ", yyvsp[-1].wval,psi_red_times); ;
    break;}
case 85:
#line 297 "_psi.y"
{ yyval.parser = expression_unary_operator(" /red ", yyvsp[-1].wval,psi_red_div); ;
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
#line 300 "_psi.y"


yyerror (char *s)
{ 
	printf ("Error line %d:  %s\n", line_num, s);
	return (0);
}

void main()
{
	yyparse();
}
