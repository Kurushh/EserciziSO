#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main (int argc, char * argv[] ){
        pid_t childpid_1, childpid_2 = 0;
        int i,n;
        //______
        if (argc != 2) {
                fprintf( stderr, "Uso: %s processi\n", argv[0]);
                return 1;
        }
        n = atoi(argv[1]);

        for (i=0; i<n-1; i++){
                if ( ( childpid_2=fork() ) && ( childpid_1=fork() ) ) {
                        break;
                }
        }

        printf("i: %d processo ID:%d padre ID:%d figlio 1 ID:%d figlio 2 ID: %d\n",i,getpid(), getppid(), childpid_1, childpid_2);

}
