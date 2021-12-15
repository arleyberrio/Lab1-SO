#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    errno = 1;
    perror("Comando invalido");
    abort();
  }
    getInfoProc(argv[1]);
    return 0;
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


    //viejo  ño

    // char  state, Name[32];
    // int
    //   Pid;

    // unsigned int voluntary_ctxt_switches, nonvoluntary_ctxt_switches;

    // // unsigned long
    // // vmexe, vmdata, vmstk;

    // float
    // vmexe, vmdata, vmstk;
    // fscanf(fd, "%d %s ",
    //             //  "%c "
    //             //  "%f"
    //             //  "%f"
    //             //  "%f"
    //             //  "%u"
    //             //  "%u",
    //              &Pid,
    //              Name
    //             //  &state,
    //             //  &vmexe, 
    //             //  &vmdata,
    //             //  &vmstk,
    //             //  &voluntary_ctxt_switches, 
    //             //  &nonvoluntary_ctxt_switches
    //              );
   
    fclose(fd);

    // printf ("PID: %d\n"
    //                 "Nombre: %s\n",
    //                 // "Estado: %c\n"
    //                 // "Tam. memoria TEXT: %f\n"
    //                 // "Tam. memoria DATA: %f\n"
    //                 // "tam. memoria STACK: %f\n"
    //                 // "No. cambios voluntarios: %u\n"
    //                 // "No. cambios NO voluntarios: %u\n",
    //                 Pid, Name); 
                    // state, vmexe, vmdata, vmstk, voluntary_ctxt_switches, nonvoluntary_ctxt_switches);
    
}
