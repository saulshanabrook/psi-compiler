main ()

{
  array Amts^3 <2 3 8>;
  array Ams^3 <2 3 4>;
  const array RAMY^3 <2 3 4>=<1 2 3 4 5 6 7 8 9 10 11 12 1 2 3 4 5 6 7 8 9 10 
				11 12>;
  const array AMY^3 <2 3 4>=<9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9>;
  const array Y^3 <2 3 4>=<8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8>;
  const array V^1 <2>=<1 1>;
  array A^1 <8>;

  Ams=RAMY + AMY;
  Amts=Y cat omega <1 1> (Ams + RAMY);
  A=V psi Amts ;
  Amts=<2> take (<2> drop (RAMY cat AMY));
}

