CC=gcc
CFLAGS=-g

mc: psi.o moa_func.o vect.o ident.o sys.o parse.o lex.o main.o
	$(CC) $(CFLAGS) -o mc psi.o moa_func.o vect.o ident.o sys.o parse.o lex.o main.o -lm

main.o:	main.c parse.h
	$(CC) $(CFLAGS) -c main.c

lex.o:	lex.c parse.h sys.e
	$(CC) $(CFLAGS) -c lex.c

parse.o:	parse.c psi.h sys.e moa_func.e psi.e
	$(CC) $(CFLAGS) -c parse.c

psi.o:	psi.c psi.h vect.e sys.e
	$(CC) $(CFLAGS) -c psi.c

moa_func.o:	moa_func.c psi.h vect.e sys.e
	$(CC) $(CFLAGS) -c moa_func.c

vect.o:	vect.c psi.h sys.e ident.e
	$(CC) $(CFLAGS) -c vect.c

ident.o:	ident.c psi.h sys.e
	$(CC) $(CFLAGS) -c ident.c

sys.o:	sys.c psi.h
	$(CC) $(CFLAGS) -c sys.c

clean:
	rm -f *~
	rm -f *.o
	rm -f mc

bkup:
	cp *.c *.e *.h makefile ../../bkup

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

moalib.o:	moalib.c
	$(CC) $(CFLAGS) -c moalib.c
