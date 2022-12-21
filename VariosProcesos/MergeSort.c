
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>

# define MSARR_NAME "/mySharedArray"
# define PERMISSIONS 00600
# define LOWER 0
# define UPPER 10

// Cantidad de elementos aleatorios a ordenar
int nElems = 0;
// Puntero al arreglo de elementos con nElems ha crear
int* arr;

int crearArrayCompartido(int bSize) {
    // File Descriptor para el objeto compartido
    int fileDesc = shm_open(MSARR_NAME, O_CREAT | O_RDWR, PERMISSIONS);
    if (fileDesc == -1) {
        printf("Error al crear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fileDesc, bSize) == -1) {
        printf("Error al reservar espacio para el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    close(fileDesc);
    return fileDesc;
}

void escribirArrayCompartido(int* write) {
    int fileDesc = shm_open(MSARR_NAME, O_RDWR, 0);
    int* ptr;
    if (fileDesc == -1) {
        printf("Error al recuperar el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    ptr = mmap(0, sizeof(int), PROT_WRITE, MAP_SHARED, fileDesc, 0);
    if (ptr == MAP_FAILED) {
        printf("Error al mapear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(ptr, &write, sizeof(int));
    close(fileDesc);
}

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

int* leerArrayCompartido() {
    struct stat msArrSt;
    int fileDesc = shm_open(MSARR_NAME, O_RDONLY, 0);
    if (fileDesc == -1) {
        printf("Error al recuperar el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    if (fstat(fileDesc, &msArrSt) == -1) {
        printf("Error al recuperar estructura msArrSt.\n");
        exit(EXIT_FAILURE);
    }
    int* ptr = mmap(NULL, msArrSt.st_size, PROT_READ, MAP_SHARED, fileDesc, 0);
    if (ptr == MAP_FAILED) {
        printf("Error al mapear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    } 
    printf("Valor en Memo Compartida:.\n");
    printArray(ptr);
    close(fileDesc);
    return ptr;
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
    // Inicializar el arreglo de enteros aleatorios
    initArray(arr);
    // Creando un FileDescriptor de memoria compartida
    int fd = crearArrayCompartido(sizeof(arr));
    // Escribimos en la memoria compartida
    escribirArrayCompartido(arr);
    // Cerramos el acceso o conexion el FileDescriptor
    leerArrayCompartido();
}
