main()

{
  array Res^3 <3 3 4>;
  const array Xi^3 <3 3 4> = < 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
			19 20 21 22 23  24 25 26 27 28 29 30 31 32 33 34 35 >;

  Res=(<2> drop Xi) cat (<2> take Xi);
}

