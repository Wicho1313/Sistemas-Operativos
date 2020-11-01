#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>


float mat1[40][40]={{1,0,0,0,0,0,0,0,0,0},
                  {1,2,0,0,0,0,0,0,0,0},
                  {1,2,3,0,0,0,0,0,0,0},
                  {1,2,3,4,0,0,0,0,0,0},
                  {1,2,3,4,5,0,0,0,0,0},
                  {1,2,3,4,5,6,0,0,0,0},
                  {1,2,3,4,5,6,7,0,0,0},
                  {1,2,3,4,5,6,7,8,0,0},
                  {1,2,3,4,5,6,7,8,9,0},
                  {1,2,3,4,5,6,7,8,9,10}};

int mat1inv[10][10]={};

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
            
             mat1inv[i][j-order]=matrix[i][j];

        }
    }

    return;
}

int main()
{
    InverseOfMatrix(mat1,10,0);
    for(int i=0; i<10; i++) {
      for(int j=0; j<10; j++) {
        printf( "%.3f ", (float)(mat1inv[i][j]));
      }
      printf("\n");
    }

    return 0;
}
