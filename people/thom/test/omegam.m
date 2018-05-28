omega_red (array in^3 <5 5 5>, array out1^2 <5 5>, array out2^2 <5 5>, array out3^2 <5 5>, array out4^2 <5 5>, array out5^2 <5 5>)
{
	out1 = +red in;
	out2 = +red omega <3> in;
	out3 = *red omega <2> in;
	out4 = -red omega <1> in;

	out5 = (+red omega <2> in) + (*red omega <1> in);
}

omega_psi (array in^3 <5 5 5>, array out1^2 <5 5>, array out2^2 <5 5>, array out3^2 <5 5>)
{  
	out1 = <1> psi omega <1 3> in;
	out2 = <1> psi omega <1 2> in;
	out3 = <1> psi omega <1 1> in;
}  
