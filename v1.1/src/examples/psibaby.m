main()
{
   array a1^2 <10 10>;
   array fish^1 <10>;
   array goat^1 <10>;
   array duck^1 <10>;
   array ind^2 <10 1>; 
   array in0^2 <10 1>;
   array in1^2 <10 1>;
   array x^1 <1>;
   const array frog^1 <1> = <5>;

#   fish = <5> psi a1;
   goat = x drop (x take duck);
   goat = frog drop (frog take duck);
   fish = <5> drop (<5> take duck);
   
#   goat = <5> psi omega <1 1> a1;
#  duck = (((iota <10 1>) * omega <1 1> <1 1>) + omega <1 1> <0 4>) psi omega <1 2> a1;
#   ind = iota <10 1>;
#   in0 = ind * omega < 1 1> <1 1>;
#   in1 = in0 + omega <1 1> <0 4>;
#   duck = in1 psi omega <1 2> a1;
}