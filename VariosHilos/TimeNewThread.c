
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort con Varios Hilos
*/

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
# define N 1000
# define MILLION 1E+06

// Metodo que recibe dos momentos y retorna la diferencia
// El tiempo se medira en MicroSegundos
double timeDiff(struct timeval start, struct timeval end) {
	// Diferencia en tiempo es diff = seconds + microSeconds
	double s = (end.tv_sec - start.tv_sec) * MILLION;
	double ms = (end.tv_usec- start.tv_usec);
	return (s + ms);
}

void* crearHilo(void* args) {
	printf("Hilo 1: He sido creado con metodo crearHilo()\n");
	// El hilo no ejecutara tarea alguna, solo nos ayuda a
	// evaluar el tiempo requerido para crear un nuevo hilo
	pthread_exit(0);
}

// Metodo Main del programa
// Para ejecutarlo utilizar el formato: ./MergeSort nElems
int main() {
	// Variable auxiliar pthread_t para crear otro hilo
	pthread_t newThread;
	// Variables auxiliares para la medicion del tiempo
	struct timeval start, end;
	// Recuperar el momento del dia en el cual estamos
	gettimeofday(&start, NULL);
	// Evaluaremos la cantidad de tiempo que necesitamos
	// para poder crear y poner en ejecucion un hilo
	pthread_create(&newThread, 0, crearHilo, NULL);
	pthread_join(newThread, NULL);
	// Recuperar el momento del dia en que se termino
	gettimeofday(&end, NULL);
	// Calculando el tiempo para crear un unico hilo
	double diff = timeDiff(start, end);
	printf("Tiempo para crear %d Thread: %.2f MicroSegundos.\n", diff);
	return 0;
}
