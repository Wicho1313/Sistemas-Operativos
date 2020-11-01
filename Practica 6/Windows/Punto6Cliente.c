#include <windows.h>
#include <stdio.h>
#define TAM_MEM 27
int main(){
  HANDLE hArchMapeo;
  char *idMemCompartida="MemoriaCompartida";
  char *apDatos,*apTrabajo,c;
  if((hArchMapeo=OpenFileMapping(
    FILE_MAP_ALL_ACCESS,
    FALSE,
    idMemCompartida))==NULL){
      printf("no se abrio el archivo de mapeo: (%i)\n",GetLastError());
      exit(-1);
    }
  if((apDatos=(char*)MapViewOfFile(hArchMapeo,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM))==NULL){
    printf("No se accedio a la memoria: (%i)\n",GetLastError());
    CloseHandle(hArchMapeo);
    exit(-1);
  }
  for(apTrabajo=apDatos;*apTrabajo != '\0';apTrabajo++)
    putchar('\n');
  *apDatos='*';
  UnmapViewOfFile(apDatos);
  CloseHandle(hArchMapeo);
  exit(0);
}
