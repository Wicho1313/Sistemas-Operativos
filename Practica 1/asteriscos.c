#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void guarda(int N){
  char entrada[51];
  fflush(stdin);//Libera el buffer
  printf("Teclea el nombre del archivo con la extension '.txt' \n");
  gets(entrada);
  FILE *ptrs;
  ptrs= fopen(entrada,"w");
  if(ptrs==NULL){
    printf("No se pudo abrir el archivo");
    exit(1);
  }else{
      int mitad=N/2;
      int mitad2=mitad/2+1;
      for (int i= 0; i< mitad2-1;i++) {
        for (int j = 0; j <mitad; j++) {
          if(mitad2+i-1==j || mitad2-i-1==j)
            fprintf(ptrs,"*");
          else
            fprintf(ptrs," ");
        }
        for (int j = mitad; j <N; j++) {
          if(mitad+mitad2+i-1<j || mitad+mitad2-i-1>j)
            fprintf(ptrs," ");
          else
            fprintf(ptrs,"*");
        }
        fprintf(ptrs,"\n");
      }

      for (int i = 0; i < N; i++) {
        fprintf(ptrs,"*");
      }
      fprintf(ptrs,"\n");
      for (int i= mitad2-2; i>=0;i--) {
        for (int j = 0; j <mitad; j++) {
          if(mitad2+i-1==j || mitad2-i-1==j)
            fprintf(ptrs,"*");
          else
            fprintf(ptrs," ");
        }
        for (int j = mitad; j <N; j++) {
          if(mitad+mitad2+i-1<j || mitad+mitad2-i-1>j)
            fprintf(ptrs," ");
          else
            fprintf(ptrs,"*");
        }
        fprintf(ptrs,"\n");
      }
    	fclose(ptrs);
      printf("La figura se cargo al archivo\n");
  }

}
int main(){
  printf("Teclee el numero de asteriscos de la linea horizontal\n");
  int N; // numero de asteriscos de la linea horizontal
  scanf("%d",&N);
  if((N-6)%4!=0 || N<6){
    printf("Teclea un numero de la forma 6+4x donde x pertenece a los numeros reales\n");
  }else{
    int mitad=N/2;
    int mitad2=mitad/2+1;
    for (int i= 0; i< mitad2-1;i++) {
      for (int j = 0; j <mitad; j++) {
        if(mitad2+i-1==j || mitad2-i-1==j)
          printf("*");
        else
          printf(" ");
      }
      for (int j = mitad; j <N; j++) {
        if(mitad+mitad2+i-1<j || mitad+mitad2-i-1>j)
          printf(" ");
        else
          printf("*");
      }
      printf("\n");
    }

    for (int i = 0; i < N; i++) {
      printf("*");
    }
    printf("\n");
    for (int i= mitad2-2; i>=0;i--) {
      for (int j = 0; j <mitad; j++) {
        if(mitad2+i-1==j || mitad2-i-1==j)
          printf("*");
        else
          printf(" ");
      }
      for (int j = mitad; j <N; j++) {
        if(mitad+mitad2+i-1<j || mitad+mitad2-i-1>j)
          printf(" ");
        else
          printf("*");
      }
      printf("\n");
    }

    printf("Quieres guardar la figura en un archivo?\n S/N \n");
    char seleccion;
    fflush(stdin);
    scanf("%c",&seleccion);
    if(seleccion=='S' || seleccion=='s')
      guarda(N);

  }
  return 0;
}
