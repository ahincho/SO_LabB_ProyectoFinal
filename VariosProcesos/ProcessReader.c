
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
# define PERMISSIONS 0600

int main() {
    key_t key = ftok(TERMINAL, PORT);
    int shmid = shmget(key, (int) sizeof(int) * N, PERMISSIONS | IPC_CREAT);
    int* arr = shmat(shmid, 0, SHM_RDONLY);
    for (int i = 0 ; i < N ; i++) {
        printf("%d \n", arr[i]);
    }
    shmdt((void *) arr);
    return 0;
}
