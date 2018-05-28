CC=gcc
CFLAGS=-g -I../
#HOME=/home/grads1/psi

maketrf:	maketrf.c
	$(CC) $(CFLAGS) -o maketrf maketrf.c

sun5lib:	node_lib.o host_lib.o
	rm -f libmoanode.a
	ar r libmoanode.a node_lib.o
	mv -f libmoanode.a $(HOME)/dist/lib/sunos5
	rm -f libmoahost.a
	ar r libmoahost.a host_lib.o
	mv -f libmoahost.a $(HOME)/dist/lib/sunos5

sun4lib:	node_lib.o host_lib.o
	rm -f libmoanode.a
	ar r libmoanode.a node_lib.o
	mv -f libmoanode.a $(HOME)/dist/lib/sunos4
	rm -f libmoahost.a
	ar r libmoahost.a host_lib.o
	mv -f libmoahost.a $(HOME)/dist/lib/sunos4

sgilib:	node_lib.o host_lib.o
	rm -f libmoanode.a
	ar r libmoanode.a node_lib.o
	mv -f libmoanode.a $(HOME)/dist/lib/sgi
	rm -f libmoahost.a
	ar r libmoahost.a host_lib.o
	mv -f libmoahost.a $(HOME)/dist/lib/sgi

node:	heat.o main.o ../moalib.o node_lib.o
	$(CC) $(CFLAGS) -o node heat.o main.o moalib.o node_lib.o -lm -lsocket -lnsl

heat.o:	heat.c
	$(CC) $(CFLAGS) -c heat.c

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

moalib.o:	../moalib.c
	$(CC) $(CFLAGS) -c ../moalib.c

host:	host_heat.o host_main.o host_lib.o moalib.o
	$(CC) $(CFLAGS) -o host host_heat.o host_main.o host_lib.o moalib.o -lm -lsocket -lnsl

host_heat.o:	host_heat.c
	$(CC) $(CFLAGS) -c host_heat.c

host_main.o:	host_main.c
	$(CC) $(CFLAGS) -c host_main.c

node_lib.o:	node_lib.c ap.h
	$(CC) $(CFLAGS) -c node_lib.c

host_lib.o:	host_lib.c ap.h
	$(CC) $(CFLAGS) -c host_lib.c
 
clean:
	rm -f *.o *~ node host
