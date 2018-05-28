CC=gcc
CFLAGS=-g -L.
MC=mcpgi
MFLAGS=
DIST=$(HOME)/dist
SRC=$(HOME)/Compiler/mc/src
#RELEASE_SRC=$(HOME)/Compiler/mc/release

mcpgi: code.o parse.o lex.o main.o dist.o extended.o libmoabase.a 
	$(CC) $(CFLAGS) -o mcpgi lex.o main.o code.o parse.o dist.o extended.o -lmoabase -lm

libmoabase.a: psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o 
	ar r libmoabase.a psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o 

main.o:	main.c parse.h
	$(CC) $(CFLAGS) -c main.c

extended.o: extended.c
	$(CC) $(CFLAGS) -c extended.c

values.o: values.c psi.h
	$(CC) $(CFLAGS) -c values.c

scalar.o: scalar.c psi.h values.e
	$(CC) $(CFLAGS) -c scalar.c

poly.o:	poly.c poly.h
	$(CC) $(CFLAGS) -c poly.c

lex.o:	lex.c parse.h sys.e
	$(CC) $(CFLAGS) -c lex.c

output.o: output.c psi.h sys.e
	$(CC) $(CFLAGS) -c output.c

parse.o: parse.c parse.h dist.h psi.h sys.e moa_func.e part.e psi.e
	$(CC) $(CFLAGS) -c parse.c

psi.o:	psi.c psi.h vect.e sys.e
	$(CC) $(CFLAGS) -c psi.c

code.o: code.c psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c code.c

part.o:	part.c psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c part.c

dist.o:	dist.c psi.h dist.h vect.e sys.e
	$(CC) $(CFLAGS) -c dist.c

moa_func.o: moa_func.c psi.h macros.h vect.e sys.e
	$(CC) $(CFLAGS) -c moa_func.c

vect.o:	vect.c psi.h sys.e ident.e
	$(CC) $(CFLAGS) -c vect.c

ident.o: ident.c psi.h sys.e
	$(CC) $(CFLAGS) -c ident.c

sys.o:	sys.c psi.h
	$(CC) $(CFLAGS) -c sys.c

clean:
	rm -f *~ *.o mcpgi *.a

rcsbak:
	co backup.sh
	./backup.sh
	/bin/rm -f backup.sh

dos:
	mcopy -n *.c *.e *.h makefile c:/bsd/bkup


lu:	lu_main.o lu.o moalib.o
	$(CC) $(CFLAGS) -o lu lu_main.o lu.o moalib.o

lu_main.o:	lu_main.c
	$(CC) $(CFLAGS) -c lu_main.c

lu.o:	lu.m
	$(MC) $(MFLAGS) lu.m lu.c
	$(CC) $(CFLAGS) -c lu.c

lib:	moalib.o
	rm -f libmoautil.a
	ar r libmoautil.a moalib.o
	mv -f libmoautil.a $(HOME)/dist/lib/$(PLATFORM)

#sun4lib:	moalib.o
#	rm -f libmoautil.a
#	ar r libmoautil.a moalib.o
#	mv -f libmoautil.a $(HOME)/dist/lib/$(PLATFORM)

#sgilib:	moalib.o
#	rm -f libmoautil.a
#	ar r libmoautil.a moalib.o
#	mv -f libmoautil.a $(HOME)/dist/lib/sgi


moalib.o:	moalib.c
	$(CC) $(CFLAGS) -c moalib.c
