CC=gcc
CFLAGS=-lm -fopenmp

jacobi: jacobi.c main.c matrices_aleatorias.c
	$(CC) $^ $(CFLAGS) -o $@

test: jacobi.c test.c
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY : clean
clean :
			 -rm jacobi

.PHONY : clean_test
clean_test :
			 -rm test
