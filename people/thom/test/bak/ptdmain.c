#include <stdio.h>

do_ptd (char *mdat, char *cdat, double *in1)
{
	FILE	*fout, *gout;
	int 	i, j, k;
	double	out1 [1][3][4], out2 [1], out3 [4], out4 [3][4]; 

    if ((fout = fopen (mdat, "w"))==NULL)
    {
        printf("Cannot open %s\n",mdat);
        exit(0);
    }

	TAKE1_M (in1, out1);
	for (i=0; i<1; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out1[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	} 
	fprintf (fout, "\n\n");
	DROP_M (in1, out1);
	for (i=0; i<1; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out1[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	} 
	fprintf (fout, "\n\n");
	TAKE2_M (in1, out2);
	fprintf (fout, "%f ", out2 [0]);
	fprintf (fout, "\n\n");
	DROP2_M (in1, out2);
	fprintf (fout, "%f ", out2 [0]);
	fprintf (fout, "\n\n");
	PTD1_M (in1, out3);
	for (i = 0; i < 4; i++)
		fprintf (fout, "%f ", out3 [i]);
	fprintf (fout, "\n\n");
	PSI1_M (in1, out4);
	for (j=0; j<3; j++) {
		for (k=0; k<4; k++) {
			fprintf(fout, "%f ",out4[j][k]);
		}
		fprintf (fout, "\n");
	} 
	fprintf (fout, "\n\n");
	PSI2_M (in1, out3);
	for (i = 0; i < 4; i++)
		fprintf (fout, "%f ", out3 [i]);
	fprintf (fout, "\n\n");
	fclose (fout);

    if ((fout = fopen (cdat, "w"))==NULL)
    {
        printf("Cannot open %s\n",cdat);
        exit(0);
    }

	TAKE1_C (in1, out1);
	for (i=0; i<1; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out1[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	} 
	fprintf (fout, "\n\n");
	DROP_C (in1, out1);
	for (i=0; i<1; i++) {
		for (j=0; j<3; j++) {
			for (k=0; k<4; k++) {
				fprintf(fout, "%f ",out1[i][j][k]);
			}
			fprintf (fout, "\n");
		}
		fprintf(fout, "\n");
	} 
	fprintf (fout, "\n\n");
	TAKE2_C (in1, out2);
	fprintf (fout, "%f ", out2 [0]);
	fprintf (fout, "\n\n");
	DROP2_C (in1, out2);
	fprintf (fout, "%f ", out2 [0]);
	fprintf (fout, "\n\n");
	PTD1_C (in1, out3);
	for (i = 0; i < 4; i++)
		fprintf (fout, "%f ", out3 [i]);
	fprintf (fout, "\n\n");
	PSI1_C (in1, out4);
	for (j=0; j<3; j++) {
		for (k=0; k<4; k++) {
			fprintf(fout, "%f ",out4[j][k]);
		}
		fprintf (fout, "\n");
	} 
	fprintf (fout, "\n\n");
	PSI2_C (in1, out3);
	for (i = 0; i < 4; i++)
		fprintf (fout, "%f ", out3 [i]);
	fprintf (fout, "\n\n");
	fclose (fout);
}

main (int argc, char *argv[])
{
	double	in1[24]={5,9,23,-3,5,3,-22,3,5,9,10,-3,9,2,3,5,-2,3,-3,-5,4,2,9,7};

    if (argc != 3)
    {
        printf("usage: %s <moa output file> <c output file>\n",argv[0]);
        exit(0);
    }

	do_ptd (argv[1], argv[2], in1);
}
	

