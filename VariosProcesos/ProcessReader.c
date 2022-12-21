
/*
* @Autor: Hincho Jove, Angel Eduardo
* @Email: ahincho@unsa.edu.pe
* @File: MergeSort.c
* @Descripcion: Algoritmo MergeSort con Varios Procesos
* - Nota: Se intento pero surgieron problemas al recuperar
*   la variable compartida entre los procesos 'mySharedArray'
*/

# include <stdio.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdio.h>
# define N 10
# define PERMISSIONS 00666
# define TERMINAL "./bin/ls"
# define PORT 34

int main() {
    key_t key = ftok(TERMINAL, PORT);
    int shmid = shmget(key, sizeof(int *) * N, PERMISSIONS | IPC_EXCL);
    int* arr = shmat(shmid, NULL, 0);
    for (int i = 0 ; i < N ; i++) {
        printf("%d \n", arr[i]);
    }
    shmdt((void *) arr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
