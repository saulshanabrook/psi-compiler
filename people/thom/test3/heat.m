# heat.m - A finite difference solution to the heat equation Ut=Uxx.
#   The i parameter is the number of iterations to be performed.

heat2d(int i, int n, array A^2 <n n>, array lambda^0 <>)

{
  array m_lambda^0 <>;
  const array one^0 <>=1.0;
  const array nfour^0 <>=-4.0;
  array b^1 <2>;
  array A2^2;
  array t^1 <1>;

  m_lambda=nfour*lambda+one;
  b=<n n>-<2 2>;
  allocate A2 b;

  for (<0> <= t < <i>) {
    A2=((b ptake (<1 2> drop A))+(b ptake (<1 0> drop A))+
	(b ptake (<2 1> drop A))+(b ptake (<0 1> drop A)))*lambda;
    <1 1> pdrop A=(b ptake (<1 1> drop A))*m_lambda+A2;
  }
}
