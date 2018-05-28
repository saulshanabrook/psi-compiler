ADD_SUB1_C (double *in1, double *in2, double *in3, double *out)
{
	int	i;
	
	for (i = 0; i < 24; i++)
		*(out + i) = *(in1 + i) + *(in2 + i) + *(in3 + i);
}

ADD_SUB2_C (double *in1, double *in2, double *in3, double *out)
{
	int	i;

	for (i = 0; i < 24; i++)
		*(out + i) = *(in1 + i) * *(in2 + i) - *(in3 + i);
}
ADD_SUB3_C (double *in1, double *in2, double *in3, double *out)
{
	double temp [24];
	int	i;

	for (i = 0; i < 24; i++)
		temp[i] = *(in2 + i) * *(in3 + i);
	for (i = 0; i < 24; i++)
	{
		*(out + i) = ((*(in1 + i) - 4) * *(in3 + i) + 25) * temp[i] / 
		*(in3 + i) - *(in2 + i); 
	}
}


