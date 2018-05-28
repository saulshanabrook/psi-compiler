main()
{
 array xin^1 <27>;
 array xnew^1 <27>;
 array i^0 <>;
 array ind^0 <>;
 array index^1 <1>;
 array j^0 <>;
 array b^0 <>;
 array a^0 <>;
 array jbound^0 <>;
 array abound^0 <>;
 array bbound^0 <>;
 array jcon^0 <>;
 array jvar^0 <>;
 array mone^1 <1>;
 array bvar0^0 <>;
 array bvar1^0 <>;
 array bvar2^0 <>;
 array foo^0 <>;
 array y^1 <1> ;
 const array sh^1 <3> = < 3 3 3 >;
 const array one^0 <> = 1;
 const array vone^0 <> = 1;
 const array vzero^0 <> =0;
 const array n^0 <> = 4;
 const array x^1 <27> = < 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
                             1 1 1 1 >;
 for ( vone <= i < n) {
    y = n - i;
    jbound = *red (y ptake sh);
    jcon = *red (y pdrop sh);
    bbound = y psi sh;
    for ( vzero <= j < <jbound>) {
       jvar = j * jcon;
       for ( vzero <= b < bbound) {
          bvar0 = b * abound;
          for ( vzero <= a < abound) {
             ind = jvar + bvar0 + a;
             index = <ind>;
             index pdrop xnew = index pdrop x;
          }
       }
    }
  }
}

