test_red (array in1^3 <9 3 7>, array in2^4 <3 5 6 8>, array out1^2 <3 7>,
  array out2^2 <3 7>, array out3^2 <6 8>, array out4^3 <2 6 8>)
{

  # these seem to create unnecessary temporaries

  out1 = * red in1;
  out2 = * red (<2> drop in1);
  out3 = * red (<1> psi in2);
  out4 = * red (<2 2> take in2);
}

test_red2 (array in1^3 <9 3 7>, array in2^3 <2 3 7>, array out1^2 <3 7>,
  array out2^2 <3 7>, array out3^0 <>)
{
  out1 = * red ((<2> take in1) + in2);
  out2 = * red (in1 cat in2);
  out3 = * red (rav in2);
}
