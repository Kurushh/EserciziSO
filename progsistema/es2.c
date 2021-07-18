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
//es input: "3 4" (without "")
//3=0, ' '=1, 4=2, '\n'=3 aka the send
//sizeof(char)=8, 8*4=32

int main(){
	char in[nbuf];
	char out[3];
	int a=0,b=0,c;

	while(a != -1 && b!= -1){

		//Clear the buffer;
		fflush(STDIN_FILENO);
		for(int i=0;i<nbuf;i++){
			in[nbuf]=(char)0; //clear input buffer
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
		sprintf(out,"%d",c); //converts integer to string
		
		
		if ( (c = write(STDOUT_FILENO, &out,sizeof(out))) != sizeof(out)){
			perror("Errore scrittura in output");
			exit(1);
		};  
		printf("\n");
	}
	exit(0);
}
