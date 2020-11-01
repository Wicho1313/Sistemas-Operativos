#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
  pid_t pid;
  char *prog1[2],*prog2[2],*prog3[2];
  prog1[0]="Evaluadordeexpresion/eval";
  prog2[0]="cambiarpermiso/permisos";
  prog3[0]="Matrizinversa/inv";
  prog1[1]=prog2[1]=prog3[1]=NULL;
  if((pid=fork())==0){
    printf("Soy el hijo ejecutando: %s\n",prog1[0]);

       pid=fork();
       if(pid){
         wait(0);
       }else{
         execv(prog1[0],prog1);
         exit(0);
       }
       pid=fork();
       if(pid){
         wait(0);
       }else{
         execv(prog2[0],prog2);
         exit(0);
       }
       pid=fork();
       if(pid){
         wait(0);
       }else{
         execv(prog3[0],prog3);
         exit(0);
       }



  }else{
    wait(0);
    printf("Soy el padre\n");
    exit(0);
  }



}
