
void writeMatrix(Matrix a, char*rout);
Matrix readMatrix(int rows, int columns, char*rout);


void writeMatrix(Matrix a, char*rout){
	int file, i, j;
	HANDLE hFile=CreateFile(rout, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD written = 0;
	char* auxiliary;

	for(i=0; i<a.rows; i++){
		for (j = 0; j < a.columns; j++)
		{
			auxiliary=(char*)calloc(50, sizeof(char));
			sprintf(auxiliary, "%.2f", a.numbers[i][j]);
			auxiliary[strlen(auxiliary)]=' ';
			WriteFile(hFile, auxiliary, strlen(auxiliary), &written, NULL);
		}
	}

	free(auxiliary);
	CloseHandle(hFile);
}

Matrix readMatrix(int rows, int columns, char*rout){
	Matrix result= newMatrix(rows, columns);
	int i, j=0;
	char * buffer=(char*)malloc(sizeof(char));
	char* auxiliary;
	HANDLE hFile=CreateFile(rout, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD read = 0;

	for(i=0; i<rows; i++){
		auxiliary=(char*)calloc(50, sizeof(char));
		while(j!=columns){
			ReadFile(hFile, buffer, sizeof(char), &read, NULL);
			if(buffer[0]==' '){
				result.numbers[i][j]=atof(auxiliary);
				j++;
				free(auxiliary);
				auxiliary=(char*)calloc(50, sizeof(char));
			}
			else{
				auxiliary[strlen(auxiliary)]=buffer[0];
			}
		}
		j=0;

	}
	CloseHandle(hFile);
	return result;
}
