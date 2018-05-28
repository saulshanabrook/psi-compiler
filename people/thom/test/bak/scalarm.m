SCALARCAT_M (array in1^1 <5>, array out1^1 <6>, array out2^1 <6>, array out3^1 <2>)
{
	const array five^0 <> = 5;

	out1 = in1 cat five;
	out2 = five cat in1;
	out3 = five cat five;
}

SCALAROPS_M (array in1^3 <2 3 4>, array out1^3 <2 3 4>) 
{
	const array five^0 <> = 5;
	
	out1 = in1 + five;
}

SCALAROPS2_M (array in1^3 <2 3 4>, array in2^3 <1 3 4>, array out1^3 <3 3 4>)
{
	const array five^0 <> = 5;
	
	out1 = (in1 cat in2) + five;
}

