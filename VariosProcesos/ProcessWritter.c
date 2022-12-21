
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
# define PERMISSIONS

int main() {
    key_t key = ftok(TERMINAL, PORT);
    printf("Size: %d\n", (int) sizeof(int) * N);
    int shmid = shmget(key, (int) sizeof(int) * N, IPC_CREAT);
    printf("OK1\n");
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
