main()

{
  array A^2 <3 3>;
  const array C^2 <5 5>=<0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
				19 20 21 22 23 24>;
  const array nsh^1 <2> = <3 3>; 
  const array zero^1 <1>=<0>;
  const array one^1 <1>=<1>;
  const array mone^1 <1>=<-1>;
  const array vdrop^1 <2>=<0 1>;
  
  A=nsh take (vdrop  drop  (one drop (mone drop C )));
}



