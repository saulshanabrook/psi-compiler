Main()
{
  array a1^1 <30>; 
  array a9^1 <3>;
  array a10^2 <4 3>;
  array a3^2 <2 30>;
  array a13^3 <2 30 1>;
  array a2^2 <4 30>;
  array a6^3 <2 3 2>;
  array r4^2 <5 5>;
  array a7^1 <1>;
  array a11^2 <30 1>;
  array a19^2 <30 2>;
  array r5^3 <3 5 5>;
  array z25^1 <2>;
  array lee^0 <>;
  const array s^2 <4 1> = <30 30 30 30>;
  const array w^2 <2 1> = <30 30>;
  const array b0^2 <2 1> = <0 0>;
  const array b1^1 <1> = <0>;
  const array z^1 <1> = <3>;
  const array q^0 <> = 3;
  const array k^2 <1 2> =  <30 1>;
  const array b5^2 <2 2> = <30 1 30 1>;
  const array f^0 <> = 30;
  const array x^1 <1> = <30>;
  const array l^2 <30 1> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
                            16 17 18 19 20 21 22 23 24 25 26 27 28 29>;
  const array zoo^1 <30> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
                            16 17 18 19 20 21 22 23 24 25 26 27 28 29>;
  const array foo^2 <4 3> = <0 1 2 3 4 5 6 7 8 9 10 11>;
  const array r^2 <2 30> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
                            16 17 18 19 20 21 22 23 24 25 26 27 28 29
                            0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
                            16 17 18 19 20 21 22 23 24 25 26 27 28 29>;
   
#lee=   <0> psi(  <0> psi    (( iota (shp foo)) psi omega <1 2> foo));
 a10  =  (( iota (shp foo)) psi omega <1 2> foo);

# a11 = l + iota x ;
# bus error on the following
#   a11 = z take iota f;
#  a13 = b5 take omega <1 1> r;
#  a3 = w take omega <1 1> iota x;
#  a19 = (iota k) cat omega <1 1> (iota k);
#  a13 = b5 take omega <1 1> iota f;
#   a3 = w take omega <1 1> zoo;
#  a7 = shp iota <3>;
#  a7 = shp iota q;
# a2 = b0 psi omega <1 1> ((iota <2>) psi  iota <30>);
# a2 = b0 psi omega <1 1> (<2> take iota <x>);
# a1 = b1 psi omega <1 1> r;
# a2 = b0 psi omega <1 1> r; 
# a1 = x take omega <1 1> iota x;
# a11 = (iota x) + omega <0 0> iota x;
# a3 = w take omega <1 1> iota x;
# a3 = w take omega <1 1> r;
# a3 = x take omega <1 1> r;
# a3 = w take omega <1 1> zoo;
# a6 = iota <2 3>;
# a10 = z take omega <1 1>  (<0 0 0> psi iota <2 3 4>);
# a10 = z take omega <1 1>  foo;
# a10 = (<0 0 0> psi iota <2 3 4>);
# This one doesn't work.
#    a3 = w take omega <1 1> a1;
#     a3 = k take omega <1 1> a1;
#     a2  = a2 - (a1 + omega <1 1> a2);
#    a2 = a1 cat (a1 cat (a1 cat a1));
#    r5 = r4 cat (r4 cat r4);
}





 
