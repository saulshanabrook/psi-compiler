/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   main.c - provides the user interface to the compiler

   6/93 - v0.1 Scott Thibault
   7/93 - v0.2 Scott Thibault

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#ifndef NEXT
#include <unistd.h>
#endif
#include "psi.h"
#include "parse.h"
#include "dist.h"

#include "dist.e"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

extern emit_t emit;

FILE *infile,*cfile,*tfile,*vfile,*hostfile,*hfile,*rfile;
int prove=FALSE;
int generic=FALSE;

void cleanup()
{
  fclose(infile);
  fclose(cfile);
  unlink("temp$$$$.moa");
  unlink("vtemp$$$$.moa");
  unlink("htemp$$$$.moa");
  unlink("junk$$$$.moa");
}


psi_main(int argc, char *argv[])
{
  int arg;

  if (argc<2) {
    printf("usage: %s <source> [-o output] [-r filename]\n",argv[0]);
    exit(0);
  }

  if ((infile=fopen(argv[1],"rt"))==NULL) {
    printf("Cannot open %s.\n",argv[1]);
    exit(0);
  }
  
  /* set defaults before getting options */
  cfile=NULL;
  prove=FALSE;

  arg=2;
  while (arg<argc) {
    if (strcmp(argv[arg],"-h")==0) {         /* host file name specified */
      arg++;
      host=TRUE;
      host_name=argv[arg];
      if ((hostfile=fopen(host_name,"wt"))==NULL) {
	fatal("Could'nt open host output file");
      }
      fprintf(hostfile,"#include \"moalib.e\"\n\n");
    } else if (strcmp(argv[arg],"-o")==0) {  /* output file name specified */
      arg++;
      if (arg<argc) {
	if ((cfile=fopen(argv[arg],"wt"))==NULL) {
	  printf("Cannot create %s.\n",argv[arg]);
	  exit(0);
	}
      } else cfile=stdout;
    } else if (strcmp(argv[arg],"-r")==0) {  /* prove file name specified */
      arg++;
      prove=TRUE;
      generic=FALSE;
      if (arg<argc) {
	if ((rfile=fopen(argv[arg],"wt"))==NULL) {
	  printf("Cannot create %s.\n",argv[arg]);
	  exit(0);
	}
      } else rfile=stdout;
    } else if (strcmp(argv[arg],"-g")==0) {  /* generic file name specified */
      arg++;
      generic=TRUE;
      if (arg<argc) {
	if ((rfile=fopen(argv[arg],"wt"))==NULL) {
	  printf("Cannot create %s.\n",argv[arg]);
	  exit(0);
	}
      } else rfile=stdout;
    } else {
      printf("usage: %s <source> [-o output] [-r filename]\n",argv[0]);
      exit(0);
    }
    arg++;
  }

  if (cfile==NULL) {
    if ((cfile=fopen("junk$$$$.moa","wt"))==NULL) {
      printf("Cannot open temporary file.\n");
      exit(0);
    }
  }

  puts("MOA Compiler version 0.4 (PSI Compiler Library v0.4)");
  puts("Copyright (c) 1993 Lenore R. Mullin\n");
 
  /* call initialization routines */ 
/*
  atexit(cleanup);
*/
  mem_init();
  lex_init();
  psi_init();
  dist_init();
  get_symbol();
  /* compile the program */
  programx();

  exit(0);
}
