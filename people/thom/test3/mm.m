# mm.m performs matrix multiplication

multiply(int m, int n, int p, array A^2 <m n>, array B^2 <n p>,
	 array C^2 <m p>)
{
  const array sig1^0 <> = 0;
  const array sig2^0 <> = 1;
  C=+red omega <2> (A [* omega <sig1 sig2>] omega <1 2> B);
}
