
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort con Varios Hilos
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# define MILLION 1E+06
# define N 100000
# define LOWER 0
# define UPPER 10

// Creamos un arreglo de enteros que vamos a arreglar
int arr[N];
// Creamos una variable de tipo pthread_t para iterar
pthread_t threadIter;
// Variable de tipo Mutex para cuidar las posibles SC
pthread_mutex_t mutex;
// Creamos una variable para contabilizar la cantidad
// de hilos que se han creado para realizar MergeSort
int nHilos = 0;

// Estructura que contiene los valores de los indices
struct indices {
    int l; // Primera posicion a la izquierda
    int r; // Ultima posicion a la derecha
};

// El metodo mergeSort al ser invocado por los hilos, debemos
// asegurarnos un acceso exclusivo a la variable compartida que
// en este caso sera nuestro arreglo, entonces utilizaremos Mutex
void mergeSort(int arr[], int l, int m, int r) {
	// Establecer las dimensiones para los nuevos
	// arreglos tanto para izquierda como para derecha
	int nLeft = m - l + 1;
	int nRight = r - m;
	// Creamos los nuevos arreglos para izquierda y derecha
	int L[nLeft];
	int R[nRight];
	// Copiamos la parte de la izquierda en el nuevo arreglo
	pthread_mutex_lock(&mutex);
	for (int i = 0 ; i < nLeft ; i++) {
		L[i] = arr[l + i];
	}
	pthread_mutex_unlock(&mutex);
	// Copiamos la parte de la derecha en el nuevo arreglo
	pthread_mutex_lock(&mutex);
	for (int j = 0 ; j < nRight ; j++) {
		R[j] = arr[m + 1 + j];
	}
	pthread_mutex_unlock(&mutex);
	// Variables de apoyo para poder iterar en las posiciones
	int i = 0, j = 0, k = l;
	// Mientras I sea menor a Left y J menor a Right
	// Verificamos que los elementos esten en orden en el arreglo
	while (i < nLeft && j < nRight) {
		// Si la posicion I mas izq es menor o igual a la posicion
		// en derecha entonces en el arreglo original, su primera
		// posicion, que es L, sera igual a ese valor menor. Este
		// proceso se hace para poder ordenar los elementos que se
		// encuentran en los arreglos copiados.
		pthread_mutex_lock(&mutex);
		if (L[i] <= R[j]) {
			// La primera sentencia If hace referencia cuando el
			// valor de la copia izq esta correctamente posicionado
			arr[k] = L[i];
			// Pasamos a la siguiente posicion en la copia izq
			i++;
		} else {
			// En caso ser mayor que los elementos del arreglo de la
			// derecha (los cuales son los mayores supuestos) entonces
			// copiamos ese valor en el arreglo de derecha al original
			arr[k] = R[j];
			// Pasamos a la siguiente posicion en la copia derecha
			j++;
		}
		pthread_mutex_unlock(&mutex);
		// La variable K hace referencia a la posicion en el arreglo
		// original en la cual nos encontramos actualmente iterando
		// En cada evaluacion copia o reasigna un valor y se continua
		k++;
	}
	// Este caso se da cuando la copia izq esta correcta
	// Copiamos los elementos restantes en el arreglo de izquierda
	pthread_mutex_lock(&mutex);
	while (i < nLeft) {
		arr[k] = L[i];
		i++;
		k++;
	}
	pthread_mutex_unlock(&mutex);
	// Este caso se da cuando la copia derecha esta correcta
	// Copiamos los elementos restantes en el arreglo de derecha
	pthread_mutex_lock(&mutex);
	while (j < nRight) {
		arr[k] = R[j];
		j++;
		k++;
	}
	pthread_mutex_unlock(&mutex);
}

void* hiloMerge(void* args) {
	// Recibiendo el parametro que contiene los indices
	struct indices* p = (struct indices *) args;
	// Aumentamos el contador de los hilos creados
	nHilos++;
	// Mientras que el valor del indice L sea menor que R
	if (p->l < p->r) {
		// Calculamos la posicion o indice del medio del arreglo
		int m = p->l + (p->r - p->l) / 2;
		// Dividimos en dos secciones mas pequenias a ordenar
		// Primero evaluaremos la parte de la izquierda desde L a M
		struct indices iLeft = { p->l, m };
		pthread_create(&threadIter, 0, hiloMerge, &iLeft);
		pthread_join(threadIter, NULL);
		// Luego evaluaremos la parte de la derecha desde M + 1 a R
		struct indices iRight = { m + 1, p->r };
		pthread_create(&threadIter, 0, hiloMerge, &iRight);
		pthread_join(threadIter, NULL);
		// Finalmente llamamos al metodo MergeSort
		mergeSort(arr, p->l, m, p->r);
	} else {
		// En caso sea lo suficientemente pequenio y no se necesite
		// dividir para ordenar entonces debemos terminar el hilo
		pthread_exit(0);
	}
}

// Metodo que recibe un array de enteros y no inicializa
// con valores aleatorios entre el rango [LOWER, UPPER]
void initArray(int a[]) {
	srand(time(0));
	for (int i = 0 ; i < N ; i++) {
		a[i] = (rand() % (UPPER - LOWER + 1) + LOWER);
	}
}

// Metodo que recibe un arreglo e imprime su contenido
void printArray(int arr[]) {
	for (int i = 0 ; i < N ; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// Metodo que recibe dos momentos y retorna la diferencia
// El tiempo se medira en MicroSegundos
double timeDiff(struct timeval start, struct timeval end) {
	// Diferencia en tiempo es diff = seconds + microSeconds
	double s = (end.tv_sec - start.tv_sec) * MILLION;
	double ms = (end.tv_usec- start.tv_usec);
	return (s + ms);
}

// Metodo Main del programa
int main() {
	// Inicializamos la variable de tipo Mutex
	pthread_mutex_init(&mutex, NULL);
	// Variables auxiliares para la medicion del tiempo
	struct timeval start, end;
	// Incializamos los valores que queremos ordenar
	struct indices p = { 0, N - 1 };
	// Inicializamos el arreglo con valores aleatorios
	initArray(arr);
	// Imprimimos el contenido original del arreglo
	// printArray(arr); Ya no imprimimos porque usamos muchos elementos
	// Ordenaremos el arreglo entre los indices 0 y 5
	gettimeofday(&start, NULL);
	// Creando un primer hilo para llamar a hiloMerge()
	pthread_create(&threadIter, 0, hiloMerge, &p);
	pthread_join(threadIter, NULL);
	gettimeofday(&end, NULL);
	// Imprimimos el contenido de arreglo ya ordenado
	// printArray(arr); Ya no imprimimos porque usamos muchos elementos
	printf("Cantidad de Elementos Ordenados: %d\n", N);
	printf("Hilos Creados: %d\n", nHilos);
	double diff = timeDiff(start, end);
	printf("Metrica de Tiempo: %.2f MicroSegundos.\n", diff);
	return 0;
}
