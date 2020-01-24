#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>
#include "jacobi.h"
#define MARGEN_DE_ERROR 0.01

int cantidad_de_tests = 0;

void inicializar_matriz(double** a, int n){
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      a[i][j] = 0;
}

bool es_igual(double* a,double* b, int n){
  for(int i = 0; i < n; i++){
    if(!((a[i] - MARGEN_DE_ERROR <  b[i]) && (b[i] < a[i] + MARGEN_DE_ERROR))){
      return false;
    }
  }
  return true;
}

void correr_test(double** a, double*b, double*x, double* x_esperado, int n){
  cantidad_de_tests++;
  printf("\033[0;34m");
  printf("\nTest %i\n", cantidad_de_tests);
  printf("\033[0m");
  printf(" [");
  for(int i = 0; i < n; i++){
    if(i!=0)
      printf(",");
    for(int j = 0; j < n; j++){
      printf(" %.2f", a[i][j]);
    }
  }
  printf("]*x=[");
  //print b
  for(int i = 0; i < n - 1; i++)
    printf("%.2f,", b[i]);
  printf("%.2f]\n", b[n-1]);

  printf(" Resultado esperado: [");
  for(int i = 0; i < n - 1; i++)
    printf("%.2f,", x_esperado[i]);
  printf("%.2f]\n", x_esperado[n-1]);

  resolver_sistema_con_jacobi(a,n,b,x);
  printf(" Resultado obtenido: [");
  for(int i = 0; i < n - 1; i++)
    printf("%.2f,", x[i]);
  printf("%.2f]\n", x[n-1]);

  if(es_igual(x,x_esperado,n)){
    //Texto verde
    printf("\033[0;32m");
    printf("Test exitoso\n\n");
    //vuelvo al default
    printf("\033[0m");
  }else{
    //Texto rojo
    printf("\033[0;31m");
    printf("Test fallido\n");
    //vuelvo al default
    printf("\033[0m");
  }
}

int main(){

  printf("\nMargen de error tolerable en resultados: %f\n", MARGEN_DE_ERROR);

  //Preparo primer test
  int n = 2; // Matriz n*n
  //Se resuelve A*x=b
  double** a = malloc(n*sizeof(double *));
  for(int i=0; i< n; i++) a[i] = malloc(n*sizeof(double));
  double* b = malloc(n*sizeof(double));
  double* x = malloc(n*sizeof(double));
  double* x_esperado = malloc(n*sizeof(double));
  inicializar_matriz(a,n);
  a[0][0]=1;
  a[1][1]=1;
  b[0] = 10;
  b[1] = 5;
  x_esperado[0]=10;
  x_esperado[1]=5;
  correr_test(a,b,x,x_esperado,n);
  free(b);
  free(x);
  free(x_esperado);
  for (int i = 0; i < n; i++)
    free(a[i]);
  free(a);

  //Preparo segundo test
  n = 3;
  a = malloc(n*sizeof(double *));
  for(int i=0; i< n; i++) a[i] = malloc(n*sizeof(double));
  b = malloc(n*sizeof(double));
  x = malloc(n*sizeof(double));
  inicializar_matriz(a,n);
  x_esperado = malloc(n*sizeof(double));
  a[0][0]=1;
  a[1][1]=2;
  a[2][2]=10;
  b[0] = 100;
  b[1] = 100;
  b[2] = 100;
  x_esperado[0]=100;
  x_esperado[1]=50;
  x_esperado[2]=10;
  correr_test(a,b,x,x_esperado,n);
  free(b);
  free(x);
  free(x_esperado);
  for (int i = 0; i < n; i++)
    free(a[i]);
  free(a);

  //Preparo tercer test
  n = 3;
  a = malloc(n*sizeof(double *));
  for(int i=0; i< n; i++) a[i] = malloc(n*sizeof(double));
  b = malloc(n*sizeof(double));
  x = malloc(n*sizeof(double));
  inicializar_matriz(a,n);
  x_esperado = malloc(n*sizeof(double));
  a[0][0]=4;
  a[0][1]=-2;
  a[0][2]=1;

  a[1][0]=1;
  a[1][1]=5;
  a[1][2]=-2;

  a[2][0]=3;
  a[2][1]=-1;
  a[2][2]=-8;

  b[0] = -3;
  b[1] = 1;
  b[2] = 2;
  x_esperado[0]=-0.57;
  x_esperado[1]=0.12;
  x_esperado[2]=-0.48;
  correr_test(a,b,x,x_esperado,n);
  free(b);
  free(x);
  free(x_esperado);
  for (int i = 0; i < n; i++)
    free(a[i]);
  free(a);

  return 0;
}
