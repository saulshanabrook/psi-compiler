#include <stdio.h>
#include <stdlib.h>

extern int check_reserved (char *name);

main ()
{
  printf ("END: %d\n", check_reserved("END"));
  printf ("SELECTED_REAL_KIND: %d\n", check_reserved("SELECTED_REAL_KIND"));
  printf ("NUMBER_OF_PROCESSORS: %d\n", check_reserved("NUMBER_OF_PROCESSORS"));
  printf ("HPF_DISTRIBUTION: %d\n", check_reserved("HPF_DISTRIBUTION"));
}
