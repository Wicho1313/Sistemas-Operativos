#include <windows.h>
#include <stdio.h>
DWORD WINAPI quinceHilos(LPVOID lpParam1);
DWORD WINAPI diezHilos(LPVOID lpParam2);
DWORD WINAPI cincoHilos(LPVOID lpParam3);
int main(){
  DWORD idHilo1;
  HANDLE manHilo1;
  printf("idHilo: %i\n",GetCurrentThreadId());
  for(int i=0;i<15;i++){
    manHilo1=CreateThread(NULL,0,quinceHilos,NULL,0,&idHilo1);
    WaitForSingleObject(manHilo1,INFINITE);
    CloseHandle(manHilo1);
  }
  return 0;
}
DWORD WINAPI quinceHilos(LPVOID lpParam1){
  DWORD idHilo2;
  HANDLE manHilo2;
  printf("\tidHilo: %i\n",GetCurrentThreadId());
  for(int i=0;i<10;i++){
    manHilo2=CreateThread(NULL,0,diezHilos,NULL,0,&idHilo2);
    WaitForSingleObject(manHilo2,INFINITE);
    CloseHandle(manHilo2);
  }
  return 0;
}
DWORD WINAPI diezHilos(LPVOID lpParam2){
  DWORD idHilo3;
  HANDLE manHilo3;
  printf("\t\tidHilo: %i\n",GetCurrentThreadId());
  for(int i=0;i<5;i++){
    manHilo3=CreateThread(NULL,0,cincoHilos,NULL,0,&idHilo3);
    WaitForSingleObject(manHilo3,INFINITE);
    CloseHandle(manHilo3);
  }
  return 0;
}
DWORD WINAPI cincoHilos(LPVOID lpParam3){
  printf("\t\t\tPractica 5\n");
  return 0;
}
