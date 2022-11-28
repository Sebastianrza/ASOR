#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void descrip_change(){

    int fdout = open("/tmp/daemon.out", O_CREAT | O_RDWR, 00777);

    if(fdout == -1){
        perror("Error en el fichero");
        exit(EXIT_FAILURE);
    }

    int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);

    if(fderr == -1){
        perror("Error en el fichero err");
        exit(EXIT_FAILURE);
    }

    int fdin = open("/dev/null", O_CREAT | O_RDWR, 00777);

    if(fdin == -1){
        perror("Error el fichero es null");
        exit(EXIT_FAILURE);
    }

    if(dup2(fdout, 1) == -1){
        perror("Error dup2 fdout");
        exit(EXIT_FAILURE);
    }

    if(dup2(fderr, 2) == -1){
        perror("Error dup2 fderr");
        exit(EXIT_FAILURE);
    }

    if(dup2(fdin, 0) == -1){
        perror("Error dup2 fdin");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]){

    if(argc < 2){
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == -1){
        perror("Error fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        setsid();
        descrip_change();

        if(execvp(argv[1], &argv[1]) == -1){
            perror("Error en el execvp");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}