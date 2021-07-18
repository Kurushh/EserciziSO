//Scrivere un programma C che:
//Prende in input coppie di interi utilizzando la system call read
//Calcola la somma degli interi
//Stampa a video il risultato utilizzando la write
//Termina quando il primo input è -1
//
//Assume che gli interi consistano di una sola cifra
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "apue.h"

#define nbuf (int)sizeof(char)*4
//Esempio di input "3 4", 
//"3 4" è una stringa composta da:
//3<-0,' '<-1,'4'<-2, \n <-3
//Quindi servono 4 byte per rappresentare questa stringa

int main(){
	char in[nbuf];
	char out[3];
	int a=0,b=0,c;

	while(a != -1 && b!= -1){

		//Pulisci standard input
		fflush(STDIN_FILENO);
		for(int i=0;i<nbuf;i++){
			in[nbuf]=(char)0; //Pulisci buffer di input
		}

		for(int i=0;i<3;i++){
			out[i]=(char)0;
		}
		

		if ( (c=read(STDIN_FILENO,&in,nbuf))==-1 ){
			perror("Errore lettura in input");
			exit(1);
		};	
		a=-2,b=-2;
		for(int i=0;i<nbuf;i++){
			c = atoi(&in[i]);
			if ( (a==-2) && (in[i] != (' ' && '-')  ) )
				a=atoi(&in[i]);
			else if ( (b==-2) && (in[i] != (' '&&'-') ) )
				b=atoi(&in[i]);
			
		};
		c = a+b;
		sprintf(out,"%d",c); //Funzione che converte la stringa ad intero
		
		
		if ( (c = write(STDOUT_FILENO, &out,sizeof(out))) != sizeof(out)){
			perror("Errore scrittura in output");
			exit(1);
		};  
		printf("\n");
	}
	exit(0);
}
