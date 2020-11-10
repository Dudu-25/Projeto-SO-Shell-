build: gcc msg
gcc: shell.c
	gcc -o exec shell.c
msg:
	@echo "digite ./exec para executar o programa"

