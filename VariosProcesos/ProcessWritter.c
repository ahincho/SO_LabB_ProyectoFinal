
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort con Varios Procesos
* - Nota: Se intento pero surgieron problemas al recuperar
*   la variable compartida entre los procesos 'mySharedArray'
*/

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# define N 10
# define TERMINAL "/bin/ls"
# define PORT 34
# define PERMISSIONS
# define ERROR -1

int main() {
    key_t key = ftok(TERMINAL, PORT);
    printf("Size: %d\n", (int) sizeof(int) * N);
    int shmid = shmget(key, (int) sizeof(int) * N, IPC_CREAT);
    if (shmid == ERROR) {
        printf("Error al crear la memoria compartida.\n");
        exit(EXIT_FAILURE);
    }
    int* arr = (int *) shmat(shmid, 0, 0);
    if (*arr == ERROR) {
        printf("Error al recuperar la memoria compartida.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0 ; i < N ; i++) {
        arr[i] = i;
    }
    for (int i = 0 ; i < N ; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nSe escribio en memoria compartida!\n");
    int detach = shmdt((void *) arr);
    if (detach == ERROR) {
        printf("Error al liberar la memoria compartida.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
