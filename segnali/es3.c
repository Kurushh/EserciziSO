/*
Si realizzi un programma in C sotto Linux che preso un intero N come parametro da 
riga di comando compreso tra 1 e 100, 
genera due figli che si comportano come segue:

Se il parametro N è pari, il programma invia il segnale SIGUSR1 al figlio f1 
che calcola la somma tra il valore del suo PID e quello del processo padre. 
Il processo f2 stamperà solo il suo PID

Se il parametro N è dispari, il programma invia SIGUSR2 al figlio 2 che calcola 
la differenza tra il valore del PID del processo padre e il suo PID. 
Il processo f1 stamperà solo il suo PID.

Alla fine, il processo principale calcolerà e stamperà il prodotto dei PID dei due processi figli f1 e f2 e terminetà stampando un messaggio di saluto.
 
  */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


static void handler_f1(int);
static void handler_f2(int);

int main(int argc, char * argv[]){
	pid_t f1,f2 = 0;
	int n = 0;
	if (argc == 1){
		printf("Err\n");
		exit(1);
	}

	n = atoi(argv[1]);
	if ( n < 0 || n > 100 ){
		printf("N deve essere compreso tra 0 e 100 inclusi\n");
		exit(2);
	}

	f1 = fork();
	f2 = fork();

	//p 
	//|\
	//f1 f2 -- f1 
	//|    
	//f2    
	//Ci sono 5 processi escludendo quelli identici f1 e f2 con pid == 0
	//Ci sarebbero 7 processi in tutto, poiché il padre ne crea due
	//e ogni figlio ne crea due, ma uno di ognuno è identico a se stesso

	if ( f1 == 0 && f2 != 0 ){ 
		//f1 == 0 significa che è il figlio, f2!=0 x evitare duplicati 
		signal(SIGUSR1, handler_f1);
		signal(SIGUSR2, handler_f1);
		pause();
	}else if (f2 == 0 && f1 != 0){
		signal(SIGUSR1, handler_f2);
		signal(SIGUSR2, handler_f2);
		pause();
	}else if (f2 != 0 && f1 != 0){
		//f2 e f1 diverso da zero quindi il padre originale-radice
		printf("Sono il padre di entrambi: %d\n", (int) getpid() );
		sleep(1);
		if (n%2 == 0){ //pari 
			kill(f1,SIGUSR1);
			kill(f2,SIGUSR1);
		}else{ //dispari
			kill(f2,SIGUSR2);
			kill(f1,SIGUSR2);
		}
		sleep(1);
		printf("Prodotto del pid dei miei figli: %ld\n",(int)(f1*f2));
		printf("Arrivederci\n");
	}

	exit(0);
}

static void handler_f1(int signo){
	int x=0;
	if (signo == SIGUSR1){
		x = (int)getpid() + (int)getppid();
		printf("Somma tra mio pid e pid di mio padre: %d\n",x);
	}else if(signo == SIGUSR2){
		printf("Sono il figlio 1: %d\n", (int)getpid() );
	}
}

static void handler_f2(int signo){
	int x=0;
	if (signo == SIGUSR2){
		x = (int)getppid() - (int)getpid();
		printf("Differenza tra il pid di mio padre e il mio: %d\n",x);
	}else{
		printf("Sono il figlio 2: %d\n", (int)getpid() );
	}
	return;
}
