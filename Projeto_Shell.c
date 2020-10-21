#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int getQntComandos(char comando[]){
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

char* separarComandos(char comando[]){
	int qntComandos=0,i,j;
	int *tamanhoComando;
	char **comandos;

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
	
	comandos = (char**)malloc(qntComandos*sizeof(char*));
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
		printf("%s\n",comandos[i]);
	}
	
	return 0;
}

int main(){
	char comando[15];
	printf("digite o comando\n");
	gets(comando);
	while(strcmp(comando,"quit")!=0){
		separarComandos(comando);
		printf("digite o comando\n");
		gets(comando);
	}
}
