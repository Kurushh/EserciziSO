#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int glob=5;
int pid = 0;
int main(){
       signal(SIGCHLD,SIG_IGN);
       int stato;
	pid = fork();
	glob--;
	fork();
	pid=1;
	glob--;
	if (!pid){
		pid=fork();
		glob--;
	}
	if (pid!=0)
		printf("PADRE.  Glob: %d\n\n",glob);
	if (pid==0)
		printf("FIGLIO.  Glob: %d\n\n",glob);
printf("Sono il processo %d, figlio di %d. GLOB = %d\n",getpid(),getppid(),glob);
wait(&stato);
exit(0);
}
