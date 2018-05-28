#include <math.h>
#include <stdio.h>
#include <string.h>

main (int argc, char *argv[])
{
	FILE	*cdat, *mdat, *edat;
	float	f1, f2;
	int	i, j;

	if (argc != 5) 
	{
		printf ("Usage:  error <infile1> <infile2> <outfile> <width>\n");
		exit (1);
	}
	cdat = fopen (argv[1], "r");
	mdat = fopen (argv[2], "r");
	edat = fopen (argv[3], "w");
	i = atoi (argv[4]);

	j = 1;
	fscanf (mdat, "%f", &f1);
	fscanf (cdat, "%f", &f2);
	while ((!feof (cdat)) && (!feof (mdat)))
	{
		fprintf (edat, "%f ", (f1 - f2));
		if (!(j % i))
			fprintf (edat, "\n");
		++j;
		fscanf (mdat, "%f", &f1);
		fscanf (cdat, "%f", &f2);
	}
	fprintf (edat, "\n");
	fclose (cdat);
	fclose (mdat);
	fclose (edat);
}

	
