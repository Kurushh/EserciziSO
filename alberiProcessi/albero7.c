#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


int glob=0;
int cocc=0;
int hug =0;
int main(){
        signal(SIGCHLD,SIG_IGN);
        int stato;
        int i=0;
        int pid = 0;
        glob++;
        cocc++;
	 pid= fork();
	 glob=cocc;
	 cocc=glob;
	 pid=fork();
        printf ("figlio = %d, padre = %d\n", getpid(),getppid());
        if (pid!=0){
		for (i=1;i<2;i++){
                        pid = fork();
                      
		}
		cocc=  glob+2*3;
	}
        else if (pid==0){
                for (i=2;i<=3;i++){
                        pid = fork();
                }
		if(pid!=0){
			hug=4;
			cocc=cocc*5;
		}
		glob=cocc-2*4;
        }
        hug=hug-3; 
wait(&stato);
printf ("figlio = %d, padre = %d, glob = %d \n", getpid(),getppid(), glob);
exit(0);

}




