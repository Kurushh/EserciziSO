#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int glob=6;
int pid=1;
int i;
int main(){
       signal(SIGCHLD,SIG_IGN);
       int stato;
	pid = fork();
	glob--;
	fork();
	pid=0;
	glob--;
	if (pid){
		pid=fork();
		glob--;
	}
	if (!pid){
		for (i=1;i<2;i++){
		pid = fork();
		glob++;
		}
	}
printf("Sono il processo %d, figlio di %d. GLOB = %d\n",getpid(),getppid(),glob);
wait(&stato);
exit(0);
}
