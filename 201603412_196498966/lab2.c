#include <unistd.h>
#include "funciones.c"


int main(int argc, char * argv[]) {
    char input[30] = "prueba_100.txt";
    char output[30] = "output.txt";
    char num_chunks[5] = "0";
    char flag[2] = "0";
    char workers[3];
    if(validate(argc,argv,input,output,flag,workers,num_chunks)){
        execlp("./broker","./broker", input,output,flag,workers,num_chunks,NULL);
        return 0;
    }
    return -1;
}