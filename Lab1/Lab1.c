#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

#include "funciones.c"

int main(int argc, char *argv[]){

    char *namefile = argv[1];
    printf("Inicia el programa: se leen %d entradas y un nombre de archivo %s\n", argc, namefile);
    FILE *file;
    file = fopen(namefile,"r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
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
    int pid;

    char linea[60];

    char* namefileSalida = argv[2];
    int i=0;
    while (fscanf(file,"%s",&linea) == 1) {
        
        pid = fork();
        if (pid < 0) {
            printf("Error al crear el proceso hijo\n");
            return 1;
        }else if(pid == 0){//Es hijo
            char buffer[60];
            close(fd[1]);
            close(fd2[0]);
            read(fd[0],buffer,sizeof(buffer));

            printf("Lo que lee el hijo %s\n",buffer);

            int respuesta = checkEtapa1(buffer,0);

            write(fd2[1],&respuesta,sizeof(int));

            exit(0);
        }else{
            printf("Funciones padre\n");

            write(fd[1],linea,strlen(linea)+1);

            int status;
            waitpid(pid,&status,0);
            printf("el pid del hijo es %d y su status es %d\n",pid,status);

            int respuesta = escrituraArchivo(namefileSalida,linea,fd2);
            
            printf("La respuesta que recibe el padre es %d\n",respuesta);
            if(respuesta){
                contadores[0] += 1;
            }else{
                contadores[1] += 1;
            }
        }
        i++;
        printf("han ocurrido %d ciclos\n",i);
        
    }
    fclose(file);
    escrituraContadores(namefileSalida,contadores);
    return 0;
}

