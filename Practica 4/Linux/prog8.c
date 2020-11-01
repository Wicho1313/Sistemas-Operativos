#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>



char archivo[10000];


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
  char *suma[2],*resta[2],*multi[2],*inversa[2],*traspuesta[2],*imprimir[2];
  suma[0]="codigosprog8/suma";
  resta[0]="codigosprog8/resta";
  multi[0]="codigosprog8/multi";
  inversa[0]="codigosprog8/inversa";
  traspuesta[0]="codigosprog8/traspuesta";
  imprimir[0]="codigosprog8/imprimir";
  suma[1]=resta[1]=multi[1]=inversa[1]=traspuesta[1]=imprimir[1]=NULL;


  int id_proc;
  id_proc=fork();
  if(id_proc==0){
    id_proc=fork();
    if(id_proc==0){
      execv(suma[0],suma);
    }else{
       wait(0);
       exit(0);
    }

    id_proc=fork();
    if(id_proc==0){
      execv(resta[0],resta);
    }else{
       wait(0);
       exit(0);
    }

    id_proc=fork();
    if(id_proc==0){
      execv(multi[0],multi);
    }else{
       wait(0);
       exit(0);
    }

    id_proc=fork();
    if(id_proc==0){
      execv(inversa[0],inversa);
    }else{
       wait(0);
       exit(0);
    }

    id_proc=fork();
    if(id_proc==0){
      execv(traspuesta[0],traspuesta);
    }else{
       wait(0);
       exit(0);
    }

  }else{
     wait(0);
     execv(imprimir[0],imprimir);
     exit(0);
  }



}
