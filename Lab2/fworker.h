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