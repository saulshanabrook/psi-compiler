test_reverse1 (array in1^3 <4 6 2>, array out1^3 <4 6 2>)
{
#  out1 = reverse omega <2> in1;
#  out1 = reverse omega <2> (reverse in1);
  out1 = reverse (reverse omega <2> in1);
}
