/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* ops.h - a structure to represent a complex operator */

#ifndef OPS_H
#define OPS_H

/* op_t - A compound operator structure.  If omega is true that the structure
     represents a complex operator of omega with the function func or next and 
     partition vector part.  The function is func if next==NULL next otherwise.
     If omega is false then it is the simple operator func. */

typedef struct op_node {
  int      omega;         /* indicates if this is an omega operator or not */
  parser_t *(*func)();
  parser_t *part;
  struct op_node *next;
} op_t;
#endif
