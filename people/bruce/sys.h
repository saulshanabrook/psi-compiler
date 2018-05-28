/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   sys.h - data structures required for the system module

   8/93 - v0.3 Scott Thibault
               save_t type was introduced for memory garabage collection.

*/

#ifndef SYS_H
#define SYS_H

typedef struct save {
  statement_t *statement;
  struct save *next;
} save_t;

#define MARK ((int) 0x8000)
#define NMARK ((int) 0x7fff)

#endif
