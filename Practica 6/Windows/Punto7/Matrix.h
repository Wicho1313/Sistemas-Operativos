typedef struct data{
    float** numbers;
    int* positions;
    int rows,columns;    
}Matrix;
int isDecimal(float);
int isRowZeros(Matrix,int);
int isColumnZeros(Matrix,int);
int isSortable(Matrix);
void fillMatrix(Matrix*,float);
//funcion para crear una matriz de nxm llena de ceros
Matrix newMatrix(int,int);
//funcion para liberar la memoria de una matriz
void destroyMatrix(Matrix*);
Matrix randomMatrix(int,int,int,int);
//funcion para copiar una matriz
Matrix copyMatrix(Matrix);
void printMatrix(Matrix);
int eqMatrix(Matrix,Matrix);
//funcion para sumar matrices
//devuelve una matriz de 0x0 si la operacion no se pudo realizar
Matrix addMatrix(Matrix,Matrix);
//funcion para restar matrices
//devuelve una matriz de 0x0 si la operacion no se pudo realizar
Matrix substractMatrix(Matrix,Matrix);
//funcion para multiplicar matrices
//devuelve una matriz de 0x0 si la operacion no se pudo realizar
Matrix multiplyMatrix(Matrix,Matrix);
//funcion para sacar la transpuesta de una matriz
Matrix transposeMatrix(Matrix);
Matrix identityMatrix(int);
int isPivotable(Matrix);
Matrix swapRow(Matrix,int,int);
int diagonalZero(Matrix,int);
int diagonalZeros(Matrix);
Matrix sortMatrix(Matrix,int,int);
Matrix changeRows(Matrix,int*);
float* copyRow(float*,int);
float* multiplyRow(float*,int,float);
float getPivot(Matrix,int);
float* addRow(float*,float*,int);
//funcion para sacar la inversa de una matriz
//devuelve una matriz de 0x0 si la operacion no se pudo realizar
Matrix invertMatrix(Matrix);
float roundFloat(float);
//funcion para redondear los decimales de los numeros de una matriz, los redondea en 2 decimales
//se debe usar al multiplicar una matriz por su inversa para no ver numeros como "1.00", "0.00", "-0.00", etc
void roundMatrix(Matrix*);
int isDecimal(float number){
    int _number = number;
    float mod = number-_number;
    if(mod==0){
        return 0;
    }else return 1;
}
int isRowZeros(Matrix a,int row){
    if(row<=a.rows){
        int i;
        for(i=0;i<a.columns;i++){
            if(a.numbers[row][i]!=0){
                return 0;
            }
        }
        return 1;
    }else return 0;
}
int isColumnZeros(Matrix a,int column){
    if(column<=a.columns){
        int i;
        for(i=0;i<a.rows;i++){
            if(a.numbers[i][column]!=0){
                return 0;
            }
        }
        return 1;
    }else return 0;
}
int isSortable(Matrix a){
    int i;
    for(i=0;i<a.rows;i++){
        if(isRowZeros(a,i)){
            return 0;
        }
    }
    for(i=0;i<a.columns;i++){
        if(isColumnZeros(a,i)){
            return 0;
        }
    }
    return 1;
}
void fillMatrix(Matrix* m,float number){
    int i,j;
    for(i=0;i<m[0].rows;i++){
        for(j=0;j<m[0].columns;j++){
            m[0].numbers[i][j]=number;
        }
    }
}
Matrix newMatrix(int rows,int columns){
    float** numbers;
    int* positions;
    int i;
    numbers=(float**)malloc(sizeof(float*)*rows);
    for(i=0;i<rows;i++){
        numbers[i]=(float*)malloc(sizeof(float)*columns);
    }
    positions=(int*)malloc(sizeof(int)*rows);
    for(i=0;i<rows;i++){
        positions[i]=i;
    }
    Matrix temp;
    temp.rows=rows;
    temp.columns=columns;
    temp.numbers=numbers;
    temp.positions=positions;
    fillMatrix(&temp,0);
    return temp;
}
void destroyMatrix(Matrix* a){
    int i;
    for(i=0;i<a[0].rows;i++){
        free(a[0].numbers[i]);
    }
    free(a[0].numbers);
    free(a[0].positions);
}
Matrix randomMatrix(int rows,int columns,int min,int max){
    Matrix result = newMatrix(rows,columns);
    int i,j,ran,sig;
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            do{
                ran=rand()%(max+1);
                sig=rand()%2;
                if(sig){
                    ran=-ran;
                }
            }while(!(ran>=min&&ran<=max));
            result.numbers[i][j]=ran;
        }
    }
    return result;
}
Matrix copyMatrix(Matrix a){
    Matrix copy = newMatrix(a.rows,a.columns);
    int i,j;
    for(i=0;i<a.rows;i++){
        for(j=0;j<a.columns;j++){
            copy.numbers[i][j]=a.numbers[i][j];
        }
    }
    for(i=0;i<a.rows;i++){
        copy.positions[i]=a.positions[i];
    }
    return copy;
}
void printMatrix(Matrix m){
    int i,j;
    for(i=0;i<m.rows;i++){
        for(j=0;j<m.columns;j++){
            if(isDecimal(m.numbers[i][j])){
                printf("%.2f\t",m.numbers[i][j]);
            }else{
                printf("%d\t",(int)m.numbers[i][j]);
            }
        }
        printf("\n");
    }
}
int eqMatrix(Matrix a,Matrix b){
    if(a.rows==b.rows&&a.columns==b.columns){
        int i,j;
        for(i=0;i<a.rows;i++){
            for(j=0;j<a.columns;j++){
                if(a.numbers[i][j]!=b.numbers[i][j]){
                    return 0;
                }
            }
        }
        return 1;
    }else
        return 0;
}
Matrix add(Matrix A, Matrix B){
    int i, j;
    if((A.rows==B.rows)&&(A.columns)){
    Matrix result=newMatrix(A.rows, A.columns);
        for(i=0; i<A.rows; i++){
            for(j=0; j<A.columns; j++){
                result.numbers[i][j]=A.numbers[i][j]+B.numbers[i][j];
            }
        }
        return result;
    }
    else return newMatrix(0,0);
}

