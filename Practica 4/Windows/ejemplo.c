#include <windows.h>
#include <stdio.h>
int main(int argc,char *argv[]){
STARTUPINFO si;
PROCESS_INFORMATION pi;

ZeroMemory(&si,sizeof(si));
si.cb=sizeof(si);
ZeroMemory(&pi,sizeof(pi));
if(argc!=2){
  printf("Usar: %s Nombre_programa_hijo\n",argv[0]);
  return 1;
}
if(!CreateProcess(NULL,argv[1],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))){
  printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
  return 1;
}
printf("Soy el padre\n");
WaitForSingleObject(pi.hProcess,INFINITE);
CloseHandle(pi.hProcess);
CloseHandle(pi.hThread);
  return 0;
}
