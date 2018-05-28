/* nn_main.c - An example main driver for the moal neural network in nn.m */
#include <stdio.h>
#include <math.h>

char buf[256];
int n_in,n_out;
FILE *infile;


get_random(double *a)

{
  *a=(double) (rand()%0xfff)/(double) 0xfff;
}


winner(double *output, double *w)

{
  int i;
  double max;
  
  *w=0.0;
  max=0.0;
  for (i=0; i<n_out; i++) {
    if (fabs(output[i])>max) {
      max=fabs(output[i]);
      *w=i;
    }
    output[i]=0.0;
  }
  output[(int) *w]=1.0;
}


read_input(double *vector)

{
/*  char *buf[256]; */
  int i;
  
  for (i=0; i<n_in; i++)
    fscanf(infile,"%lg",vector+i);
}


write_output(double *vector)

{
  int i;

  for (i=0; i<n_out; i++)
    printf("%g ",vector[i]);
  printf("\n");
}


main(int argc, char *argv[])

{
  int n_i,i;
  double *W,eta;
  long pos;

  if (argc!=4) {
    printf("usage: %s <n_in> <n_out> <inputs>\n",argv[0]);
    exit(0);
  }
  if ((infile=fopen(argv[3],"rt"))==NULL) {
    printf("Could not open input file %s.\n",argv[3]);
    exit(0);
  }

  n_in=atoi(argv[1]);
  n_out=atoi(argv[2]);

  fgets(buf,255,infile);
  n_i=atoi(buf);
  pos = ftell(infile);
  
  W=(double *) get_mem(n_in*n_out*sizeof(double));
  eta=0.001;

  reset(n_in,n_out,W);

  puts("before:");
  fseek(infile,pos,SEEK_SET);
  run(n_i,n_in,n_out,W);
  
  for (i=0; i<500; i++)  {
    fseek(infile,pos,SEEK_SET);
    learn(n_i,n_in,n_out,W,&eta);
  }

  puts("after:");
  fseek(infile,pos,SEEK_SET);
  run(n_i,n_in,n_out,W);
}
