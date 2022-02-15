#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int glob = 5;

int main ()
{        signal(SIGCHLD,SIG_IGN);
	pid_t pid;
	int i, stato;
	for (i = 1; i < glob; i ++)
	{
		pid = fork();
		if (pid == 0)
		{  
			glob = glob - 1;
               
		}
	}
       
	printf("processo %d, padre %d, glob %d, i %d\n", getpid(), getppid(), glob, i);
        wait(&stato);
	exit (0);
}
