main()
{
#  array b4^2 <10 30>;
#  array goat^2 <10 30>;
#  array fish^2 <20 30>;
#  array a4^2 <10 60>;

#  fish = b4 cat goat;

#  a4 = b4 cat omega <1 1> goat;

   array b5^1 <30>;
   array fish^1 <30>;
   array t1^1 <30>;

#   t1 = iota <30> * omega <1 1> <1>;

#   b5 =   (iota <30>) psi omega <1 1> fish;

#   b5 = fish;

   b5 = ((iota <30> * omega <1 1> <1>) + omega <1 1> <0>) psi omega <1 1> fish;

}
