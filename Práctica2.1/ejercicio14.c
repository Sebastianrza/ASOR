#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){


    struct tm *tstruct;

    time_t t;

    if(t == -1){
        perror("Error");
        return -1;
    }

    tstruct = localtime(&t);

    if(tstruct == NULL){
        perror("ERROR");
        return -1;
    }

    printf("Año actual: %i\n", 1900 + tstruct->tm_year);

    return 0;
}