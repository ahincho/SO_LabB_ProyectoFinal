
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Autor: Neira Carrasco, Darwin Jesus
* @Autor: Tacca Apaza, Nohelia Estefhania
* @Email: ahincho@unsa.edu.pe
* @Email: dneirac@unsa.edu.pe
* @Email: ntacca@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort con Varios Procesos
* - Nota: Se intento pero surgieron problemas al recuperar
*   la variable compartida entre los procesos 'mySharedArray'
*/

# include "./SharedMemory.h"
# include <stdio.h>
# include <sys/mman.h>
# define LOWER 0
# define UPPER 10

// Cantidad de elementos aleatorios a ordenar
int nElems = 0;
// Puntero al arreglo de elementos con nElems ha crear
int* arr;

// Metodo que recibe un array de enteros y no inicializa
// con valores aleatorios entre el rango [LOWER, UPPER]
void initArray(int a[]) {
	srand(time(0));
	for (int i = 0 ; i < nElems ; i++) {
		a[i] = (rand() % (UPPER - LOWER + 1) + LOWER);
	}
}

// Metodo que recibe un arreglo e imprime su contenido
void printArray(int arr[]) {
	for (int i = 0 ; i < nElems ; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// Metodo Main del programa
// Para ejecutarlo utilizar el formato: ./MergeSort nElems
int main(int argc, char *argv[]) {
    // Pediremos la cantidad de elementos como argumento al ejecutar
	if (argc != 2) {
		printf("Para ejecutar el programa seguir el formato:\n");
		printf("\t./MergeSort nElems\n");
		printf("Siendo 'nElems' una cantidad entera de elementos.\n");
		exit(EXIT_FAILURE);
	}
	// Se recibio el parametro de nElems correctamente
	sscanf(argv[argc - 1], "%d", &nElems);
    // Creamos un arreglo de nElems
	arr = (int *) calloc(nElems, sizeof(int));
    int* b = (int *) calloc(nElems, sizeof(int));
    // Inicializar el arreglo de enteros aleatorios
    initArray(arr);
    printArray(arr);
    // Creando un FileDescriptor de memoria compartida
    int fd = crearArrayCompartido(nElems * sizeof(int));
    // Escribimos en la memoria compartida
    escribirArrayCompartido(arr);
    // Cerramos el acceso o conexion el FileDescriptor
    b = leerArrayCompartido();
    printArray(b);
}
