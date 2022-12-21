
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>

# define MSARR_NAME "/mySharedArray"
# define PERMISSIONS 00600
# define SIZE 100

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
    return fileDesc;
}

void escribirArrayCompartido() {
    int fileDesc = shm_open(MSARR_NAME, O_RDWR, 0);
    int i = 15;
    int* ptr;
    if (fileDesc == -1) {
        printf("Error al recuperar el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    ptr = nmap(0, sizeof(int) , PROT_WRITE, MAP_SHARED, fileDesc, 0);
    if (ptr == MAP_FAILED) {
        printf("Error al mapear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(ptr, i, sizeof(buf));
    close(fileDesc);
}

// Metodo Main del programa
// Para ejecutarlo utilizar el formato: ./MergeSort nElems
int main() {
    // Creando un FileDescriptor de memoria compartida
    int fd = crearArrayCompartido(SIZE);
    // Escribimos en la memoria compartida
    escribirArrayCompartido();
    // Cerramos el acceso o conexion el FileDescriptor
    close(fd);
}
