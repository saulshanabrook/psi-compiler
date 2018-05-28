omega_red_c (double in [], double out1 [], double out2 [], double out3 [],
	double out4 [], double out5 [])
{
	int	i, j, k, l, m;
	double	temp2 [25];

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			*(out1 + i*5 + j) = 0;
			*(out2 + i*5 + j) = 0;
			*(out3 + i*5 + j) = 1;
			*(out4 + i*5 + j) = 0;
			*(out5 + i*5 + j) = 0;
			temp2 [i*5 + j] = 1;
			for (k = 0; k < 5; k++)
			{
				*(out1 + i*5 + j) += *(in + k*25 + i*5 + j);
				*(out2 + i*5 + j) += *(in + k*25 + i*5 + j);
				*(out3 + i*5 + j) *= *(in + i*25 + j + k*5);
				*(out4 + i*5 + j) -= *(in + i*25 + j*5 + k);
				*(out5 + i*5 + j) += *(in + i*25 + j + k*5);
				temp2 [i * 5 + j] *= *(in + i*25 + j*5 + k);
			}
		}
	}
	for (i = 0; i < 25; i++)
		*(out5 + i) += temp2 [i];
}

omega_psi_c (double in [], double out1 [], double out2 [], double out3 [])
{
	int		i, j, k;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			*(out1 + i*5 +j) = *(in + 1*25 + i*5 + j);
			*(out2 + i*5 +j) = *(in + i*25 + 1*5 + j);
			*(out3 + i*5 +j) = *(in + i*25 + j*5 + 1);
		}
	}
}
	
