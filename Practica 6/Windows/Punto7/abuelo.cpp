#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include"Matrix.h"
#include"FilesWin.h"
#define num 10
#define TAM_MEM 999999

void Servidor();
void imprimirMatriz(float MAt[][num]);
void Cliente();
int Cliente1();
float MatrizX[num][num];

Matrix MatrizR1=randomMatrix(10,10,0,10);
Matrix MatrizR2=randomMatrix(10,10,0,10);

STARTUPINFO si;
PROCESS_INFORMATION pi;

int main(void){

	Servidor();


	return 0;
}



void Servidor(){
	HANDLE hArchMapeo;
	char *idMemCompartida =(char *)"Matriz";
	float *apDatos, *apMatriz1, *apMatriz2;

	if((hArchMapeo = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMemCompartida))== NULL){
		printf("No se mapeo la memoria compartida(%i)\n", GetLastError());
		exit(-1);
	}

	if ((apDatos = (float * )MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL){
		printf("No se creo la memoria compartida:(%i)\n",GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}

	apMatriz1 = apDatos;
	apMatriz2 = apMatriz1;

	//CREACION DE PROCESO PADRE
	ZeroMemory( &si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi));

	//Creacion del proceso hijo
	CreateProcess("padre.exe",NULL, NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);

	while(*apDatos != 111000)
		sleep(1);

	Cliente();
	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);

	exit(0);
}



void Cliente(){
	HANDLE hArchMapeo;
	char *idMemCompartida = (char *)"Matriz1";
	float *apDatos, *apMatriz1, *apMatriz2;

	if((hArchMapeo = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE, idMemCompartida)) == NULL){
		printf("No se abrio archivo de mapeo de la memoria compartida AB: (%i)\n", GetLastError());
		exit(-1);
	}

	if((apDatos= (float *)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS,0,0,TAM_MEM))== NULL){
		printf("No se accedio a la memoria compartida(%i)\n", GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}

	apMatriz1 = apDatos;

	*apDatos=111000;
	printf("MATRIZ 1\n");
	//imprimirMatriz(MatrizR1);

	while(Cliente1() != TRUE)
		sleep(1);

	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);

	exit(0);
}



int Cliente1(){
	char *routR1, *routR2;

	routR1="R1_INV.txt";
	routR2="R2_INV.txt";

	HANDLE hArchMapeo;
	char *idMemCompartida = (char *)"Matriz3";
	float *apDatos, *apMatriz1, *apMatriz2;

	if((hArchMapeo = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE, idMemCompartida)) == NULL){
		return FALSE;
	}

	if((apDatos= (float *)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS,0,0,TAM_MEM))== NULL){
		return FALSE;
	}

	apMatriz1 = apDatos;


	*apDatos=111000;
	printf("MATRIZ 2\n");
	//imprimirMatriz(MatrizR2);

	//I N V E R S A
	writeMatrix(invert(MatrizR1), routR1);
	printf("Inversa de MATRIZ 1= \n");
	Matrix result1= readMatrix(10,10,routR1);;
	printMatrix(result1);

	writeMatrix(invert(MatrizR2), routR2);
	printf("Inversa de MATRIZ 2= \n");
	Matrix result2= readMatrix(10,10,routR2);
	printMatrix(result2);


	UnmapViewOfFile(apDatos);
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(hArchMapeo);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	exit(0);
	return 1;

}



void imprimirMatriz(float MAt[][num]){
	for(int x = 0; x<num; x++){
		for(int y = 0; y<num; y++){
			printf("[%.2f]", MAt[x][y]);
		}
	printf("\n");
	}
	printf("\n");
}
