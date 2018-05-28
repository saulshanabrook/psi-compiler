heat4d(int i, int n, array A^4 <n n n n>, array lambda^0 <>)
{
  array m_lambda^0 <>;
  const array one^0 <>=1.0;
  const array neight^0 <>=-8.0;
  array b^1 <4>;
  array A2^4;
  array t^1 <1>;

  m_lambda=neight*lambda+one;
  b=<n n n n>-<2 2 2 2>;
  allocate A2 b;
  for (<0> <= t < <i>) {
    A2=((b ptake (<1 1 2 1> drop A))+(b ptake (<1 1 0 1> drop A))+
	(b ptake (<1 1 1 2> drop A))+(b ptake (<1 1 1 0> drop A))+
	(b ptake (<1 2 1 1> drop A))+(b ptake (<1 0 1 1> drop A))+
	(b ptake (<2 1 1 1> drop A))+(b ptake (<0 1 1 1> drop A)))*lambda;
    <1 1 1 1> pdrop A=(b ptake (<1 1 1 1> drop A))*m_lambda+A2;
  }
}
