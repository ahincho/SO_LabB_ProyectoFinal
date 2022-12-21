
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
# define PERMISSIONS 0600

int main() {
    key_t key = ftok(TERMINAL, PORT);
    int shmid = shmget(key, (int) sizeof(int) * N, IPC_EXCL);
    int* arr = shmat(shmid, 0, SHM_RDONLY);
    for (int i = 0 ; i < N ; i++) {
        printf("%d \n", arr[i]);
    }
    printf("\nSe leyo la memoria compartida!\n");
    shmdt((void *) arr);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
