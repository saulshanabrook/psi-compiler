shp_tau_dim_iota_ex(int j)

{
  array a^3 <4 j 5>;
  array b^3 <4 j 5>;
  array c^1 <3>;
  array g^0 <>;

  g=tau a;
  g=dim a;
  b=(iota (shp a)) psi omega <1 3> a;
}


red_ex()

{
  array a^3 <4 2 5>;
  array b^1 <5>;
  array c^1 <5>;

  b=*red (+red a);
}


ravel_ex()

{
  array a^3 <3 2 4>;
  array b^3 <3 2 4>;
  array c^2 <2 4>;
  array d^1 <28>;
  array e^3 <3 3 4>;
  array f^1 <10>;

  d=<28> take (<5> drop (rav e));
}