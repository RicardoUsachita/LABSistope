#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

// Entradas: entra un char*
// Salidas: un int 0 o 1
// Descripción: verifica que el string de entrada este conformado solo por digitos
int digitValidate(char * string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) {
            if ('.' == string[i]) {
                continue;
            } else
                return 0;
        }
    }
    return 1;
}
// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: 0 o 1
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
int validate(int argc, char * argv[], char input[], char output[], char flag[], char workers[], char num_chunks[]){
    int opt;
    while((opt = getopt(argc,argv,":i:o:c:n:b"))!= -1){
        switch (opt) {
            case 'i':
                strcpy(input,optarg);
                break;
            case 'o':
                strcpy(output,optarg);
                break;
            case 'c':
                if(digitValidate(optarg)) {
                    strcpy(num_chunks, optarg);
                }
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'n':
                if(digitValidate(optarg))
                    strcpy(workers,optarg);
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'b':
                *flag = 1;
                break;
            case '?':
                printf("Case ?\n");
                printf("Unknown option: %c\n",optopt);
                break;
            case ':':
                printf("Case :\n");
                printf("Missing arg for %c\n",optopt);
                break;
        }
    }
    return 1;
}