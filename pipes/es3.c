#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd1[2];
	int fd2[2];
	int a=-2,b=-2;

	if ( argc != 2 ){
		perror("Usage: <pat>\n");
		exit(1);
	}

	if ( pipe(fd1) == -1){
		perror("Pipe1 error");
		exit(2);
	}

	if ( pipe(fd2) == -1){
		perror("Pipe2 error");
		exit(2);
	}

	a = fork();
	b = fork();

	if (a == 0 && b!=0){ //child A

		close(fd1[0]);
		dup2(fd1[1],1); //child A write to stdout
		close(fd1[1]);

		execlp("ls","ls",NULL);
		exit(3);
	}else { //parent
		close(fd1[1]); //doesn't write into fd1
		dup2(fd1[0],0); //cpy pipe 1 into stdin
		close(fd1[0]);
	}


	if (b == 0 && a!=0){
		close(fd2[1]);
		dup2(fd2[0],0);
		close(fd2[0]);
		execlp("grep","grep",argv[1], NULL);
		exit(1);
	}else {
		close(fd2[0]); //parent doesn't read here
		dup2(fd2[1],1); //parent write into stdout here
		close(fd2[1]);

		execlp("sort","sort",NULL);
		exit(2);

	}


	exit(0);
}
