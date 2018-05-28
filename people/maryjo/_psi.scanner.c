#include <stdio.h>

#include "psi.h"
#include "ops.h"
#include "_psi.tab.h"

#define MAXRW 19
#define MAXRWLEN 7 
extern int line_num;
#ifdef DEBUG
  extern FILE *dinterp;
#endif
char rwnames[MAXRW][MAXRWLEN] = {
	"for",
	"int",
	"psi",
	"cat",
	"dim",
	"tau",
	"rav",
	"red",
	"take",
	"drop",
	"iota",
	"pdrop",
	"shape",
	"ptake",
	"float",
	"array",
	"const",
	"omega",
	"global"
};

int rwtokens[MAXRW] = {
	FOR1,
	INT1,
	PSI1,
	CAT1,
	DIM1,
	TAU1,
	RAV1,
	RED1,
	TAKE1,
	DROP1,
	IOTA1,
	PDROP1,
	SHP1,
	PTAKE1,
	FLOAT1,
	ARRAY1,
	CONST1,
	OMEGA1,
	GLOBAL1
};

int rwidxtab [8] = { 0, 0, 0, 0, 8, 11, 18 ,19};

int check_reserved (char *name)
{
  int length;
  int i, j;

  length = strlen (name);
  if (length >= MAXRWLEN) {
    return NAME1;
  } else {
    for (i = rwidxtab[length], j = rwidxtab[length+1];
      (i < j) && (strcmp (rwnames[i], name) != 0); i++) {}
    #ifdef DEBUG
      fprintf(dinterp, "\t-- %d : %s>",line_num,name);
    #endif
    if (i == j) {
      #ifdef DEBUG
	fprintf(dinterp, "\t-- Name 1\n");
      #endif
      return NAME1;
    } else {
      #ifdef DEBUG
	fprintf(dinterp, "\t-- Token %d (%d)\n",rwtokens[i],i);
      #endif
      return (rwtokens[i]);
    }
  }
}
