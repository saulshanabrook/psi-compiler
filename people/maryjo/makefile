CC=gcc
LEX=flex
YACC=bison

LFLAGS=
YFLAGS= --defines --verbose

#  At UMR
#  BASE_PATH = /u2/psi/Compiler/mc/src
#
#  Up at Albany
BASE_PATH = /cook/p/psi/Compiler/mc/src
#
CCREALOPTIONS = -O2
CLIBPATHS= -L. -L/usr/lib -L/usr/local/lib -L$(BASE_PATH)
CLIBRARIES= -lmoabase -lfl -lm
INCLUDES=-I. -I/usr/include -I$(BASE_PATH)

CCDEBUGOPTIONS = -g -DDEBUG
CDEBUGLIBRARIES = -lmoabase -lfl -lm

CFLAGS=$(CCDEBUGOPTIONS) $(INCLUDES) $(OTHERINCLUDES)
CLIBS=$(CLIBPATHS) $(CDEBUGLIBRARIES)
COUT = _mc

$(COUT): lex.yy.o _psi.tab.o _psi.scanner.o _psi.sem.o code.o main.o dist.o extended.o moabase
	$(CC) $(CFLAGS) -o $(COUT) lex.yy.o _psi.tab.o _psi.scanner.o _psi.sem.o $(BASE_PATH)/code.o main.o $(BASE_PATH)/dist.o $(BASE_PATH)/extended.o $(BASE_PATH)/part.o $(CLIBS) 

lex.yy.o: lex.yy.c _psi.tab.c
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: _psi.lex
	$(LEX) $(LFLAGS) _psi.lex

_psi.tab.o : _psi.tab.c
	$(CC) $(CFLAGS) -c _psi.tab.c

_psi.tab.c: _psi.y
	$(YACC) $(YFLAGS) _psi.y

_psi.scanner.o : _psi.scanner.c
	$(CC) $(CFLAGS) -c _psi.scanner.c

_psi.sem.o : _psi.sem.c
	$(CC) $(CFLAGS) -c _psi.sem.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

extended.o:
	cd $(BASE_PATH); make extended.o

code.o:
	cd $(BASE_PATH); make code.o

dist.o:
	cd $(BASE_PATH); make dist.o

moabase:
	cd $(BASE_PATH); make libmoabase.a

clean: 
	rm *.o _mc _psi.tab.c lex.yy.c
