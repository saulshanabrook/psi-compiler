F90=f90
HPFM=../hpfm

all:	test heat mm

test:
	$(HPFM) test1.hpf -o test1.f90
	$(HPFM) test2.hpf -o test2.f90
	$(HPFM) test3.hpf -o test3.f90
	$(HPFM) test4.hpf -o test4.f90

heat:
	$(HPFM) heat.hpf -o heat.f90
	$(F90) heat.f90 heat_main.f90 -o heat

mm:
	$(HPFM) mm.hpf -o mm.f90
	$(F90) mm.f90 mm_main.f90 -o mm

clean:
	rm -f *.o
	rm -f test1.f90 test2.f90 test3.f90 test4.f90 heat.f90 mm.f90 mm heat
