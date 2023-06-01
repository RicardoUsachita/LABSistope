#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    char* namefile = argv[0];
    FILE* file;
    file = fopen(namefile,"r");
    int fd[2];
    int fd2[2];
    int contadores[2];
    contadores[0]=0;
    contadores[1]=0;
    if(pipe(fd) == -1){
        printf("error\n");
        exit(-1);
    }
    if(pipe(fd2) == -1){
        printf("error\n");
        exit(-1);
    }
    pid_t pid;
    int bufferPadre;
    char* bufferHijo; (char *) malloc(sizeof (char)*100);
    char linea[60];

    char* namefileSalida = argv[1];
    while((fscanf(file,"$s",&linea) != EOF)){
        pid = fork();
        if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
        }else if(pid = 0){//Es hijo
            hijo(fd,fd2);
            exit(1);
        }else{

            if(padre(linea,namefileSalida,fd,fd2)){
                contadores[0] += 1;
            }else{
                contadores[1] += 1;
            }
            
        }
    }
    escrituraContadores(namefileSalida,contadores);
    return 0;
}

