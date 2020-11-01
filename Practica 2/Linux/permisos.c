#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{

    char buf[100];
    char archivo[100];
    char permiso[9];
    printf("Tecleea el archivo a cambiar los permisos\n");
    scanf("%s",buf );
    strcpy(archivo,buf);
    printf("\nTeclea 1 en el permiso que quieres activar y 0 en el que no\nrwxrwxrwx\n");
    scanf("%s" ,permiso );
    fflush(stdin);
    char a='0';
    int b=(permiso[0]-'0')*4+(permiso[1]-'0')*2+(permiso[2]-'0');
    int c=(permiso[3]-'0')*4+(permiso[4]-'0')*2+(permiso[5]-'0');
    int d=(permiso[6]-'0')*4+(permiso[7]-'0')*2+(permiso[8]-'0');
    printf("%d %d %d\n",b,c,d );
    char mode[5];
    mode[0]=a; mode[1]=b+'0'; mode[2]=c+'0'; mode[3]=d+'0';   mode[4]='\0';
    //mode[0]='0'; mode[1]='7'; mode[2]='7'; mode[3]='7';

    int i;
    i = strtol(mode, 0, 8);
    if (chmod (archivo,i) < 0)
    {
        fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                argv[0], buf, mode, errno, strerror(errno));
        exit(1);
    }
    return(0);
}
