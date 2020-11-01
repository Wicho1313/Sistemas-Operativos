#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

float mat1[40][40]={{1,0,0,0,0,0,0,0,0,0},
                  {1,2,0,0,0,0,0,0,0,0},
                  {1,2,3,0,0,0,0,0,0,0},
                  {1,2,3,4,0,0,0,0,0,0},
                  {1,2,3,4,5,0,0,0,0,0},
                  {1,2,3,4,5,6,0,0,0,0},
                  {1,2,3,4,5,6,7,0,0,0},
                  {1,2,3,4,5,6,7,8,0,0},
                  {1,2,3,4,5,6,7,8,9,0},
                  {1,2,3,4,5,6,7,8,9,10}};

float mat2[40][40]={{10,9,8,7,6,5,4,3,2,1},
                  {0,9,8,7,6,5,4,3,2,1},
                  {0,0,8,7,6,5,4,3,2,1},
                  {0,0,0,7,6,5,4,3,2,1},
                  {0,0,0,0,6,5,4,3,2,1},
                  {0,0,0,0,0,5,4,3,2,1},
                  {0,0,0,0,0,0,4,3,2,1},
                  {0,0,0,0,0,0,0,3,2,1},
                  {0,0,0,0,0,0,0,0,2,1},
                  {0,0,0,0,0,0,0,0,0,1}};
int mat1t[10][10]={};
int mat2t[10][10]={};
int mat1inv[10][10]={};
int mat2inv[10][10]={};
int multi[10][10]={};

char archivo[10000];


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

int main(void){
  int id_proc;

  id_proc=fork();
  if(id_proc==0){
    id_proc=fork();
    if(id_proc==0){
      FILE* fichero;
      fichero = fopen("suma.txt", "w");
      for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
          //printf("%d ",(int)(mat1[i][j]+mat2[i][j]));
          fprintf(fichero, "%d ", (int)(mat1[i][j]+mat2[i][j]));
        }
        fprintf(fichero,"\n");
      }
      fclose(fichero);
      exit(0);
    }else wait(0);

    id_proc=fork();
    if(id_proc==0){
      FILE* fichero;
      fichero = fopen("resta.txt", "w");
      for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
          //printf("%d ",(int)(mat1[i][j]-mat2[i][j]));
          fprintf(fichero, "%d ", (int)(mat1[i][j]-mat2[i][j]));
        }
        fprintf(fichero,"\n");
      }
      fclose(fichero);
      exit(0);
    }else wait(0);

    id_proc=fork();
    if(id_proc==0){
      FILE* fichero;
      fichero = fopen("multi.txt", "w");

      int i, j, k;
      for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            multi[i][j] = 0;
            for (k = 0; k < 10; k++)
                multi[i][j] += mat1[i][k]*mat2[k][j];
        }
      }

      for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
          fprintf(fichero, "%d ", (int)(multi[i][j]));
        }
        fprintf(fichero,"\n");
      }

      fclose(fichero);
      exit(0);
    }else wait(0);

    id_proc=fork();
    if(id_proc==0){
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
      exit(0);
    }else wait(0);

    id_proc=fork();
    if(id_proc==0){
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
      exit(0);
    }else wait(0);

  }else{
    wait(0);
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
    exit(0);
  }


}
