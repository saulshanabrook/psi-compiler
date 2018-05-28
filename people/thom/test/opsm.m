ADD_SUB1 (array in1^3 <2 3 4>, array in2^3 <2 3 4>, array in3^3 <2 3 4>, array out^3 <2 3 4>)
{
	out = in1;
	out = out + in2;
	out = out + in3;
}

ADD_SUB2 (array in1^3 <2 3 4>, array in2^3 <2 3 4>, array in3^3 <2 3 4>, array out^3 <2 3 4>)
{
	array temp^3 <2 3 4>;

	temp = in1;
	temp = temp *in2;
	temp = temp - in3;
	out = temp;
}

ADD_SUB3 (array in1^3 <2 3 4>, array in2^3 <2 3 4>, array in3^3 <2 3 4>, array out^3 <2 3 4>)
{
	const array four^0 <> = 4;
	const array tfive^0 <> = 25;
	array temp^3 <2 3 4>;
	
	temp = in2 * in3;
	out = in1 - four * in3 + tfive * temp / in3 - in2;
}

