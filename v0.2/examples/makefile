CC=cc
CFLAGS=-g
MC=../mc_next
MFLAGS=

all: ex1.c ex2.c ex3.c ex4.c lu

ex1.c:	ex1.m
	$(MC) $(MFLAGS) ex1.m ex1.c

ex2.c:	ex2.m
	$(MC) $(MFLAGS) ex2.m ex2.c

ex3.c:	ex3.m
	$(MC) $(MFLAGS) ex3.m ex3.c

ex4.c:	ex4.m
	$(MC) $(MFLAGS) ex4.m ex4.c

lu:	lu_main.o lu.o moalib.o
	$(CC) $(CFLAGS) -o lu lu_main.o lu.o moalib.o

lu_main.o:	lu_main.c
	$(CC) $(CFLAGS) -c lu_main.c

lu.o:	lu.m
	$(MC) $(MFLAGS) lu.m lu.c
	$(CC) $(CFLAGS) -c lu.c

moalib.o:	moalib.c
	$(CC) $(CFLAGS) -c moalib.c

clean:
	rm -f *.o
	rm -f *~
	rm -f lu lu.c ex1.c ex2.c ex3.c ex4.c
