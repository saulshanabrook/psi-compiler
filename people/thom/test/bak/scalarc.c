SCALARCAT_C (double in1 [], double out1 [], double out2 [], double out3 [])
{
	int	i;

	for (i = 0; i < 5; i++)
		*(out1 + i) = *(in1 + i);
	*(out1 + 5) = 5;
	for (i = 0; i < 5; i++)
		*(out2 + i + 1) = *(in1 + i);
	*(out2) = 5;
	for (i = 0; i < 2; i++)
		*(out3 + i) = 5;
}

SCALAROPS_C (double in1 [], double  out1 []) 
{
	int	i;  
	
	for (i = 0; i < 24; i++)
		*(out1 + i) = *(in1 + i) + 5;
}

SCALAROPS2_C (double in1 [], double  in2 [], double out1 [])
{
	int	i;

	for (i = 0; i < 24; i++)
		*(out1 + i) = *(in1 + i) + 5;
	for (i = 0; i < 12; i++)
		*(out1 + 24 + i) = *(in2 + i) + 5;
}

