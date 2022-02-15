#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int glob=4;
int pid=0;
int temp, i;

int main(){
        signal(SIGCHLD,SIG_IGN);
        int stato;
	for (i=0;i<=2;i++){
		pid = fork();
		glob++;
	}
	if (glob>5){
		glob++;
		if (pid==0){
			pid=fork();
		}
		if (pid!=0){
			pid = fork();
			glob--;
		}
		if (pid==0){
			pid = fork();
			glob--;
		}
		if (pid!=0){
			temp=12;
			glob++;
			temp = glob;
			glob--;
               
		}
	}
	wait(&stato);
	printf ("figlio %d, padre %d ,glob = %d, temp = %d, i = %d\n", getpid(),getppid(), glob, temp, i);
exit(0);
}

