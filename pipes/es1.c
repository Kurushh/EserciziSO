//Crea un programma che prende in input un valore
//crea un processo padre e figlio
//Il processo figlio incrementa una variabile di 5
//Il padre verifica se questa è maggiore 10 e stampa video qualcosa


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	pid_t ppid=0; //parent pid
	pid_t cpid=0; //child pid
	int pfd[2];
	int buf;

	if (pipe(pfd) == -1){ //anon pipe
		perror("Pipe error\n");
		exit(4);
	}

	if ( argc != 2){
		perror("Usage: prog #number\n");
		exit(1);
	}

	int a=0,x=0,b=0;
	if ( ( a = atoi(argv[1]) ) == 0 ){
		perror("Input error\n");
		exit(2);
	}
	b = a;
	a = fork();

	if (a == 0){ //child
		cpid = getpid();
		printf("Child %d\n",cpid);
		b = b + 5;
		close(pfd[0]); //child doesn't read 
		write(pfd[1], &b, sizeof(b));
		close(pfd[1]); //close the other side

	}else{ // parent
		close(pfd[1]); //parent doesn't write
		x = read(pfd[0], &b, sizeof(b));
		close(pfd[0]); //c t o s
		printf("Read %d bytes\n",x);
		ppid = getpid();
		printf("Parent %d\n",ppid);
		if (b>10)
			printf("b=%d > 10\n",b);
		else
			printf("b=%d <= 10\n",b);
	}
	exit(0);

}
