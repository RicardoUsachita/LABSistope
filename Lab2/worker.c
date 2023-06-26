#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fworker.c"

int main(int argc, char * argv[]){
    char buffer[60];
    int lineas = 0;
    int flag = atoi(argv[1]);
    int num_chunks = atoi(argv[2]);
    int out[num_chunks];
    read(STDIN_FILENO,buffer, sizeof(char)*60);
    while (strcmp(buffer,"FIN")!=0) {
        printf("Print buffer %s\n", buffer);
        fflush(stdout);
        //fflush(stdin);
        if(strcmp(buffer,"")!=0){
            int respuesta = checkEtapa1(buffer,0);
            printf("Respuesta worker.c %d\n", respuesta);
            out[lineas] = respuesta;
            lineas++;
        }
        read(STDIN_FILENO,buffer, sizeof(char)*60);
        
    }
    //out[lineas] = lineas;
    write(121, out, sizeof(out));

    if(flag)
        printf("\nProceso %d = %d Lineas procesadas\n",getpid(),lineas);
    return 0;
}