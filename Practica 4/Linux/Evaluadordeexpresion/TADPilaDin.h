/*
LIBRERIA: Cabecera de el TAD PILA DINÁMICA
AUTOR: Edgardo Adrián Franco Martínez (C) Septiembre 2012
VERSIÓN: 1.3

DESCRIPCIÓN: TAD pila o stack.
Estructura de datos en la que se cumple:
Los noto2s se añaden y se remueven por un solo extremo.
Este extremo es llamado “tope” de la pila.

OBSERVACIONES: Hablamos de una Estructura de datos dinámica
cuando se le asigna memoria a medida que es necesitada,
durante la ejecución del programa. En este caso la memoria
no queda fija durante la compilación y se logrará este dinamismo
a travez del modelo "nodo" el cuál se reservará dinamicamente logrando
modelar una pila.
*/

//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;

typedef struct nodo2
{
	char operador;
	char num;
	struct nodo2 *parent;
	struct nodo2 *izq;
	struct nodo2 *der;
	char childtype;
}nodo2;

typedef nodo2 *ptr;


//Definir un nodo que será utilizado para almacenar una posición de la pila (Nodo), lo que incluira a un noto2 y a un apuntador al siguiente nodo
typedef struct nodo
{
	//Elemento a almacenar en cada nodo de la pila
	ptr e;
	//Apuntador al noto2 de debajo (Requerido por ser una implementación dinámica -Usuario: No modificar)
	struct nodo *abajo;
}nodo;

//Definir una pila (Se modela con una estructura que unicamente incluye un puntero a "noto2")
typedef struct pila
{
	nodo *tope;
}pila;

//DECLARACIÓN DE FUNCIONES
void Initialize(pila *s);			//Inicializar pila (Iniciar una pila para su uso)
void Push(pila *s, ptr e);		//Empilar (Introducir un noto2 a la pila)
ptr Pop (pila *s);				//Desempilar (Extraer un ptr de la pila)
boolean Empty(pila *s);				//Vacia (Preguntar si la pila esta vacia)
ptr Top(pila *s);				//Tope (Obtener el "noto2" del tope de la pila si extraerlo de la pila)
int Size(pila *s);					//Tamaño de la pila (Obtener el número de noto2s en la pila)
void Destroy(pila *s);				//Elimina pila (Borra a todos los noto2s y a la pila de memoria)
