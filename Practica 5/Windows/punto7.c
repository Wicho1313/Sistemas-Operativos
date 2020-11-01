#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <windows.h>
DWORD WINAPI suma(LPVOID lpParam1);
DWORD WINAPI resta(LPVOID lpParam2);
DWORD WINAPI multipli(LPVOID lpParam3);
DWORD WINAPI traspuesta(LPVOID lpParam4);
DWORD WINAPI inversa(LPVOID lpParam5);
DWORD WINAPI hilocentral(LPVOID lpParam6);
DWORD WINAPI imprimir(LPVOID lpParam7);
float mat1[40][40];
float mat2[40][40];
int mat1inv[40][40];
int mat2inv[40][40];
int mat1t[40][40];
int mat2t[40][40];
int multi[40][40];
char archivo[10000];


void InverseOfMatrix(float matrix[][40], int order,int opc){

    float temp;
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 2 * order; j++) {
            if (j == (i + order))
                matrix[i][j] = 1;
        }
    }

    for (int i = order - 1; i > 0; i--) {
        if (matrix[i - 1][0] < matrix[i][0])
            for (int j = 0; j < 2 * order; j++) {
                temp = matrix[i][j];
                matrix[i][j] = matrix[i - 1][j];
                matrix[i - 1][j] = temp;
            }
    }

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 2 * order; j++) {
            if (j != i) {
                temp = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * order; k++) {
                    matrix[j][k] -= matrix[i][k] * temp;
                }
            }
        }
    }

    for (int i = 0; i < order; i++) {

        temp = matrix[i][i];
        for (int j = 0; j < 2 * order; j++) {

            matrix[i][j] = matrix[i][j] / temp;
        }
    }

    for (int i = 0; i < order; i++) {
        for (int j = order; j < 2 * order; j++) {
            if(opc==0)
             mat1inv[i][j-order]=matrix[i][j];
            else
             mat2inv[i][j-order]=matrix[i][j];
        }
    }

    return;
}

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
void guardar(){
  char *secuencia;
  FILE *ptrs,*ptrs2;
  int i,j;
  ptrs= fopen("mat1.txt","r");
  ptrs2= fopen("mat2.txt","r");
  if(ptrs==NULL){
    printf("No hay datos");
    exit(1);
  }else{
        for(i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
              fscanf(ptrs,"%f", &mat1[i][j]);
        fclose(ptrs);
   }
   if(ptrs2==NULL){
     printf("No hay datos");
     exit(1);
   }else{
         for(i = 0; i < 10; i++)
             for(j = 0; j < 10; j++)
               fscanf(ptrs2,"%f", &mat2[i][j]);
         fclose(ptrs2);
    }
}

int main(void){
  DWORD idHilo1;
  HANDLE manHilo1;
  manHilo1=CreateThread(NULL,0,hilocentral,NULL,0,&idHilo1);
  WaitForSingleObject(manHilo1,INFINITE);
  CloseHandle(manHilo1);
  return 0;
}

DWORD WINAPI imprimir(LPVOID lpParam7){
  printf("\n=== Suma ===\n");
  leer("suma.txt");
  printf("\n=== Resta ===\n");
  leer("resta.txt");
  printf("\n=== Multiplicacion ===\n");
  leer("multi.txt");
  printf("\n=== Traspuesta ===\n");
  leer("traspuesta.txt");
  printf("\n=== Inversa ===\n");
  leer("inversa.txt");
}

DWORD WINAPI hilocentral(LPVOID lpParam6){
  DWORD idHilo2;
  HANDLE manHilo2;
  manHilo2=CreateThread(NULL,0,suma,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  manHilo2=CreateThread(NULL,0,resta,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  manHilo2=CreateThread(NULL,0,multipli,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  manHilo2=CreateThread(NULL,0,traspuesta,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  manHilo2=CreateThread(NULL,0,inversa,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  manHilo2=CreateThread(NULL,0,imprimir,NULL,0,&idHilo2);
  WaitForSingleObject(manHilo2,INFINITE);
  CloseHandle(manHilo2);
  return 0;
}

DWORD WINAPI inversa(LPVOID lpParam5){
  guardar();
  InverseOfMatrix(mat1,10,0);
  InverseOfMatrix(mat2,10,1);
  FILE* fichero;
  fichero = fopen("inversa.txt", "w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%.3f ", (float)(mat1inv[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fprintf(fichero,"\n");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%.3f ", (float)(mat2inv[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}

DWORD WINAPI multipli(LPVOID lpParam3){
  guardar();
  FILE* fichero;
  fichero = fopen("multi.txt", "w");

  int i, j, k;
  for (i = 0; i < 10; i++){
    for (j = 0; j < 10; j++){
        multi[i][j] = 0;
        for (k = 0; k < 10; k++)
            multi[i][j] += mat1[i][k]*mat2[k][j];
    }
  }

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%d ", (int)(multi[i][j]));
    }
    fprintf(fichero,"\n");
  }

  fclose(fichero);
  return 0;
}

DWORD WINAPI resta(LPVOID lpParam2){
  guardar();
  FILE* fichero;
  fichero = fopen("resta.txt","w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero,"%d ", (int)(mat1[i][j]-mat2[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}

DWORD WINAPI suma(LPVOID lpParam1){
  guardar();
  FILE* fichero;
  fichero = fopen("suma.txt","w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero,"%d ", (int)(mat1[i][j]+mat2[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}

DWORD WINAPI traspuesta(LPVOID lpParam4){
  guardar();
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      mat1t[i][j] = mat1[j][i];
      mat2t[i][j] = mat2[j][i];
    }
  }
  FILE* fichero;
  fichero = fopen("traspuesta.txt", "w");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%d ", (int)(mat1t[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fprintf(fichero,"\n");
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      fprintf(fichero, "%d ", (int)(mat2t[i][j]));
    }
    fprintf(fichero,"\n");
  }
  fclose(fichero);
  return 0;
}
