test_rav (array out1^1 <16>, array out2^1 <17>, array out3^1 <27>, 
  array in1^3 <3 3 3>)
{
  out1 = <4> drop (<20> take rav (in1));
  out2 = <17> take rav (in1);
  out3 = rav (in1);
}

test_rav2 (array in1^3 <10 20 30>, array out1^2 <10 600>,
           array out2^2 <10 200>)
{
  out1 = rav omega <2> in1;
  out2 = <200> take omega <1 1> (rav omega <2> in1);
}

test_rav3 (array in1^2 <8 9>, array out1^0 <>, array out2^1 <9>)
{
  out1 = <13> psi (<16> take (rav in1));
}
