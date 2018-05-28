#include <stdio.h>

do_ops (char *mdat, char *cdat, double *in1, double *in2, double *in3,
        double *out)
{
	FILE	*fout, *gout;
	int 	i, j, k;

	if ((fout = fopen (mdat, "w"))==NULL)
	{
		printf("Cannot open %s\n",mdat);
		exit(0);
	}

	ADD_SUB1 (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf (fout, "\n\n");

	ADD_SUB2 (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf (fout, "\n\n");

	ADD_SUB3 (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fclose (fout);

	if ((fout = fopen (cdat, "w"))==NULL)
	{
		printf("Cannot open %s\n",cdat);
		exit(0);
	}

	ADD_SUB1_C (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf (fout, "\n\n");

	ADD_SUB2_C (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf (fout, "\n\n");

	ADD_SUB3_C (in1, in2, in3, out);
	for (i=0; i<2; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out[i*12+j*4+k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fclose (fout);
}

main (int argc, char *argv[])
{
	double	in1[24]={0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11};
	double	in2[24]={11,10,9,8,7,6,5,4,3,2,1,0,11,10,9,8,7,6,5,4,3,2,1,0};
	double	in3[24]={5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,1,1,1,1};
	double	out[24];

	if (argc != 3)
	{
		printf("usage: %s <moa output file> <c output file>\n",argv[0]);
		exit(0);
	}

	do_ops (argv[1], argv[2], in1, in2, in3, out);
}
