CC=cc
FC=f90
BASE_PATH=..
CFLAGS=-g -I../../../pccts/h -I$(BASE_PATH) -L$(BASE_PATH)
FFLAGS=-g

all:	hpfm

hpfm: main.o hpfm.o sym.o err.o hpfm_sys.o code.o dist.o compat.o hpfm_func.o moabase
	$(CC) $(CFLAGS) -o hpfm main.o sym.o scan.o hpfm.o err.o hpfm_sys.o code.o dist.o compat.o hpfm_func.o -lmoabase -lm

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

hpfm_sys.o:	hpfm_sys.c
	$(CC) $(CFLAGS) -c hpfm_sys.c

sym.o: sym.c sym.h
	$(CC) $(CFLAGS) -c sym.c

code.o: code.c $(BASE_PATH)/sys.h $(BASE_PATH)/psi.h $(BASE_PATH)/dist.h
	$(CC) $(CFLAGS) -c code.c

dist.o: dist.c $(BASE_PATH)/psi.h $(BASE_PATH)/dist.h $(BASE_PATH)/sys.h
	$(CC) $(CFLAGS) -c dist.c

compat.o: compat.c f90.h $(BASE_PATH)/sys.h $(BASE_PATH)/psi.h
	$(CC) $(CFLAGS) -c compat.c

hpfm_func.o: hpfm_func.c f90.h $(BASE_PATH)/sys.h $(BASE_PATH)/psi.h
	$(CC) $(CFLAGS) -c hpfm_func.c

scan.o: scan.c $(BASE_PATH)/psi.h $(BASE_PATH)/dist.h $(BASE_PATH)/sys.h
	$(CC) $(CFLAGS) -c scan.c

scan.c:	parser.dlg
	dlg -C2 parser.dlg scan.c

mpibase: mpinet.o mpifunc.o

mpinet.o: mpinet.f90
	$(FC) $(FFLAGS) -fixed  -I/software/all/mpi/include -c mpinet.f90 $(FLIBS)

mpifunc.o: mpifunc.c
	$(CC) $(CFLAGS) -c mpifunc.c $(CLIBS)

hpfm.c err.c parser.dlg: hpfm.g
	antlr -ga -k 4 hpfm.g

moabase:
	cd $(BASE_PATH); make libmoabase.a

test:
	hpfm test1.hpf -o test1.f90
	hpfm test2.hpf -o test2.f90
	hpfm test3.hpf -o test3.f90
	hpfm test4.hpf -o test4.f90

heat:
	hpfm heat.hpf -o heat.f90
	f90 heat.f90 heat_main.f90 -o heat

mm:
	hpfm mm.hpf -o mm.f90
	f90 mm.f90 mm_main.f90 -o mm

bkup:
	tar -cvf /u3/sthib/tmp/hpfm.tar *.c *.h *.e *.g makefile *.hpf
	compress /u3/sthib/tmp/hpfm.tar

clean:
	rm -f *.o 
	rm -f test1.f90 test2.f90 test3.f90 test4.f90 heat.f90 mm.f90 mm heat
	cd $(BASE_PATH); make clean
