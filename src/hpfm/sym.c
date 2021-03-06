/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.
   
   sym.c - manages a symbol table

   5/94 - Scott Thibault - created

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../psi.h"

#define MAXKEY 631
#define uchar unsigned char
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define MAXSYMHASH 512

#define sym_key(i) ((i)%MAXSYMHASH)

ident_t *sym_hash[MAXSYMHASH];

typedef struct symbol {
  char          *name;
  int           index;
  struct symbol *next;
} symbol_t;

symbol_t *hash[MAXKEY];
int index;
int name_no;

extern FILE *infile;


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

symbol_t *insert(char *name, int index, int key)

{
  int size;
  symbol_t *new;

  new=(symbol_t *) malloc(sizeof(symbol_t));
  new->next=hash[key];
  size=strlen(name);
  new->name=(char *) malloc(size+1);
  strcpy(new->name,name);
  new->index=index;
  hash[key]=new;

  return(new);
}


name_id(char *name)

{
  int index;

  search(name,&index);
  return(index);
}


char *id_text(int index)

{
  int i;
  char *name;
  symbol_t *sym;

  name=NULL;
  for (i=0; i<MAXKEY; i++) {
    sym=hash[i];
    while ((name==NULL)&&(sym!=NULL)) {
      if (sym->index==index)
	name=sym->name;
      sym=sym->next;
    }
  }
  if (name==NULL)
    fatal("Internal error: id_text");
}


/* search - search for a name in the symbol table, if none is found
     it is inserted. */

search(char *name, int *index)

{
  symbol_t *sym;
  int key_no;
  uchar done;

  key_no=key(name);
  sym=hash[key_no];
  done=FALSE;
  while ((!done)&&(sym!=NULL)) {
    if (strcmp(sym->name,name)==0) {
      *index=sym->index;
      done=TRUE;
    }
    if (!done) sym=sym->next;
  }
  if (!done) {
    *index=(++name_no);
    sym=insert(name,*index,key_no);
    done=TRUE;
  }
}


ident_t **ret_table(int *size)

{
  *size=MAXSYMHASH;
  return(sym_hash);
}


clear_syms()

{
  int i;

  for (i=0; i<MAXSYMHASH; i++) {
    sym_hash[i]=NULL;
  }
}


ident_t *find_sym(int index,int talk)

{
  ident_t *ident;

  ident=sym_hash[sym_key(index)];
  while ((ident!=NULL)&&(ident->index!=index)) {
    ident=ident->next;
  }

  if ((ident==NULL)&&talk) error("Undefined identifier");
  return(ident);
}  


insert_sym(ident_t *ident, int index)

{
  if (find_sym(index,FALSE)!=NULL) 
    error("duplicate variable definition");
  else {
    ident->next=sym_hash[sym_key(index)];
    sym_hash[sym_key(index)]=ident;
    ident->index=index;
  }
}


/* sym_init - initializes the symbol table module */

sym_init()

{
  int i;

  name_no=1;
  for (i=0; i<MAXKEY; i++) hash[i]=NULL;
  clear_syms();
}
