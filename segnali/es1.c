//Scrivere un programma che intercetta CTRL-c
//ed invece di terminare 
//scrive su stdout "non voglio terminare"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//#include "apue.h"

static void handler(int);
int main(){
	int i=0;
	printf("Programma iniziato...\n");
	signal(SIGINT, handler);
	while( (i++) < 10){
		sleep(1);
	}
	printf("Programma finito\n");
	exit(0);
};

static void handler(int signo){
	if (signo==SIGINT){
		printf("\nNon voglio terminare\n");
	};
	return;
};
