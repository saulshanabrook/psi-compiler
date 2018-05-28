main()

{
  array A^3 <0 4 5>;
  array v^1 <3>;
  array B^0 <>;
  array i^0 <>;
  array e^2 <4  5>;
  array D^3 <3 4 5>;
  const array C^3 <3 4 5>=<0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
				19 20 21 22 23 24 25 26 27 28 29 30 31
                                32 33 34 35 36 37 38 39 40 41 42 43 44
                                45 46 47 48 49 50 51 52 53 54 55 56 57
                                58 59 >;
  const array five^0 <> = 5;
  const array nsh^1 <3> = <1 2 3>; 
  const array zero^1 <1>=<0>;
  const array one^1 <1>=<1>;
  const array mone^1 <1>=<-1>;
  const array vdrop^1 <3>=<0 1 1 >;
  
#  A=(<3> drop  (<3 4 5> take (<0 0 0>  drop  (<3> take (<0> drop (C cat (C cat (C cat (C cat (C cat (C cat C )))))))))));
#  B= (<2> psi  (<1> psi ( <0> psi C)));
#  for (<0> <= <i> < <5>){
#  <i> psi B = (<i> psi (<1> psi ( <0> psi C)));
#  }

#  e  =  (<0> psi( <1> take one ))  psi (iota (shp C)) ;
#   e  =  <0>   psi (iota (shp C)) ;
   e  =  <2 3 4> + <0 0 0>;

#  D  = (iota v) psi omega <1 3> (C cat C  );
#  D =  <3> take  (C cat C);
   

}
