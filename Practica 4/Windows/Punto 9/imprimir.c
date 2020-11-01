#include<stdio.h>
#include <string.h>
#include<stdlib.h>

char archivo[10000];

void leer(char entrada[]){
  char *secuencia;
  FILE *ptrs;
  ptrs= fopen(entrada,"r");
  if(ptrs==NULL){
    printf("No hay datos");
    exit(1);
  }else{
      while (fgets((char*)&archivo, sizeof(archivo), ptrs)){
            printf("%s",archivo);
      }
        fclose(ptrs);
   }
}

int main(int argc, char *argv[]){

  printf("\n=== Suma ===\n");
  leer("suma.txt");
  printf("\n=== Resta ===\n");
  leer("resta.txt");
  printf("\n=== Multiplicacion ===\n");
  leer("multi.txt");
  printf("\n=== Traspuesta ===\n");
  leer("traspuesta.txt");
  printf("\n=== Inversa ===\n");
  leer("inversa.txt");

  return 0;
}
