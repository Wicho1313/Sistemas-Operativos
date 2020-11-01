#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <string.h>
#include <pthread.h>


void *hilo3(void *arg){
  //int id= pthread_self();
  //printf("\t\t- %d\n",id);
  char* men=(char*)arg;
  printf("\t\tPractica 8\n");
  return NULL;
}


void *hilo2(void *arg){
  int id= pthread_self();
  printf("\t2- %d\n",id);
  pthread_t id_hilo;
  for(int i=0;i<5;i++){
    pthread_create(&id_hilo,NULL,(void*)hilo3,NULL);
  }
  pthread_join(id_hilo,NULL);

  return NULL;
}


void *hilo(void *arg){
  int id= pthread_self();
  printf("1- %d\n",id);
  pthread_t id_hilo;
  for(int i=0;i<10;i++){
    pthread_create(&id_hilo,NULL,(void*)hilo2,NULL);
  }
  pthread_join(id_hilo,NULL);

  return NULL;
}


int main(void){

  int id_proc;

  id_proc=fork();
  if(id_proc==0){
    pthread_t id_hilo;
    for(int i=0;i<15;i++){
      pthread_create(&id_hilo,NULL,(void*)hilo,NULL);
    }
    pthread_join(id_hilo,NULL);
  }else wait(0);

  return 0;
}
