CC=cc
FC=f90
HPFM=../hpfm

CCOPTIONS =-g 
CLIBPATHS= -L../ -L/software/all/mpi/lib/solaris/ch_p4 -L/usr/local/psi/lib/sun -L/software/sun/nag/NAGWare_f90/lib
CLIBRARIES= -lmoautil -lsocket -lnsl -lthread -lmpi -lm -lf90
INCLUDES=-I../ -I/usr/include -I/software/all/mpi/include -I/usr/local/psi/include -I/software/sun/nag/NAGWare_f90/lib
 
CFLAGS=$(CCOPTIONS) $(INCLUDES) $(OTHERINCLUDES)
CLIBS=$(CLIBPATHS) $(CLIBRARIES)
FFLAGS=$(CFLAGS)
FLIBS=$(CLIBS)

all: tom5

tom5: tom5.o tom5_main.o mpistuff
	$(CC) $(CFLAGS) tom5_main.o tom5.o ../mpinet.o ../moalib.o ../mpifunc.o -o tom5 $(CLIBS)

tom5.o: tom5.f90
	$(FC) $(FFLAGS) -g -c tom5.f90

tom5_main.o: tom5_main.c
	$(FC) $(FFLAGS) -c tom5_main.c

tom5.f90: tom5.hpf $(HPFM)
	$(HPFM) tom5.hpf -o tom5.f90

mpistuff: 
	cd ..; make mpibase

clean:
	rm -f tom5.o tom5_main.o tom5
