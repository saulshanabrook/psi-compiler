CC=cc
MC=../mcorg/mc
BASE_PATH=..
CFLAGS=-g 

all:    ops doerror opse.dat

ops: opsmain.o opsc.o opsm.o
	$(CC) $(CFLAGS) -o ops opsmain.o opsc.o opsm.o 

opse.dat: opsm.dat opsc.dat
	doerror opsm.dat opsc.dat opse.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

opsm.dat opsc.dat:
	ops opsm.dat opsc.dat

opsmain.o: opsmain.c
	$(CC) $(CFLAGS) -c opsmain.c

opsc.o: opsc.c
	$(CC) $(CFLAGS) -c opsc.c

opsm.o: opsm.c
	$(CC) -c opsm.c

opsm.c: opsm.m
	$(MC) opsm.m -o opsm.c

clean:
	rm -f *.o *.dat doerror ops

