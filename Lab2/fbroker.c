#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fbroker.h"

//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers
//Salidas void
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este txt se almacena en un arreglo
int leerTXT(char nombreArchivo[30], int num_chunks, int num_lineas, int fd[][2], int workers){
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
    while(fscanf(fp,"%s",string)==1){
        printf("contadores i %d, j %d, k %d, m %d\n",i,j,k,m);
        if(i == (num_lineas - resto) && resto > 0){
            if(k < resto){
                write(fd[j][1], string, sizeof(string));
                k++;
            
            }else{
                k=0;
            }
        }
        if(j < workers){
            printf("String en while leet txt %s \n",string);
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
        return workers;
    }
    return j;
}

//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
void escrituraArchivo(char* file,char** arreglo, int * linea, int * tamano, int fd[][2], int workers, int num_chunks,int contadores[2]){
    int * respuestasHijo =(int *)malloc(sizeof(int)*num_chunks);
    for(int i = 0;i < workers;i++) {
        read(fd[i][0], respuestasHijo, sizeof(respuestasHijo));
        for(int p = 0; p < num_chunks;p++){
            printf("arreglo de respuestas p = %d respuesta = %d\n",p,respuestasHijo[p]);
        }
        
        
        //*tamano = respuestasHijo[num_chunks];
        //printf("tamano %d \n", *tamano);
        for(int i = 0;i < num_chunks;i++) {
            char respuesta[3];
            if (respuestasHijo[i]) {
                strcpy(respuesta,"Si");
                contadores[0]+=1;
            } else {
                strcpy(respuesta,"No");
                contadores[1]+=1;
            }

            FILE *output = fopen(file, "a");
            fprintf(output, "%s %s\n", arreglo[*linea], respuesta);

            fclose(output);
            *linea += 1;
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

