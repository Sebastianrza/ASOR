#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){

    time_t t;

    t = time(&t);

    if(t == -1){
        perror("ERROR");
        return -1;
    } 

    printf("Tiempo desde el Epoch: %i \n", t);
}