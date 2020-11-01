#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
int main(){
  int w;
  char gg[200],nombreArchivo[10];
  HANDLE hfile;
  char cadenas[10][15]= {"silla","pastel","forma","casual","intenso","combinacio","memoria","contexto","portable","contador"};
  char ruta[100];
  printf("\nIngresa la ruta de la carpeta donde quieres crear los archivos\n\n");
  scanf("%s",ruta);
  strcat(ruta,"/NuevoDirectorio/");
  CreateDirectory(ruta,NULL);
  srand(time(NULL));
  int numArchivos=rand()%10;
  if(numArchivos==0)numArchivos=1;
  printf("\nSe han creado %d archivos de nombres:\n\n",numArchivos);
  for(int i=0;i<numArchivos;i++){
    strcpy(gg,ruta);
    for(int j=0;j<3;j++){
      nombreArchivo[j]= 'a'+rand()%25;
     }
    printf("\t%s.txt\n",nombreArchivo);
    strcat(gg,nombreArchivo);
    strcat(gg,".txt");
    hfile=CreateFile(gg,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    w=WriteFile(hfile,cadenas[i],strlen(cadenas[i]),0,NULL);

  }
  CloseHandle(hfile);
  return 0;
}
