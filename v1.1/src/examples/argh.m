main()
{
  array goat^2 <2 5>;
  array duck^2 <2 5>;
  const array foo^3 <2 5 2> = <0 0 0 1 0 2 0 3 0 4 1 0 1 1 1 2 1 3 1 4>;

# HPF       goat = duck(2:8:3,17:46) + duck(1:9:4,13:42)

#  goat = duck + duck;

#  goat = ((iota <3 30> * omega <1 1> <1 1>) + omega <1 1> <0 0>) psi omega <1 2> duck;
   goat = (((iota (shp duck))) psi omega <1 2>  duck) + ((iota (shp ( duck ))) psi omega < 1 2>  duck); 
#   goat = foo psi omega < 1 2>  duck;
}
