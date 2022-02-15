#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int glob = 8;
int pid = 0;

int main ()
{        signal(SIGCHLD,SIG_IGN);
	int i, stato;
	for (i = 2; i <= glob; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob - 2;
		}
		glob --;
}
	

	printf("processo %d, padre %d, glob %d, i %d\n", getpid(), getppid(), glob, i);
        wait(&stato);
exit(0);
}
