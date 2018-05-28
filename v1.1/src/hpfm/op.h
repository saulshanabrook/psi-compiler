/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.
   
   op.h - a type for passing functions around the parser

   5/94 - Scott Thibault - created

*/

typedef struct {
  parser_t *(*func)();
} psiop_t;
