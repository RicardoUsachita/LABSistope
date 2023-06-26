#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fbroker.h"

//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers
//Salidas void
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este txt se almacena en un arreglo
int * leerTXT(char nombreArchivo[30], int num_chunks, int num_lineas, int fd[][2], int workers){
    FILE* fp;
    fp= fopen(nombreArchivo,"r");
    char string[60];
    int div = num_lineas/num_chunks;
    int resto = num_lineas - (num_chunks * div);
    //printf("div %s resto %s\n",div,resto);
    int i = 0;//contador de lineas
    int j = 0;//contador de workers
    int k = 0;//contador de chunks
    int m = 0;//
    int * resultado =(int*)malloc(sizeof(int)*2);
    while(fscanf(fp,"%s",string)==1){
        printf("contadores i %d, j %d, k %d, m %d\n",i,j,k,m);
        if(i >= (num_lineas - resto) && resto > 0){
            if(k < resto){
                printf("String en if k < resto lee txt %s \n",string);
                write(fd[j][1], string, sizeof(string));
                k++;
            
            }if(k == resto){
                j++;
                k=0;
            }
        }
        else if(j < workers){
            printf("String en while lee txt %s \n",string);
            if(k < num_chunks) {
                write(fd[j][1], string, sizeof(string));
                k++;

            }
            if(k == num_chunks){
                j++;
                k=0;
            }
            
        }
        if(j==workers && i<num_lineas){
            j=0;
            m++;
        }
        i++;
        
    }
    printf("contadores al terminar i %d, j %d, k %d, m %d\n",i,j,k,m);

    printf("Lineas leidas = %d div = %d resto = %d\n",i,div,resto);

    strncpy(string,"FIN",sizeof(char)*4);
    for(int i=0;i<=workers;i++){
        write(fd[i][1],string,sizeof(string));
    }
    fclose(fp);
    if(m>0){
        resultado[0] = workers;
        resultado[1] = resto;
        return resultado;
    }
    resultado[0] = j;
    resultado[1] = resto;
    return resultado;
}

//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
void escrituraArchivo(char* file,char** arreglo, int * linea, int resto, int fd[][2], int workers, int num_chunks,int contadores[2]){
    //int * respuestasHijo =(int *)malloc(sizeof(int)*num_chunks);
    //int * respuestasResto =(int *)malloc(sizeof(int)*resto);
    int respuestasHijo[num_chunks];
    int respuestasResto[resto];
    printf("workers %d\n", workers);
    for(int i = 0;i < workers;i++) {
        if(i == workers - 1 && resto != 0){
            read(fd[i][0], respuestasResto, sizeof(respuestasResto));
            for (int j = 0; j < resto; j++) {
                printf("Entre al Resto y tengo esto: %d\n", respuestasResto[j]);
                char respuesta[3];
                if (respuestasResto[j]) {
                    printf("Respuesta Resto %d\n", respuestasResto[j]);
                    strcpy(respuesta, "Si");
                    contadores[0] += 1;
                } else {
                    strcpy(respuesta, "No");
                    contadores[1] += 1;
                }
                FILE *output = fopen(file, "a");
                fprintf(output, "%s %s\n", arreglo[*linea], respuesta);

                fclose(output);
                *linea += 1;
            }
        }else {
            read(fd[i][0], respuestasHijo, sizeof(respuestasHijo));
            for (int j = 0; j < num_chunks; j++) {
                char respuesta[3];
                if (respuestasHijo[j]) {
                    strcpy(respuesta, "Si");
                    contadores[0] += 1;
                } else {
                    strcpy(respuesta, "No");
                    contadores[1] += 1;
                }

                FILE *output = fopen(file, "a");
                fprintf(output, "%s %s\n", arreglo[*linea], respuesta);

                fclose(output);
                *linea += 1;
            }
        }
    }
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

