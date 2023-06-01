int padre(char* linea,char* file,int fd[2], int fd2[2]);
int escrituraArchivo(char* file,char* linea, int fd2[2]);

void escrituraContadores(char* file, int* contadores);

void hijo(int fd[2],int fd2[2]);

int checkEtapa1(char linea[60],int pos);

int checkEtapa2(char linea[60],int pos);
int checkEtapa3(char linea[60],int pos);
int checkEtapa4(char linea[60],int pos);

