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

    char *npath1 = "pipe1";
    char *npath2 = "pipe2";
    char buff[256];
    int nfd;
    int pip1 = open(npath1, O_WRONLY | O_NONBLOCK);

    if(pip1 == -1){
        mkfifo(npath1, 0777);
    }

    int pip2 = open(npath2, O_WRONLY | O_NONBLOCK);

    if(pip2 == -1){
        mkfifo(npath2, 0777);
    }
    
    if(pip2 > pip1) nfd = pip2+1;
    else nfd = pip1 + 1;

    while(1){
        fd_set readfd;

        FD_ZERO(&readfd);
        FD_SET(pip1, &readfd);
        FD_SET(pip2, &readfd);

        int numf = select(nfd, &readfd, NULL,NULL,NULL);

        if(numf == -1){
            perror("Error en la instrucción select");
            close(pip2);
            close(pip1);
            exit(EXIT_FAILURE);
        }

        if(FD_ISSET(pip1, &readfd)){
            int leido = read(pip1, buff, 256);
            if(leido == 0){
                close(pip1);
                int pip1 = open(npath1, O_RDONLY | O_NONBLOCK, 0222);
                if(pip1 == -1){
                    pip1 = mkfifo(npath1, 0666);
                }

                if(pip1+1 > nfd) nfd = pip1 + 1;
            }
            else{
                write(1, "tuberia:", strlen("tuberia: "));
                write(1, buff, leido);
            }
        }

        if(FD_ISSET(pip2, &readfd)){
            int leido = read(pip2, buff, 256);
            if(leido == 0){
                close(pip2);
                int pip2 = open(npath2, O_RDONLY | O_NONBLOCK, 0222);
                if(pip2 == -1){
                    pip2 = mkfifo(npath2, 0666);
                }

                if(pip2+1 > nfd) nfd = pip2 + 1;
            }
            else{
                write(1, "tuberia2:", strlen("tuberia2: "));
                write(1, buff, leido);
            }
        }
    }

    close(pip1);
    close(pip2);

    return 0;
}