#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sighandler(int);
int a=0,b=0;

int main(){
	while(1){
		a=0,b=0;
		fflush(stdin);
		printf("Inserisci due interi in input\n");
		if (scanf("%d%d",&a,&b) !=2 ){
			printf("Errore in input\n");
			fflush(stdin);
		}
		signal(SIGUSR1, sighandler);
		signal(SIGUSR2, sighandler);
		signal(SIGINT, sighandler);
		printf("In attesa di un segnale\n");
		pause();
	};
	exit(1);
}

static void sighandler(int signo){

		if(signo==SIGUSR1)
			printf("%d\n",a+b);
		else if ( signo==SIGUSR2 )
			printf("%d\n",a-b);
		else if(signo==SIGINT)
			exit(0);
		else
			return;
};
