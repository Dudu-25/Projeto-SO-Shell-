#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int getQntComandos(char comando[]){
	int qntVirgulas=0,i=0;
	
	//separando comandos por virgula
	while(i!=strlen(comando)){
		if(comando[i]==','){
			qntVirgulas++;	
		}
		i++;
	}
	
	return qntVirgulas+1;
}

char* separar_executar_Comandos(char comando[]){
	int qntComandos=0,i=0,j=0,posicao = 0,tamanhoComando=0,pid;
	int *posicaoFimComando;
	char diretorio[4096];
	char *argv[3],*argg[5];
	char **comandos;
	char *verificar[1];
	
	//a quantidade de comandos é igual a quantidade de virgulas+1
	qntComandos=getQntComandos(comando); 
	posicaoFimComando = (int*)malloc((qntComandos)*sizeof(int));
	
	//guardando posicao em que os comandos terminam
	while(i!=strlen(comando)){
		if(comando[i]==','){
			posicaoFimComando[j]=i;
			j++;	
		}
		i++;
	}	
	posicaoFimComando[j]=strlen(comando);
	
	comandos = (char**)malloc(qntComandos*sizeof(char*));
	if(comandos==NULL){
		printf("algo deu errado!");
		exit(1);
	}
	
	for(i=0;i<qntComandos;i++){
	comandos[i]=(char*)malloc((posicaoFimComando[i])*sizeof(char));
	}
	
	//preencher matriz de comandos
	for(i=0;i<qntComandos;i++){
		tamanhoComando=posicaoFimComando[i]-tamanhoComando;
		for(j=0;j<tamanhoComando;j++){
			//variavel posicao define a posicao do comando
			comandos[i][j]=comando[posicao];
			posicao++;
		}
		comandos[i][tamanhoComando]='\0';
		//'+1' significa que estamos pulando a posicao da virgula	
		posicao = posicaoFimComando[i]+1;
		//tamanhocomando agora recebe o tamanho total do comando, inclusive a virgula
		tamanhoComando= posicaoFimComando[i]+1;
	}
	
	//executar o shell
	for(i=0;i<qntComandos;i++){
		if (strcmp(comandos[i],"") == 0){
			printf("comando invalido\n");
		}
		else{
			argv[0] = strtok(comandos[i], " ");
			if(strcmp(argv[0],"quit") == 0){	
				return "quit";
			}
			else if(strcmp(argv[0], "grep") == 0) {
				argg[2] = strtok(NULL, " ");
				argg[3] = strtok(NULL, " ");
				argg[4] = NULL;
				argg[0] = "grep";
				argg[1] = "-n";
			}
			else{
				argv[1] = strtok(NULL, " ");
				argv[2] = NULL;
			}
			if(strcmp(argv[0], "grep") == 0) {
				pid = fork();
			    	if (pid == 0) {
		       		if (execvp(argg[0], argg) == -1) {
			  			printf("Comando invalido\n");
			  			exit (0);
					}
		    		}
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
			}
		}
        		
	}
	free(posicaoFimComando);	
	for(i=0;i<qntComandos;i++){
		free(comandos[i]);
	}
	free(comandos);
	return "continuar o shell";
}

int main(){
	char comando[512];
	strcpy(comando ,"");
	while(strcmp(comando,"quit")!=0){
		sleep(0.7);
		printf("Shell> ");
		fgets(comando,511,stdin);
		comando[strlen(comando)-1]=0;
		strcpy(comando ,separar_executar_Comandos(comando));
		//faz o programa esperar o termino da execucao da funçao acima
		sleep(0.7);
	}
	return 0;
}
