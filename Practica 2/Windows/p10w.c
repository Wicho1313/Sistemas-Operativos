#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
int main(){
DIR *dir;
struct stat buf;
struct dirent *sd;
int i=0;
char ruta[100],atime[100],rutaArchivo[150];
long size;
char archivito[20][30];
printf("\nIngresa la ruta de la carpeta que quieres escanear\n");
scanf("%s",ruta);
system("CLS");
dir= opendir(ruta);
if(dir==NULL){
  exit(1);
}
while((sd=readdir(dir)) != NULL){
  if(i>=2)
  {strcpy(rutaArchivo,ruta);
  strcat(rutaArchivo,"/");
  strcat(rutaArchivo,sd->d_name);
  stat(rutaArchivo,&buf);
  strcpy(atime,ctime(&buf.st_atime));
  printf("Nombre: %s\t Tamano en bytes: %lld\t Ultima hora de acceso: %s",sd->d_name,(long long)buf.st_size,atime);}
  i++;
}
closedir(dir);
printf("\n");
return 0;
}
