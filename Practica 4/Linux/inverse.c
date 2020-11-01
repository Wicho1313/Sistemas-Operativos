#include <iostream>
#include <vector>
using namespace std;




void PrintInverse(float ar[][40], int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = n; j < m; j++) {
            printf("%.3f  ", ar[i][j]);
        }
        printf("\n");
    }
    return;
}


void InverseOfMatrix(float matrix[][40], int order)
{


    float temp;



    printf("=== Matrix ===\n");
    PrintMatrix(matrix, order, order);




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


    printf("\n=== Augmented Matrix ===\n");
    PrintMatrix(matrix, order, order * 2);



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


    printf("\n=== Inverse Matrix ===\n");
    PrintInverse(matrix, order, 2 * order);

    return;
}


int main()
{
    int order;


    order = 10;
    int matrix[40][40] = {{1,0,0,0,0,0,0,0,0,0},
                            {1,2,0,0,0,0,0,0,0,0},
                            {1,2,3,0,0,0,0,0,0,0},
                            {1,2,3,4,0,0,0,0,0,0},
                            {1,2,3,4,5,0,0,0,0,0},
                            {1,2,3,4,5,6,0,0,0,0},
                            {1,2,3,4,5,6,7,0,0,0},
                            {1,2,3,4,5,6,7,8,0,0},
                            {1,2,3,4,5,6,7,8,9,0},
                            {1,2,3,4,5,6,7,8,9,10}};

    InverseOfMatrix(matrix, order);

    return 0;
}
