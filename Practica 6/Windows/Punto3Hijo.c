#include <windows.h>
#include <stdio.h>
#include <string.h>
int main(){
  int mensaje;
  char mensaje2[]="holi";
  DWORD leidos,escritos;
  HANDLE hStdIn=GetStdHandle(STD_INPUT_HANDLE),hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
  ReadFile(hStdIn,&mensaje,4,&leidos,NULL);
  mensaje+=22;
  WriteFile(hStdOut,&mensaje,4,&leidos,NULL);
  CloseHandle(hStdIn);
  CloseHandle(hStdOut);
  return 0;
}
