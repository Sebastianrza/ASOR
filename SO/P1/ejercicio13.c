#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

    struct timeval tv1, tv2;

    if(gettimeofday(&tv1, NULL)==-1){
        perror("ERROR");
        return -1;
    }

    int i = 0;

    while(i < 1000000){
        i++;
    }

    if(gettimeofday(&tv2, NULL) == -1){
        perror("ERROR");
        return -1;
    }

    int result = tv2.tv_sec - tv1.tv_usec;
    printf("El tiempo restante es: %i \n", result);

    return 0;
}