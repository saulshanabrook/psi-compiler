#include <stdio.h>

clear_outs (double out1 [], double out2 [], double out3 [], double out4 [],
	 double out5 [])
{
	int	i;
	
	for (i = 0; i < 125; i++);
	{
		*(out1 + i) = 0;
		*(out2 + i) = 0;
		*(out3 + i) = 0;
		*(out4 + i) = 0;
		*(out5 + i) = 0;
	}
}

do_omegas (double in [], double out1 [], double out2 [], double out3 [],
	double out4 [], double out5 [])
{
	FILE	*fout, *gout;
	int 	i, j, k;
	
	fout = fopen ("omegam.dat", "w");

	clear_outs (out1, out2, out3, out4, out5);
	omega_red (in, out1, out2, out3, out4, out5);
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out1[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out2[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out3[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out4[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out5[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");

	omega_psi (in, out1, out2, out3);
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out1[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out2[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out3[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	fclose (fout);
	
	fout = fopen ("omegac.dat", "w");
	clear_outs (out1, out2, out3, out4, out5);
	omega_red_c (in, out1, out2, out3, out4, out5);
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out1[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out2[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out3[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out4[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out5[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");

	omega_psi_c (in, out1, out2, out3);
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out1[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out2[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	for (j=0; j<5; j++) {
		for (k=0; k<5; k++) {
			fprintf(fout, "%f ",out3[j*5+k]);
		}
		fprintf (fout, "\n");
	}
	fprintf (fout, "\n\n");
	fclose (fout);

}

main ()
{
	double	in[125];
	double	out1[125], out2 [125], out3 [125], out4 [125], out5 [125];
	int		i;

	for (i = 0; i < 125; i++)
		in[i] = (float)i/100;

	do_omegas (in, out1, out2, out3, out4, out5);
}
	

