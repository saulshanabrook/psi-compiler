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

