/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   moalib.h - prototypes for functions in moalib.c

*/

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

extern int min(int a, int b);
extern int max(int a, int b);
extern void *get_mem(long size);
