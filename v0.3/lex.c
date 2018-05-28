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

extern int generic;
extern FILE *infile,*rfile;


/* what_name - returns the name just parsed. */

char *what_name()

{
  char *ret;

  ret=last_name;
  return(ret);
}


/* skip_list - skips a line in the input file */

skip_line()

{
  if (generic) fputc('#',rfile);
  while ((!feof(infile))&&(ch!='\n')) {
    ch=fgetc(infile);
    if (generic) fputc(ch,rfile);
  }
  if (generic) fputc('\n',rfile);
  if feof(infile) ch=ETX;
  else {
    line_no++;
    syntax_report=TRUE;
    nextchar();
  }
}


/* nextchar - get the next character */

nextchar()

{
  ch=fgetc(infile);
  if (ch=='\n') {
    line_no++;
    syntax_report=TRUE;
  }
  if feof(infile) ch=ETX;
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


/* get_symbol - get the next symbol. */

get_symbol()

{
  char buf[256];
  uchar isname;
  int index,i;

  while (isspace(ch)) nextchar();
  while (ch=='#') {
    skip_line();
    while (isspace(ch)) nextchar();
  }

  switch (ch) {
  case '$':
    emit.index=DOLLAR1;
    nextchar();
    break;
  case '(':
    emit.index=LEFTPAREN1;
    nextchar();
    break;
  case ')':
    emit.index=RIGHTPAREN1;
    nextchar();
    break;
  case '[':
    emit.index=LEFTBRACKET1;
    nextchar();
    break;
  case ']':
    emit.index=RIGHTBRACKET1;
    nextchar();
    break;
  case ',':
    emit.index=COMMA1;
    nextchar();
    break;
  case '*':
    emit.index=TIMES1;
    nextchar();
    break;
  case ';':
    emit.index=SEMI1;
    nextchar();
    break;
  case '=':
    emit.index=EQUAL1;
    nextchar();
    break;
  case '^':
    emit.index=HAT1;
    nextchar();
    break;
  case '<':
    emit.index=LESS1;
    nextchar();
    if (ch=='=') {
      nextchar();
      emit.index=LEQ1;
    }
    break;
  case '>':
    emit.index=GREATER1;
    nextchar();
    break;
  case '.':
    emit.index=PERIOD1;
    nextchar();
    break;
  case '{':
    emit.index=LEFTBRACE1;
    nextchar();
    break;
  case '}':
    emit.index=RIGHTBRACE1;
    nextchar();
    break;
  case '+':
    emit.index=PLUS1;
    nextchar();
    break;
  case '-':
    nextchar();
    if (isdigit(ch)) {
      i=0;
      while (isdigit(ch)) {
	buf[i]=ch;
	i++;
	nextchar();
      }
      buf[i]=0;
      emit.index=NUMBER1;
      emit.arg=-atoi(buf);
    } else
      emit.index=MINUS1;
    break;
  case '/':
    emit.index=DIVIDE1;
    nextchar();
    break;
  default:
    if (isdigit(ch)) {
      i=0;
      while (isdigit(ch)) {
	buf[i]=ch;
	i++;
	nextchar();
      }
      buf[i]=0;
      emit.index=NUMBER1;
      emit.arg=atoi(buf);
    } else if (isalpha(ch)) {
      i=0;
      while ((isalnum(ch))||(ch=='_')||(ch=='.')) {
	buf[i]=ch;
	i++;
	nextchar();
      }
      buf[i]=0;
      search(buf,&isname,&index);
      if (isname) {
	emit.index=NAME1;
	emit.arg=index;
      } else emit.index=index;
    } else if (ch==ETX) {
      emit.index=ETX;
    } else {
      emit.index=UNKNOWN1;
      nextchar();
    }
  break;
  }
}


/* lex_init - initializes the lex module */

lex_init()

{
  int i;
  
  for (i=0; i<MAXKEY; i++) hash[i]=NULL;
  define(FALSE,"global",GLOBAL1);
  define(FALSE,"const",CONST1);
  define(FALSE,"rav",RAV1);
  define(FALSE,"array",ARRAY1);
  define(FALSE,"psi",PSI1);
  define(FALSE,"take",TAKE1);
  define(FALSE,"drop",DROP1);
  define(FALSE,"ptake",PTAKE1);
  define(FALSE,"pdrop",PDROP1);
  define(FALSE,"cat",CAT1);
  define(FALSE,"omega",OMEGA1);
  define(FALSE,"int",INT1);
  define(FALSE,"double",FLOAT1);
  define(FALSE,"for",FOR1);
  define(FALSE,"iota",IOTA1);
  define(FALSE,"shp",SHP1);
  define(FALSE,"dim",DIM1);
  define(FALSE,"red",RED1);
  define(FALSE,"tau",TAU1);
  define(FALSE,"allocate",ALLOCATE1);
  syntax_report=TRUE;
  nextchar();
}
