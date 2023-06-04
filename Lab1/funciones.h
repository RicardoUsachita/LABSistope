void validate(int argc, char * argv[], char input[], char output[], int * flag);
int escrituraArchivo(char* file,char* linea, int fd2[2]);
void escrituraContadores(char* file, int* contadores);
int checkEtapa1(char linea[60],int pos);
int checkEtapa2(char linea[60],int pos);
int checkEtapa3(char linea[60],int pos);
int checkEtapa4(char linea[60],int pos);

