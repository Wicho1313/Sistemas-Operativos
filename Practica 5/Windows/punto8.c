#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
struct rutas{
  char rutaOrigen[100],rutaDestino[100];
};
DWORD WINAPI copiarCarpeta(LPVOID lpParam){
  struct rutas *ruta;
  char aux1[200],aux2[200],contenido[1000000];

  ruta=(struct rutas*)lpParam;
  int p='.';
  HANDLE archivoOrigen,archivoDestino;
  DIR *dir;
  struct dirent *sd;
  dir= opendir(ruta->rutaOrigen);
  if(dir==NULL){
    exit(1);
  }
  while((sd=readdir(dir)) != NULL){
    if(strchr(sd->d_name,p)==NULL){
      DWORD idHilo;
      HANDLE manHilo;
      struct rutas *carpeta;
      carpeta=(struct rutas*)malloc(sizeof(struct rutas));
      strcpy(carpeta->rutaOrigen,ruta->rutaOrigen);
      strcat(carpeta->rutaOrigen,"/");
      strcat(carpeta->rutaOrigen,sd->d_name);
      strcpy(carpeta->rutaDestino,ruta->rutaDestino);
      strcat(carpeta->rutaDestino,"/");
      strcat(carpeta->rutaDestino,sd->d_name);
      CreateDirectory(carpeta->rutaDestino,NULL);
      manHilo=CreateThread(NULL,0,copiarCarpeta,carpeta,0,&idHilo);
      WaitForSingleObject(manHilo,INFINITE);
    }
    else{
      strcpy(aux1,ruta->rutaOrigen);
      strcat(aux1,"/");
      strcat(aux1,sd->d_name);
      archivoOrigen=CreateFile(aux1,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
      ReadFile(archivoOrigen,contenido,1000000,0,NULL);
      strcpy(aux1,ruta->rutaDestino);
      strcat(aux1,"/");
      strcat(aux1,sd->d_name);
      archivoDestino=CreateFile(aux1,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
      WriteFile(archivoDestino,contenido,strlen(contenido),0,NULL);
    }
  }
  return 0;
}
int main(){
  struct rutas *origen;
  origen=(struct rutas*)malloc(sizeof(struct rutas));
  DWORD idHilo1;
  HANDLE manHilo1;
  printf("Ingresa la ruta de origen: \n");
  gets(origen->rutaOrigen);
  printf("Ingresa la ruta de destino: \n");
  gets(origen->rutaDestino);
  manHilo1=CreateThread(NULL,0,copiarCarpeta,origen,0,&idHilo1);
  WaitForSingleObject(manHilo1,INFINITE);
  CloseHandle(manHilo1);
  return 0;
}
