main()
{

  array a3^2 <2 30>;
  array a19^2 <30 2>;
  array l^2 <2 1>;
  const array w^2 <2 1> = <30 30>;
  const array k^2 <1 2> =  <30 1>;
  const array x^0 <> = 30;
#  const array empty^1 <0> = <>;

# a3 = w take omega <1 1> iota x;
# a3 = <> psi (iota x);
# a3 = empty psi omega <1 1> iota x;
 l = (iota( shp w)) psi omega <1 2> w;
}


