//Si realizzi un programma in C e Posix sotto Linux che con l'ausilio della
//libreria pthread lancia m thread per calcolare il prodotto di due matrici
//di dimensione mxn e nxp.
//Non appena sarà calcolata la matrice prodotto, un m+1-esimo thread
//che era in attesa stampa la matrice risultato. Le matrici devono
//essere allocate dinamicamente. Usare i semafori con nome.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

struct matrix{
	int **ptr1;
	int **ptr2;
	int **ptr3;
} ma;

sem_t *accesso;
#define oflags O_CREAT|O_EXCL
#define semname "/samm"
#define filemod S_IRWXU|S_IRWXO|S_IRWXG 

int m,n,p;
int v;
void * fnc_thread(void *arg){
	int k = (int )arg;
	printf("Thread: %lu, input k: %d\n\n",pthread_self(), k);
	int i=0,j=0,pp=0,tmp1=0,tmp2=0;

	if (accesso > 0){
		sem_wait(accesso);

		for(i=0; i<p;i++){
			pp = 0;
			for(j=0;j<n;j++){
				tmp1 = ma.ptr1[k][j];
				tmp2 = ma.ptr2[j][i];
				pp =  pp +  tmp1*tmp2;
			}
			ma.ptr3[k][i] = pp;
		}
		sem_post(accesso);
	}else{
		printf("Error in thread\n");
	}
	printf("Thread: %lu, input k: %d completed!\n\n",pthread_self(), k);
	sem_wait(accesso);
	v++;
	sem_post(accesso);
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	v=0;
	int fd;
	sem_unlink(semname);
	accesso = sem_open(semname,oflags, filemod, 1);
	if (accesso == 0){
		perror("Error semaphore\n");
		exit(2);
	}

	if (argc != 4){
		printf("Usage: program #m #n #p\n");
		exit(1);
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	p = atoi(argv[3]);

	//Dynamic allocation of matrix 1, matrix 2 and matrix 3
	ma.ptr1 = (int **)calloc(sizeof(int), m);
	for (int i=0;i<m;i++){
		ma.ptr1[i] = (int *)calloc( sizeof(int), n);
	}


	ma.ptr2 = (int **)calloc(sizeof(int), n);
	for (int i=0;i<n;i++){
		ma.ptr2[i] = (int *)calloc( sizeof(int), p);
	}

	ma.ptr3 = (int **)calloc(sizeof(int), m);
	for(int i=0; i < m; i++){
		ma.ptr3[i] = (int *)calloc(sizeof(int), p);
	};

	for(int i=0; i<m; i++){
		for (int j=0; j<n; j++){
			ma.ptr1[i][j] = 1 + rand() % 10;
			printf("%d ",ma.ptr1[i][j]);
		}
		printf("\n");
	}
	printf("__________________\n");

	for(int i=0; i<n; i++){
		for (int j=0; j<p; j++){
			ma.ptr2[i][j] = 1 + rand() % 10;
			printf("%d ",ma.ptr2[i][j]);
		}
		printf("\n");
	}

	//Declaration and creation of pthreads
	pthread_t thread[m];
	int *index = (int *)calloc(sizeof(int),m);
	for(int i=0;i<m;i++){
		index[i]=i;
		pthread_create(&thread[m], NULL, fnc_thread, (void *)index[i]); 
	}
	do{
	sleep(1);
	}while(v != m);


	printf("Result: \n");
	for(int i=0; i<m;i++){
		for(int j=0; j<p; j++){
			printf("%d ",ma.ptr3[i][j]);
		}
		printf("\n");
	}


	exit(0);
}
