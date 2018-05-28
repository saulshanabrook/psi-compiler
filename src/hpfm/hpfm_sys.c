/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.
   
   hpfm_sys - system utility functions specific to the hpfm front/back ends

   5/94 - Scott Thibault - created

*/

#include "../psi.h"
#include "../sys.h"

extern ident_t const1_i;
extern vect_t const1_v;


unmark_statics()

{
  const1_i.type&=NMARK;
  const1_v.op&=NMARK;
}
