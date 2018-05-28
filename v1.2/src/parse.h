/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   parse.h - definitions for the parser

   6/93 - v0.1 Scott Thibault
   7/93 - v0.2 Scott Thibault

*/

#define LEFTPAREN1 0
#define RIGHTPAREN1 1
#define COMMA1 2
#define TIMES1 3
#define CONST1 4
#define SEMI1 5
#define ARRAY1 6
#define EQUAL1 7
#define HAT1 8
#define LESS1 9
#define GREATER1 10
#define PERIOD1 11
#define LEFTBRACE1 12
#define RIGHTBRACE1 13
#define PLUS1 14
#define MINUS1 15
#define DIVIDE1 16
#define PSI1 17
#define TAKE1 18
#define DROP1 19
#define CAT1 20
#define OMEGA1 21
#define NAME1 22
#define NUMBER1 23
#define UNKNOWN1 24
#define ETX 25
#define INT1 26
#define FLOAT1 27
#define FOR1 28
#define LEQ1 29
#define PDROP1 30
#define PTAKE1 31
#define IOTA1 32
#define SHP1 33
#define DIM1 34
#define RED1 35
#define TAU1 36
#define RAV1 37
#define DOLLAR1 38
#define GLOBAL1 39
#define ALLOCATE1 40
#define LEFTBRACKET1 41
#define RIGHTBRACKET1 42
#define REVERSE1 43
#define LAST 50 /* this has to be the greatest number */

typedef struct {
  int index;
  int arg;
} emit_t;

