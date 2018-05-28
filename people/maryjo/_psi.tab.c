
/*  A Bison parser, made from _psi.y  */

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
#define	ALLOCATE1	284
#define	PICL1	285
#define	UNEG	286
#define	OMEGAB	287
#define	OMEGAU	288

#line 1 "_psi.y"

/* This is inserted in resulting .C file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include "psi.h"
#include "dist.h"
#include "sys.h"
#include "ops.h"
#include "_psi.sem.h"
 
#include "code.e"
#include "part.e"
#include "dist.e"
#include "psi.e"
#include "vect.e"
#include "ident.e"
#include "sys.e"
#include "moa_func.e"

extern char expr_str[1024];
extern int line_num;
extern int vector_const2_num;
extern op_t *op;
FILE *cfile;

#line 28 "_psi.y"
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

#ifndef __STDC__
#define const
#endif



#define	YYFINAL		249
#define	YYFLAG		-32768
#define	YYNTBASE	51

#define YYTRANSLATE(x) ((unsigned)(x) <= 288 ? yytranslate[x] : 97)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    39,     2,     2,     2,    48,
    49,    33,    31,    47,    32,     2,    34,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    46,    43,
    45,    44,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    36,     2,    50,    42,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    40,     2,    41,     2,     2,     2,     2,     2,
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
    26,    27,    28,    29,    30,    35,    37,    38
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     2,     7,     8,    11,    15,    19,    23,    27,
    28,    29,    37,    38,    41,    44,    47,    52,    53,    62,
    63,    72,    77,    90,   101,   103,   106,   109,   112,   113,
   117,   121,   125,   126,   128,   129,   132,   133,   134,   139,
   140,   146,   147,   150,   152,   154,   156,   158,   162,   167,
   176,   185,   195,   196,   200,   201,   202,   207,   208,   215,
   220,   222,   223,   226,   228,   230,   233,   236,   237,   240,
   242,   243,   244,   250,   254,   258,   262,   266,   270,   274,
   278,   282,   286,   290,   294,   297,   300,   303,   306,   309,
   312,   315,   319,   323,   327,   331,   334,   338,   340,   343,
   346,   349,   352,   354,   356,   358,   360,   362,   364,   366,
   368,   370,   372,   378,   386,   392
};

#endif

static const short yyrhs[] = {    -1,
     0,    52,    54,    53,    59,     0,     0,    39,    25,     0,
    39,    26,     5,     0,    39,    27,     4,     0,    39,    28,
     4,     0,    39,    30,     4,     0,     0,     0,    56,    72,
    40,    68,    57,    74,    41,     0,     0,    55,    58,     0,
    55,    58,     0,     8,     4,     0,     6,     4,    42,     5,
     0,     0,     6,     4,    42,     5,    61,    43,    86,    44,
     0,     0,     6,     4,    42,     5,    63,    43,    86,    44,
     0,     6,     4,    42,     5,     0,    16,     6,     4,    42,
     5,    43,    86,    44,    45,    43,    85,    44,     0,    16,
     6,     4,    42,     5,    43,    86,    44,    45,    64,     0,
     5,     0,    31,     5,     0,    32,     5,     0,     7,     4,
     0,     0,    62,    46,    66,     0,    65,    46,    66,     0,
    62,    46,    66,     0,     0,    67,     0,     0,    60,    70,
     0,     0,     0,    47,    71,    60,    70,     0,     0,     4,
    48,    73,    69,    49,     0,     0,    75,    74,     0,    76,
     0,    77,     0,    82,     0,    84,     0,    40,    74,    41,
     0,     4,    45,    90,    46,     0,    43,    85,    44,    14,
     4,    45,    90,    46,     0,    43,    85,    44,    10,     4,
    45,    90,    46,     0,     3,    48,    90,    22,    90,    43,
    90,    49,    75,     0,     0,     4,    79,    80,     0,     0,
     0,    47,     4,    81,    80,     0,     0,     4,    48,    83,
    78,    49,    46,     0,    29,     4,    90,    46,     0,    86,
     0,     0,    87,    89,     0,     5,     0,     4,     0,    31,
     5,     0,    32,     5,     0,     0,    88,    89,     0,     4,
     0,     0,     0,    48,    91,    90,    92,    49,     0,    43,
    85,    44,     0,    90,    31,    90,     0,    90,    32,    90,
     0,    90,    33,    90,     0,    90,    34,    90,     0,    90,
    10,    90,     0,    90,    11,    90,     0,    90,    12,    90,
     0,    90,    13,    90,     0,    90,    14,    90,     0,    90,
    15,    90,     0,    31,    90,     0,    32,    90,     0,    17,
    90,     0,    18,    90,     0,    19,    90,     0,    20,    90,
     0,    21,    90,     0,    31,    23,    90,     0,    32,    23,
    90,     0,    33,    23,    90,     0,    34,    23,    90,     0,
    95,    90,     0,    90,    96,    90,     0,    21,     0,    31,
    23,     0,    32,    23,     0,    33,    23,     0,    34,    23,
     0,    31,     0,    32,     0,    34,     0,    33,     0,    10,
     0,    11,     0,    12,     0,    13,     0,    14,     0,    15,
     0,    93,    24,    43,    85,    44,     0,    36,    95,    50,
    24,    43,    85,    44,     0,    94,    24,    43,    85,    44,
     0,    36,    96,    50,    24,    43,    85,    44,     0
};

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   109,   112,   114,   117,   118,   119,   120,   121,   122,   125,
   128,   132,   136,   137,   140,   144,   146,   148,   149,   151,
   153,   154,   159,   163,   169,   171,   172,   174,   178,   179,
   181,   184,   189,   190,   192,   193,   196,   197,   197,   200,
   203,   206,   208,   212,   214,   215,   216,   217,   220,   223,
   225,   229,   234,   238,   241,   242,   245,   248,   251,   256,
   260,   265,   268,   271,   273,   274,   275,   278,   279,   282,
   286,   289,   291,   292,   295,   297,   299,   301,   303,   305,
   307,   309,   311,   313,   316,   318,   320,   322,   324,   326,
   328,   330,   332,   334,   336,   338,   340,   344,   346,   347,
   348,   349,   352,   354,   355,   356,   357,   358,   359,   360,
   361,   362,   365,   368,   372,   375
};

static const char * const yytname[] = {   "$","error","$illegal.","FOR1","NAME1",
"NUMBER1","ARRAY1","GLOBAL1","INT1","FLOAT1","PSI1","TAKE1","DROP1","CAT1","PDROP1",
"PTAKE1","CONST1","IOTA1","DIM1","SHP1","TAU1","RAV1","LTE1","RED1","OMEGA1",
"TRACE1","PROCS1","ARCH1","HOSTNAME1","ALLOCATE1","PICL1","'+'","'-'","'*'",
"'/'","UNEG","'['","OMEGAB","OMEGAU","'$'","'{'","'}'","'^'","'<'","'>'","'='",
"';'","','","'('","')'","']'","executable_program","@1","@2","directives_opt",
"procedure_mand","@3","@4","procedure_opt","procedure_list","arg_dec","@5","var_dec",
"@6","anynumber","global_dec","var_dec_statement_cont","var_dec_statement_mand",
"var_dec_statement_opt","arg_list_opt","arg_list_cont","@7","declaration","@8",
"statement_base_opt","statement_base_mand","assignment","for_statement","actual_list_base",
"@9","actual_list_opt","@10","procedure_call","@11","alloc_statement","vector_const_ident_base",
"vector_const2_base","@12","vector_const2_mand","vector_const2_opt","expression",
"@13","@14","unary_op","binary_op","omega_unop","omega_binop",""
};
#endif

static const short yyr1[] = {     0,
    52,    53,    51,    54,    54,    54,    54,    54,    54,    56,
    57,    55,    58,    58,    59,    60,    60,    61,    60,    63,
    62,    62,    62,    62,    64,    64,    64,    65,    66,    66,
    66,    67,    68,    68,    69,    69,    70,    71,    70,    73,
    72,    74,    74,    75,    75,    75,    75,    75,    76,    76,
    76,    77,    79,    78,    80,    81,    80,    83,    82,    84,
    85,    87,    86,    88,    88,    88,    88,    89,    89,    90,
    91,    92,    90,    90,    90,    90,    90,    90,    90,    90,
    90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
    90,    90,    90,    90,    90,    90,    90,    93,    93,    93,
    93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
    94,    94,    95,    95,    96,    96
};

static const short yyr2[] = {     0,
     0,     0,     4,     0,     2,     3,     3,     3,     3,     0,
     0,     7,     0,     2,     2,     2,     4,     0,     8,     0,
     8,     4,    12,    10,     1,     2,     2,     2,     0,     3,
     3,     3,     0,     1,     0,     2,     0,     0,     4,     0,
     5,     0,     2,     1,     1,     1,     1,     3,     4,     8,
     8,     9,     0,     3,     0,     0,     4,     0,     6,     4,
     1,     0,     2,     1,     1,     2,     2,     0,     2,     1,
     0,     0,     5,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
     2,     3,     3,     3,     3,     2,     3,     1,     2,     2,
     2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     5,     7,     5,     7
};

static const short yydefact[] = {     1,
     4,     0,     2,     5,     0,     0,     0,     0,    10,     6,
     7,     8,     9,    10,     0,     3,    10,    15,     0,     0,
    14,    40,    33,    35,     0,     0,     0,    34,    11,     0,
     0,    37,     0,     0,     0,    29,    42,     0,    16,    38,
    36,    41,     0,     0,     0,     0,     0,    32,     0,     0,
     0,    42,    62,     0,    42,    44,    45,    46,    47,     0,
     0,    20,     0,    28,    29,    29,     0,     0,    58,     0,
     0,     0,    61,    68,    12,    43,    17,    37,     0,     0,
    30,    31,    70,     0,     0,     0,     0,    98,     0,     0,
     0,     0,     0,    62,    71,     0,     0,     0,     0,     0,
     0,    48,     0,    65,    64,     0,     0,    68,    63,     0,
    39,    62,    62,    87,    88,    89,    90,    91,    99,    85,
   100,    86,   101,   102,    98,     0,     0,     0,     0,     0,
     0,     0,   107,   108,   109,   110,   111,   112,     0,   103,
   104,   106,   105,     0,     0,     0,     0,    96,    49,    53,
     0,    60,     0,     0,    66,    67,    69,    62,     0,     0,
    92,    93,    94,    95,    99,   100,   101,   102,     0,    74,
    72,    79,    80,    81,    82,    83,    84,     0,    75,    76,
    77,    78,   107,   108,   109,   110,   111,   112,   103,   104,
   106,   105,     0,     0,    97,    62,    55,     0,     0,     0,
     0,    21,     0,     0,     0,     0,     0,    62,     0,     0,
    54,    59,     0,     0,    19,     0,    62,    73,     0,     0,
     0,   113,    56,     0,     0,    25,     0,     0,    62,    24,
     0,     0,    62,   115,    55,    51,    50,    26,    27,     0,
   114,    52,     0,    57,    23,   116,     0,     0,     0
};

static const short yydefgoto[] = {   247,
     1,     9,     3,    17,    15,    37,    18,    16,    32,   110,
    46,    79,   230,    47,    48,    28,    29,    33,    41,    61,
    20,    24,    54,    55,    56,    57,   151,   197,   211,   235,
    58,   100,    59,    72,    73,    74,   108,   109,    96,   132,
   205,    97,   145,    98,   146
};

static const short yypact[] = {-32768,
   -12,    92,-32768,-32768,     9,    40,    43,    50,-32768,-32768,
-32768,-32768,-32768,    57,    72,-32768,    57,-32768,    35,    45,
-32768,-32768,    27,    44,    82,    81,    42,-32768,-32768,    85,
    91,    51,    52,    58,    95,    32,     2,    60,-32768,-32768,
-32768,-32768,   103,    68,   107,    66,    67,-32768,    75,   -33,
   110,     2,-32768,    84,     2,-32768,-32768,-32768,-32768,   121,
    44,    83,   122,-32768,    32,    32,   138,   138,-32768,   138,
    87,    86,-32768,     5,-32768,-32768,    88,    51,    89,    90,
-32768,-32768,-32768,   138,   138,   138,   138,   138,    73,   130,
   112,   114,    -8,-32768,-32768,   269,   115,   138,   177,   137,
   183,-32768,    -3,-32768,-32768,   139,   147,     5,-32768,   100,
-32768,-32768,-32768,   118,   118,   118,   118,   118,   138,   118,
   138,   118,   138,   138,-32768,   142,   144,   145,   152,   126,
   116,   138,   138,   138,   138,   138,   138,   138,   138,   138,
   138,   138,   138,   297,   153,   138,   136,-32768,-32768,-32768,
   131,-32768,   178,   179,-32768,-32768,-32768,-32768,   140,   141,
   118,   118,   118,   118,-32768,-32768,-32768,-32768,   175,-32768,
   303,   118,   118,   118,   118,   118,   118,   263,   118,   118,
   118,   118,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   150,   158,-32768,-32768,   155,   157,   159,   160,
   162,-32768,   167,   164,   169,   138,   196,-32768,   180,   217,
-32768,-32768,   138,   138,-32768,     3,-32768,-32768,    48,   182,
   184,-32768,-32768,   220,   226,-32768,   221,   222,-32768,-32768,
   198,     2,-32768,-32768,   155,-32768,-32768,-32768,-32768,   199,
-32768,-32768,   200,-32768,-32768,-32768,   245,   246,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,   213,-32768,-32768,   230,-32768,   187,-32768,
   227,-32768,-32768,-32768,   -25,-32768,-32768,-32768,   171,-32768,
-32768,-32768,   -23,    23,-32768,-32768,-32768,-32768,    26,-32768,
-32768,-32768,-32768,   -93,  -109,-32768,-32768,   156,   -68,-32768,
-32768,-32768,-32768,   170,   123
};


#define	YYLAST		339


static const short yytable[] = {    99,
   131,   101,   159,   160,    49,    50,   153,   226,   104,   105,
   154,    68,   125,    10,    69,   114,   115,   116,   117,   118,
   120,   122,   126,   127,   128,   129,     2,    93,    71,   148,
    51,    76,    25,   227,   228,   106,   107,    25,    45,    81,
    82,    52,    26,    11,    53,   229,    12,    26,   201,    30,
   161,    31,   162,    13,   163,   164,   -13,   133,   134,   135,
   136,   137,   138,   171,   172,   173,   174,   175,   176,   177,
   178,   179,   180,   181,   182,    19,    83,   195,   140,   141,
   142,   143,    22,   144,    23,    34,    35,    36,    38,    84,
    85,    86,    87,    88,    39,   119,   232,    40,    44,    43,
    42,    60,   209,    89,    90,    91,    92,    62,    93,    63,
    64,    65,    66,    70,   221,    94,     4,     5,     6,     7,
    95,     8,    67,   231,    75,    77,    80,   102,   -22,   103,
   -18,   112,   113,    83,   123,   240,   124,   219,   147,   243,
   150,    83,   158,   155,   224,   225,    84,    85,    86,    87,
    88,   156,   121,   144,    84,    85,    86,    87,    88,   170,
    89,    90,    91,    92,   165,    93,   166,   167,    89,    90,
    91,    92,    94,    93,   168,   169,   194,    95,   196,   198,
    94,   199,   200,   202,   203,    95,   133,   134,   135,   136,
   137,   138,   133,   134,   135,   136,   137,   138,   204,   207,
   208,   210,   212,   213,   214,   215,   217,   140,   141,   142,
   143,   216,   144,   140,   141,   142,   143,   218,   144,   220,
   223,    14,   149,   222,   233,   238,   239,   234,   152,   133,
   134,   135,   136,   137,   138,   133,   134,   135,   136,   137,
   138,   241,   245,   246,   248,   249,    21,    78,   111,    27,
   140,   141,   142,   143,   242,   144,   140,   141,   142,   143,
   244,   144,   130,   157,     0,   236,   193,     0,     0,     0,
     0,   237,   133,   134,   135,   136,   137,   138,   133,   134,
   135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
   139,     0,     0,   140,   141,   142,   143,     0,   144,   140,
   141,   142,   143,     0,   144,   206,   183,   184,   185,   186,
   187,   188,   133,   134,   135,   136,   137,   138,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   189,   190,   191,
   192,     0,   144,   140,   141,   142,   143,     0,   144
};

static const short yycheck[] = {    68,
    94,    70,   112,   113,     3,     4,    10,     5,     4,     5,
    14,    45,    21,     5,    48,    84,    85,    86,    87,    88,
    89,    90,    31,    32,    33,    34,    39,    36,    52,    98,
    29,    55,     6,    31,    32,    31,    32,     6,     7,    65,
    66,    40,    16,     4,    43,    43,     4,    16,   158,     6,
   119,     8,   121,     4,   123,   124,     0,    10,    11,    12,
    13,    14,    15,   132,   133,   134,   135,   136,   137,   138,
   139,   140,   141,   142,   143,     4,     4,   146,    31,    32,
    33,    34,    48,    36,    40,     4,     6,    46,     4,    17,
    18,    19,    20,    21,     4,    23,    49,    47,     4,    42,
    49,    42,   196,    31,    32,    33,    34,     5,    36,    42,
     4,    46,    46,     4,   208,    43,    25,    26,    27,    28,
    48,    30,    48,   217,    41,     5,     5,    41,    46,    44,
    43,    43,    43,     4,    23,   229,    23,   206,    24,   233,
     4,     4,    43,     5,   213,   214,    17,    18,    19,    20,
    21,     5,    23,    36,    17,    18,    19,    20,    21,    44,
    31,    32,    33,    34,    23,    36,    23,    23,    31,    32,
    33,    34,    43,    36,    23,    50,    24,    48,    43,    49,
    43,     4,     4,    44,    44,    48,    10,    11,    12,    13,
    14,    15,    10,    11,    12,    13,    14,    15,    24,    50,
    43,    47,    46,    45,    45,    44,    43,    31,    32,    33,
    34,    45,    36,    31,    32,    33,    34,    49,    36,    24,
     4,     9,    46,    44,    43,     5,     5,    44,    46,    10,
    11,    12,    13,    14,    15,    10,    11,    12,    13,    14,
    15,    44,    44,    44,     0,     0,    17,    61,    78,    23,
    31,    32,    33,    34,   232,    36,    31,    32,    33,    34,
   235,    36,    93,   108,    -1,    46,   144,    -1,    -1,    -1,
    -1,    46,    10,    11,    12,    13,    14,    15,    10,    11,
    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
    22,    -1,    -1,    31,    32,    33,    34,    -1,    36,    31,
    32,    33,    34,    -1,    36,    43,    10,    11,    12,    13,
    14,    15,    10,    11,    12,    13,    14,    15,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
    34,    -1,    36,    31,    32,    33,    34,    -1,    36
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
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
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

#line 169 "/usr/local/lib/bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

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
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
#ifdef YYLSP_NEEDED
		 &yyls1, size * sizeof (*yylsp),
#endif
		 &yystacksize);

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
#line 110 "_psi.y"
{ executable_header(); ;
    break;}
case 2:
#line 112 "_psi.y"
{ executable_post_declaration(); ;
    break;}
case 3:
#line 114 "_psi.y"
{ executable_footer(); ;
    break;}
case 5:
#line 118 "_psi.y"
{directive_trace(); ;
    break;}
case 6:
#line 119 "_psi.y"
{ directive_procs(yyvsp[0].ival);;
    break;}
case 7:
#line 120 "_psi.y"
{directive_arch(yyvsp[0].cval);;
    break;}
case 8:
#line 121 "_psi.y"
{directive_hostname(yyvsp[0].cval);;
    break;}
case 9:
#line 122 "_psi.y"
{directive_picl(yyvsp[0].cval);;
    break;}
case 10:
#line 126 "_psi.y"
{procedure_header();;
    break;}
case 11:
#line 130 "_psi.y"
{ procedure_post_declaration(); ;
    break;}
case 12:
#line 133 "_psi.y"
{ procedure_footer(yyvsp[-1].statement); ;
    break;}
case 16:
#line 145 "_psi.y"
{ arg_dec_int(yyvsp[0].cval); ;
    break;}
case 17:
#line 146 "_psi.y"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].ival); 
	 yyval.ident = arg_dec_array_3(yyvsp[-2].cval, yyvsp[1].ident); ;
    break;}
case 18:
#line 148 "_psi.y"
{ yyval.ident = arg_dec_array(yyvsp[-2].cval,yyvsp[0].ival); ;
    break;}
case 19:
#line 149 "_psi.y"
{ yyval.ident = arg_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ival,yyvsp[-4].ival,yyvsp[-3].ident); ;
    break;}
case 20:
#line 152 "_psi.y"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].ival); ;
    break;}
case 21:
#line 153 "_psi.y"
{ yyval.ident = var_dec_array_2(yyvsp[-6].cval,yyvsp[-1].ival,yyvsp[-4].ival,yyvsp[-3].ident); ;
    break;}
case 22:
#line 154 "_psi.y"
{ yyval.ident = var_dec_array(yyvsp[-2].cval,yyvsp[0].ival); 
	 yyval.ident = var_dec_array_3(yyvsp[-2].cval,yyvsp[1].ident); ;
    break;}
case 23:
#line 162 "_psi.y"
{ yyval.ident=const_dec_array_3(yyvsp[-9].cval,const_dec_array_2(yyvsp[-5].ival,yyvsp[-7].ival,const_dec_array(yyvsp[-9].cval,yyvsp[-7].ival))); ;
    break;}
case 24:
#line 166 "_psi.y"
{ yyval.ident=const_dec_array_4(yyvsp[-7].cval,const_dec_array_2(yyvsp[-3].ival,yyvsp[-5].ival,const_dec_array(yyvsp[-7].cval,yyvsp[-5].ival)),yyvsp[0].ival); ;
    break;}
case 25:
#line 170 "_psi.y"
{ yyval.ival = yyvsp[0].ival ;
    break;}
case 26:
#line 171 "_psi.y"
{ yyval.ival = yyvsp[0].ival ;
    break;}
case 27:
#line 172 "_psi.y"
{ yyval.ival = 0 - yyvsp[0].ival ;
    break;}
case 28:
#line 175 "_psi.y"
{ yyval.ident = global_dec(yyvsp[0].cval); ;
    break;}
case 29:
#line 178 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 33:
#line 189 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 35:
#line 192 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 37:
#line 196 "_psi.y"
{ yyval.ident = NULL; ;
    break;}
case 38:
#line 197 "_psi.y"
{dual_fprintf(","); ;
    break;}
case 39:
#line 197 "_psi.y"
{ yyval.ident = yyvsp[-1].ident; ;
    break;}
case 40:
#line 201 "_psi.y"
{ declaration_name(yyvsp[-1].cval);;
    break;}
case 41:
#line 203 "_psi.y"
{  declaration_footer(); ;
    break;}
case 42:
#line 207 "_psi.y"
{ yyval.statement=NULL;
    break;}
case 43:
#line 209 "_psi.y"
{ yyval.statement=yyvsp[-1].statement; yyvsp[-1].statement->next=yyvsp[0].statement; collect_garbage(NULL,save_list,NULL); ;
    break;}
case 44:
#line 213 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 45:
#line 214 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 46:
#line 215 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 47:
#line 216 "_psi.y"
{ yyval.statement=yyvsp[0].statement ;
    break;}
case 48:
#line 217 "_psi.y"
{ yyval.statement=yyvsp[-1].statement ;
    break;}
case 49:
#line 222 "_psi.y"
{ yyval.statement=assignment_normal(yyvsp[-3].cval,yyvsp[-1].parser);;
    break;}
case 50:
#line 224 "_psi.y"
{ yyval.statement=assignment_pdrop(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 51:
#line 226 "_psi.y"
{ yyval.statement=assignment_psi(yyvsp[-6].ident,yyvsp[-3].cval,yyvsp[-1].parser); ;
    break;}
case 52:
#line 231 "_psi.y"
{ yyval.statement = for_statement(yyvsp[-6].parser,yyvsp[-4].parser,yyvsp[-2].parser,yyvsp[0].statement); ;
    break;}
case 53:
#line 236 "_psi.y"
{ yyval.reduced = actual_list_1(yyvsp[0].cval); ;
    break;}
case 54:
#line 238 "_psi.y"
{ yyval.statement=actual_list_2(yyvsp[-1].reduced,yyvsp[0].reduced); ;
    break;}
case 55:
#line 241 "_psi.y"
{ yyval.reduced = NULL; ;
    break;}
case 56:
#line 243 "_psi.y"
{ yyval.reduced=actual_list_3(yyvsp[0].cval); ;
    break;}
case 57:
#line 245 "_psi.y"
{ yyval.reduced = actual_list_4(yyvsp[-1].reduced,yyvsp[0].reduced); ;
    break;}
case 58:
#line 250 "_psi.y"
{ do_procedure_call_1 (yyvsp[-1].cval); ;
    break;}
case 59:
#line 253 "_psi.y"
{ yyval.statement = do_procedure_call_2 (yyvsp[-2].statement); ;
    break;}
case 60:
#line 257 "_psi.y"
{ yyval.statement = allocate_statement(yyvsp[-2].cval,yyvsp[-1].parser); ;
    break;}
case 61:
#line 262 "_psi.y"
{ yyval.ident = vector_const2_ident(); ;
    break;}
case 62:
#line 266 "_psi.y"
{ vector_const2_init(); ;
    break;}
case 63:
#line 268 "_psi.y"
{yyval.ival=vector_const2_num; vector_const2_footer(); ;
    break;}
case 64:
#line 272 "_psi.y"
{ yyval.ival = vector_const2_number(yyvsp[0].ival);;
    break;}
case 65:
#line 273 "_psi.y"
{ yyval.ival = vector_const2_name(yyvsp[0].cval); ;
    break;}
case 66:
#line 274 "_psi.y"
{ yyval.ival = vector_const2_number(yyvsp[0].ival); ;
    break;}
case 67:
#line 275 "_psi.y"
{ yyval.ival = vector_const2_number(-yyvsp[0].ival); ;
    break;}
case 68:
#line 278 "_psi.y"
{ yyval.ival = 0; ;
    break;}
case 69:
#line 279 "_psi.y"
{ yyval.ival = yyvsp[-1].ival + yyvsp[0].ival; ;
    break;}
case 70:
#line 283 "_psi.y"
{ yyval.parser=expression_name(yyvsp[0].cval); ;
    break;}
case 71:
#line 287 "_psi.y"
{ sprintf (expr_str+strlen(expr_str),"%c",'('); ;
    break;}
case 72:
#line 289 "_psi.y"
{ sprintf (expr_str+strlen(expr_str),"%c",')'); ;
    break;}
case 73:
#line 291 "_psi.y"
{ yyval.parser = yyvsp[-2].parser; ;
    break;}
case 74:
#line 293 "_psi.y"
{ yyval.parser=psi_access(yyvsp[-1].ident); ;
    break;}
case 75:
#line 296 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," + ",yyvsp[0].parser,psi_plus);;
    break;}
case 76:
#line 298 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," - ",yyvsp[0].parser,psi_minus);;
    break;}
case 77:
#line 300 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," * ",yyvsp[0].parser,psi_times);;
    break;}
case 78:
#line 302 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," / ",yyvsp[0].parser,psi_div);;
    break;}
case 79:
#line 304 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," psi ",yyvsp[0].parser,psi_psi);;
    break;}
case 80:
#line 306 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," take ",yyvsp[0].parser,psi_take);;
    break;}
case 81:
#line 308 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," drop ",yyvsp[0].parser,psi_drop);;
    break;}
case 82:
#line 310 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," cat ",yyvsp[0].parser,psi_cat);;
    break;}
case 83:
#line 312 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," pdrop ",yyvsp[0].parser,psi_pdrop);;
    break;}
case 84:
#line 314 "_psi.y"
{ yyval.parser=expression_binary_operator(yyvsp[-2].parser," ptake ",yyvsp[0].parser,psi_ptake);;
    break;}
case 85:
#line 317 "_psi.y"
{ yyval.parser = expression_unary_operator(" + ", yyvsp[0].parser,psi_plus); ;
    break;}
case 86:
#line 319 "_psi.y"
{ yyval.parser = expression_unary_operator(" - ", yyvsp[0].parser,psi_minus); ;
    break;}
case 87:
#line 321 "_psi.y"
{ yyval.parser = expression_unary_operator(" iota ", yyvsp[0].parser,psi_iota); ;
    break;}
case 88:
#line 323 "_psi.y"
{ yyval.parser = expression_unary_operator(" dim ", yyvsp[0].parser,psi_dim); ;
    break;}
case 89:
#line 325 "_psi.y"
{ yyval.parser = expression_unary_operator(" shp ", yyvsp[0].parser,psi_shp); ;
    break;}
case 90:
#line 327 "_psi.y"
{ yyval.parser = expression_unary_operator(" tau ", yyvsp[0].parser,psi_tau); ;
    break;}
case 91:
#line 329 "_psi.y"
{ yyval.parser = expression_unary_operator(" rav ", yyvsp[0].parser,psi_rav); ;
    break;}
case 92:
#line 331 "_psi.y"
{ yyval.parser = expression_unary_operator(" +red ", yyvsp[0].parser,psi_red_plus); ;
    break;}
case 93:
#line 333 "_psi.y"
{ yyval.parser = expression_unary_operator(" -red ", yyvsp[0].parser,psi_red_minus); ;
    break;}
case 94:
#line 335 "_psi.y"
{ yyval.parser = expression_unary_operator(" *red ", yyvsp[0].parser,psi_red_times); ;
    break;}
case 95:
#line 337 "_psi.y"
{ yyval.parser = expression_unary_operator(" /red ", yyvsp[0].parser,psi_red_div); ;
    break;}
case 96:
#line 339 "_psi.y"
{ yyval.parser = omega_unary (yyvsp[-1].op, yyvsp[0].parser); ;
    break;}
case 97:
#line 341 "_psi.y"
{ yyval.parser = omega_binary (yyvsp[-2].parser, yyvsp[-1].op, yyvsp[0].parser); ;
    break;}
case 98:
#line 345 "_psi.y"
{ yyval.op = set_opt (psi_rav, " rav "); ;
    break;}
case 99:
#line 346 "_psi.y"
{ yyval.op = set_opt (psi_red_plus, " + red "); ;
    break;}
case 100:
#line 347 "_psi.y"
{ yyval.op = set_opt (psi_red_minus, " - red "); ;
    break;}
case 101:
#line 348 "_psi.y"
{ yyval.op = set_opt (psi_red_times, " * red "); ;
    break;}
case 102:
#line 349 "_psi.y"
{ yyval.op = set_opt (psi_red_div, " / red "); ;
    break;}
case 103:
#line 353 "_psi.y"
{ yyval.op = set_opt (psi_plus, " + "); ;
    break;}
case 104:
#line 354 "_psi.y"
{ yyval.op = set_opt (psi_minus, " - "); ;
    break;}
case 105:
#line 355 "_psi.y"
{ yyval.op = set_opt (psi_div, " / "); ;
    break;}
case 106:
#line 356 "_psi.y"
{ yyval.op = set_opt (psi_times, " * "); ;
    break;}
case 107:
#line 357 "_psi.y"
{ yyval.op = set_opt (psi_psi, " psi "); ;
    break;}
case 108:
#line 358 "_psi.y"
{ yyval.op = set_opt (psi_take, " take "); ;
    break;}
case 109:
#line 359 "_psi.y"
{ yyval.op = set_opt (psi_drop, " drop "); ;
    break;}
case 110:
#line 360 "_psi.y"
{ yyval.op = set_opt (psi_cat, " cat "); ;
    break;}
case 111:
#line 361 "_psi.y"
{ yyval.op = set_opt (psi_pdrop, " pdrop "); ;
    break;}
case 112:
#line 362 "_psi.y"
{ yyval.op = set_opt (psi_ptake, " ptake "); ;
    break;}
case 113:
#line 367 "_psi.y"
{ yyval.op = omega_no_bracket (yyvsp[-4].op, yyvsp[-1].ident); ;
    break;}
case 114:
#line 369 "_psi.y"
{ yyval.op = omega_yes_bracket (yyvsp[-5].op, yyvsp[-1].ident); ;
    break;}
case 115:
#line 374 "_psi.y"
{ yyval.op = omega_no_bracket (yyvsp[-4].op, yyvsp[-1].ident); ;
    break;}
case 116:
#line 376 "_psi.y"
{ yyval.op = omega_yes_bracket (yyvsp[-5].op, yyvsp[-1].ident); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 442 "/usr/local/lib/bison.simple"

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
	  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = 0; x < (sizeof(yytname) / sizeof(char *)); x++)
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
#line 379 "_psi.y"


yyerror (char *s)
{ 
	printf ("Error line %d:  %s\n", line_num, s);
	return (0);
}
