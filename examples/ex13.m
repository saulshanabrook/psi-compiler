main()
{
 array res0^1 <6>;
 array a^3 <0 3 4>;

 const array xnew^3 <2 3 4> = < 0 1 6 7 2 3 8 9 4 5 10 11 12
                                  13 18 19 14 15 20 21 16 17 22 23>;

 const array x^1 <1> = < 2 > ;
 const array j^1 <1> = <1> ;

 res0 = x drop ( x take ( j psi omega < 1 2 > xnew ) ) ;


}
