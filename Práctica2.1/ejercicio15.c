#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>

int main(){ 

    struct tm *t_Struct;

    time_t t;

    t = time(&t);

    if(t == -1){
        perror("Error");
        return -1;
    }

    t_Struct = localtime(&t);

    if(t_Struct == NULL){
        perror("Error");
        return -1;
    }

    setlocale(LC_ALL, "es_ES");

    char buf[100];

    strftime(buf, 100, "%A, %d de %B de %Y, %H:%M\n", t_Struct);

    printf("Fecha: %s", buf);

    return 0;

}