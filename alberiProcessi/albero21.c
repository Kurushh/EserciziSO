#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int glob=3;
int pid=0;
int i;
int main(){
       signal(SIGCHLD,SIG_IGN);
       int stato;
	pid = fork();
	glob--;
	fork();
	pid=1;
	if (pid){
		pid=fork();
		glob--;
	}
	if (!pid){
		glob++;
		}
	for (i=1;i<2;i++)
		pid = fork();
printf("Sono il processo %d, figlio di %d. GLOB = %d\n",getpid(),getppid(),glob);
wait(&stato);
exit(0);
}
