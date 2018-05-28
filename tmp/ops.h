/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   8/93 - Original sources by Scott Thibault

*/

/* ops.h - a structure to represent a complex operator */

#ifndef OPS_H
#define OPS_H

typedef struct op_node {
  int      omega;
  parser_t *(*func)();
  parser_t *part;
  struct op_node *next;
} op_t;
#endif
