#include <windows.h>
#include <stdio.h>
#include <string.h>
struct matriz{
  int mat1[40][40],mat2[40][40],suma[40][40],multi[40][40];
};
struct matriz *datos;
int sumaMatrices(int arr1[40][40],int arr2[40][40]){
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      datos->multi[i][j]=(arr1[i][j]+arr2[i][j]);
    }
  }
  return 0;
}
int main(){
  // datos=malloc(sizeof(int)*40*40*4);
  DWORD leidos,escritos;
  HANDLE hStdIn=GetStdHandle(STD_INPUT_HANDLE),hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
  ReadFile(hStdIn,datos,40*40*4*4,&leidos,NULL);
  HANDLE hLecturaPipe, hEscrituraPipe;
  PROCESS_INFORMATION piHijo;
  STARTUPINFO siHijo;
  SECURITY_ATTRIBUTES pipeSeg={sizeof(SECURITY_ATTRIBUTES), NULL,TRUE};
  GetStartupInfo(&siHijo);
  CreatePipe(&hLecturaPipe, &hEscrituraPipe, &pipeSeg, 0);
  WriteFile(hEscrituraPipe, datos,40*40*4*4, &escritos, NULL);
  siHijo.hStdInput=hLecturaPipe;
  siHijo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
  siHijo.hStdOutput=hEscrituraPipe;
  siHijo.dwFlags=STARTF_USESTDHANDLES;
  CreateProcess(NULL, "Punto4Nieto", NULL, NULL, TRUE,
  0, NULL, NULL, &siHijo, &piHijo);
  WaitForSingleObject(piHijo.hProcess,INFINITE);
  ReadFile(hStdIn,datos,40*40*4*4,&leidos,NULL);
  sumaMatrices(datos->mat1,datos->mat2);
  WriteFile(hStdOut,datos,40*40*4*4,&leidos,NULL);
  CloseHandle(hLecturaPipe);
  CloseHandle(hEscrituraPipe);
  CloseHandle(piHijo.hThread);
  CloseHandle(piHijo.hProcess);
  CloseHandle(hStdIn);
  CloseHandle(hStdOut);
  return 0;
}
