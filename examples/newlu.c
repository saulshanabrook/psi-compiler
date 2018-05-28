#include "moalib.e"

NEWLU(int _n, float _a[])

{
  int i0;
  int i1;
  int step1[2];
  int step2[2];
  int shift,offset;
  float *_c;
  float _i[1];
  float _n1[1];
  float _i1[1];
  float _mi[1];
  float _ni[1];
  float _mni[1];
  float consta0[1];
  float consta1[1];
  float consta2[1];
  float consta3[1];
  int forall_i0[1];
  int shp0;
  float *tmp_vect0;
  float *tmp_vect1;
  int forall_i1[1];
  float *tmp_vect2;
  int forall_i2[1];
  int forall_i3[1];
  float *tmp_vect3;
  float *tmp_vect4;
  float *temp1;
  float *tmp_vect5;

  for (_i[0]=0; _i[0]<(_n); _i[0]++) {
    shift=0;
    offset=0;
    *(_i1+shift)=*(_i+offset);

    consta0[0]=1.000000;
    shift=0;
    offset=0;
    *(_i1+shift)+=*(consta0+offset);

    consta1[0]=0.000000;
    shift=0;
    offset=0;
    *(_mi+shift)=*(consta1+offset);

    shift=0;
    offset=0;
    *(_mi+shift)-=*(_i1+offset);

    consta2[0]=(_n);
    shift=0;
    offset=0;
    *(_ni+shift)=*(consta2+offset);

    shift=0;
    offset=0;
    *(_ni+shift)-=*(_i1+offset);

    consta3[0]=0.000000;
    shift=0;
    offset=0;
    *(_mni+shift)=*(consta3+offset);

    shift=0;
    offset=0;
    *(_mni+shift)-=*(_ni+offset);

    shp0=(_n-_i1[0+0]);
      _c=(float *) malloc(shp0*sizeof(float));

    for (forall_i0[0]=0; forall_i0[0]<0+(_n-_i1[0+0]); forall_i0[0]++) {
      shift=(forall_i0[0+0]);
      offset=(_i1[0+0]+forall_i0[0+0])*(_n)+(_i[0]);
      *(_c+shift)=*(_a+offset);

    }
      tmp_vect0=(float *) malloc((1)*sizeof(float));
    shift=0;
    offset=(_i[0])*(_n)+(_i[0]);
    *(tmp_vect0+shift)=*(_a+offset);

    shift=0;
    for (i0=0; i0<(_n-_i1[0+0]); i0++) {
      *(_c+shift)/=tmp_vect0[0+0];
      shift++;
    }

      tmp_vect1=(float *) malloc((2)*sizeof(float));
    shift=0;
    offset=0;
    *(tmp_vect1+shift)=*(_mni+offset);

    shift=1;
    offset=0;
    *(tmp_vect1+shift)=*(_i+offset);

      tmp_vect2=(float *) malloc((2)*sizeof(float));
    shift=0;
    offset=0;
    *(tmp_vect2+shift)=*(_i1+offset);

    shift=1;
    offset=0;
    *(tmp_vect2+shift)=*(_i1+offset);

    shift=0*(_n)+0;
    offset=0*(_n)+0;
    for (i0=0; i0<(min(min(_i[0]+1+shp0,_i[0]+1),_i[0])); i0++) {
      for (i1=0; i1<(_n); i1++) {
        *(_a+shift)=*(_a+offset);
        shift++;
        offset++;
      }
    }

    shift=(min(min(_i[0]+1+shp0,_i[0]+1),_i[0]))*(_n)+(0);
    offset=(_i[0])*(_n)+(0);
    for (i0=0; i0<(min(_i[0]+1+shp0,_i[0]+1)-min(min(_i[0]+1+shp0,_i[0]+1),_i[0])); i0++) {
      for (i1=0; i1<(_n); i1++) {
        *(_a+shift)=*(_a+offset);
        shift++;
        offset++;
      }
    }

    for (forall_i3[0]=0; forall_i3[0]<0+(_i[0]+1+shp0-min(_i[0]+1+shp0,_i[0]+1)); forall_i3[0]++) {
      for (forall_i1[0]=(forall_i3[0+0]); forall_i1[0]<(forall_i3[0+0])+(1); forall_i1[0]++) {
          tmp_vect3=(float *) malloc((2)*sizeof(float));
        shift=0;
        offset=0;
        *(tmp_vect3+shift)=*(_mni+offset);

        shift=1;
        offset=0;
        *(tmp_vect3+shift)=*(_i+offset);

        shift=(min(_i[0]+1+shp0,_i[0]+1)+forall_i3[0+0]+forall_i1[0+0]-forall_i3[0+0])*(_n)+(0);
        offset=((tmp_vect3[0+0]+_n)*((tmp_vect3[0+0]<0))+forall_i1[0+0])*(_n)+((tmp_vect3[1+0]+_n)*((tmp_vect3[1+0]<0))+0);
        for (i1=0; i1<(min(min(_n,fabs(tmp_vect1[0+1])+1),fabs(tmp_vect1[0+1]))); i1++) {
          *(_a+shift)=*(_a+offset);
          shift++;
          offset++;
        }

        shift=(min(_i[0]+1+shp0,_i[0]+1)+forall_i3[0+0]+forall_i1[0+0]-forall_i3[0+0])*(_n)+(min(min(_n,fabs(tmp_vect1[0+1])+1),fabs(tmp_vect1[0+1])));
        offset=forall_i1[0+(0)];
        *(_a+shift)=*(_c+offset);

      }
        tmp_vect4=(float *) malloc((2)*sizeof(float));
      shift=0;
      offset=0;
      *(tmp_vect4+shift)=*(_i1+offset);

      shift=1;
      offset=0;
      *(tmp_vect4+shift)=*(_i1+offset);

      shift=(min(_i[0]+1+shp0,_i[0]+1)+forall_i3[0+0])*(_n)+(min(_n,fabs(tmp_vect1[0+1])+1));
      offset=(tmp_vect4[0+0]+forall_i3[0+0])*(_n)+(tmp_vect4[1+0]+0);
      for (i1=0; i1<(_n-min(_n,fabs(tmp_vect1[0+1])+1)); i1++) {
        *(_a+shift)=*(_a+offset);
        shift++;
        offset++;
      }

      for (forall_i2[0]=(forall_i3[0+0]); forall_i2[0]<(forall_i3[0+0])+(1); forall_i2[0]++) {
          temp1=(float *) malloc((((_n)*(_n)))*sizeof(float));
          tmp_vect5=(float *) malloc((1)*sizeof(float));
        shift=0;
        offset=forall_i2[0+(0)];
        *(tmp_vect5+shift)=*(_c+offset);

        shift=0;
        for (i0=0; i0<(_n-min(_n,fabs(tmp_vect1[0+1])+1)); i0++) {
          *(temp1+shift)=tmp_vect5[0+0];
          shift++;
        }

        shift=0;
        offset=(_i[0])*(_n)+(_i1[0+0]);
        for (i1=0; i1<(_n-min(_n,fabs(tmp_vect1[0+1])+1)); i1++) {
          *(temp1+shift)*=*(_a+offset);
          shift++;
          offset++;
        }

      }
      shift=(min(_i[0]+1+shp0,_i[0]+1)+forall_i3[0+0])*(_n)+(min(_n,fabs(tmp_vect1[0+1])+1));
      offset=0;
      for (i1=0; i1<(_n-min(_n,fabs(tmp_vect1[0+1])+1)); i1++) {
        *(_a+shift)-=*(temp1+offset);
        shift++;
        offset++;
      }

    }
  }
}


