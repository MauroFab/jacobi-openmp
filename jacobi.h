#ifndef JACOBI_H
#define JACOBI_H

#define LIMITE_DE_ITERACIONES 1000
#define EPSILON 0.00001

// Usar omp_set_num_threads(n), con n un entero, para configurar la Cantidad
//de threads, y en consecuencia, de nucleos que podra usar.
void resolver_sistema_con_jacobi(double** matriz, int tamanio_matriz,
  double* b, double* solucion);

#endif
