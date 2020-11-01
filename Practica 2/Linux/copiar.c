#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

void visualizar(char archivo_ini[]){
   int leer = open(archivo_ini, O_RDONLY);
   char aux;
   printf("------------------------------------------------------------------\n");
   while (read(leer, &aux,1)>0){ printf("%c",aux);}
   printf("\n------------------------------------------------------------------\n");
   close(leer);
}
void copiar(char archivo_ini[],char archivo_fin[])
{
    int leer = open(archivo_ini, O_RDONLY);
    int escribir = open(archivo_fin, O_WRONLY | O_CREAT, 0644);
    int count = 0;
    char buff[100];
    if(leer<1)printf("Error al abrir el archivo\n");
    read(leer,buff,100);
    close(leer);
    write (escribir, buff, strlen(buff)-2);
    close(escribir);
}


int main()
{
    char archivo_ini[100], archivo_fin[100];
    int n,opcion;
    n = 5;

    while(1){
      printf("Teclea 1 para visualizar un archivo\n");
      printf("       2 para copiar un archivo\n");
      printf("       3 para salir\n");
      scanf("%d",&opcion);
      if(opcion==1){
        printf("Teclea la direccion del archivo a visualizar\n");
        scanf("%s",archivo_ini);
        visualizar(archivo_ini);
      }else if(opcion==2){
        printf("Teclea la direccion del archivo a copiar\n");
        scanf("%s",archivo_ini);
        printf("\nTeclea la direccion del archivo de destino\n");
        scanf("%s",archivo_fin);
        copiar(archivo_ini,archivo_fin);

      }else{
        printf("El programa ha terminado exitosamente\n");
        break;
      }
    }
    return 0;
}
