main()
{
 array xin^1 <27>;
 array xnew^1 <27>;
 array i^0 <>;
 array j^0 <>;
 array b^0 <>;
 array a^0 <>;
 array i1^0 <>;
 array n^0 <>;
 array ind0^0 <>;
 array ind1^0 <>;
 array ind2^0 <>;
 array index^0 <>;
 array abound^0 <>;
 array bbound^0 <>;
 array jcon^0 <> ;
 array jbound^0 <>;
 array jvar^0 <>;
 array bvar0^0 <>;
 array llim^0 <>;
 array ulim^0 <>;
 array bvar1^0 <>;
 array bvar2^0 <>;
 array h^1 <1>;
 array k^0 <>;
 array y^0 <>;
 array z^1 <1>;
 array q^1 <1>;
 array e^0 <>;
 const array four^0 <> = 4;
 const array one^0 <> = 1;
 const array zero^0 <> = 0;
 const array sh^1 <3> = < 3 3 3 >;
 const array x^1 <27> = < 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
                             1 1 1 1 >;
 n = four;
 xin = x;
 for ( one <= i < n){
    jcon = one;
    jbound = one;
    abound = one;
    y = (n - one) - i;
    jcon = *red  ( y pdrop sh );
#   for ( zero <= k < i ){
#     e = y  + k;
#     jcon = jcon * (<e> psi sh);
#   }
    jbound = *red  ( y  ptake sh );
#   for ( zero <= k < y ){
#     jbound = jbound * (<k> psi sh);
#   }
    abound = *red ( y + one ) drop sh ;
#   i1 = i + one;
#   for ( zero <= k < <i1> ){
#     e = y  + one + k;
#     abound = abound * (<e> psi sh);
#   }
    bbound = <y> psi sh;
     for ( zero <= j < jbound) {
       jvar =j * jcon;
          llim = bbound - one;
          for ( zero <= b < one){
             bvar0 = b * abound;       
             bvar1 = ( b + one ) * abound;      
             bvar2 = (llim + b) * abound;
          for ( zero <= a < abound) {
             ind0 = jvar + bvar0 + a;
             ind1 = jvar + bvar1 + a;
             ind2 = jvar + bvar2 + a;
             index =  ind0 - one;
             index pdrop xnew =  (<ind0> psi x) + (<ind1> psi x)
                                   +  (<ind2> psi x) ;
            }
        }
          for ( one <= b < llim ){
             bvar0 = b * abound;       
             bvar1 = ( b + one ) * abound;      
             bvar2 = b * abound;

          for ( zero <= a < abound) {
             ind0 = jvar + bvar0 + a;
             ind1 = jvar + bvar1 + a;
             ind2 = jvar + bvar2 + a;
             index =  ind0 - one;
             index pdrop xnew =  (<ind0> psi x) + (<ind1> psi x)
                                   +  (<ind2> psi x) ;
            }
        }
           for ( llim <= b < bbound ){
             bvar0 = b * abound;       
             bvar1 = (b - llim) * abound;
             bvar2 = b * abound;
          for ( zero <= a < abound) {
             ind0 = jvar + bvar0 + a;
             ind1 = jvar + bvar1 + a;
             ind2 = jvar + bvar2 + a;
             index =  ind0 - one;
             index pdrop xnew =  (<ind0> psi x) + (<ind1> psi x)
                                   +  (<ind2> psi x) ;
              }
        }
    }
 }
     n = n - one;
     e = n;
     for ( zero <= k < one ){
          n  = n *  e;
          }
     n = n - one;
  xnew = ( xnew - xin ) / n;
}
 

