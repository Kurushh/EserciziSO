#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
signal(SIGCHLD,SIG_IGN);
int stato;
pid_t f1, f2, f3;
f1=fork();
f2=fork();
f3=fork();
printf("io sono: %i, mio padre è: %i\n ", getpid(),getppid());
wait(&stato);
return 0;
}