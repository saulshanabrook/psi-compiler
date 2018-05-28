CC=cc
MC=../../src/mc
BASE_PATH=..
CFLAGS=-g 

all:    omega doerror omegae.dat

omega: omegamain.o omegac.o omegam.o moalib.o
	$(CC) $(CFLAGS) -o omega omegamain.o omegac.o omegam.o moalib.o

omegae.dat: omegam.dat 
	doerror omegam.dat omegac.dat omegae.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

omegam.dat:
	omega omegam.dat omegac.dat

omegamain.o: omegamain.c
	$(CC) $(CFLAGS) -c omegamain.c

omegac.o: omegac.c
	$(CC) $(CFLAGS) -c omegac.c

omegam.o: omegam.c moalib.e
	$(CC) -c omegam.c

moalib.o: moalib.c
	$(CC) -c moalib.c

omegam.c: omegam.m
	$(MC) omegam.m -o omegam.c

clean:
	rm -f omegac.o omegam.o omegamain.o omegam.dat omegac.dat omegae.dat omegam.c omega

