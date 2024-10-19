#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {

  int n;
  double **M;
  double r, t;
  
  if (scanf("%d\n", &n) != 1) {
    printf("Formato de saída INCORRETO\n");
    exit(1);
  }
  
  M = (double **) malloc(sizeof(double *) * n);
  for (int i = 0; i < n; ++i)
    M[i] = (double *) malloc(sizeof(double) * n);
    
  for (int i =0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (scanf("%lf", &(M[i][j])) != 1) {
        printf("Formato de saída INCORRETO\n");
        exit(1);
      }

  if (scanf("%lf\n%lf", &r, &t) != 2) {
    printf("Formato de saída INCORRETO\n");
    exit(1);
  }

  printf("n = %d\n", n);
  printf("A':\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("%.15e ", M[i][j]);
    printf("\n");
  }
  printf("r = %.15e\n", r);
  printf("t = %.8e\n", t);
  printf("Formato de saída correto!\n");
  
  for (int i = 0; i < n; ++i)
    free(M[i]);
  free(M);
}
