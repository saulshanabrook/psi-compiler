test_rav3 (array in1^2 <5 5>, array in2^2 <5 5>, array out1^1 <50>,
           array out2^1 <23>, array out3^0 <>)
{
# The following will work
  out1 = rav (in1 cat omega <1 1> in2);
 
# but this seems to have some problems.  probably a bug in block_rav,
# but i can't be sure.  perhaps linked to the next bug.
  out2 = <23> take (rav (in1 cat omega <1 1> in2));
 
# This bug arises from improper computation of the variable ti in
# block_rav in psi.c.  ti is alway set to 0, and thus the loop in the
# output C code will start at 0 instead of 3
  out3 = <3> psi rav in1;
}
