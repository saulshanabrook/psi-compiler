TAKE1_C (double in1 [], double out [])
{
	int	i;

	for (i = 0; i < 3*4; i++)
		*(out + i) = *(in1 + i);
}

DROP_C (double in1 [], double out [])
{
	int	i;
	
	for (i = 0; i < 3*4; i++)
		*(out + i) = *(in1 + 3*4 + i);
}

TAKE2_C (double in1 [], double out [])
{
	*out = *(in1 + 1*4);
}

DROP2_C (double in1 [], double out [])
{
	*out = *(in1 + 1*4);
}

PTD1_C (double in1 [], double out [])
{
	int	i;

	for (i = 0; i < 4; i++)
	{
		*(out + i) = *(in1 + 12 + 2*4 + i);
	}
}

PSI1_C (double in1 [], double out [])
{
	int	i;
	
	for (i = 0; i < 1*3*4; i++)
	{
		*(out + i) = *(in1 + 12 + i);
	}
}

PSI2_C (double in1 [], double out [])
{
	int	i;

	for (i = 0; i < 4; i++)
	{
		*(out + i) = *(in1 + 1*3*4 + 2*4 + i);
	}
}
