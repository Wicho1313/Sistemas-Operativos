#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
int main(){
  char nombrerRuta[20][50],nombreRutaGuardada[60],contenido[20][200],nombreArchivos[20][20];
  HANDLE archivo;
  DWORD tamano=20;
  DIR *dir;
  struct dirent *sd;
  struct stat buf;
  int i=0,pruebaArchivo,numeroArchivo;
  char ruta[100],rutaGuardada[100];
  printf("\nIngresa la ruta de la carpeta que quieres escanear\n");
  scanf("%s",ruta);
  dir= opendir(ruta);
  if(dir==NULL){
    exit(1);
  }
  while((sd=readdir(dir)) != NULL){
    strcpy(nombreArchivos[i],sd->d_name);
    strcpy(nombrerRuta[i],ruta);
    strcat(nombrerRuta[i],"/");
    strcat(nombrerRuta[i],sd->d_name);
    archivo=CreateFile(nombrerRuta[i],GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(pruebaArchivo=ReadFile(archivo,contenido[i],tamano,0,NULL)!= 0){
        printf("id: %d\t\tNombre: %s\n",i+1,nombreArchivos[i]);
        i++;
    }
  }
  char pregunta[3];
  printf("Quieres ver el contenido de algun archivo\n");
  scanf("%s",pregunta);
  if(strcmp(pregunta,"no")==0 || strcmp(pregunta,"NO")==0 || strcmp(pregunta,"No")==0);
  else{
    printf("teclea el id de los archvos que quieres ver su contenido (para terminar teclea 0)\n");
    while(scanf("%d",&numeroArchivo) && numeroArchivo && numeroArchivo<(i+1)){
      printf("Contenido: \t%s\n",contenido[numeroArchivo-1]);
    }
  }
  printf("Quieres copiar algun archivo en otra carpeta?\n");
  scanf("%s",pregunta);
  if(strcmp(pregunta,"no")==0 || strcmp(pregunta,"NO")==0 || strcmp(pregunta,"No")==0)
    exit(1);
  else{
    printf("Introduce la ruta a donde quieres copiarlos\n");
    scanf("%s",rutaGuardada);
    printf("teclea los numeros de archivos que quieres copiar (Para dejar de copiar teclea 0)\n");
      scanf("%d",&numeroArchivo);
      while(numeroArchivo){
        if(numeroArchivo>i){
          printf("ese numero no pertenece a ningun archivo\n");
        }else{
          strcpy(nombreRutaGuardada,rutaGuardada);
          strcat(nombreRutaGuardada,"/");
          strcat(nombreRutaGuardada,nombreArchivos[numeroArchivo-1]);
          archivo=CreateFile(nombreRutaGuardada,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
          if(WriteFile(archivo,contenido[numeroArchivo-1],strlen(contenido[numeroArchivo-1]),0,NULL)!=0)printf("Archivo Copiado Exitosamente\n");
        }
        fflush(stdin);
        scanf("%d",&numeroArchivo);
      }
    }
  return 0;

}
