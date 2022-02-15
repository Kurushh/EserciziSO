#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int glob = 5;
int pid = 0;

int main ()
{       int stato;
	int i = 0;
        signal(SIGCHLD,SIG_IGN);
        printf(" radice %d\n", getpid());
	for (i = 1; i < 3; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob * 2;
			sleep (i + 1);
		}
		
		glob = glob + 1;
	}
        wait(&stato);
	printf (" figlio %d, padre %d, glob %d\n\n ", getpid(), getppid(), glob);

	exit (0);
}
