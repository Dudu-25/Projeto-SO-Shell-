
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int getQntComandos(char comando[])
{
	int i,qntComandos=0;
	i=0;
	while(i!=strlen(comando)){
		if(comando[i]==','){
			qntComandos++;	
		}
		i++;
	}
	return qntComandos+1;
}

char* separarComandos(char comando[])
{
	int qntComandos=0,i,j;
	int *tamanhoComando;
	char **comandos;
	char diretorio[4096];
	char *argv[3];
	int pid;
	qntComandos=getQntComandos(comando); //a quantidade de comandos é iguala a quantidade de virgulas+1
	tamanhoComando = (int*)malloc((qntComandos)*sizeof(int));
	i=0;
	j=0;
	
	while(i!=strlen(comando)){
		if(comando[i]==','){
			tamanhoComando[j]=i;
			j++;	
		}
		i++;
	}
	
	tamanhoComando[j]=strlen(comando);
	comandos = (char*)malloc(qntComandos*sizeof(char));
	
	if(comandos==NULL){
		printf("algo deu errado!");
		exit(1);
	}
	for(i=0;i<qntComandos;i++){
		int a=0;
		comandos[i]=(char*)malloc((tamanhoComando[i]-a)*sizeof(char));
		a=tamanhoComando[i];
	}
	
	int posicao = 0,tamanho=0;
	
	for(i=0;i<qntComandos;i++){
		tamanho=tamanhoComando[i]-tamanho;
		for(j=0;j<tamanho;j++){
			comandos[i][j]=comando[posicao];
			posicao++;
		}
		comandos[i][tamanho]='\0';	
		posicao = tamanhoComando[i]+1;
		tamanho= tamanhoComando[i]+1;
	}
	for(i=0;i<qntComandos;i++){
		
		argv[0] = strtok(comandos[i], " ");
        argv[1] = strtok(NULL, " ");
        argv[2] = NULL;
        	
        if (strcmp(comandos[i],"") == 0){
        printf("comando invalido\n");
        }
        	
        else if (strcmp(argv[0], "pwd") == 0) {
            getcwd(diretorio, 4096);
            printf("%s\n", diretorio);
        }
        else if (strcmp(argv[0], "cd") == 0) {
            if (chdir(argv[1]) != 0) {
               	printf("Caminho invalido!\n");
            }
        }
    	else {
        	pid = fork();
        	if (pid == 0) {
           		if (execvp(argv[0], argv) == -1) {
              		printf("Comando invalido\n");
              		exit (0);
            	}
        	}
        	else {
           		wait();
        	}
    	}	
	}
	free(tamanhoComando);	
	for(i=0;i<qntComandos;i++){
		free(comandos[i]);
	}
	free(comandos);
	return 0;
}

int main(){
	
	char comando[512];
	printf("digite o comando\n");
	fgets(comando,511,stdin);
	comando[strlen(comando)-1]=0;
	while(strcmp(comando,"quit")!=0){
		separarComandos(comando);
		printf("digite o comando\n");
		fgets(comando,511,stdin);
		comando[strlen(comando)-1]=0;
	}
	return 0;
}
