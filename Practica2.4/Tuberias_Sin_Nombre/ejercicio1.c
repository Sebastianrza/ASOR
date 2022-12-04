#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char ** argv){
    if(argc < 5){
        fprintf(stderr, "Usage: %s <comando1> <arg1> <comando2> <arg2>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];

    if(pipe(fd) == -1){
        perror("Error en el Pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid == -1) {
        perror("Error en el fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){ // HIJO

        if(dup2(fd[0], 0) == -1){
            perror("ERROR EN EL DUP2 HIJO");
            exit(EXIT_FAILURE);
        }

        close(fd[0]);
        close(fd[1]);

        char *nwargv[] = {NULL, NULL, NULL};

        nwargv[0] = argv[3];    
        nwargv[1] = argv[4];

        if(execvp(argv[3], nwargv) == -1){
            perror("Error execvp del hijo");
            exit(EXIT_FAILURE);
        }
        
    }else{ // padre

        if(dup2(fd[1], 0) == -1){
            perror("ERROR EN EL DUP2 Padre");
            exit(EXIT_FAILURE);
        }

        close(fd[0]);
        close(fd[1]);

        char *nwargv[] = {NULL, NULL, NULL};

        nwargv[0] = argv[1];    
        nwargv[1] = argv[2];

        if(execvp(argv[1], nwargv) == -1){
            perror("Error execvp del padre");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}