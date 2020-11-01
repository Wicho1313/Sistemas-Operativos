#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
  char mensaje[100];
  strcpy(mensaje,"Hola mundo ");
  strcpy(mensaje,"Hola mundo desde ");
  strcat(mensaje,argv[0]);
  printf("%s\n",mensaje );
  exit(0);
}
