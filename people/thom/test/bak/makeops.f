CC=cc
FORT=f90 
MC=../mcsrc/mc
BASE_PATH=..
CFLAGS=-g 
FFLAGS=-free
CLIBS = -lf90
CINCLUDES = -L/usr/local/lib/f90 -I/usr/local/lib/f90 -L/usr/local/lib  

all:    ops doerror opse.dat

opse.dat: opsm.dat 
	doerror opsm.dat opsf.dat opse.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

opsm.dat: ops 
	ops opsm.dat opsf.dat

ops: opsmain.o opsf.o opsm.o
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -o ops opsmain.o opsf.o opsm.o 

opsmain.o: opsmain.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c opsmain.f

opsf.o: opsf.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c opsf.f

opsm.o: opsm.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c opsm.f

opsm.f: opsm.m
	$(MC) opsm.m -o opsm.f

clean:
	rm -f opsf.o opsm.o opsmain.o opsm.dat opsf.dat opse.dat opsm.f ops

