#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main( int argc, char **argv){

    if(argc != 2){
        fprintf(stderr, "Usage: %s<comando con comillas>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    
    if(execvp(argv[1],argv+1) == -1){
        perror("error execvp");
        exit(EXIT_FAILURE);
    }

    printf("El comando terminó de ejecutarse");

    return 0;
}