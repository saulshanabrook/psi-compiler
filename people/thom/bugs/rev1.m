test_reverse1 (array in1^3 <4 6 2>, array out1^3 <4 6 2>)
{
# This does not work
  out1 = reverse (reverse omega <2> in1);
 
# while this one does
  out1 = reverse omega <2> (reverse in1);
 
# For the first example, the argument to red_reverse in psi.c to take care
# of the first reverse you see is an expression of type FORALL, and thus
# the index and stride of the forall loop is changed, and code.c does not
# handle this correctly.
# For the second example, the argument to red_reverse to take care of the
# second reverse is an expression that has PSI as it's root operator.  This
# seems to work ok, since the index and stride of the forall loop are not
# changed.
}

