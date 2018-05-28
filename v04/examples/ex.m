main()
{
 array res0^1 <6>;
 array res1^1 <6>;
 const array a^2 <4 6> = < 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
                           20 21 22 23>;
 const array xnew^4 <2 3 2 2> = < 0 1 6 7 2 3 8 9 4 5 10 11 12 
                                  13 18 19 14 15 20 21 16 17 22 23>;
 const array x^1 <1> = < 6 >;
 const array y^1 <1> = < 2 > ;
 const array i^1 <1> = <2> ;
 const array j^1 <1> = <0> ;
 res0 = i psi a;
 res1 = x take ( x drop ( rav ( j psi omega < 1 2 > xnew )) ) ;


}



