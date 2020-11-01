#include <sys/types.h>	//Cliente de la memoria compartida
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
  int i, j, k;
  int mat1h[10][10]={};
  int mat2h[10][10]={};
  float sumahh[10][10]={};

  llave = 5680;
  if((shmid = shmget(llave,TAM_MEM, IPC_CREAT |0666)) <0){
    perror("Error al obtener memoria compartida: shmget");
    exit(-1);
  }

  if((shm = shmat(shmid,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }

  llave = 5681;
  if((shmid3= shmget(llave, TAM_MEM, IPC_CREAT | 0666)) <0){
    perror("Error al obtener memoria compartida: shmget"); exit(-1);
  }

  if((shm3 = shmat(shmid3,NULL,0)) == (int*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }

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

  printf("se recibio\n");

  s3 = shm3;
  int z=0;
  for (i = 0, z = 0; i < 10; i++){
    for (j = 0; j < 10; j++){
        s3[z]=mat1h[i][j]+mat2h[i][j];
        z++;
    }
  }
  while(*shm3 != -10)
    sleep(1);

  printf("se envio\n");

  exit(0);
}
