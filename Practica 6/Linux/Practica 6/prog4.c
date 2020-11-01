#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <stdlib.h>
#define VALOR 1

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

float mat1inv[10][10]={};
float mat2inv[10][10]={};
float multi[40][40]={};
float suma[40][40]={};

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

int main(void){
  int tube1[2], tube3[2], tube4[2];
  char matriz[100];
  if(pipe(tube1)!=0)
    exit(1);
  if(pipe(tube3)!=0)
    exit(1);

  if(pipe(tube4)!=0)
    exit(1);

  if(fork()==0){
    while(VALOR){
      int tube2[2];
      float math1[40][40]={};
      float math2[40][40]={};
      float multih[40][40]={};
      if(pipe(tube2)!=0)
        exit(1);

      //recibe matriz 1
      read(tube1[0],math1,sizeof(math1));
      //printf("Se recibió mat1\n");

      read(tube1[0],math2,sizeof(math2));
      //printf("Se recibió mat2\n");


      //escribe la matriz en el hijo
      // multiplica matriz
      int i, j, k;
      for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            multih[i][j] = 0;
            for (k = 0; k < 10; k++)
                multih[i][j] +=math1[i][k]*math2[k][j];
            //printf("%.3f ",multih[i][j]);
        }
        // printf("\n");
      }
      write(tube3[1], multih,sizeof(multih));
      //printf("se multiplico\n");
      write(tube2[1], math1,sizeof(math1));
      write(tube2[1], math2,sizeof(math2));
      //enviar resultado a padre

      if(fork()==0){
        while(VALOR){
          float mathh1[40][40]={};
          float mathh2[40][40]={};
          float sumahh[40][40]={};

          read(tube2[0],mathh1,sizeof(mathh1));

          read(tube2[0],mathh2,sizeof(mathh2));

          //suma matrices

          for(int i=0; i<10; i++) {
            for(int j=0; j<10; j++) {
              sumahh[i][j]=(int)mat1[i][j]+mat2[i][j];
            }
          }

          //envia resultado a abuelo
          write(tube4[1], sumahh,sizeof(sumahh));
          exit(0);
        }
      }

      exit(0);
    }
  }
  while(VALOR){
    //enviar matriz
    write(tube1[1], mat1,sizeof(mat1));

    write(tube1[1], mat2,sizeof(mat2));

    read(tube3[0],multi,sizeof(multi));

    read(tube4[0],suma,sizeof(suma));

    InverseOfMatrix(multi,10,0);
    
    for(int i=0; i<10; i++) {
      for(int j=0; j<10; j++) {
        printf("%.3f ", (float)(mat1inv[i][j]));
      }
      printf("\n");
    }
    printf("\n");



    InverseOfMatrix(suma,10,1);

    for(int i=0; i<10; i++) {
      for(int j=0; j<10; j++) {
        printf("%.3f ", (float)(mat2inv[i][j]));
      }
      printf("\n");
    }
    exit(0);
  }
}
