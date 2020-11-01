#include <sys/types.h> //Cliente de la memoria compartida
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#define TAM_MEM 27	//Tamaño de la memoria compartida en bytes


int mat1[10][10]={{1,0,0,0,0,0,0,0,0,0},
{1,2,0,0,0,0,0,0,0,0},
{1,2,3,0,0,0,0,0,0,0},
{1,2,3,4,0,0,0,0,0,0},
{1,2,3,4,5,0,0,0,0,0},
{1,2,3,4,5,6,0,0,0,0},
{1,2,3,4,5,6,7,0,0,0},
{1,2,3,4,5,6,7,8,0,0},
{1,2,3,4,5,6,7,8,9,0},
{1,2,3,4,5,6,7,8,9,10}};

int mat2[10][10]={{10,9,8,7,6,5,4,3,2,1},
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



int main(){
  char c;
  int shmid;
  int shmid2;
  int shmid3;
  key_t llave;
  int *shm, *s;
  int *shm2, *s2;
  int *shm3, *s3;
  int i,j,k;
  float **m1, **m2;


  llave = 5678;
  if((shmid = shmget(llave, TAM_MEM, IPC_CREAT | 0666)) < 0){
    perror("1 Error al obtener memoria compartida 1: shmget");
    exit(-1);
  }

  if((shm = shmat(shmid,NULL,0)) == (int *)-1){
    perror("Error al enlazar la memoria compartida 1: shmat");
    exit(-1);
  }

  llave = 5679;
  if((shmid2 = shmget(llave, TAM_MEM,IPC_CREAT | 0666)) <0){
    perror("Error al obtener memoria compartida 2: shmget"); exit(-1);
  }

  if((shm2 = shmat(shmid2,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida 2: shmat");
    exit(-1);
  }

  llave = 5681;
  if((shmid3 = shmget(llave, TAM_MEM, IPC_CREAT | 0666)) <0){
    perror("Error al obtener memoria compartida 3: shmget"); exit(-1);
  }

  if((shm3 = shmat(shmid3,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida 3: shmat");
    exit(-1);
  }

  //envia matriz
  s = shm;
  for(i = 0,k = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      s[k++] = mat1[i][j];
    }
  }
  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      s[k++] = mat2[i][j];
    }
  }
  while(*shm != -10)
    sleep(1);

  s2 = shm2;
  for(i = 0, k = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      multi[i][j] = s2[k++];
      //printf("%.3f ",multi[i][j]);
    }
    //printf("\n");
  }
  *shm2=-10;

  s3 = shm3;
  for(i = 0, k = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      suma[i][j] = s3[k++];
      //printf("%.3f ",suma[i][j]);
    }
    //printf("\n");
  }
  *shm3=-10;

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
