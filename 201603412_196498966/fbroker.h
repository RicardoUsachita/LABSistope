//Entradas Char* del nombre del archivo, int del numero de chunks, pipes, int de cant de workers
//Salidas int *, entrega un arreglo de enteros correspondiente a la cantidad de workers totales que se hicieron uso ya al resto
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este txt se almacena en un arreglo
int * leerTXT(char nombreArchivo[30], int num_chunks, int num_lineas, int fd[][2], int workers);
//Entradas: char* file que corresponde al nombre del archivo, char** arreglo que corresponde al arreglo en donde esta
// guardado el contenido del archiv, char* linea que corresponde a la linea que
//se va a escribir, int fd[][2] es el pipe por el cual el padre lee, int workers es la cantidad de hijos, int num_chunks
// es la cantidad de chunks a leer por el hijo, int contadores[2] contador que se encarga de contar las expresiones que son
// y que no son regulares y int flag que corresponde a la bandera para mostrar todo por pantalla.
//Salidas: void.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
void escrituraArchivo(char* file,char** arreglo, int * linea, int resto, int fd[][2], int workers, int num_chunks,int contadores[2],int flag);
//Entradas: char* file que corresponde al nombre del archivo de salida, int* contadores que corresponde
//a un arreglo de enteros donde estan la cantidad de lineas que si son expresiones regulares y la cantidad
//de lineas que no son expresiones regulares y int flag que corresponde a la bander que indica si hay o no que mostrar
// por pantalla.
//Salidas: ninguna, sin embargo, hace un print del total de expresiones regulares, no regulares y
//total de lineas leídas.
//Descripción: Función que guarda en el archivo el total de expresiones regulares, no regulares y
//total de lineas leídas y si corresponde los printea.
void escrituraContadores(char* file, int* contadores, int flag);
