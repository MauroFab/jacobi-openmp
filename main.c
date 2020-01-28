#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>
#include "jacobi.h"
#include "matrices_aleatorias.h"

const int n = 20000; //La matriz es de nxn
const int MAX_NUCLEOS = 8;

int main(){
  srand(time(NULL));
  double** matriz = malloc(n*sizeof(double *));
  for(int i=0; i< n; i++) matriz[i] = malloc(n*sizeof(double));
  double* b = malloc(n*sizeof(double));
  double* solucion = malloc(n*sizeof(double));

  alocar_un_vector_aleatorio(b, n);
  alocar_una_matriz_diagonal_dominante_aleatoria(matriz, n);

  double tiempo_usado[MAX_NUCLEOS];
  double start_t, end_t;
  for(int i = 0; i < MAX_NUCLEOS; i++){
    printf("Comienzo usando %i nucleos\n", i+1);
    omp_set_num_threads(i+1);
    start_t = omp_get_wtime();
    resolver_sistema_con_jacobi(matriz,n,b,solucion);
    end_t = omp_get_wtime();
    tiempo_usado[i] = end_t - start_t;
    printf("Fin usando %i nucleos\n", i+1);
  }

  printf("\n");

  for(int i = 1; i < MAX_NUCLEOS; i++){
    printf("Speedup %i nucleos: %f\n", i+1, tiempo_usado[0] / tiempo_usado[i]);
  }

  /*
  for(int i = 0; i < n; i++){
    if(i!=0)
      printf(",");
    for(int j = 0; j < n; j++){
      printf(" %.2f", matriz[i][j]);
    }
  }*/
  return 0;
}
