
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>

# define MSARR_NAME "/mySharedArray"
# define PERMISSIONS 00600

void crearArrayCompartido(int fileDesc, int bSize) {
    // File Descriptor para el objeto compartido
    fileDesc = shm_open(MSARR_NAME, O_CREAT | O_RDWR, PERMISSIONS);
    if (fileDesc == -1) {
        printf("Error al crear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fileDesc, bSize) == -1) {
        printf("Error al reservar espacio para el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int fd;
    crearArrayCompartido(fd, 100);
}
