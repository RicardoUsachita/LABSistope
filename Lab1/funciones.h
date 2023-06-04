// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: void
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
void validate(int argc, char * argv[], char input[], char output[], int * flag);
//Entradas: char* file que corresponde al nombre del archivo, char* linea que corresponde a la linea que
//se va a escribir, int fd2[2] es el pipe por el cual el padre lee.
//Salidas: 0 o 1, estas representan si es que la linea leida por el hijo es o no una expresión regular.
//Descripción: Función que lee la respuesta del hijo (si es que es o no expresión regular) y la escribe
//en el archivo salida.
int escrituraArchivo(char* file,char* linea, int fd2[2]);
//Entradas: char* file que corresponde al nombre del archivo de salida, int* contadores que corresponde
//a un arreglo de enteros donde estan la cantidad de lineas que si son expresiones regulares y la cantidad
//de lineas que no son expresiones regulares.
//Salidas: ninguna, sin embargo, hace un print del total de expresiones regulares, no regulares y
//total de lineas leídas.
void escrituraContadores(char* file, int* contadores);
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la primera etapa en donde si lee una G se va directo
//a la segunda etapa. Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa1(char linea[60],int pos);
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la segunda etapa en donde si lee una T se va directo
//a la tercera etapa, si lee una G se queda en esta etapa y si lee una A o una C vuelve a la primera etapa.
//Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa2(char linea[60],int pos);
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la tercera etapa en donde si lee una C se va directo
//a la cuarta etapa, si lee una T se queda en esta etapa, si lee una G se devuelve a la etapa 2
//y si lee una A vuelve a la primera etapa. Si llega al ultimo caracter retorna una respuesta, la cual es negativa.
int checkEtapa3(char linea[60],int pos);
//Entradas: char linea[60] corresponde a la linea que le entrega el padre al hijo, int pos corresponde a
//a la posición del string.
//Salidas: Es una función recursiva y sus salidas van a otras etapas que corroboran las letras del string
//entregado, ademas puedo retornar 0 o respuesta que es el final de la función.
//Descripción: Función recursiva que corresponde a la cuarta etapa en donde si lee una A,C,T o G se qeda
//en la misma etapa y si llega al ultimo caracter retorna una respuesta, la cual es positiva.
int checkEtapa4(char linea[60],int pos);

