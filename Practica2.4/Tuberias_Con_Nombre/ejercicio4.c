#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char** argv){
    

    if(argc < 2){
        fprintf(stderr, "Usage: %s <arg>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char cpath[200];
    getcwd(cpath, 200);

    char *npath = strcat(cpath, "/pipe");

    mkfifo(npath, 0777);

    int fd = open(npath, O_WRONLY);
    if(fd == -1){
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    if(write(fd, argv[1], strlen(argv[1])) == -1){
        perror("Error en el write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;

}