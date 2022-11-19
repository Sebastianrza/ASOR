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

    if(dup2(fd,1) == -1){
        perror("Error con Dup2");
        exit(EXIT_FAILURE);
    }

    printf("Se está escribiendo en el fichero... \n");
    close(fd);

    return 0;
}