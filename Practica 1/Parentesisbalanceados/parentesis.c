
/*
COMPILACIÃ“N: 	gcc -o EvaluaParentesis EvaluaParentesis.c TADPilaDin.o (Si se tiene el objeto de la implementacion)
				gcc -o parentesis parentesis.c TADPilaDin.c (Si se tiene el fuente de la implementacion)
*/

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>	//Para usar exit()
#include <string.h> //Para usar strlen()
//#include "TADPila/TADPilaEst.h" //Inclusion de la libreria del TAD Pila EstÃ¡tica (Si se desea usar una pila estÃ¡tica)
#include "TADPilaDin.h" //Inclusion de la libreria del TAD Pila DinÃ¡mica (Si se desea usar una pila dinÃ¡mica)

//DEFINICIONES
#define TAM_CADENA 100 //Tamaño maximo de la cadena a evaluar considerando el '\0'

//PROGRAMA PRINCIPAL
int main(void)
{
	int tam_cadena;
	int i,j;
	char cadena[TAM_CADENA];

	//Se declara una pila "mi_pila"
	pila mi_pila;
	//Declaro un elemento "e1"
	elemento e1;
	//Inicializacion de "mi_pila"
	Initialize(&mi_pila);

	//Leer cadena a evaluar sus parentesis
	scanf("%s",cadena);

	//Medir el tamaÃ±o de la cadena
	tam_cadena=strlen(cadena);

	//Recorrer cada caracter de la cadena
	for(i=0;i<tam_cadena;i++){
		//Si el caracter es ( introducirlo a la pila
		if(cadena[i]=='(' || cadena[i]=='[' || cadena[i]=='{'){
				e1.c=cadena[i];
				Push(&mi_pila,e1);
		}else if(cadena[i]==')' || cadena[i]==']' || cadena[i]=='}'){//Si el caracter es ) realizar un Pop a la pila

				//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
				if(Empty(&mi_pila)){
					printf("ERROR: Existen mas parentesis que cierran de los que abren");
					exit(1); //Salir del programa con error
				}
				if((Top(&mi_pila).c=='(' && cadena[i]==')') || (Top(&mi_pila).c=='[' && cadena[i]==']') || (Top(&mi_pila).c=='{' && cadena[i]=='}'))
					e1=Pop(&mi_pila);
		}
	}

	//Si al terminar de revisar la expresion aÃºn hay elementos en la pila Error: P.g. (a+b)*c(a-c
	if(!Empty(&mi_pila)){
		printf("ERROR: Los parentesis no estan balanceados");
		exit(1); //Salir del programa con error
	}

	//Si la ejecucion termina de manera correcta
	printf("EXCELENTE: Expresion correcta");

	//Destruir los elementos de la pila
	Destroy(&mi_pila);
	exit(0); //Terminar el programa sin errores
}
