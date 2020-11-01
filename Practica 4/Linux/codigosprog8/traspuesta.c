#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#include<stdlib.h>
#include<sys/wait.h>

int mat1[40][40];
int mat2[40][40];
int mat1t[40][40];
int mat2t[40][40];

void guardar(){
  char *secuencia;
  FILE *ptrs,*ptrs2;
  int i,j;
  ptrs= fopen("mat1.txt","r");
  ptrs2= fopen("mat2.txt","r");
  if(ptrs==NULL){
    printf("No hay datos");
    exit(1);
  }else{
        for(i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
              fscanf(ptrs,"%d", &mat1[i][j]);
        fclose(ptrs);
   }
   if(ptrs2==NULL){
     printf("No hay datos");
     exit(1);
   }else{
         for(i = 0; i < 10; i++)
             for(j = 0; j < 10; j++)
               fscanf(ptrs2,"%d", &mat2[i][j]);
         fclose(ptrs2);
    }
}


int main(int argc, char *argv[]){
  guardar();
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      mat1t[i][j] = mat1[j][i];
      mat2t[i][j] = mat2[j][i];
    }
  }
  FILE* fichero;
  fichero = fopen("traspuesta.txt", "w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%d ", (int)(mat1t[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fprintf(fichero,"\n");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%d ", (int)(mat2t[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}
