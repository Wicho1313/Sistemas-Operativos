#include <stdio.h>
#include <windows.h>
int main(){
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&(si),sizeof(si));
  si.cb=sizeof(si);
  ZeroMemory(&(pi),sizeof(pi));
  printf("ID Padre: %d\n",GetCurrentProcessId());
  for(int i=0;i<5;i++){
    if(!CreateProcess(NULL,"PrimerNivel",NULL,NULL,FALSE,0,NULL,NULL,&(si),&(pi)))
    {
        printf("fallo al invocar CreateProcess (%d)\n",GetLastError());
        return 1;
      }
    WaitForSingleObject(pi.hProcess,INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
  return 0;
}
