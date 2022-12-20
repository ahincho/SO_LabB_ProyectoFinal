/*
* @Autor: Neira Carrasco, Darwin
* @Autor: Hincho Jove, Angel Eduardo
* @Email: dneirac@unsa.edu.pe
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort Recursivo
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define N 6
# define LOWER 0
# define UPPER 10

void mergeSort(int arr[], int l, int m, int r) {
	// Establecer las dimensiones para los nuevos
	// arreglos tanto para izquierda como para derecha
	int nLeft = m - l + 1;
	int nRight = r - m;
	// Creamos los nuevos arreglos para izquierda y derecha
	int L[nLeft];
	int R[nRight];
	// Copiamos la parte de la izquierda en el nuevo arreglo
	for (int i = 0 ; i < nLeft ; i++) {
		L[i] = arr[l + i];
	}
	// Copiamos la parte de la derecha en el nuevo arreglo
	for (int j = 0 ; j < nRight ; j++) {
		R[j] = arr[m + 1 + j];
	}
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
		// La variable K hace referencia a la posicion en el arreglo
		// original en la cual nos encontramos actualmente iterando
		// En cada evaluacion copia o reasigna un valor y se continua
		k++;
	}
	// Este caso se da cuando la copia izq esta correcta
	// Copiamos los elementos restantes en el arreglo de izquierda
	while (i < nLeft) {
		arr[k] = L[i];
		i++;
		k++;
	}
	// Este caso se da cuando la copia derecha esta correcta
	// Copiamos los elementos restantes en el arreglo de derecha
	while (j < nRight) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// Algoritmo Recursivo para MergeSort
void merge(int arr[], int l, int r) {
	// Mientras que el valor del indice L sea menor que R
	if (l < r) {
		// Calculamos la posicion o indice medio del arreglo
		int m = l + (r - l)/2;
		// Dividimos en dos secciones recursivas
		// Primero evaluaremos la parte de la izquierda desde L a M
		merge(arr, l, m);
		// Luego evaluaremos la parte de la derecha desde M + 1 a R
		merge(arr, m + 1, r);
		// Finalmente llamamos al metodo MergeSort 
		mergeSort(arr, l, m, r);
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

// Metodo Main del programa
int main() {
	// Creamos un arreglo de enteros que vamos a arreglar
	int arr[N];
	// Inicializamos el arreglo con valores aleatorios
	initArray(arr);
	// Imprimimos el contenido original del arreglo
	printArray(arr);
	// Ordenaremos el arreglo entre los indices 0 y 5
	merge(arr, 0, N - 1);
	// Imprimimos el contenido de arreglo ya ordenado
	printArray(arr);
	return 0;
}
