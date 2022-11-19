#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    struct stat sb;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(stat(argv[1], &sb) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("MAJOR: %li\n", (long) minor(sb.st_dev));
	printf("MINOR: %li\n", (long) major(sb.st_dev));

    printf("I-Node: %li\n",sb.st_ino);

    printf("MODE: %i\n", sb.st_mode);

    mode_t mode = sb.st_mode;

    if(S_ISLNK(mode)){

        printf("%s es un enlace simbólico.\n", argv[1]);

    }
    else if(S_ISREG(mode)){

        printf("%s es un archivo ordinario.\n", argv[1]);

    }else if(S_ISDIR(mode)){

        printf("%s es un directorio.\n", argv[1]);

    }


    printf("Ultimo cambio: %s" , ctime(&sb.st_ctime));
    printf("Ultimo acceso: %s" , ctime(&sb.st_atime));
    printf("Ultimo modificación: %s", ctime(&sb.st_mtime));    

    /*
     
     st_mtime se actualiza cuando se modifica el contenido, mientras que st_ctime
     se actualiza cuando se modifica el inodo.
    
    */

   return 0;
}