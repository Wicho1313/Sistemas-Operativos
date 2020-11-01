#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
int main(){
  double total_time;
  clock_t start, end;
  start = clock();
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&(si),sizeof(si));
  si.cb=sizeof(si);
  ZeroMemory(&(pi),sizeof(pi));
  if(!CreateProcess(NULL,"suma",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }
  if(!CreateProcess(NULL,"resta",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }
  if(!CreateProcess(NULL,"multiplicacion",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }

  if(!CreateProcess(NULL,"traspuesta",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }
  if(!CreateProcess(NULL,"inversa",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }
  if(!CreateProcess(NULL,"imprimir",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi))){
      printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
      return 1;
    }
    WaitForSingleObject(pi.hProcess,INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  end = clock();
  total_time = ((double) (end - start)) / CLK_TCK;
  printf("\n\t----El tiempo de ejecucion fue de: %f\n", total_time);
  return 0;
}
