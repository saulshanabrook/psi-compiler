CC=cc
MC=../mcorg/mc
BASE_PATH=..
CFLAGS=-g 

all:    ptd doerror ptde.dat

ptd: ptdmain.o ptdc.o ptdm.o
	$(CC) $(CFLAGS) -o ptd ptdmain.o ptdc.o ptdm.o 

ptde.dat: ptdm.dat ptdc.dat
	doerror ptdm.dat ptdc.dat ptde.dat 5

doerror: error.c
	$(CC) $(CFLAGS) error.c -o doerror

ptdm.dat ptdc.dat:
	ptd ptdm.dat ptdc.dat

ptdmain.o: ptdmain.c
	$(CC) $(CFLAGS) -c ptdmain.c

ptdc.o: ptdc.c
	$(CC) $(CFLAGS) -c ptdc.c

ptdm.o: ptdm.c
	$(CC) -c ptdm.c

ptdm.c: ptdm.m
	$(MC) ptdm.m -o ptdm.c

clean:
	rm -f ptdc.o ptdm.o ptdmain.o ptdm.dat ptdc.dat ptde.dat ptdm.c ptd

