#include <stdio.h>
#include <string.h>
#include <windows.h>
struct matriz{
  int mat1[40][40],mat2[40][40],suma[40][40],multi[40][40];
};
int mat1inv[40][40];
int mat2inv[40][40];
int matr1[40][40]={{1,0,0,0,0,0,0,0,0,0},
                  {1,2,0,0,0,0,0,0,0,0},
                  {1,2,3,0,0,0,0,0,0,0},
                  {1,2,3,4,0,0,0,0,0,0},
                  {1,2,3,4,5,0,0,0,0,0},
                  {1,2,3,4,5,6,0,0,0,0},
                  {1,2,3,4,5,6,7,0,0,0},
                  {1,2,3,4,5,6,7,8,0,0},
                  {1,2,3,4,5,6,7,8,9,0},
                  {1,2,3,4,5,6,7,8,9,10}};
int matr2[40][40]={{10,9,8,7,6,5,4,3,2,1},
                  {0,9,8,7,6,5,4,3,2,1},
                  {0,0,8,7,6,5,4,3,2,1},
                  {0,0,0,7,6,5,4,3,2,1},
                  {0,0,0,0,6,5,4,3,2,1},
                  {0,0,0,0,0,5,4,3,2,1},
                  {0,0,0,0,0,0,4,3,2,1},
                  {0,0,0,0,0,0,0,3,2,1},
                  {0,0,0,0,0,0,0,0,2,1},
                  {0,0,0,0,0,0,0,0,0,1}};
struct matriz *datos;
void InverseOfMatrix(int matrix[][40], int order,int opc){

    int temp;
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
int inversa(){

  InverseOfMatrix(datos->mat1,10,0);
  InverseOfMatrix(datos->mat2,10,1);
  // printf("gg");
  FILE* fichero;
  fichero = fopen("inversa1.txt", "w");

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


int main(int argc, char *argv[]){
  datos=malloc(sizeof(int)*40*40*4);
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++){
      datos->mat1[i][j]=matr1[i][j];
      datos->mat2[i][j]=matr2[i][j];
    }
  DWORD escritos,leidos;
  HANDLE hLecturaPipe, hEscrituraPipe;
  PROCESS_INFORMATION piHijo;
  STARTUPINFO siHijo;
  SECURITY_ATTRIBUTES pipeSeg={sizeof(SECURITY_ATTRIBUTES), NULL,TRUE};
  GetStartupInfo(&siHijo);
  CreatePipe(&hLecturaPipe, &hEscrituraPipe, &pipeSeg, 0);
  printf("gg");
  WriteFile(hEscrituraPipe,datos,40*40*4*4+1, &escritos, NULL);
  siHijo.hStdInput=hLecturaPipe;
  siHijo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
  siHijo.hStdOutput=hEscrituraPipe;
  siHijo.dwFlags=STARTF_USESTDHANDLES;
  CreateProcess(NULL, "Punto4Hijo", NULL, NULL, TRUE,
  0, NULL, NULL, &siHijo, &piHijo);
  WaitForSingleObject(piHijo.hProcess,INFINITE);
  printf("Mensaje recibido en el proceso hijo, termina el proceso padre\n");
  ReadFile(hLecturaPipe,datos,40*40*4*4,&leidos,NULL);
  inversa();
  CloseHandle(hLecturaPipe);
  CloseHandle(hEscrituraPipe);
  CloseHandle(piHijo.hThread);
  CloseHandle(piHijo.hProcess);
  return 0;
}
