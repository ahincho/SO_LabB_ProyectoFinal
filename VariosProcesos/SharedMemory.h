
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Modulo para trabajar con memoria compartida
*/

# ifndef SHAREDMEMORY_H
# define SHAREDMEMORY_H

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

void escribirArrayCompartido(int write) {
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
    memcpy(ptr, &write, sizeof(write));
    close(fileDesc);
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

# endif
