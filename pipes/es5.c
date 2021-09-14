/* Esercizio 2 15/05/2008
 Realizzare un programma che riceve 2 nm di file da riga di comando, e genera 1 proc figlio. 
 Il padre legge dal primo file e scrive quello ke legge in una pipe. il figlio legge dalla pipe
 e scrive quello ke legge nel secondo file.Il tutto termina quando il padre nn ha altra da
 leggere.il secondo file deve essere creato,se nn esiste,cn permessi di lett e scritt per il
 proprietario e per il gruppo.*/
//Nota usa pipe con nome 

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
			printf("%s\n",buffer);
//			rd = atoi(buffer);
			printf("%d \n",rd);
			write(pipe_descr, buffer, 1024);
			memset(buffer,0,1024);
		}
	}else if (res == 0){ //children
		char c = '\n';
		int t = 666;
		file2_descr = open(argv[2], O_WRONLY|O_APPEND);
		printf("file2_descr = %d\n",file2_descr);
		pipe_descr = open("pipe",O_RDONLY);
		while (read(pipe_descr, buffer, 1024) ){
			printf("t: %d\n",t);
			write(file2_descr, buffer,1024);
			memset(buffer,0,1024);
		}
	}

	exit(0);
	
}