Matrix substract(Matrix A, Matrix B){
    int i, j;
    if((A.rows==B.rows)&&(A.columns)){
    Matrix result=newMatrix(A.rows, A.columns);
        for(i=0; i<A.rows; i++){
            for(j=0; j<A.columns; j++){
                result.numbers[i][j]=A.numbers[i][j]-B.numbers[i][j];
            }
        }
        return result;
    }
    else return newMatrix(0,0);
}
Matrix multiply(Matrix A,Matrix B){
    if(A.columns==B.rows){
        int i,j,k;
        Matrix result = newMatrix(A.rows,B.columns);
        for(i=0;i<A.rows;i++){
            for(j=0;j<B.columns;j++){
                for(k=0;k<A.columns;k++){
                    result.numbers[i][j]+=A.numbers[i][k]*B.numbers[k][j];
                }
            }
        }
        return result;
    }else return newMatrix(0,0);
}
Matrix transpose(Matrix a){
    Matrix result = newMatrix(a.columns,a.rows);
    int i,j;
    for(i=0;i<result.rows;i++){
        for(j=0;j<result.columns;j++){
            result.numbers[i][j]=a.numbers[j][i];
        }
    }
    return result;
}
Matrix identity(int number){
    Matrix result = newMatrix(number,number);
    int i,j;
    for(i=0;i<number;i++){
        for(j=0;j<number;j++){
            if(i==j){
                result.numbers[i][j]=1.0;
            }
        }
    }
    return result;
}
int isPivotable(Matrix a){
    int i,j;
    if(a.rows==a.columns){
        for(i=0;i<a.rows;i++){
            if(!a.numbers[i][i]){
                return 0;
            }
        }
    }else
        return 0;
    return 1;
}
Matrix swapRow(Matrix a,int row1,int row2){
    Matrix result = copyMatrix(a);
    float* aux = result.numbers[row1];
    result.numbers[row1]=result.numbers[row2];
    result.numbers[row2]=aux;
    result.positions[row1]=a.positions[row2];
    result.positions[row2]=a.positions[row1];
    return result;
}
int diagonalZero(Matrix a,int row){
    if(a.numbers[row][row]==0){
        return 1;
    }else return 0;
}
int diagonalZeros(Matrix a){
    int i,count=0;
    for(i=0;i<a.rows;i++){
        if(!a.numbers[i][i]){
            count++;
        }
    }
    return count;
}
Matrix sortMatrix(Matrix a,int error,int count){
    if(isSortable(a)){
        if(count>120){
            return newMatrix(0,0);
        }
        Matrix b=copyMatrix(a),c=copyMatrix(a);
        int i,j,pivotable=0,zeros=diagonalZeros(b);
        for(i=0;i<a.rows-1;i++){
            error++;
            if(error>120){
                b=sortMatrix(swapRow(b,0,1),0,count+1);
                if(isPivotable(b)){
                    return b;
                }else{
                    b=sortMatrix(swapRow(b,0,2),0,count+1);
                    if(isPivotable(b)){
                        return b;
                    }else return newMatrix(0,0);
                }
            }
            if(!pivotable){
                for(j=i+1;j<a.rows;j++){
                    if(isPivotable(b)){
                        pivotable=1;
                        break;
                    }else if(diagonalZeros(b)<zeros){
                        c=copyMatrix(b);
                        zeros=diagonalZeros(b);
                        i=0;
                        j=0;
                    }else{
                        b=copyMatrix(c);
                        b=swapRow(b,i,j);
                    }
                }
            }else{
                break;
            }
        }
        if(isPivotable(b)){
            return b;
        }else{
            b = sortMatrix(swapRow(b,0,1),error,count);
            if(isPivotable(b)){
                return b;
            }else {
                return newMatrix(0,0);
            }
        }
    }else {
        return newMatrix(0,0);
    }
}
Matrix changeRows(Matrix a,int* positions){
    int i,j,k;
    Matrix b = copyMatrix(a);
    for(i=0;i<a.rows;i++){
        a.numbers[i]=b.numbers[positions[i]];
        a.positions[i]=positions[i];
    }
    return a;
}
float getPivot(Matrix a,int row){
    return (float)(1/a.numbers[row][row]);
}
float* copyRow(float* row,int size){
    float* result=(float*)malloc(sizeof(float)*size);
    int i;
    for(i=0;i<size;i++){
        result[i]=row[i];
    }
    return result;
}
float* multiplyRow(float* row,int size,float number){
    float* result = (float*)malloc(sizeof(float)*size);
    int i;
    for(i=0;i<size;i++){
        result[i]=row[i]*number;
    }
    return result;
}
float* addRow(float* row1,float* row2,int size){
    float* result=copyRow(row1,size);
    int i;
    for(i=0;i<size;i++){
        result[i]+=row2[i];
    }
    return result;
}
Matrix invert(Matrix a){
    Matrix result=identity(a.rows),aux=copyMatrix(a);
    int i,j;
    float pivot,number;
    if(isSortable(aux)){
        aux=sortMatrix(aux,0,0);
        if(isPivotable(aux)){
            result=changeRows(result,aux.positions);
            for(i=0;i<aux.rows;i++){
                pivot=getPivot(aux,i);
                aux.numbers[i]=multiplyRow(aux.numbers[i],aux.rows,pivot);
                result.numbers[i]=multiplyRow(result.numbers[i],aux.rows,pivot);
                for(j=i+1;j<aux.rows;j++){
                    number=-aux.numbers[j][i];
                    if(number){
                        aux.numbers[j]=addRow(aux.numbers[j],multiplyRow(aux.numbers[i],aux.rows,number),aux.rows);
                        result.numbers[j]=addRow(result.numbers[j],multiplyRow(result.numbers[i],result.rows,number),result.rows);
                    }
                }
                if(!isSortable(aux)){
                    return newMatrix(0,0);
                }
            }
            for(i=aux.rows-1;i>=0;i--){
                for(j=i-1;j>=0;j--){
                    number=-aux.numbers[j][i];
                    if(number){
                        aux.numbers[j]=addRow(aux.numbers[j],multiplyRow(aux.numbers[i],aux.rows,number),aux.rows);
                        result.numbers[j]=addRow(result.numbers[j],multiplyRow(result.numbers[i],result.rows,number),result.rows);
                    }
                }
            }
        }else{
            return newMatrix(0,0);
        }
    }else{
        return newMatrix(0,0);
    }
    return result;
}
float roundFloat(float f){
    char number[10];
    sprintf(number,"%.2f",f);
    f=atof(number);
    return f;
}
void roundMatrix(Matrix* a){
    int i,j;
    for(i=0;i<a[0].rows;i++){
        for(j=0;j<a[0].columns;j++){
            a[0].numbers[i][j]=roundFloat(a[0].numbers[i][j]);
        }
    }
}
