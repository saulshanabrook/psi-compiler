/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#ifndef NEXT
#include <unistd.h>
#endif
#include "parse.h"

extern emit_t emit;

FILE *infile,*cfile,*tfile,*vfile,*afile;

void cleanup()

{
  fclose(infile);
  fclose(cfile);
  fclose(tfile);
  unlink("temp$$$$.moa");
  fclose(vfile);
  unlink("vtemp$$$$.moa");
}


main(int argc, char *argv[])

{
  if ((argc<2)||(argc>3)) {
    printf("usage: %s <source> [output]\n",argv[0]);
    exit(0);
  }
  
  if ((infile=fopen(argv[1],"rt"))==NULL) {
    printf("Cannot open %s.\n",argv[1]);
    exit(0);
  }

  if (argc==3) {
    if ((cfile=fopen(argv[2],"wt"))==NULL) {
      printf("Cannot create %s.\n",argv[2]);
      exit(0);
    } 
  } else cfile=stdout;

/*
  puts("MOA Compiler version 0.1");
  puts("Copyright (c) 1993 University of Missouri-Rolla");
*/
  
  mem_init();
  lex_init();
  psi_init();
  get_symbol();
  programx();

  cleanup();
  exit(0);
}
