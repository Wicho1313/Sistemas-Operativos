#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#undef _POSIX_SOURCE

int buscar(const char *arch)
{
    DIR *dirp;
    struct dirent *buscador;

    if ((dirp = opendir(".")) == NULL) {
        perror("couldn't open '.'");
        return 0;
    }

    do {
        errno = 0;
        if ((buscador = readdir(dirp)) != NULL) {
            if (strcmp(buscador->d_name, arch) != 0)
                continue;
            (void) printf("found %s\n", arch);
            (void) closedir(dirp);
                return 1;
        }
    } while (buscador != NULL);


    if (errno != 0)
        perror("error reading directory");
    else
        (void) printf("Se creo el archivo %s\n", arch);
    (void) closedir(dirp);
    return 0;
}


int main( )
{
    int i,longitud=5, num_archivos=5;
    char ruta[100];
    struct stat st = {0};
    printf("Teclea el nuevo directorio\n");
    while(scanf("%s",ruta)){
      if (stat(ruta, &st) == -1) {
        mkdir(ruta, 0700);
        break;
      }else{
        printf("El directorio ya existe intentalo de nuevo\n");
      }

    }

    int path=chdir(ruta);
    char contenido[5][10] = {"archivo1","archivo2","archivo3","archivo4","archivo5"};
    srand(time(NULL));
    for(int z=0 ; z<num_archivos; z++){
      char fn[]="holas.txt";
    	for( int i = 0; i < longitud; i++){
          fn[i] = 'a' + rand()%25; // empieza en a y termina en z
      }

      if(buscar(fn)==0){
    	    int fd = creat(fn, S_IRUSR | S_IWUSR);
            fd= open(fn,O_WRONLY);
        	  write(fd, contenido[z], strlen(contenido[z]));
        	  close(fd);
    	}else{
    	    i--;
    	}

    }

    return (0);
}
