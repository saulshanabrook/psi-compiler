CC=gcc
CFLAGS=-g -L.
MC=mc
MFLAGS=

mc: code.o parse.o lex.o main.o dist.o extended.o libmoabase.a 
	$(CC) $(CFLAGS) -o mc lex.o main.o code.o parse.o dist.o extended.o -lmoabase -lm

libmoabase.a: psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o debug.o
	ar r libmoabase.a psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o debug.o

main.o:	main.c parse.h
	$(CC) $(CFLAGS) -c main.c

extended.o:	extended.c
	$(CC) $(CFLAGS) -c extended.c

values.o:	values.c psi.h
	$(CC) $(CFLAGS) -c values.c

scalar.o:	scalar.c psi.h values.e
	$(CC) $(CFLAGS) -c scalar.c

poly.o:	poly.c poly.h
	$(CC) $(CFLAGS) -c poly.c

lex.o:	lex.c parse.h sys.e
	$(CC) $(CFLAGS) -c lex.c

output.o:	output.c psi.h sys.e
	$(CC) $(CFLAGS) -c output.c

parse.o:	parse.c parse.h dist.h psi.h sys.e moa_func.e part.e psi.e
	$(CC) $(CFLAGS) -c parse.c

psi.o:	psi.c psi.h vect.e sys.e
	$(CC) $(CFLAGS) -c psi.c

code.o:	code.c debug.e psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c code.c

debug.o: psi.h debug.c
	$(CC) $(CFLAGS) -c debug.c

part.o:	part.c psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c part.c

dist.o:	dist.c psi.h dist.h vect.e sys.e
	$(CC) $(CFLAGS) -c dist.c

moa_func.o:	moa_func.c psi.h macros.h vect.e sys.e
	$(CC) $(CFLAGS) -c moa_func.c

vect.o:	vect.c psi.h sys.e ident.e
	$(CC) $(CFLAGS) -c vect.c

ident.o:	ident.c psi.h sys.e
	$(CC) $(CFLAGS) -c ident.c

sys.o:	sys.c psi.h
	$(CC) $(CFLAGS) -c sys.c

clean:
	rm -f *~ *.o mc *.a

ubkup:
	tar -cf ../moacompiler.tar *
	compress ../moacompiler.tar
	mv ../moacompiler.tar.Z /u3/sthib/backup

rcsbak:
	co backup.sh
	./backup.sh
	/bin/rm -f backup.sh

dos:
	mcopy -n *.c *.e *.h makefile c:/bsd/bkup

release:	mc
	cp *.c *.e *.h makefile VERSION ../../mc_release
	cp mc ../dist
	strip ../dist/mc
	cp ../doc/* ../dist
	cp ../examples/* ../dist/examples
	cd ../dist; rm -f *~
	cd ../dist/examples; make clean

lu:	lu_main.o lu.o moalib.o
	$(CC) $(CFLAGS) -o lu lu_main.o lu.o moalib.o

lu_main.o:	lu_main.c
	$(CC) $(CFLAGS) -c lu_main.c

lu.o:	lu.m
	$(MC) $(MFLAGS) lu.m lu.c
	$(CC) $(CFLAGS) -c lu.c

sunlib:	moalib.o
	rm -f libmoautil.a
	ar r libmoautil.a moalib.o
	mv -f libmoautil.a /u2/psi/dist/lib/sun

sgilib:	moalib.o
	rm -f libmoautil.a
	ar r libmoautil.a moalib.o
	mv -f libmoautil.a /u2/psi/dist/lib/sgi


moalib.o:	moalib.c
	$(CC) $(CFLAGS) -c moalib.c
