Rômulo César de Freitas Monteiro - 3932
Victor Paiva de Castro - 5973
Eduardo Nunes de Oliveira - 6021


Exemplos de como utilizar:


Shell> ls -ll, pwd
Shell> grep foo arquivo.txt
Shell> cd diretório
Shell> touch teste
Shell> quit


Bugs conhecidos ou problemas  


* Caso ocorra da entrada ser “ ,,ls ” o programa entenderá que entre as vírgulas terá um comando, assim tratando que esse comando é um comando invalido.
Ex: Shell> ,,ls
comando invalido
comando invalido
saída do ls


* Após a entrada de comandos seguido de um quit, o programa irá executar todos os comandos que estiverem antes do quit, assim após a execução dos comandos o quit será executado e efetuando a saída do programa. Ex: Shell> ls, pwd, quit.


* Caso aconteça a entrada de um comando seguida de mais de um sub comando (Ex: ls -ll -la) somente o primeiro sub comando será executado (Ex: ls -ll).