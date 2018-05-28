$procs 10
$arch network
$hostname ohost.f90
ADD_SUB1 (array in1^3 <20 30 40>, array in2^3 <20 30 40>, array in3^3 <20 30 40>, array out^3 <20 30 40>)
{
	out = in1;
	out = out + in3;
}
