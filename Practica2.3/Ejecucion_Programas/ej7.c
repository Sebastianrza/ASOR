#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main( int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "Usage: %s<comando con comillas>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int tamanio = strlen(argv[1])+1;

    char *cmd = malloc(sizeof(char)*tamanio);
    cmd = argv[1];
    cmd[tamanio-1] = '\0';

    if(system(cmd) == -1){
        fprintf(stderr, "Error en el comando system\n");
        exit(EXIT_FAILURE);
    }

    printf("El comando terminó de ejecutarse");
    return 0;
}