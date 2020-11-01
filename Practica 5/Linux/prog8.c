/*
  COMPILAR :  gcc prog8.c -lpthread -o prog8
  EJECUTAR : ./prog8f /home/ulises/Desktop/Practica4 /home/ulises/Desktop/Practica9

*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

void* abrirDirectorio (void* arg);
int verEstado (char* rutaArchivo);
void copiarArchivo(char* rutaArchivo, char* rutaSalida);

struct rutas {
    char archivo_ini[100];
    char archivo_fin[100];
};

int main (int argc, char* argv[]){
	if(argc < 3) return 1;
  struct rutas *origen;
  origen=(struct rutas*)malloc(sizeof(struct rutas));

  strcpy(origen->archivo_ini,argv[1]);
  strcpy(origen->archivo_fin,argv[2]);

	pthread_t thread;
	pthread_create (&thread, NULL, abrirDirectorio,(void*)origen);
	pthread_join(thread,NULL);
	return 0;

}



void *abrirDirectorio(void *arg){
  struct rutas *ruta;
  ruta=(struct rutas*)arg;
	DIR *dir;
	struct dirent *sd;
	dir=opendir(ruta->archivo_ini);
	char** auxi;
	auxi=malloc(sizeof(char*)*3);
	auxi[0]=malloc(sizeof(char)*500);
	auxi[1]=malloc(sizeof(char)*500);


	if(dir==NULL){
		printf("Error, no se pudo abrir el directorio\n");
		exit(1);
	}

	while( (sd=readdir(dir)) != NULL ){
		if(strcmp(sd->d_name,".")!=0 && strcmp(sd->d_name,"..")!=0  ){

			strcat(auxi[0],ruta->archivo_ini);
			strcat(auxi[0],"/");            //COPIAR RUTA ORIGEN
			strcat(auxi[0],sd->d_name);

			if(verEstado(auxi[0])>1){
				printf("Carpeta:%s \n", sd->d_name );

				strcat(auxi[1],ruta->archivo_fin);
				strcat(auxi[1],"/");       //COPIAR RUTA SALIDA
				strcat(auxi[1],sd->d_name);

				mkdir(auxi[1], 0777);   //Crear carpeta


        struct rutas *origen;
        origen=(struct rutas*)malloc(sizeof(struct rutas));

        strcpy(origen->archivo_ini,auxi[0]);
        strcpy(origen->archivo_fin,auxi[1]);

				//abrirDirectorio(aux,auxSalida);
				pthread_t subthread;
				pthread_create (&subthread, NULL, abrirDirectorio,(void*)origen);
				pthread_join(subthread,NULL);

				strcpy(auxi[1], "");
			}else{
				printf("Archivo:%s \n", sd->d_name );
				strcat(auxi[1],ruta->archivo_fin);
				strcat(auxi[1],"/");
				strcat(auxi[1],sd->d_name);
				copiarArchivo(auxi[0],auxi[1]);
				strcpy(auxi[1], "");
			}
			strcpy(auxi[0], "");

		}

	}
}

int verEstado (char* rutaArchivo){
	 struct stat fileStat;
	 if(stat(rutaArchivo,&fileStat) < 0)
    	return -1;
    return fileStat.st_nlink;
}

void copiarArchivo(char archivo_ini[],char archivo_fin[]){
    printf("Archivo: %s\n", archivo_ini);
    printf("Salida: %s/\n", archivo_fin);
    int leer = open(archivo_ini, O_RDONLY);
    int escribir = open(archivo_fin, O_WRONLY | O_CREAT, 0644);
    int count = 0;
    char buff[10000];
    if(leer<1)printf("Error al abrir el archivo\n");

    while(read(leer,buff,10000))
      write (escribir, buff, strlen(buff));
    close(leer);
    close(escribir);
}
