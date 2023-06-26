#include "fbroker.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * i input
 * o output
 * c cant chunks
 * n cant workers
 * b prints console
 */
int main(int argc, char * argv[]){
    char input[30];
    char output[30];
    strcpy(input,argv[1]);
    strcpy(output,argv[2]);
    int num_chunks = atoi(argv[5]);
    int workers = atoi(argv[4]);
    int flag = atoi(argv[3]);
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
    int div = contador / num_chunks;
    int resto = contador - (num_chunks * div);
    char restoS[3];
    snprintf(restoS, sizeof(restoS), "%d", resto);
    int contadores[2];
    contadores[0] = 0;
    contadores[1] = 0;
    pid_t worker_pid,wpid;
    int status=0;
    //genera n pipes para enviar la info con dupe
    int pipesEscritura[workers][2];
    int pipesLectura[workers][2];
    int ja;
    int i;
    for( i = 0; i<workers;i++){
        pipe(pipesEscritura[i]);
        pipe(pipesLectura[i]);
        //genera los n workers
        if((worker_pid = fork()) == 0) {
            close(pipesEscritura[i][1]);
            dup2(pipesEscritura[i][0], STDIN_FILENO);
            dup2(pipesLectura[i][1], 121);
            fflush(stdout);
            ja = execlp("./worker", "./worker", argv[3], argv[5], argv[4], restoS, NULL);
            if(ja==-1)
                printf("error de execlp\n");
            exit(0);
        }else
            close(pipesEscritura[i][0]);
    }
    //lee el txt (linea x linea)
    int * trabajadores = leerTXT(input,num_chunks,contador,pipesEscritura,workers);
    while((wpid=wait(&status))>0);
    int trabajador = trabajadores[0];
    
    int line = 0;
    
    escrituraArchivo(output, arreglo, &line, trabajadores[1], pipesLectura, trabajadores[0],num_chunks,contadores,flag);

    

  
    escrituraContadores(output, contadores, flag);

    for(int i = 0;i < contador;i++){
        free(arreglo[i]);
    }
    free(arreglo);

    return 0;
}