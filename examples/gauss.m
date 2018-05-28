main()
{
  array j^1 <1>;
  array i^1 <1>;
  array d^0 <>;
  array ishp^1 <2>;
  array ivec^1 <2>;
  array res^2 <3 3>;
  const array tvec^1 <2> = <3 3>;
  const array dvec^1 <2> = <1 1>;
  const array jvec^1 <2> = < 0 2 >;
  const array ones^1 <2> = < 1 1 >;
  const array xold^2 <5 5> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                               15 16 17 18 19 20 21 22 23 24>;	
  const array fives^2 <3 3> = < 5 5 5 5 5 5 5 5 5>;
  d = dim res;
  ishp = (shp xold) - <2 2>;
  ivec = iota d; 
  res = ishp take ( ones drop xold );
  for ( <0> <= i < <d> ){
   for ( <0> <= j < <2> ){
     res = res + (ishp take  ((( i  take ones ) cat
           ((j psi jvec) cat ((i + <1>) drop  ones))) drop xold));
       }
   }
#   tvec take ( dvec drop xold)  = (res / fives) ;
 }
