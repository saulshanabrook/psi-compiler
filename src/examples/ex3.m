main()

{
  array Amts^2 <1 8>;
  const array RAMY^3 <2 3 4>=<1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6 7 8 9 10
				11 12>;
  const array AMY^3 <2 3 4>=<9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9>;
  const array Y^3 <2 3 4>=<8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8>;

  Amts=<2> drop (<1> psi (Y cat omega <1 1> ((RAMY + AMY) + RAMY)));
}

