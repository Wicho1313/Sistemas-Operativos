/*
COMPILACION: 	gcc -o EvaluaParentesis EvaluaParentesis.c TADPilaDin.o (Si se tiene el objeto de la implementacion)
				gcc -o parentesis parentesis.c TADPilaDin.c (Si se tiene el fuente de la implementacion)
*/

#include<stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>	//Para usar exit()
#include <string.h> //Para usar strlen()
#include "TADPilaDin.h" //Inclusion de la libreria del TAD Pila DinÃ¡mica (Si se desea usar una pila dinÃ¡mica)


void create(int k,ptr node[], char operador, char numero)
{
  ptr t;
  t = malloc(sizeof(nodo2));
  t->operador=operador;
  t->num=numero;
  t->parent = NULL;
  node[k] = t;
}
ptr node[100];
int cont=0;

int esmenor(char tope, char caracter){
  int n1,n2;
  switch (tope) {
    case '^': n1=3; break;
    case '/': n1=2; break;
    case '*': n1=2; break;
    case '+': n1=1; break;
    case '-': n1=1; break;
    case '(': n1=0; break;
  }
  switch (caracter) {
    case '^': n2=3; break;
    case '/': n2=2; break;
    case '*': n2=2; break;
    case '+': n2=1; break;
    case '-': n2=1; break;
    case '(': n2=0; break;
  }
  if(n1<n2) return 1;
  return 0;
}
float calcula(ptr raiz){
  if(raiz->operador=='@')
    return (float)atoi(&raiz->num);
  else{
    switch (raiz->operador) {
      case '^': return (float)pow(calcula(raiz->izq),calcula(raiz->der)); break;
      case '/': return (float)calcula(raiz->izq)/calcula(raiz->der); break;
      case '*': return (float)calcula(raiz->izq)*calcula(raiz->der); break;
      case '+': return (float)calcula(raiz->izq)+calcula(raiz->der); break;
      case '-': return (float)calcula(raiz->izq)-calcula(raiz->der); break;
    }
  }
}
int main(){
  int boolnumero=0;
  char cad[100];
  ptr derecha=NULL,izquierda=NULL,centro=NULL;
  printf("Teclea la expresion\n");
  fflush(stdin);
  gets(cad);
  pila operadores;
  pila valores;
	//Declaro un ptr "e1"
	//Inicializacion de pilas
	Initialize(&operadores);
  Initialize(&valores);

  char *ptr1;
  ptr1=cad;
  for(; *ptr1!='\0'; ptr1++){
    //printf("--%c", *ptr1);
    if(*ptr1=='^' || *ptr1=='*' || *ptr1=='/' || *ptr1=='+' || *ptr1=='-' || *ptr1=='(' || *ptr1==')'){
        if(*ptr1==')'){

          while(Top(&operadores)->operador!='('){

            ptr op=Pop(&operadores);
            ptr c2=Pop(&valores);
            derecha=c2;
            fflush(stdin);
            ptr c1=Pop(&valores);
            izquierda=c1;
            op->izq=izquierda;
            op->der=derecha;
            Push(&valores, op);
          }
          Pop(&operadores);
        }else{
          while(!Empty(&operadores) && *ptr1!='(' && esmenor(Top(&operadores)->operador,*ptr1)==0 ){
            ptr op=Pop(&operadores);
            ptr c2=Pop(&valores);
            derecha=c2;
            fflush(stdin);
            ptr c1=Pop(&valores);
            izquierda=c1;
            op->izq=izquierda;
            op->der=derecha;
            Push(&valores, op);
          }
          create(cont,node,*ptr1,'$');
          Push(&operadores,node[cont++]);

        }
    }else{
        ptr e1; e1->num=*ptr1; e1->operador='@';
        fflush(stdin);
        create(cont,node,e1->operador,e1->num);
        Push(&valores,node[cont++]);
    }

  }
  printf("%f\n",calcula(Top(&valores)) );

  return 0;
}
