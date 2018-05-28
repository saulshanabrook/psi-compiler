main()

{
  array Amts^3 <0 3 4>;
  array Bmts^3 <2 3 4>;
  const array RAMY^3 <2 3 4>=<0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
				19 20 21 22 23>;
  const array TAMY^3 <2 3 4>=<9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9>;
  const array Zero^1 <1>=<0>;
  const array One^1 <1>=<1>;

  Amts=One drop (One take (Zero drop ((One drop RAMY) cat (One take RAMY))));
  Bmts=Amts cat TAMY;
}
