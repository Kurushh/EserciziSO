
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[]){
	int rd,res,pipe_descr,file1_descr,file2_descr = 0;
	char buffer[1024];

	memset(buffer,0,1024);
	
	//Check for argc
	if (argc != 3){
		perror("Usage: ex5 file1 file2 \n");
		exit(1);
	}

	//Check if files exists
	if ( (access(argv[1], F_OK ) == -1) ){
		perror("Error file1 doesn't exists\n");
		exit(3);
	}

	//If file2 doesn't exists, create it
	if ( (access(argv[2], F_OK) == -1) ){
		creat(argv[2], 0666 );
		if (access (argv[2], F_OK) == -1 ){  
			perror("Can't create file2\n");
			exit(4);
		}
	}


	//Check if pipe is ok
	unlink("pipe");
	mkfifo("pipe",0666);


	//Create children process
	res = fork();
	if (res == -1){
		perror("Error creating a child\n");
		exit(2);
	}else if ( res != 0){ //parent
		int t = 777;
		file1_descr = open(argv[1], O_RDONLY);
		pipe_descr = open("pipe",O_WRONLY);
		
		while ( read(file1_descr, buffer, 1024) != 0 ){
			write(pipe_descr, buffer, 1024);
			memset(buffer,0,1024); //Clear buffer
		}
	}else if (res == 0){ //children
		file2_descr = open(argv[2], O_WRONLY|O_APPEND);
		pipe_descr = open("pipe",O_RDONLY);
		
		while (read(pipe_descr, buffer, 1024) ){
			write(file2_descr, buffer,1024);
			memset(buffer,0,1024); //Clear buffer
		}
	}

	exit(0);
	
}
