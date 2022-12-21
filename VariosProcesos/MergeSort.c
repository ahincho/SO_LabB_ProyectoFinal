
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>

# define MSARR_NAME "/mySharedArray"
# define PERMISSIONS 00600

int main() {
    int fd; // File Descriptor para el objeto compartido
    fd = shm_open(MSARR_NAME, O_CREAT | O_RDWR, PERMISSIONS);
    if (fd == -1) {
        printf("Error al crear el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
    int byteSz = 200;
    if (ftruncate(fd, byteSz) == -1) {
        printf("Error al reservar espacio para el objeto compartido.\n");
        exit(EXIT_FAILURE);
    }
}
