NEWLU(int n, array a^2 <n n>)

{
  array c^1;			# A temporary to store the pivots so as not
				# to have to compute them twice
  array i^1 <1>;		# A looping variable
  array n1^1 <1>;		# Loop bound
  array i1^1 <1>;		# =i+1  for convience
  array ni^1 <1>;               # =n-i-1; for convience
  forall (<0> <= i < <n>) {
    i1=i+<1>;
    mi=<0>-<i1> ;
    ni=<n>-i1;
    ni=<0>-<ni>;
    # Calculate the pivots
    c=(<i> psi omega <1 1> (i1 pdrop a))  / (<i i> psi a);

    # Perform the complete LU in one expression
    a=(<i> ptake a) cat (<i> psi a) cat
	(((((ni)  cat i) take a) cat omega <1 0> c)
	cat omega <1 1>
	(((i1 cat i1) pdrop a)-(c * omega <0 1> (i1 pdrop (<i> psi a)))));
    
  }
}










