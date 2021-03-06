//gcc  test.c -o test
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("%d\n",argc);
    for(int i=0;i<argc;i++)
    {
      /* Validar primer argumento
      if(argv[1]=="-l" OR argv[1]=="-list"){
        if(i>1){
          getInfoProc(argv[i])
        } 
      }else if(argv[1]=="-r" OR argv[1]=="-read" && i==1){
        Generar un metodo que genere un file y retorne su name con el reporte de cada pid
      }else{
        if((argc-1)==i){
          getInfoProc(argv[i])
        }else{
          return perror("Formato no valido"), 1;
        }
        
      }
      */
        printf("%s\n",argv[i]);
    }
}
void getInfoProc(int pid){
  if (argc<2)
        return perror("Falta un argumento"), 1;
    char statFileName[128];             /* /proc/PIC/stat - I think 512 bytes is far enough */
    
    sprintf(statFileName, "/proc/%s/stat", pid);
    /* Podíamos comprobar que argv[1] es numérico y que es de poco
       tamaño, pero para el ejemplo nos vale. */
    FILE *fd = fopen(statFileName, "r");
    if (fd == NULL)
        return perror("No puedo encontrar el proceso especificado"),1;
    char  state, name[32];
    int
      pid,
      ppid,
      pgrp,
      session,
      tty,
      tpgid,
      nlwp;

    unsigned long
    flags,
      min_flt,
      cmin_flt,
      maj_flt,
      cmaj_flt,
      vsize;

    unsigned long long
    utime,
      stime,
      cutime,
      cstime,
      start_time;

    long
    priority,
      nice,
      alarm,
      rss;
   
    fscanf(fd, "%d %s "
                 "%c "
                 "%d %d %d %d %d "
                 "%lu %lu %lu %lu %lu "
                 "%Lu %Lu %Lu %Lu "
                 "%ld %ld "
                 "%d "
                 "%ld "
                 "%Lu "
                 "%lu "
                 "%ld",
                 &pid,
                 name,
                 &state,
                 &ppid, &pgrp, &session, &tty, &tpgid,
                 &flags, &min_flt, &cmin_flt, &maj_flt, &cmaj_flt,
                 &utime, &stime, &cutime, &cstime,
                 &priority, &nice,
                 &nlwp,
                 &alarm,
                 &start_time,
                 &vsize,
                 &rss);
   
    fclose(fd);

    printf ("PID: %d\n"
                    "CMD: %s\n"
                    "Estado: %c\n"
                    "PPID: %d\n"
                    "Tiempo usuario: %Lu\n"
                    "Tiempo kernel: %Lu\n"
                    "Nice: %ld\n"
                    "Threads: %d\n"
                    "Iniciado en: %Lu\n"
                    "Tamaño: %lu\n",
                    pid, name, state, ppid, utime, stime, nice, nlwp, start_time, vsize);
    
}
