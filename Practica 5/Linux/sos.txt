#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <string.h>

char* itoa(int val, int base);

void *hilo3(void *arg){
  char* men=(char*)arg;
  printf("ses - + %s\n",men);

  return NULL;
}



void *hilo2(void *arg){
  char* men=(char*)arg;
  printf("ses - %s\n",men);
  pthread_t id_hilo;
  for(int i=0;i<5;i++){
    char* mensaje=itoa((48+i),10);
    pthread_create(&id_hilo,NULL,(void*)hilo3,(void*)mensaje);
    pthread_join(id_hilo,NULL);
  }

  return NULL;
}


void *hilo(void *arg){
  char* men=(char*)arg;
  printf("ses %s\n",men);
  pthread_t id_hilo;
  for(int i=0;i<10;i++){
    char* mensaje=itoa((48+i),10);
    //printf("%s\n",mensaje);
    pthread_create(&id_hilo,NULL,(void*)hilo2,(void*)mensaje);
    pthread_join(id_hilo,NULL);
  }

  return NULL;
}


int main(void){

  int id_proc;

  id_proc=fork();
  if(id_proc==0){
    pthread_t id_hilo;
    for(int i=0;i<15;i++){
      char* mensaje=itoa((48+i),10);
      //printf("%s\n",mensaje);
      pthread_create(&id_hilo,NULL,(void*)hilo,(void*)mensaje);
      pthread_join(id_hilo,NULL);
    }
    //pthread_exit(NULL);
  }else wait(0);

  return 0;
}

char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}
