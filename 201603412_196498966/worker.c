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
    int num_workers = atoi(argv[3]);
    int resto = atoi(argv[4]);
    int out[num_chunks];
    int out2[resto];

    read(STDIN_FILENO,buffer, sizeof(char)*60);
    while (strcmp(buffer,"FIN")!=0) {
        fflush(stdout);
        //fflush(stdin);
        if(strcmp(buffer,"")!=0){
            int respuesta = checkEtapa1(buffer,0);
            out[lineas] = respuesta;
            lineas++;
        }
        read(STDIN_FILENO,buffer, sizeof(char)*60);
    }
    if(lineas == resto){
        for(int i = 0;i < resto;i++){
            out2[i] = out[i];
            
        }
        write(121, out2, sizeof(out2));

    }else {
        write(121, out, sizeof(out));
    }
    if(flag)
        printf("\nProceso %d = %d Lineas procesadas\n",getpid(),lineas);
    return 0;
}