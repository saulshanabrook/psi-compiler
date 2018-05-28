CC=cc
FORT=f90 
MC=../mcsrc/mc
BASE_PATH=..
CFLAGS=-g 
FFLAGS=-free
CLIBS = -lf90
CINCLUDES = -L/usr/local/lib/f90 -I/usr/local/lib/f90 -L/usr/local/lib  

all:    ptd doerror ptde.dat

ptde.dat: ptdm.dat 
	doerror ptdm.dat ptdf.dat ptde.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

ptdm.dat: ptd 
	ptd ptdm.dat ptdf.dat

ptd: ptdmain.o ptdf.o ptdm.o
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -o ptd ptdmain.o ptdf.o ptdm.o 

ptdmain.o: ptdmain.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c ptdmain.f

ptdf.o: ptdf.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c ptdf.f

ptdm.o: ptdm.f
	$(FORT) $(FFLAGS) $(CFLAGS) $(CINCLUDES) -c ptdm.f

ptdm.f: ptdm.m
	$(MC) ptdm.m -o ptdm.f

clean:
	rm -f ptdf.o ptdm.o ptdmain.o ptdm.dat ptdf.dat ptde.dat ptdm.f ptd

