void writeMatrix(Matrix a, char*rout);
Matrix readMatrix(int rows, int columns, char*rout);


void writeMatrix(Matrix a, char*rout){
	int file, i, j;
	file=open(rout, O_WRONLY, 07000);

	char * auxiliary=(char*)malloc(sizeof(char));
	for(i=0; i<a.rows; i++){
		for (j = 0; j < a.columns; ++j)
		{
			sprintf(auxiliary, "%.4f", a.numbers[i][j]); 
			auxiliary[strlen(auxiliary)]=' ';
			write(file, auxiliary, strlen(auxiliary));
		}
	}

	close(file);
}

Matrix readMatrix(int rows, int columns, char*rout){
	Matrix result= newMatrix(rows, columns);
	int i, j=0, file, position=0, p, k, point;
	char * buffer=(char*)malloc(sizeof(char));
	char* auxiliary=(char*)malloc(sizeof(char));

	file=open(rout, O_RDONLY, 07000);

	for(i=0; i<rows; i++){
		
			
		
		while(j!=columns){
			read(file, buffer, sizeof(char));
			if(buffer[0]==' '){
				result.numbers[i][j]=atof(auxiliary);
				j++;
				free(auxiliary);
				auxiliary=(char*)calloc(50,sizeof(char));
			}
			else{			
				auxiliary[strlen(auxiliary)]=buffer[0];
			}
		}
		j=0;	
		
	}
	return result;
}

