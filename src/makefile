CC=clang
CFLAGS=-g -L. -Wno-everything -DDEBUG=0
MC=mc
MFLAGS=
DIST=$(HOME)/dist
SRC=$(HOME)/Compiler/mc/src
RELEASE_SRC=$(HOME)/Compiler/mc/release
EMCC=emcc -g -Wno-everything

mc: code.o parse.o lex.o main.o dist.o extended.o libmoabase.a 
	$(CC) $(CFLAGS) -o mc lex.o main.o code.o parse.o dist.o extended.o -lmoabase -lm

mc.js: code.bc parse.bc lex.bc main.bc dist.bc extended.bc moabase.bc mainJS.bc
	$(EMCC) -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall"]' -o $@ $^

libmoabase.a: psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o 
	ar r libmoabase.a psi.o moa_func.o vect.o ident.o sys.o part.o scalar.o poly.o values.o output.o 

moabase.bc: psi.bc moa_func.bc vect.bc ident.bc sys.bc part.bc scalar.bc poly.bc values.bc output.bc
	$(EMCC) -o $@ $^

main.o:	main.c parse.h
	$(CC) $(CFLAGS) -c main.c

main.bc: main.c
	$(EMCC) -o $@ $^

mainJS.bc: mainJS.c
	$(EMCC) -o $@ $^

extended.o: extended.c
	$(CC) $(CFLAGS) -c extended.c

extended.bc: extended.c
	$(EMCC) -o $@ $^

values.o: values.c psi.h
	$(CC) $(CFLAGS) -c values.c

values.bc: values.c
	$(EMCC) -o $@ $^

scalar.o: scalar.c psi.h values.e
	$(CC) $(CFLAGS) -c scalar.c

scalar.bc: scalar.c
	$(EMCC) -o $@ $^

poly.o:	poly.c poly.h
	$(CC) $(CFLAGS) -c poly.c

poly.bc: poly.c
	$(EMCC) -o $@ $^

lex.o:	lex.c parse.h sys.e
	$(CC) $(CFLAGS) -c lex.c

lex.bc: lex.c
	$(EMCC) -o $@ $^

output.o: output.c psi.h sys.e
	$(CC) $(CFLAGS) -c output.c

output.bc: output.c
	$(EMCC) -o $@ $^

parse.o: parse.c parse.h dist.h psi.h sys.e moa_func.e part.e psi.e
	$(CC) $(CFLAGS) -c parse.c

parse.bc: parse.c
	$(EMCC) -o $@ $^

psi.o:	psi.c psi.h vect.e sys.e
	$(CC) $(CFLAGS) -c psi.c

psi.bc: psi.c
	$(EMCC) -o $@ $^

code.o: code.c psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c code.c

code.bc: code.c
	$(EMCC) -o $@ $^

part.o:	part.c psi.h dist.h vect.e ident.e sys.e
	$(CC) $(CFLAGS) -c part.c

part.bc: part.c
	$(EMCC) -o $@ $^

dist.o:	dist.c psi.h dist.h vect.e sys.e
	$(CC) $(CFLAGS) -c dist.c

dist.bc: dist.c
	$(EMCC) -o $@ $^

moa_func.o: moa_func.c psi.h macros.h vect.e sys.e
	$(CC) $(CFLAGS) -c moa_func.c

moa_func.bc: moa_func.c
	$(EMCC) -o $@ $^

vect.o:	vect.c psi.h sys.e ident.e
	$(CC) $(CFLAGS) -c vect.c

vect.bc: vect.c
	$(EMCC) -o $@ $^

ident.o: ident.c psi.h sys.e
	$(CC) $(CFLAGS) -c ident.c

ident.bc: ident.c
	$(EMCC) -o $@ $^

sys.o:	sys.c psi.h
	$(CC) $(CFLAGS) -c sys.c

sys.bc: sys.c
	$(EMCC) -o $@ $^

clean:
	rm -f *~ *.o mc *.a *.bc *.js

rcsbak:
	co backup.sh
	./backup.sh
	/bin/rm -f backup.sh

dos:
	mcopy -n *.c *.e *.h makefile c:/bsd/bkup

release:	mc
	tar cvf $(RELEASE_SRC)/mc.`date '+%y%m%d'`.tar *.c *.e *.h makefile VERSION 
	cp mc $(DIST)/bin/$(PLATFORM)
	strip $(DIST)/bin/$(PLATFORM)/mc
	#cp $(SRC)/doc/* $(DIST)/doc
	echo "be sure to copy the documentation to the dist dir!!"
	cp $(SRC)/examples/* $(DIST)/examples/general
	cd $(DIST); rm -f *~
	cd $(DIST)/examples/general; make clean

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
