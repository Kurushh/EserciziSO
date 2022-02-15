#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int main ()

{       signal(SIGCHLD,SIG_IGN);
        int stato;
	int glob = 5;
	int pid = 0;
	glob --;

	if (pid != 0)
	{
		pid = fork();
		glob --;
         
	}
        
	printf ("Process %d, padre %d , valore di glob = %d\n", getpid(),getppid(), glob);
        wait(&stato);
	exit (0);
}
