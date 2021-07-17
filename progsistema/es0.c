//Crea un programma C che legge con la system call read 
//4000 bytes da un file li stampa in output con fprintf

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NBUFF 4000

int main(){
	int fd; //file descripto
	char buf[NBUFF];

	if ( (fd = open("file0.txt",O_RDONLY) )== -1 ){
		perror("Errore apertura file");
		exit(-1);
	}

	if (read(fd, &buf, NBUFF-1) == -1 ){
		perror("Errore lettura file");
		exit(-2);
	}
	fprintf(stdout,"%s",buf);

	
	exit(0);
}
