/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   parse.e - exported functions from parse.c

*/

extern report(char *msg);
extern ident_t **ret_table(int *size);
extern ident_t *find_sym(int index, int talk);
extern char *id_text(int index);
