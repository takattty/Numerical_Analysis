#include <stdio.h>
#include <math.h>

#define N 5

int main(void) {
  double a[N][N+1] = {
    { 1.0, 2.0, 3.0, 2.0, 1.0, 3.0 },
    { 1.0, 1.0, 1.0, 3.0, 4.0, 4.0 },
    { 2.0, 1.0, 2.0, 2.0, 3.0, 3.0 },
    { -1.0, -1.0, 2.0, 1.0, 3.0, 1.0 },
    { 1.0, 1.0, 3.0, 1.0, -1.0, 3.0 }
  };

  int i, j, k, l;
  double m;
 
  for(l=0; l<N; l++) {
    for(j=0; j<N; j++) {
      m = a[j][l] / a[l][l];
      for(k=1; k<N+1; k++){
	if(j != l) {
	  a[j][k] -= m*a[l][k];
	}
      }
    }
  }
  
  for(j=0; j<N; j++) {
    for(k=0; k<N+1; k++) {
      printf("%f ", a[j][k]);
    }
    printf("\n");
  }
  


  for (i=0; i<N; i++){
    a[i][N] /= a[i][i];
    printf("x%d = %f\n", i, a[i][N]);
  }
  return 0;
}
