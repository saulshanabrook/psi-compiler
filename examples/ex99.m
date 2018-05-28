main()
{
  array res^2 <2 3>;
  array r0^0 <>;
  array r1^1 <5>; 
  array r2^2 <3 5>;
  array r3^2 <3 5>; 
  array k^3 <2 3 2>;
  array e^0 <>;
  array i^1 <1>;
  array foo^2 <0 5>;
  array goo^2 <3 3>;
  array kk^1 <2>;
  const array x^1 <2> = <0 1>;
  const array a^1 <1> = <0>;
  const array h^1 <2> = < 3 5 >;
  const array y^2 <5 5> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
                           19 20 21 22 23 24>;
  const array v^2 <10 5> = <0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                            0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                            0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                            0 1 2 3 4 >;

# res = <0 0> psi (iota h  ) psi omega <1 2> v;
# r0 =  (iota h  ) psi omega <1 2> v;
#  r0 = <> psi (iota h  ) psi omega <1 2> v;
#  k = iota h;
#   r1 = <0> psi (k) psi omega <1 2> v;
#  r1 = <0> psi (iota h  ) psi omega <1 2> v;
#   r2 = (iota h) psi omega <1 2> v; 
#   r3 = (iota <3 5> ) psi omega <1 2> v; 
#   r3 = (iota (shp v)) psi omega <1 2> v; 
#   r3 = e psi v;
#    foo =   <5> drop (       <5> take v );
    forall (<0> <= i < <2>){
    kk = 1 cat i;
    goo= <1>  drop omega <kk> (<-1> drop omega <kk> v) ;
}
   
  
}
