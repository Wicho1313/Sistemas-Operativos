#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <string.h>

//recibe el numero de discos, el palo de inicio, el palo auxiliar y el palo de destino

int hanoi(int n, int ini, int aux,int dest){
  if(n==1) {
    printf("Mueve el disco de arriba de %d a %d\n",ini,dest);
    return 0;
  }
  hanoi(n-1,ini,dest,aux); //llama a hanoi con n-1 discos cambiando el destino por auxiliar y viceversa
  printf("Mueve el disco de arriba de %d a %d\n",ini,dest);
  hanoi(n-1,aux,ini,dest); //llama a hanoi con n-1 discos cambiando el inicio por el destino y viceversa
  return 0;
}

int main(){
  int discos=0;
  printf("Teclea el numero de discos\n");
  fflush(stdin);
  scanf("%d",&discos);
  long long pasos= (long long)pow(2,discos)-1; //formula del minimo numero de pasos
  hanoi(discos,1,2,3);
  printf("minimo numero de pasos %lld\n",pasos );
  return 0;
}
