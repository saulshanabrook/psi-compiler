main()

{
  array A^3 <0 3 4>;
  array B^3 <2 3 4>;
  const array C^3 <2 3 4>=<0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
				19 20 21 22 23>;
  const array D^3 <2 3 4>=<100 101 102 103 104 105 106 107 108 109 110 111
                                112 113 114 115 116 117 118
                                119 120 121 122 123>;
  const array Zero^1 <1>=<0>;
  const array One^1 <1>=<1>;

  A=One drop (One take (Zero drop ((One drop C) cat (One take C))));
  B=A cat D;
}
