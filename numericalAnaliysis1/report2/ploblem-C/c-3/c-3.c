#include <stdio.h>
#include <math.h>

#define N 3
#define EPSILON 1.e-8


int main(void) {
  double a[N][N] = {
    { 4.0, 2.0, 1.0 },
    { 2.0, 4.0, 2.0 },
    { 1.0, 2.0, 4.0 }
  };

  double u[N][N];
  double b[N][N];
  double coef_max;
  double theta, cc, ss;
  double error = 1. ;
  int i, j, p, q, k, l;
  int count = 0 ;
  FILE *fp ;
  fp = fopen("c-3.d", "w");

  for( l=0; l<N; l++ ) {
    for( k=0; k<N; k++ ) {
      u[l][k] = 0.0;
    }
  }

  for( i=0; i<N; i++ ) {
    u[i][i] = 1.0 ;
  }

  while( error > EPSILON ) {
    coef_max = 0.0;
    for( i=0; i<N-1; i++ ) {
      for( j=i+1; j<N; j++ ) {
	      if( fabs(a[i][j]) > coef_max ) {
	        p = i;
	        q = j;
	        coef_max = fabs( a[i][j] );
	      }
      }
    }

    if( a[p][p] != a[q][q] ) {
      theta = 0.5 * atan( 2.*a[p][q]/(a[q][q] - a[p][p]) );
    }
    else {
      theta = 0.25 * M_PI * a[p][q] / fabs( a[p][q] );
    }

    cc = cos(theta);
    ss = sin(theta);

    for( i=0; i<p; i++ ) {
      for( j=0; j<q; j++ ) {
	      b[i][j] = a[i][j];
      }
      for( j=q+1; j<N; j++) {
	      b[i][j] = a[i][j];
      }
    }
    for( i=p+1; i<N; i++ ) {
      for( j=0; j<q; j++ ) {
	      b[i][j] = a[i][j];
      }
      for( j=q+1; j<N; j++ ) {
	      b[i][j] = a[i][j];
      }
    }


    for( j=0; j<q; j++ ) {
      b[p][j] = a[p][j] * cc - a[q][j] * ss ;
      b[q][j] = a[p][j] * ss + a[q][j] * cc ;
    }

    for( j=q+1; j<N; j++ ) {
      b[p][j] = a[p][j] * cc - a[q][j] * ss ;
      b[q][j] = a[p][j] * ss + a[q][j] * cc ;
    }

    for( i=0; i<p; i++ ) {
      b[i][p] = a[i][p] * cc - a[i][q] * ss ;
      b[i][q] = a[i][p] * ss + a[i][q] * cc ;
    }

    for( i=p+1; i<N; i++ ) {
      b[i][p] = a[i][p] * cc - a[i][q] * ss ;
      b[i][q] = a[i][p] * ss + a[i][q] * cc ;
    }

    b[p][p] = a[p][p] * cc * cc + a[q][q] * ss * ss - 2.*a[p][q] * ss * cc ; 
    b[q][q] = a[q][q] * cc * cc + a[p][p] * ss * ss + 2.*a[p][q] * ss * cc ; 
    b[p][q] = ( a[p][p] - a[q][q] ) * ss * cc + a[p][q] * ( cc * cc - ss * ss );
    b[q][p] = b[p][q];

    error = 0.;
    for( i=0; i<N; i++ ) {
      for( j=0; j<N; j++ ) {
	      error += fabs( a[i][j] - b[i][j] );
      }
    }

    for( i=0; i<N; i++ ) {
      for( j=0; j<N; j++ ) {
	      a[i][j] = b[i][j];
      }
    }

    for( i=0; i<N; i++ ) {
      double w = u[i][p] * cc - u[i][q] * ss;
      u[i][q] = u[i][p] * ss + u[i][q] * cc;
      u[i][p] = w;
    }
    printf("Step No.%2d error = %.16e\n", count, error);
    count++;
  }

  printf("\n");

  printf("Eigenvalue:  Eigenvector\n");
  fprintf(fp, "Eigenvalue:  Eigenvector\n");

  for(i=0;i<N;i++){
    printf("%9.6f ", a[i][i]);
    fprintf(fp, "%9.6f ", a[i][i]);
  }
  printf("\n\n");
  fprintf(fp, "\n\n");

  printf(" Eigenvector\n" );
  fprintf(fp, " Eigenvector\n" );
  for(i=0;i<N;i++){
    for(j=0; j<N; j++){
      printf( "%9.6f ", u[i][j]) ;
      fprintf(fp, "%9.6f ", u[i][j]) ;
    }
    printf("\n");
    fprintf(fp, "\n");
  }

  fclose(fp);
  return 0;
}