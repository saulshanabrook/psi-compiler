#include <stdio.h>

do_scalars (double *in1, double *in2, double *in3)
{
	FILE	*fout, *gout;
	int 	i, j, k;
	double	out1 [6], out2 [6], out3 [2], out4 [2][3][4], out5 [3][3][4]; 

	fout = fopen ("scalarm.dat", "w");

	SCALARCAT_M (in1, out1, out2, out3);
	for (i = 0; i < 6; i++)
		fprintf (fout, "%f ", out1 [i]);
	fprintf (fout, "\n\n");
	for (i = 0; i < 6; i++)
		fprintf (fout, "%f ", out2 [i]);
	fprintf (fout, "\n\n");
	fprintf (fout, "%f %f\n\n", out3 [0], out3 [1]);

	SCALAROPS_M (in2, out4);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out4[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	} 
	fprintf (fout, "\n\n");

	SCALAROPS2_M (in2, in3, out5);
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out5[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fclose (fout);

	fout = fopen ("scalarc.dat", "w");
	SCALARCAT_C (in1, out1, out2, out3);
	for (i = 0; i < 6; i++)
		fprintf (fout, "%f ", out1 [i]);
	fprintf (fout, "\n\n");
	for (i = 0; i < 6; i++)
		fprintf (fout, "%f ", out2 [i]);
	fprintf (fout, "\n\n");
	fprintf (fout, "%f %f\n\n", out3 [0], out3 [1]);

	SCALAROPS_C (in2, out4);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out4[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf (fout, "\n\n");

	SCALAROPS2_C (in2, in3, out5);
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out5[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}

	fclose (fout);
}

main ()
{
	double	in1[5]={7,8,9,10,11};
	double	in2[24]={11,10,9,8,7,6,5,4,3,2,1,0,11,10,9,8,7,6,5,4,3,2,1,0};
	double	in3[24]={5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,1,1,1,1};

	do_scalars (in1, in2, in3);
}
	

