/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   dist.h - data structures and definitions related to partitioning and 
     distributed arrays.

   8/93 - Scott Thibault

*/

/* dist_t - represents a distributed array partitioning as a
    list of arrays and their distribution. */

typedef struct dist {
  ident_t *ident;   /* the array being distributed */
  vect_t  *shp;     /* the shape of the array */
  vect_t  *c;       /* the shape of cyclic portion of the dist. mem. */
  vect_t  *g;       /* the shape of the processors array */
  vect_t  *e;       /* the shape of the processors local memory */
  vect_t  *pl;      /* the location of the processor sub-array used */
  vect_t  *pb;      /* the shape of the processor sub-array used */
  struct dist *next;
} dist_t;           /* the shape of the dist. mem. is c,pb,e */

