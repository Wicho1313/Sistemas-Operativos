#include<stdio.h>
#include <string.h>
#include<stdlib.h>

float mat1[40][40];
float mat2[40][40];
int mat1inv[40][40];
int mat2inv[40][40];

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
              fscanf(ptrs,"%f", &mat1[i][j]);
        fclose(ptrs);
   }
   if(ptrs2==NULL){
     printf("No hay datos");
     exit(1);
   }else{
         for(i = 0; i < 10; i++)
             for(j = 0; j < 10; j++)
               fscanf(ptrs2,"%f", &mat2[i][j]);
         fclose(ptrs2);
    }
}


void InverseOfMatrix(float matrix[][40], int order,int opc){

    float temp;
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 2 * order; j++) {
            if (j == (i + order))
                matrix[i][j] = 1;
        }
    }

    for (int i = order - 1; i > 0; i--) {
        if (matrix[i - 1][0] < matrix[i][0])
            for (int j = 0; j < 2 * order; j++) {
                temp = matrix[i][j];
                matrix[i][j] = matrix[i - 1][j];
                matrix[i - 1][j] = temp;
            }
    }

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 2 * order; j++) {
            if (j != i) {
                temp = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * order; k++) {
                    matrix[j][k] -= matrix[i][k] * temp;
                }
            }
        }
    }

    for (int i = 0; i < order; i++) {
        temp = matrix[i][i];
        for (int j = 0; j < 2 * order; j++) {
            matrix[i][j] = matrix[i][j] / temp;
        }
    }

    for (int i = 0; i < order; i++) {
        for (int j = order; j < 2 * order; j++) {
            if(opc==0)
             mat1inv[i][j-order]=matrix[i][j];
            else
             mat2inv[i][j-order]=matrix[i][j];
        }
    }

    return;
}

int main(int argc, char *argv[]){
  guardar();
  InverseOfMatrix(mat1,10,0);
  InverseOfMatrix(mat2,10,1);
  FILE* fichero;
  fichero = fopen("inversa.txt", "w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%.3f ", (float)(mat1inv[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fprintf(fichero,"\n");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%.3f ", (float)(mat2inv[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}
