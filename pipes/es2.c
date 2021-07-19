//Scrivere un programma che esegue il comando
//di shell "ls -R | grep <pat>" dove <pat> è
//un pattern inserito dall'utente

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int fd[2];

	if ( argc != 2 ){
		perror("Usage: <pat>\n");
		exit(1);
	}

	if ( pipe(fd) == -1){
		perror("Pipe error");
		exit(2);
	}


	if (fork() > 0 ){ //parent
		close(fd[1]);
		dup2(fd[0],0); //cpy pipe-read-side on stdin
		close(fd[1]);

		execlp("grep","grep", argv[1], NULL);
	}else{ // child
		close(fd[0]); //child doesn't read
		dup2(fd[1],1); //cpy pipe-write-side on stdout
		close(fd[0]);

		execlp("ls","ls","-R", NULL);
	}

	exit(0);
};
