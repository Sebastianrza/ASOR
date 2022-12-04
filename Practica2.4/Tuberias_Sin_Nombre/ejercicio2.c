#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char ** argv){
   
   int p_h[2];
   int h_p[2];



    if(pipe(p_h) == -1){
        perror("Error en el Pipe p_h");
        exit(EXIT_FAILURE);
    }

    if(pipe(h_p) == -1){
        perror("Error en el Pipe h_p");
        exit(EXIT_FAILURE);
    }
    char buff[64];
    char flag;
    pid_t pid = fork();

    if(pid == -1) {
        perror("Error en el fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){ // HIJO

        close(p_h[1]);
        close(h_p[0]);
        flag = 'l';
        int i = 0;

        for(i = 0; i < 10; i++){
            read(p_h[0], &buff, sizeof(char)*64);
            printf("(hijo) mensaje recibido (%i): %s\n", i+1, buff);
            if(i == 9){
               flag = 'q';
            }
            write(h_p[1], &flag, sizeof(char));
            printf("(hijo) flag enviado: %c\n", flag);
        }
        printf("(hijo) ha finalizado la comunicación. \n");

        close(p_h[0]);
        close(h_p[1]);

        
    }else{ // padre

        close(p_h[0]);
        close(h_p[1]);
        do{
            printf("\n (padre) escribe un mensaje: ");
            scanf("%s", buff);
            write(p_h[1], &buff, sizeof(char)*64);
            read(h_p[0], &flag, 1);
            printf("(padre) Flag recibido: %c\n", flag);
        }while(flag != 'q');
        printf("(padre) ha finalizado la comunicación. \n\n");

        close(p_h[1]);
        close(h_p[0]);
    }
    return 0;
}