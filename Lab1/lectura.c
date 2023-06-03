#include <stdlib.h>
#include <stdio.h>

#include <string.h>

int main(){
    FILE* file;
    file = fopen("prueba_10.txt","r");
    int contador = 0;
    int capacidad = 0;
    char ** arreglo = NULL;
    char buffer[60];
    while (fscanf(file, "%s", buffer) == 1){
        
        if (contador >= capacidad) {
            capacidad += 10;
            arreglo = realloc(arreglo, capacidad * sizeof(char*));
        }
        arreglo[contador] = strdup(buffer);
        printf("contador %d, string guardado %s\n",contador, arreglo[contador]);
        contador++;
            
    }
    fclose(file);
    for (int i = 0; i < contador; i++) {
        printf("%s\n", arreglo[i]);
    }

    // Liberar la memoria asignada
    for (int i = 0; i < contador; i++) {
        free(arreglo[i]);
    }
    free(arreglo);

    return 0;
}