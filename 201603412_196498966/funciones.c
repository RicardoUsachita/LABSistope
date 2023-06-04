#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"
// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: void
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
void validate(int argc, char * argv[], char input[], char output[], int * flag){
    int opt;
    while((opt = getopt(argc,argv,":i:o:b"))!= -1){
        switch (opt) {
            case 'i':
                strcpy(input,optarg);
                break;
            case 'o':
                strcpy(output,optarg);
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
}

//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
int escrituraArchivo(char* file,char* linea, int fd2[2]){

    int respuestaHijo;
    read(fd2[0],&respuestaHijo,sizeof(int));
    char* respuesta;
    if(respuestaHijo){
        respuesta = "Si";
    }else{
        respuesta = "No";
    }
    FILE* output = fopen(file,"a");
    fprintf(output,"%s %s\n", linea,respuesta);
    printf("%s %s\n", linea,respuesta);
    fclose(output);
    return respuestaHijo;
}
//Entradas: char* file que corresponde al nombre del archivo de salida, int* contadores que corresponde
//a un arreglo de enteros donde estan la cantidad de lineas que si son expresiones regulares y la cantidad
//de lineas que no son expresiones regulares.
//Salidas: ninguna, sin embargo, hace un print del total de expresiones regulares, no regulares y
//total de lineas leídas.
void escrituraContadores(char* file, int* contadores){
    int suma = contadores[0] + contadores[1];
    FILE* archivo = fopen(file,"a");
    fprintf(archivo,"\nTotal de expresiones que si son regulares %d \n",contadores[0]);
    fprintf(archivo,"Total de expresiones que no son regulares %d \n",contadores[1]);
    fprintf(archivo,"Total de lineas leídas %d \n",suma);
    printf("\nTotal de expresiones que si son regulares %d \n",contadores[0]);
    printf("Total de expresiones que no son regulares %d \n",contadores[1]);
    printf("Total de lineas leídas %d \n",suma);

    fclose(archivo);
}
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la primera etapa en donde si lee una G se va directo
//a la segunda etapa. Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa1(char linea[60],int pos){
    int respuesta = 0;
    if(pos == 59){
        return respuesta;
    }
    if(linea[pos]=='G'){
        return checkEtapa2(linea,pos+1);
        
    }else if (linea[pos] == 'A' || linea[pos] == 'C' || linea[pos] == 'T' ){
        return checkEtapa1(linea,pos+1);
    }
    else{
        return 0;}
}
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la segunda etapa en donde si lee una T se va directo
//a la tercera etapa, si lee una G se queda en esta etapa y si lee una A o una C vuelve a la primera etapa.
//Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa2(char linea[60],int pos){
    int respuesta = 0;
    if(pos == 59){
        return respuesta;
    }
    if(linea[pos]=='T'){
        return checkEtapa3(linea,pos+1);
    }else if(linea[pos]=='G'){

        return checkEtapa2(linea,pos+1);

    }else if (linea[pos] == 'A' || linea[pos] == 'C'){
        return checkEtapa1(linea,pos+1);
    }
    else{
        return 0;}
}
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la tercera etapa en donde si lee una C se va directo
//a la cuarta etapa, si lee una T se queda en esta etapa, si lee una G se devuelve a la etapa 2
//y si lee una A vuelve a la primera etapa. Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa3(char linea[60],int pos){
    int respuesta = 0;
    if(pos == 59){
        return respuesta;
    }
    if(linea[pos]=='C'){
        return checkEtapa4(linea,pos+1);
    }else if(linea[pos]=='T'){
        return checkEtapa3(linea,pos+1);
    }else if(linea[pos]=='G'){
        return checkEtapa2(linea,pos+1);
    }else if (linea[pos] == 'A'){
        return checkEtapa1(linea,pos+1);
    }
    else{
        return 0;}
}
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la cuarta etapa en donde si lee una A,C,T o G se qeda
//en la misma etapa y si llega al ultimo caracter retorna una respuesta, la cual es positiva.
int checkEtapa4(char linea[60],int pos){
    int respuesta = 1;
    if(pos == 59){
        return respuesta;
    }
    if(linea[pos] == 'A' || linea[pos] == 'C' || linea[pos] == 'T' || linea[pos] == 'G' ){
        return checkEtapa4(linea,pos+1);
    }
    else{
        return 0;
        }
}



