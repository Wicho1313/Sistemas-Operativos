#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_MEM 27
int main(){
  HANDLE hArchMapeo;
  char *idMemCompartida="MemoriaCompartida";
  char *apDatos,*apTrabajo,c;
  if((hArchMapeo=CreateFileMapping(
    INVALID_HANDLE_VALUE,
    NULL,
    PAGE_READWRITE,
    0,
    TAM_MEM,
    idMemCompartida))==NULL){
      printf("no se abrio el archivo de mapeo: (%i)\n",GetLastError());
      exit(-1);
    }
  if((apDatos=(char*)MapViewOfFile(hArchMapeo,FILE_MAP_ALL_ACCESS,0,0,TAM_MEM))==NULL){
    printf("No se accedio a la memoria: (%i)",GetLastError());
    CloseHandle(hArchMapeo);
    exit(-1);
  }
  apTrabajo=apDatos;
  for(c='a';c<='Z';c++)
    *apTrabajo++=c;
  *apTrabajo='\0';
  while(*apDatos !='*')
    Sleep(1);
  UnmapViewOfFile(apDatos);
  CloseHandle(hArchMapeo);
  exit(0);
}
