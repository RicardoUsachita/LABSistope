#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
int padre(char* linea,char* file,int fd[2],int fd2[2]){
    write(fd[1],linea,sizeof(linea));
    WAIT(NULL);
    int respuesta = escrituraArchivo(file,linea,fd2);
}
int escrituraArchivo(char* file,char* linea, int fd2[2]){

    int respuestaHijo;
    read(fd2[0],&respuestaHijo,sizeof(int));
    char* respuesta;
    if(respuestaHijo){
        respuesta = "Si";
    }else{
        respuesta = "No";
    }
    FILE* output = fopen(file,"w");
    fprintf(output,"%s %s\n", linea,respuesta);
    fclose(output);
    return respuestaHijo;
}

void escrituraContadores(char* file, int* contadores){
    int suma = contadores[0] + contadores[1];
    FILE* archivo = fopen(file,"w");
    fprintf(archivo,"\n Total de espresiones que si son regulares %d \n",contadores[0]);
    fprintf(archivo,"Total de espresiones que no son regulares %d \n",contadores[1]);
    fprintf(archivo,"Total de lineas leidas %d \n",suma);

    fclose(archivo);
}

void hijo(int fd[2],int fd2[2]){
    char buffer[60];
    close(fd[1]);
    close(fd2[0]);
    read(fd[0],buffer,sizeof(buffer));

    int respuesta = checkEtapa1(buffer,0);

    write(fd2[1],&respuesta,sizeof(int));
    
}

int checkEtapa1(char linea[60],int pos){
    int respuesta = 0;
    if(linea[pos]==NULL){
        return respuesta;
    }
    if(linea[pos]=='G'){
        return checkEtapa2(linea,pos+1);
        
    }else if (linea[pos] == 'A' || linea[pos] == 'C' || linea[pos] == 'T' ){
        return checkEtapa1(linea,pos+1);
    }
    return 0;
}

int checkEtapa2(char linea[60],int pos){
    int respuesta = 0;
    if(linea[pos]==NULL){
        return respuesta;
    }
    if(linea[pos]=='T'){
        //etapa3
    }else if(linea[pos]=='G'){

        return checkEtapa2(linea,pos+1);

    }else if (linea[pos] == 'A' || linea[pos] == 'C'){
        return checkEtapa1(linea,pos+1);
    }
    return 0;
}

int checkEtapa3(char linea[60],int pos){
    int respuesta = 0;
    if(linea[pos]==NULL){
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
    return 0;
}

int checkEtapa4(char linea[60],int pos){
    int respuesta = 1;
    if(linea[pos]==NULL){
        return respuesta;
    }
    if(linea[pos] == 'A' || linea[pos] == 'C' || linea[pos] == 'T' || linea[pos] == 'G' ){
        return checkEtapa4(linea,pos+1);
    }
    return 0;
}



