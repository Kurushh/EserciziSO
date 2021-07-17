#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nbuff 2048

int main(int argc, char **argv){
	int fd_rd=0; 
	int fd_wrt=0; //file descriptors
	int c=0,d=0;
	char buf[nbuff];
	for(int i=1;i<argc;i++){
		printf("Arg[%d]: %s\n",i,argv[i]);
	}

	//Check there are enough arguments
	if (argc < 2){
		perror("Usage: $./prog file1 file2");
		exit(-1);
	};

	//Open the file to copy
	if ( (fd_rd = open(argv[1],O_RDONLY) )==-1 ){
		perror("Errore opening file to copy");
		exit(-2);
	}

	//Check if the target file exists, if not create it
	if ( (fd_wrt = open(argv[2], O_WRONLY) )== -1 ){
		perror("Error opening file to copy");
		exit(-3);
	}
	

	//Read the file then write the content into the other file
	while ( (c = read(fd_rd, &buf, nbuff)) > 0 ){
		printf("%s\n",buf);

		//Write (append) into the target file
		if ( (d =write(fd_wrt, &buf, c) != c) ){
			perror("Error opening target file");
			exit(-4);
		}; 
	};


	//Chiusura dei file
	close(fd_rd);
	close(fd_wrt);
	exit(0);
}

