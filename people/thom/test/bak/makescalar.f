CC=cc
FORT=f90 
MC=../mcsrc/mc
BASE_PATH=..
CFLAGS=-g 
FFLAGS=-free
CLIBS = -lf90
CINCLUDES = -L/usr/local/lib/f90 -I/usr/local/lib/f90 -L/usr/local/lib  

all:    scalar doerror scalare.dat

scalare.dat: scalarm.dat 
	doerror scalarm.dat scalarf.dat scalare.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

scalarm.dat: scalar 
	scalar scalarm.dat scalarf.dat

scalar: scalarmain.o scalarf.o scalarm.o
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -o scalar scalarmain.o scalarf.o scalarm.o 

scalarmain.o: scalarmain.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c scalarmain.f

scalarf.o: scalarf.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c scalarf.f

scalarm.o: scalarm.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c scalarm.f

scalarm.f: scalarm.m
	$(MC) scalarm.m -o scalarm.f

clean:
	rm -f scalarf.o scalarm.o scalarmain.o scalarm.dat scalarf.dat scalare.dat scalarm.f scalar

