CC= cc
MC= mc.prot
CLIBS= -lsocket -lnsl
NODELIBS= -lmoanode -lmoautil
HOSTLIBS= -lmoahost -lmoautil
MFLAGS=

# Use these for Sun
CFLAGS=-g -I/usr/local/psi/include -L/usr/local/psi/lib/sun 

T1MCOUTS= test1_node.c test1_host.c
T1MCOBJS= test1_node.o test1_host.o
T1OBJS  = test1_node_main.o test1_host_main.o
T1EXES  = test1_node test1_host

T2MCOUTS= test2_node.c test2_host.c
T2MCOBJS= test2_node.o test2_host.o
T2OBJS  = test2_node_main.o test2_host_main.o
T2EXES  = test2_node test2_host

T3MCOUTS= test3_node.c test3_host.c
T3MCOBJS= test3_node.o test3_host.o
T3OBJS  = test3_node_main.o test3_host_main.o
T3EXES  = test3_node test3_host

MCOUTS= $(T1MCOUTS) $(T2MCOUTS) $(T3MCOUTS)
MCOBJS= $(T1MCOBJS) $(T2MCOBJS) $(T3MCOBJS)
OBJS  = $(T1OBJS) $(T2OBJS) $(T3OBJS)
EXES  = $(T1EXES) $(T1EXES) $(T1EXES)

all:   $(T1EXES) $(T2EXES) $(T3EXES) 
test1: $(T1EXES)
test2: $(T2EXES)
test3: $(T3EXES)

test1_host: test1_host.o test1_host_main.o
	$(CC) $(CFLAGS) test1_host.o test1_host_main.o -o test1_host $(CLIBS) $(HOSTLIBS)

test1_node: test1_node.o test1_node_main.o
	$(CC) $(CFLAGS) -o test1_node test1_node.o test1_node_main.o $(CLIBS) $(NODELIBS)

test1_node_main.o: test1_node_main.c
	$(CC) $(CFLAGS) -c test1_node_main.c

test1_host_main.o: test1_host_main.c
	$(CC) $(CFLAGS) -c test1_host_main.c

test1_node.o: test1_node.c
	$(CC) $(CFLAGS) -c test1_node.c

test1_host.o: test1_host.c
	$(CC) $(CFLAGS) -c test1_host.c

test1_node.c test1_host.c : test1.m
	$(MC) test1.m -o test1_node.c

test2_host: test2_host.o test2_host_main.o
	$(CC) $(CFLAGS) -o test2_host test2_host.o test2_host_main.o $(CLIBS) $(HOSTLIBS)

test2_node: test2_node.o test2_node_main.o
	$(CC) $(CFLAGS) -o test2_node test2_node.o test2_node_main.o $(CLIBS) $(NODELIBS)

test2_node_main.o: test2_node_main.c
	$(CC) $(CFLAGS) -c test2_node_main.c

test2_host_main.o: test2_host_main.c
	$(CC) $(CFLAGS) -c test2_host_main.c

test2_node.o: test2_node.c
	$(CC) $(CFLAGS) -c test2_node.c

test2_host.o: test2_host.c
	$(CC) $(CFLAGS) -c test2_host.c

test2_node.c test2_host.c : test2.m
	$(MC) test2.m -o test2_node.c

test3_host: test3_host.o test3_host_main.o
	$(CC) $(CFLAGS) -o test3_host test3_host.o test3_host_main.o $(CLIBS) $(HOSTLIBS)

test3_node: test3_node.o test3_node_main.o
	$(CC) $(CFLAGS) -o test3_node test3_node.o test3_node_main.o $(CLIBS) $(NODELIBS)

test3_node_main.o: test3_node_main.c
	$(CC) $(CFLAGS) -c test3_node_main.c

test3_host_main.o: test3_host_main.c
	$(CC) $(CFLAGS) -c test3_host_main.c

test3_node.o: test3_node.c
	$(CC) $(CFLAGS) -c test3_node.c

test3_host.o: test3_host.c
	$(CC) $(CFLAGS) -c test3_host.c

test3_node.c test3_host.c : test3.m
	$(MC) test3.m -o test3_node.c

clean:
	rm -f *.o $(MCOUTS) $(EXES)
t1clean:
	rm -f $(T1MCOUTS) $(T1EXES) $(T1OBJS) $(T1MCOBJS)

t2clean:
	rm -f $(T2MCOUTS) $(T2EXES) $(T2OBJS) $(T2MCOBJS)

t3clean:
	rm -f $(T3MCOUTS) $(T3EXES) $(T3OBJS) $(T3MCOBJS)
