shp_tau_dim_iota_ex(int j)

{
  array a^3 <4 j 5>;
  array b^3 <4 j 5>;
  array c^1 <3>;
  array g^0 <>;
  array k^1 <1>;
  array kk^1 <2>;
  const array d^1 <1> = <3>;
  g=tau a;
  g=dim a;
  forall (<0> <= k < <d>) {
  kk = k cat k;
   b=(iota (shp a)) psi omega <kk> a;
  }
}

