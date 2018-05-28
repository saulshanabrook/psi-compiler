
/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.
   
   lex.c - preforms lexical analysis.

   6/93 - v0.1 Scott Thibault
   7/93 - v0.2 Scott Thibault

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

#define MAXKEY 631
#define uchar unsigned char
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct symbol {
  uchar         isname;
  char          *name;
  int           index;
  struct symbol *next;
} symbol_t;

symbol_t *hash[MAXKEY];
emit_t emit;
int name_no=LAST;
int line_no=1;
int syntax_report;
char ch,last_name[256];



/* what_name - returns the name just parsed. */

char *what_name()

{
  char *ret;

  ret=last_name;
  return(ret);
}






/* key - hashing function */

int key(char *name)

{
  int sum;
  
  sum=0;
  while (*name) {
    sum=(sum+(*name))%32641;
    name++;
  }
  return(sum%MAXKEY);
}


/* insert - inserts a name into the hash table at key. */

symbol_t *insert(uchar isname, char *name, int index, int key)

{
  int size;
  symbol_t *new;

  new=(symbol_t *) malloc(sizeof(symbol_t));
  new->next=hash[key];
  size=strlen(name);
  new->name=(char *) malloc(size+1);
  strcpy(new->name,name);
  new->isname=isname;
  new->index=index;
  hash[key]=new;

  return(new);
}


/* define - inserts name in the symbol table */

define(uchar isname, char *name, int index)

{
  insert(isname,name,index,key(name));
}


/* search - search for a name in the symbol table, if none is found
     it is inserted. */

search(char *name, uchar *isname, int *index)

{
  symbol_t *sym;
  int key_no;
  uchar done;

  key_no=key(name);
  sym=hash[key_no];
  done=FALSE;
  while ((!done)&&(sym!=NULL)) {
    if (strcmp(sym->name,name)==0) {
      *isname=sym->isname;
      *index=sym->index;
      done=TRUE;
    }
    if (!done) sym=sym->next;
  }
  if (!done) {
    *isname=TRUE;
    *index=(++name_no);
    sym=insert(TRUE,name,*index,key_no);
    done=TRUE;
  }
  strcpy(last_name,sym->name);
}
/*	try the symbol table operations.	*/

void	main()						{
char	*name;
char	*names[] ={"a", "a2", "a3", "d3"};
uchar	z;
int	index;
int	i;

for (i = 0; i < 4; i++)				{
name = names[i];
search(name,&z,&index);
printf("Looking for %s, index = %d\n",name,index);
						}
return;
							}
