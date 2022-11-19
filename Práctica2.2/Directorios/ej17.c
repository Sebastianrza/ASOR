#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/sysmacros.h>

int main( int argc, char *argv[]){

    struct stat sb;
    int tamanio = 0;

    if(argc != 2){

        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(stat(argv[1], &sb) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if(!S_ISDIR(sb.st_mode)){
        fprintf(stderr, "%s tiene que ser un directorio. \n", argv[0]);
        exit(EXIT_FAILURE);
    }else{

        DIR *dir;

        dir = opendir(argv[1]);
        struct dirent *structDir = readdir(dir);

        while(structDir != NULL){

            if(structDir->d_type == DT_REG){

                printf("%s\n", structDir->d_name);
                tamanio = tamanio + structDir->d_reclen;

            }
            else if(structDir->d_type == DT_DIR){

                printf("%s\n", structDir->d_name);
                tamanio = tamanio + structDir->d_reclen;

            }
            else if(structDir->d_type == DT_LNK){

                char path[PATH_MAX];
                int btes = readlink(structDir->d_name,path,PATH_MAX);

                if(btes == -1){
                    perror("Error con el nombre del fichero enlazado");
                    exit(EXIT_FAILURE);
                }

                path[btes] = "\0";
                printf("%s->%s\n", structDir->d_name, path);
            }

            structDir = readdir(dir);
        }
    }

    printf("Tamanio: %d\n", tamanio);
    return 0;

}