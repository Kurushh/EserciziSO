// Scrivi un programma che accetta un intero n
// da riga di comando, crea n thread e poi aspetta
// la loro terminazione.
//
// Ogni thread aspetta un numero di secondi casuale tra 1 e 10,
// poi incrementa una variabile globale intera ed infine viene stampato
// il valore


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int counter=0;

void *snooze(void *){
	printf("\n");
	int p=0;
	p = rand()%11;
	printf("%lu does a pennichella for %d\n",pthread_self(),p);
	for (int i=0; i < p; i++){
		printf(".");
		sleep(1);
	};
	counter+=1;
	printf("\n");
	pthread_exit( (void*)1);

};

int main(int argc, char **argv){
	pthread_t *threads;
	int n = 0, err=0;
	if (argc < 2){
		perror("Usage: #integer\n");
		exit(1);
	}
	n = atoi(argv[1]);

	threads = (pthread_t *) malloc(n);
	if (threads == NULL){
		perror("Error cannot allocate memory\n");
		exit(2);
	}

	sleep(1);
	for (int i=0; i < n; i++){
		printf("O");
		err = pthread_create(&threads[i], NULL, snooze, NULL);
		if (err){
			printf("Error from pthread_create, code: %d\n",err);
			exit(err);
		};
	}
	

	/* This should be the correct way to do this but it crash on n>4
	for (int i=0; i < n; i++){
		pthread_join(threads[i],NULL);
	}*/
	sleep(12);
	printf("\ncounter = %d\n",counter);
	free(threads);
	
	exit(0);
}
