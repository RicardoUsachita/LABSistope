#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

#include "funciones.c"

int main(int argc, char *argv[]){
    char input[30] = "prueba_10.txt";
    char output[30] = "salida.txt";
    int flag = 0;
    validate(argc, argv, input, output, &flag);
    if(flag) {
        FILE *file;
        file = fopen(input, "r");
        if (file == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return 1;
        }
        int contador = 0;
        int capacidad = 0;
        char ** arreglo = NULL;
        char linea[60];
        while (fscanf(file, "%s", linea) == 1){
            if (contador >= capacidad) {
                capacidad += 10;
                arreglo = realloc(arreglo, capacidad * sizeof(char*));
            }
            arreglo[contador] = strdup(linea);
            contador++;
        }
        fclose(file);
        int fd[2];
        int fd2[2];
        int contadores[2];
        contadores[0] = 0;
        contadores[1] = 0;
        if (pipe(fd) == -1) {
            printf("error\n");
            exit(-1);
        }
        if (pipe(fd2) == -1) {
            printf("error\n");
            exit(-1);
        }
        int pid;

        for (int i = 0; i < contador;i++) {

            pid = fork();
            if (pid < 0) {
                printf("Error al crear el proceso hijo\n");
                return 1;
            } else if (pid == 0) {//Es hijo
                char buffer[60];
                close(fd[1]);
                close(fd2[0]);
                read(fd[0], buffer, sizeof(buffer));


                int respuesta = checkEtapa1(buffer, 0);

                write(fd2[1], &respuesta, sizeof(int));

                exit(1);
            } else {

                write(fd[1], arreglo[i], sizeof(char)*60);

                //int status;
                //waitpid(pid, &status, 0);
                //printf("el pid del hijo es %d y su status es %d\n", pid, status);
                wait(NULL);

                int respuesta = escrituraArchivo(output, arreglo[i], fd2);

                if (respuesta) {
                    contadores[0] += 1;
                } else {
                    contadores[1] += 1;
                }
            }

        }
        escrituraContadores(output, contadores);

    }else{
        printf("Por favor ingrese una entrada correcta\n");
    }
    return 0;
}

