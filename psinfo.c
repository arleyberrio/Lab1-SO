#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include <errno.h>
#include <string.h>
#include<stdbool.h>
FILE* fichero;
int main(int argc, char* argv[]) {
  if(argc==1){
    invalidCommand();
  }else{  
    for(int i=0;i<argc;i++){
     if(strcmp(argv[1],"-r") ==0 || strcmp(argv[1],"-read")==0){
       if(argc == 2 ){
         invalidCommand();
       }
       if(i == 1){
         
       }
        if(i>1){
          fichero = fopen("psinfo-report-[pids].info", "a");
            getInfoProc(argv[i]);
                  
        }
      }else{
        if((argc)==2){
          printf("entre 1"); 
          getInfoProc(argv[1]);
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
   
    char statFileName[360];             
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
      fprintf (fichero, "%s%s", "Nombre del proceso:\n", value);
      if(currentLine == 2){
        fprintf (fichero, "%s%s", "Estado:\n", value);
      }
      
      
      if(currentLine == 17){
        fprintf (fichero, "%s%s", "Tamaño total de la imagen de memoria:\n", value);
      }
      if(currentLine == 25){
        fprintf (fichero, "%s%s", "Tamaño de la memoria en la region:\n", value);
      }
      if(currentLine == 26){
        fprintf (fichero, "%s%s", "Tamaño de la memoria en la region:\n", value);
      }
      if(currentLine == 27){
        fprintf (fichero, "%s%s", "Tamaño de la memoria en la region:\n", value);
      }
      if(currentLine == 55){
        fprintf (fichero, "%s%s", "Numero de cambios de contexto realizados (voluntarios - no voluntarios):\n", value);    
      }
      if(currentLine == 56){
        fputs(value, fichero);     
      }
      currentLine++;
    }
    fputs("\n______________________________________\n", fichero); 
    fclose(fichero);   
    fclose(fd);
}
