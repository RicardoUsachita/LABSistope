#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fbroker.h"

//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers.
//Salidas int *, entrega un arreglo de enteros correspondiente a la cantidad de workers totales que se hicieron uso y al resto.
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
        if(i >= (num_lineas - resto) && resto > 0){
            if(k < resto){
                
                write(fd[j][1], string, sizeof(string));
                k++;
            
            }if(k == resto){
                j++;
                k=0;
            }
        }
        else if(j < workers){
            
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

//Entradas: char* file que corresponde al nombre del archivo, char** arreglo que corresponde al arreglo en donde esta
// guardado el contenido del archiv, char* linea que corresponde a la linea que
//se va a escribir, int fd[][2] es el pipe por el cual el padre lee, int workers es la cantidad de hijos, int num_chunks
// es la cantidad de chunks a leer por el hijo, int contadores[2] contador que se encarga de contar las expresiones que son
// y que no son regulares y int flag que corresponde a la bandera para mostrar todo por pantalla.
//Salidas: void.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
void escrituraArchivo(char* file,char** arreglo, int * linea, int resto, int fd[][2], int workers, int num_chunks,int contadores[2],int flag){
    //int * respuestasHijo =(int *)malloc(sizeof(int)*num_chunks);
    //int * respuestasResto =(int *)malloc(sizeof(int)*resto);
    int respuestasHijo[num_chunks];
    int respuestasResto[resto];
    for(int i = 0;i < workers;i++) {
        if(i == workers - 1 && resto != 0){
            read(fd[i][0], respuestasResto, sizeof(respuestasResto));
            for (int j = 0; j < resto; j++) {
                
                char respuesta[3];
                if (respuestasResto[j]) {
                    
                    strcpy(respuesta, "Si");
                    contadores[0] += 1;
                } else {
                    strcpy(respuesta, "No");
                    contadores[1] += 1;
                }
                FILE *output = fopen(file, "a");
                fprintf(output, "%s %s\n", arreglo[*linea], respuesta);
                if(flag){
                    printf("%s %s\n",arreglo[*linea],respuesta);
                }

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
                if(flag){
                    printf("%s %s\n",arreglo[*linea],respuesta);
                }

                fclose(output);
                *linea += 1;
            }
        }
    }
}
//Entradas: char* file que corresponde al nombre del archivo de salida, int* contadores que corresponde
//a un arreglo de enteros donde estan la cantidad de lineas que si son expresiones regulares y la cantidad
//de lineas que no son expresiones regulares y int flag que corresponde a la bander que indica si hay o no que mostrar
// por pantalla.
//Salidas: ninguna, sin embargo, hace un print del total de expresiones regulares, no regulares y
//total de lineas leídas.
//Descripción: Función que guarda en el archivo el total de expresiones regulares, no regulares y
//total de lineas leídas y si corresponde los printea.
void escrituraContadores(char* file, int* contadores, int flag){
    int suma = contadores[0] + contadores[1];
    FILE* archivo = fopen(file,"a");
    fprintf(archivo,"\nTotal de expresiones que si son regulares %d \n",contadores[0]);
    fprintf(archivo,"Total de expresiones que no son regulares %d \n",contadores[1]);
    fprintf(archivo,"Total de lineas leídas %d \n",suma);
    if(flag) {
        printf("\nTotal de expresiones que si son regulares %d \n", contadores[0]);
        printf("Total de expresiones que no son regulares %d \n", contadores[1]);
        printf("Total de lineas leídas %d \n", suma);
    }
    fclose(archivo);
}

