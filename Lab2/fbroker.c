#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fbroker.h"

//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers
//Salidas void
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este txt se almacena en un arreglo
void leerTXT(char nombreArchivo[30], int num_chunks, int num_lineas, int fd[][2], int workers){
    FILE* fp;
    fp= fopen(nombreArchivo,"r");
    char string[150];
    int div = num_lineas/num_chunks;
    int resto = num_lineas - (num_chunks * div);
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    while(fgets(string,150,fp)!=NULL){
        if(i == (num_lineas - resto) && resto > 0){
            l = j;
            while(m < resto){
                write(fd[l][1], string, sizeof(string));
                i++;
                m++;
            }
        }
        while(j < workers){
            while(k < num_chunks) {
                write(fd[j][1], string, sizeof(string));
                i++;
                k++;
            }
            j++;
        }
        if(j == workers){
            j = 0;
        }
    }
    printf("Lineas leidas = %d\n",i);
    strcpy(string,"FIN");
    for(int i=0;i<=workers;i++){
        write(fd[i][1],string,sizeof(string));
    }
}

//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
int * escrituraArchivo(char* file,char** arreglo, int * linea, int * tamano, int fd[][2], int workers){
    int * respuestasHijo =(int *)malloc(sizeof(int)*1000);
    for(int i = 0;i < workers;i++) {
        read(fd[i][0], respuestasHijo, sizeof(respuestasHijo));
        int* ptr = respuestasHijo; // Puntero al primer elemento del arreglo
        while (*(ptr + 1) != '\0') {  // Avanza hasta el último elemento
            ptr++;
        }
        *tamano = *ptr;
        for(int i = 0;i < *tamano-1;i++) {
        char *respuesta;
        if (respuestasHijo[i]) {
            respuesta = "Si";
        } else {
            respuesta = "No";
        }
        FILE *output = fopen(file, "a");
        fprintf(output, "%s %s\n", arreglo[*linea], respuesta);
        printf("%s %s\n", arreglo[*linea], respuesta);
        fclose(output);
        *linea += 1;
        }
    }
    return respuestasHijo;
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

