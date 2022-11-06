#include <sys/types.h>
#include <unistd.h>

int main(){

    if(setuid(0) == -1){
        return -1;
    }
    return 0;

}