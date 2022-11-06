#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>


int main(){

    if(setuid(0) == -1){
        perror("Error");
        printf("Salida: %s", strerror(errno));
    }

    return 0;
}