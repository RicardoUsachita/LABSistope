int padre(char* linea,char* file,int fd[2], int fd2[2]);
int escrituraArhivo(char* file, char* linea);

void escrituraContadores(char* file, int* contadores);

int hijo(int fd[2],int fd2[2]);

int checkEtapa1(char linea[60],int pos);

int checkEtapa2(char linea[60],int pos);
int checkEtapa3(char linea[60],int pos);
int checkEtapa4(char linea[60],int pos);


