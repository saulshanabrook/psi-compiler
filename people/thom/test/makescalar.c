CC=cc
MC=../../src/mc
BASE_PATH=..
CFLAGS=-g 

all:    scalar doerror scalare.dat

scalar: scalarmain.o scalarc.o scalarm.o
	$(CC) $(CFLAGS) -o scalar scalarmain.o scalarc.o scalarm.o 

scalare.dat: scalarm.dat 
	doerror scalarm.dat scalarc.dat scalare.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

scalarm.dat:
	scalar scalarm.dat scalarc.dat

scalarmain.o: scalarmain.c
	$(CC) $(CFLAGS) -c scalarmain.c

scalarc.o: scalarc.c
	$(CC) $(CFLAGS) -c scalarc.c

scalarm.o: scalarm.c
	$(CC) -c scalarm.c

scalarm.c: scalarm.m
	$(MC) scalarm.m -o scalarm.c

clean:
	rm -f scalarc.o scalarm.o scalarmain.o scalarm.dat scalarc.dat scalare.dat scalarm.c scalar

