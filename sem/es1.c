
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>


int main(int argc, char*argv[]){
	sem_t *fibo,*fact;
	pid_t child;
	int i,n=0;
	sem_unlink("fibo");
	sem_unlink("fact");
	
	fibo = sem_open("fibo",O_CREAT|O_EXCL,0666,1);
	fact = sem_open("fact",O_CREAT|O_EXCL,0666,0);

	//check input
	if (argc < 2 ){
		perror("Usage: ./ex1 n\n");
		exit(1);
	}
	n = atoi(argv[1]);

	child = fork();
	if (child == -1){
		perror("Error fork\n");
		exit(2);
	}else if (child != 0 ){ //parent
		int fnmeno2, fnmeno1, fn;
		fnmeno2 = 0;
		fnmeno1 = 1;
		for(int i=0; i<n; i++){
			sem_wait(fibo);
			fn = fnmeno2+fnmeno1;
			printf("Fibonacci(%d): %d\n",i,fn);
			fnmeno2 = fnmeno1;
			fnmeno1 = fn;
			sem_post(fact);

		}
	}else if (child == 0){ //son
		int k = 1;
		for(int i=0; i<n; i++){
			sem_wait(fact);
			k = 1*i;
			printf("Factorial(%d): %d\n",i,k);
			sem_post(fibo);
		}
	}

	sem_close(fibo);
	sem_close(fact);

}
