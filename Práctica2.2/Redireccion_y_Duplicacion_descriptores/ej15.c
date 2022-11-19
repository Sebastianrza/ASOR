#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main( int argc, char *argv[]){

    int fd;

    if(argc != 2){

        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(fd == open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644) == -1){
        perror("Error al abrir el fichero");
        exit(EXIT_FAILURE);
    }

    if(lockf(fd, F_TLOCK,0) == -1){
        printf("El cerrojo se encuentra bloqueado.\n");
    }else{

        printf("La hora: %ld\n", time(NULL));
        sleep(30);
        lockf(fd, F_ULOCK,0);
        printf("Cerrojo libre \n");
    }

    close(fd);

    return 0;

}