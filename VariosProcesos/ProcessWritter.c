
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
# include <stdio.h>
# define N 10
# define TERMINAL "/bin/ls"
# define PORT 34

int main() {
    key_t key = ftok(TERMINAL, PORT);
    printf("Size: %d\n", sizeof(int) * N);
    int shmid = shmget(key, sizeof(int) * N, IPC_CREAT);
    int* arr = (int *) shmat(shmid, 0, 0);
    for (int i = 0 ; i < N ; i++) {
        arr[i] = i;
    }
    for (int i = 0 ; i < N ; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nSe escribio en memoria compartida!\n");
    shmdt((void *) arr);
    return 0;
}
