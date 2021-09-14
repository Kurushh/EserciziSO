
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char * argv[]){
	DIR *input; 
	struct dirent *content; 
	struct stat fd;
	char *absolute, *fname = NULL;
	int dirlen, filelen;
	off_t fsize= (off_t)99999999; //check 'man stat', st_size is an off_t-type
	mode_t mask;

	//check if input is ok
	if (argc < 2){
		perror("Usage: ex5 /path/to/directory\n");
		exit(1);
	}

	dirlen = strlen(argv[1]);

	//open dir
	input = opendir(argv[1]);
	if (input == NULL){
		perror("Error opening the directory\n");
		exit(2);
	}

	while ((content = readdir(input)) != NULL ){

		//Some C-style acrobatics to get the full pathname
		filelen = strlen(content->d_name);
		absolute = calloc(filelen+dirlen+1, sizeof(char *));
		strcpy(absolute, argv[1]);
		absolute[dirlen] = '/';
		strcpy(absolute+dirlen+1, content->d_name);

		if ( (stat(absolute, &fd) ) == 0){
			if( !(S_ISDIR(fd.st_mode) ) ){
				//Probably is more correct checking 
				//S_ISREG(fd.st_mode) too
				if ( fd.st_mode < fsize ){ 
					mask = fd.st_mode;
					if (fname != NULL)
						free(fname);
					fname = calloc(filelen, sizeof(char *));
					strcpy(fname, content->d_name);
				}
			}
		}
		free(absolute); //To avoid incorrect pathnames
	}

	//The permission mask is an octal
	//The bit a bit AND comparision is made to check which
	//"others" permission got the file
	printf("Result: %s \tother permission: ",fname);

	printf("%o\n", mask & S_IRWXO);
	//Explanation: let's say the file mask is 000644
	//S_IRWXO is 000007, since this is the octal format
	//The & operation at binary level looks something like:
	//Mask:   000110100100 &
	//S_IRWXO 000000000111 =
	//------------------------
	//	  000000000100 -> 4

	free(fname);

	
	exit(0);
}
