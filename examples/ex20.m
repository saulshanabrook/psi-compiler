main()

{
  array A^2 <2 4>;
  array B^2 <2 4>;
  const array C^2 <6 4>=<0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
				19 20 21 22 23>;
  const array Two^1 <1>=<2>;
  const array Mfour^1 <1>=<-4>;

  A=Two take C;
  B=Mfour drop C;
}
