#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int x,y,z,l,N=10;
pid_t pid;
pid_t cpid;
void lista(int n){
  if(n){
      pid=fork();
      if(pid==0){
          if(n){
              printf("linea %d PID: %d\t PPID: %d\n",n,getpid(),getppid());
              lista(n-1);
              exit(0);
          }
          else{
            //sleep(1);
            return;
          }
      }else{
        wait(0);
      }
  }else{

    for(l=x;l<=N;l++){
       pid=fork();
       if(pid){
         // printf("Soy el proceso %d\n",getpid());
         wait(0);
       }else{
          printf("ramas PID: %d\t PPID: %d\n",getpid(),getppid());
          exit(0);
       }

    }
  }
}

int main(void){

   for(x=1;x<=N;x++){
    pid=fork();
    if(pid){
      // printf("Soy el proceso %d\n",getpid());
      wait(0);
    }else{
       printf("raiz PID: %d\t PPID: %d\n",getpid(),getppid());

       lista(N-x+1);
       exit(0);
    }

  }
 return 0;
}
