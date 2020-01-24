#include <time.h>
#include <math.h>
#include "matrices_aleatorias.h"
#include <stdlib.h>

void alocar_una_matriz_diagonal_dominante_aleatoria(double** matriz, int tamanio){
  const int MAX_NUMERO_i_DISTINTO_j = 9;
  const int MINIMO_NUMERO_i_IGUAL_j = MAX_NUMERO_i_DISTINTO_j * tamanio;
  for(int i = 0; i < tamanio; i++){
    for(int j = 0; j < tamanio; j++){
      if(i == j){
        matriz[i][j] = MINIMO_NUMERO_i_IGUAL_j + ((rand() % 100));
      }else{
        matriz[i][j] = rand() % (MAX_NUMERO_i_DISTINTO_j + 1);
      }
    }
  }
}


void alocar_un_vector_aleatorio(double* array, int tamanio){
  for(int i = 0; i < tamanio; i++){
    array[i] = rand() % 10;
  }
}
