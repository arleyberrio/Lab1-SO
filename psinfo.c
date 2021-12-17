#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if(argc==1){
    invalidCommand();
  }else{  
    for(int i=0;i<argc;i++){
     if(strcmp(argv[1],"-l") ==0 || strcmp(argv[1],"-list")==0){
       if(argc == 2 ){
         invalidCommand();
       }
       if(i == 1){
         //print "-- Informacion recolectada!!!"
       }
        if(i>1){
          getInfoProc(argv[i]);
        }
      }else{
        if((argc)==2){
          getInfoProc(argv[1]);
          i = argc;
        }else{
          invalidCommand();
        }
      }
    }
  }
  
    return 0;
}
void invalidCommand(){
  errno = 1;
  perror("Comando invalido");
  abort();
}
void getInfoProc(char* currentPid){
    char statFileName[360];             /* /proc/PIC/stat - I think 512 bytes is far enough */
    int lineNumber[] = {0,2,17,25,26,27,56,57};

    sprintf(statFileName, "/proc/%s/status", currentPid);
    FILE *fd = fopen(statFileName, "r");
    if (fd == NULL){
      errno = 1;
      perror("No puedo encontrar el proceso especificado");
      abort();
    }

    int currentLine = 0;
    char line[1024];

    char *value;
    while(fgets(line, sizeof line, fd) != NULL){ //read a line

      value = strtok(line, ":");
      value = strtok(NULL, ":");
      if(currentLine == 0)
        printf("Nombre del proceso:%s\n", value);

      if(currentLine == 2)
        printf("Estado:%s\n", value);
      
      if(currentLine == 17)
        printf("Tamaño total de la imagen de memoria:%s\n", value);

      if(currentLine == 25)
        printf("\tTamaño de la memoria en la region:%s\n", value);

      if(currentLine == 26)
        printf("\tTamaño de la memoria en la region:%s\n", value);

      if(currentLine == 27)
        printf("\tTamaño de la memoria en la region:%s\n", value);

      if(currentLine == 55){
        printf("Numero de cambios de contexto realizados (voluntarios - no voluntarios):%s-", value);        
      }
      if(currentLine == 56){
        printf("%s\n", value);        
      }

      currentLine++;
    }
    fclose(fd);
}
