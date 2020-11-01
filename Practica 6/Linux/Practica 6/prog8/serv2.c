#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#define TAM_MEM 27	//Tamaño de la memoria compartida en bytes
int main(){
  char c;
  int shmid;
  int shmid2;
  int shmid3;
  key_t llave;
  int *shm, *s;
  int *shm2, *s2;
  int *shm3, *s3;
  int **mat, **mat2, **sum,**mat3, **mat4;

  int i, j, k;
  llave = 5678;
  if((shmid = shmget(llave,TAM_MEM, 0666)) <0){
    perror("Error al obtener memoria compartida: shmget"); exit(-1);
  }

  if((shm = shmat(shmid,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }

  llave = 5679;
  if((shmid2 = shmget(llave,TAM_MEM,IPC_CREAT | 0666)) <0){
    perror("Error al obtener memoria compartida: shmget"); exit(-1);
  }

  if((shm2 = shmat(shmid2,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }

  llave = 5680;
  if((shmid3 = shmget(llave, TAM_MEM, IPC_CREAT | 0666)) <0){
    perror("Error al obtener memoria compartida: shmget"); exit(-1);
  }

  if((shm3 = shmat(shmid3,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }

  int mat1h[10][10]={};
  int mat2h[10][10]={};
  float multih[10][10]={};

  s = shm;
  for(i = 0, k =0; i < 10; i++){
    for(j = 0; j < 10; j++){
      mat1h[i][j] = s[k++];
    }
  }
  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      mat2h[i][j] = s[k++];
    }
  }
  *shm=-10;


  //envia matriz
  s3 = shm3;
  for(i = 0,k = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      s3[k++] = mat1h[i][j];
    }
  }
  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      s3[k++] = mat2h[i][j];
    }
  }
  while(*shm3 != -10)
    sleep(1);

  printf("sos\n");

  //envia

  s2 = shm2;
  int z=0;
  for (i = 0, z = 0; i < 10; i++){
    for (j = 0; j < 10; j++){
        s2[z]=0;
        for (k = 0; k < 10; k++)
            s2[z]+=mat1h[i][k]*mat2h[k][j];
        z++;
    }
  }
  while(*shm2 != -10)
    sleep(1);

  printf("se envio\n");

  exit(0);
}
