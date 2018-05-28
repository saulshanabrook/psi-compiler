$trace
$hostname unihost.c
$arch uni
$procs 4

heat1d(int i, int n, array A^1 <n>, array lambda^0 <>)

{
  array m_lambda^0 <>;
  const array one^0 <>=1.0;
  const array ntwo^0 <>=-2.0;
  array b^1 <1>;
  array A2^1;
  array t^1 <1>;

  global m_lambda;
  global one;
  global ntwo;
  global b;
  global t;

  m_lambda=ntwo*lambda+one;
  b=<n>-<2>;
  allocate A2 b;
  for (<0> <= t < <i>) {
    A2=((b ptake (<0> drop A))+(b ptake (<2> drop A)))*lambda;
    <1> pdrop A=(b ptake (<1> drop A))*m_lambda+A2;
  }

  printout(i,n,A,lambda);
}


#heat2d(int i, int n, array A^2 <n n>, array lambda^0 <>)
#
#{
#  array m_lambda^0 <>;
#  const array one^0 <>=1.0;
#  const array nfour^0 <>=-4.0;
#  array b^1 <2>;
#  array A2^2;
#  array t^1 <1>;
#
#  global m_lambda;
#  global one;
#  global nfour;
#  global b;
#  global t;
#
#  m_lambda=nfour*lambda+one;
#  b=<n n>-<2 2>;
#  allocate A2 b;
#  for (<0> <= t < <i>) {
#    A2=((b ptake (<1 2> drop A))+(b ptake (<1 0> drop A))+
#	(b ptake (<2 1> drop A))+(b ptake (<0 1> drop A)))*lambda;
#    <1 1> pdrop A=(b ptake (<1 1> drop A))*m_lambda+A2;
#  }
#}


#heat3d(int i, int n, array A^3 <n n n>, array lambda^0 <>)
#
#{
#  array m_lambda^0 <>;
#  const array one^0 <>=1.0;
#  const array nsix^0 <>=-6.0;
#  array b^1 <3>;
#  array A2^3;
#  array t^1 <1>;
#
#  global m_lambda;
#  global one;
#  global nsix;
#  global b;
#  global t;
#
#  m_lambda=nsix*lambda+one;
#  b=<n n n>-<2 2 2>;
#  allocate A2 b;
#  for (<0> <= t < <i>) {
#    A2=((b ptake (<1 2 1> drop A))+(b ptake (<1 0 1> drop A))+
#	(b ptake (<1 1 2> drop A))+(b ptake (<1 1 0> drop A))+
#	(b ptake (<2 1 1> drop A))+(b ptake (<0 1 1> drop A)))*lambda;
#    <1 1> pdrop A=(b ptake (<1 1 1> drop A))*m_lambda+A2;
#  }
#}

