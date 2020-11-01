#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main()
{
    struct stat sb;
    DIR *d;
    struct dirent *dir;
    char ruta[100];
    printf("Teclea la ruta\n");
    scanf("%s",ruta);
    int path=chdir(ruta);
    d = opendir(".");

    if (d) {
      while ((dir = readdir(d)) != NULL) {
        printf("-> %s\n", dir->d_name);

        if (lstat(dir->d_name, &sb) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        printf("Tamano:                   %lld bytes\n",(long long) sb.st_size);
        printf("Ultimo cambio de estado:  %s", ctime(&sb.st_ctime));
        printf("Ultimo acceso al archivo: %s", ctime(&sb.st_atime));
        printf("Ultima modificacion:      %s", ctime(&sb.st_mtime));
      }
      closedir(d);
    }


    exit(EXIT_SUCCESS);
}
