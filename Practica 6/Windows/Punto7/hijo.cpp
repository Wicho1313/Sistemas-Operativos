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

void sumarMatriz();
void cliente();
void servidor(Matrix Mat);
void imprimirMatriz(float arr1[][num]);
float MatrizX[num][num], MatrizY[num][num];


Matrix Am=randomMatrix(10,10,0,10);
Matrix Bm=randomMatrix(10,10,0,10);

int main(void){
	cliente();
}



void cliente(){
	HANDLE hArchMapeo;
	char *idMemCompartida = (char *)"Matriz2";
	float *apDatos, *apMatriz1, *apMatriz2;

	if((hArchMapeo = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE, idMemCompartida)) == NULL){
		printf("No se abrio archivo de mapeo de la memoria compartidaHIJ: (%i)\n", GetLastError());
		exit(-1);
	}

	if((apDatos= (float *)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS,0,0,TAM_MEM))== NULL){
		printf("No se accedio a la memoria compartida(%i)\n", GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}

	apMatriz1 = apDatos;

	apMatriz2 = apMatriz1;

	*apDatos=111000;
	printf("Matrix Am: \n");
	printMatrix(Am);
	printf("Matrix Bm: \n");
	printMatrix(Bm);

	sumarMatriz();

	servidor(add(Am,Bm));
	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);
	exit(0);
}



void imprimirMatriz(float arr1[][num]){
	for(int x = 0; x<num; x++){
		for(int y = 0; y<num; y++){
			printf("[%.2f]", arr1[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}



void sumarMatriz(){
	char *rout;
	rout="SUMA.txt";

	writeMatrix(add(Am, Bm), rout);
	printf("Am+Bm= \n");
	printMatrix(readMatrix(10,10,rout));
}



void servidor(Matrix MAt){
	HANDLE hArchMapeo;
	char *idMemCompartida =(char *)"Matriz3";
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

	while(*apDatos != 111000)
		sleep(1);

	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);
}
