#include <windows.h>
#include <stdio.h>
#include <string.h>
struct matriz{
  int mat1[40][40],mat2[40][40],suma[40][40],multi[40][40];
};
struct matriz *datos;
int multiMatrices(int arr1[40][40],int arr2[40][40]){
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
        datos->multi[i][j] = 0;
        for (int k = 0; k < 10; k++)
            datos->multi[i][j] += arr1[i][k]*arr2[k][j];
    }
  }
  return 0;
}
int main(){
  // datos=malloc(sizeof(int)*40*40*4);
  DWORD leidos,escritos;
  HANDLE hStdIn=GetStdHandle(STD_INPUT_HANDLE),hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
  ReadFile(hStdIn,datos,40*40*4*4,&leidos,NULL);
  multiMatrices(datos->mat1,datos->mat2);
  WriteFile(hStdOut,datos,40*40*4*4,&leidos,NULL);
  CloseHandle(hStdIn);
  CloseHandle(hStdOut);
  return 0;
}
