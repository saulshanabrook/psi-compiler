main()
{
  array foo^2 <5 6>;
  const array x^2 <6 6> = < 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
                            19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34
                            35>;

  array i^0 <>;
  const array llim^0 <> = 2;
  const array ulim^0 <> = 3;
  const array l^1 <1> = <5>;
  for( <2> <= i < <3> ) {
    foo = (<5> take omega <0 1> x) + i;
  }
}

