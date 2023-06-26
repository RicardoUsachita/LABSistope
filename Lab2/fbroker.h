//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers
//Salidas void
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este txt se almacena en un arreglo
int * leerTXT(char nombreArchivo[30], int num_chunks, int num_lineas, int fd[][2], int workers);
//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
void escrituraArchivo(char* file,char** arreglo, int * linea, int resto, int fd[][2], int workers, int num_chunks,int contadores[2]);
//Entradas: char* file que corresponde al nombre del archivo de salida, int* contadores que corresponde
//a un arreglo de enteros donde estan la cantidad de lineas que si son expresiones regulares y la cantidad
//de lineas que no son expresiones regulares.
//Salidas: ninguna, sin embargo, hace un print del total de expresiones regulares, no regulares y
//total de lineas leídas.
void escrituraContadores(char* file, int* contadores);
