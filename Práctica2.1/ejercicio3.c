#include <errno.h>
#include <string.h>
#include <stdio.h>


int main(){
    int i;//el limite de errores es 133
    for(i = 0; i < 255; i++) printf("Error %i: %s \n", i, strerror(i));
}