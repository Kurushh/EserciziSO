//Scrivi un programma che prende in input una directory da riga di 
//comando e stampa in input il size di tutti i file al suo interno
//e scarta le directory


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
	DIR *dir;
	struct dirent *dd;
	char *path;
	struct stat buf;
	int pathsize = 0;
	int dirsize = 0;
	int filename = 0;

	if (argc < 2 ){
		printf("Inserire una directory in input\n");
		exit(1);
	}


	printf("%s\n",argv[1]);
	dirsize = strlen(argv[1]);

	if ( !(dir = opendir(argv[1]) ) ){
		printf("Err apertura directory\n");
	       	exit(2);
	}

	while ( (dd = readdir(dir)) ){
		pathsize = 0;
		if ( dd->d_type != DT_DIR ){
			printf("%s",dd->d_name);
			filename = strlen(dd->d_name);

			pathsize = filename + dirsize + 1;
			//plus one because we need to add a '/' before the filename
			path = calloc(pathsize, sizeof(char *));

			strcpy(path, argv[1]);
			path[dirsize]='/';
			strcpy(path+dirsize+1, dd->d_name);

			stat(path, &buf);
			printf(" %d\n",buf.st_size);

			memset(path, 0, pathsize);
			free(path);
		}
	}

	exit(0);
}
