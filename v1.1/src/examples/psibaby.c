#include <stdlib.h>
#include "moalib.e"

main()

{
  double *offset0;
  int i0;
  double *shift;
  double _frog[]={5.000000};
  double _x[1];
  double _goat[10];
  double _duck[10];

/*******
goat=x drop (x take duck)
********/

  shift=_goat+0;
  offset0=_duck+((((int) _x[0])+10)*(((((int) _x[0]))<0))+(((int) _x[0]))*(((((int) _x[0]))>0)));
  for (i0=0; i0<((abs(((int) _x[0])))-(abs(((int) _x[0])))); i0++) {
    *(shift)= *(offset0);
    offset0+=1;
    shift+=1;
  }


/*******
goat=frog drop (frog take duck)
********/



/*******
fish=<5.000000> drop (<5.000000> take duck)
********/



}


