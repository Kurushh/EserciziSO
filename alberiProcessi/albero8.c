#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>


int glob=4;
int pid = 0;
int i;
int main(){
        signal(SIGCHLD,SIG_IGN);
        int stato;
	for (i=1;i<4;i++){
		if (pid==0){
			pid = fork();
                     
                         
}
		if (pid!=0){
			glob = glob*2;
                      
}
		glob = glob-1;
	}
	
printf ("figlio = %d, padre = %d, glob = %d \n", getpid(),getppid(), glob);
wait(&stato);
exit(0);
}
