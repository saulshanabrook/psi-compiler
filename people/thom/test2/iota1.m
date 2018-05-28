iota1 (array out0^1 <5>, array out1^1 <5>, array out2^3 <5 6 2>, array out3^4 <5 6 7 3>, array out4^0 <>, array out5^1 <3>, array out6^1 <2>, array arr0_1^1 <2>)

{
  const array in1^1 <1> = <2>;
  const array in2^1 <2> = <5 6>;
  const array in3^1 <3> = <5 6 7>;
  const array ten^0 <> = 10;
  const array five^1 <1> = <5>;
  const array numb2^0 <> = 2;
  const array numb3^1 <2>=<2 0>;

  out0 = iota ten;
  out1 = iota five;
  out2 = iota in2;
  out3 = iota in3;
  out4 = <3> psi (iota ten);
  out5 = <2 5 1> psi (iota in3);
  out6 = iota in1;

  arr0_1 = (numb3 + (iota numb2));
  arr0_1 = ((iota numb2) + numb3);
}
