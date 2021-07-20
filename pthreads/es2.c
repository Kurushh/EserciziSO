#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5 

int x=-1;
int y=-1;

char c=' ';
const char alpha[]= "abcdefghilmnopqrstuvz!-+*/$%()1234567890?^|&";
const int na = strlen(alpha);

char matrix[N][N];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cmut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_cond_t cseek = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mseek = PTHREAD_MUTEX_INITIALIZER;

void iniz(){
	int i=0,j=0,k=0;
	srand(time(0));
	for(i=0; i<N;i++){
		for(j=0; j<N; j++){
			k = rand()%na;
			matrix[i][j]=alpha[k];
		}
	}
	i = rand()%N;
	j = rand()%N;
	printf("i=%d, j=%d\n",i,j);
	c = matrix[i][j];
	printf("c: %c\n",c);
	return;
};


void* seek(void * arg){
	int *ptr;
	ptr = (int *)arg;
	int i=*ptr;

	for(int j=0; j < N; j++){
		pthread_cond_wait(&cseek,&mseek); //signal is reading
		//note: a process can't write if he hasn't read first
		pthread_mutex_lock(&mutex); //mutual exclusion isn't a must here
		if (x != -1){
			pthread_cond_signal(&cseek);
			pthread_mutex_unlock(&mutex); //!!!
			pthread_exit(NULL);
		} 
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cseek); //signal ended reading

		printf("Thread %lu seeks: matrix[%d][%d] = %c\n",pthread_self(),i,j,matrix[i][j]);
		if ( matrix[i][j] == c ){
			pthread_mutex_lock(&mutex); //value found, write index into x and y
			x = i;
			y = j;
			pthread_mutex_unlock(&mutex); //end of critical section
			pthread_cond_signal(&cond); //signal parent thread that can proceeds
		}
	}
	pthread_exit(NULL);
}

int main(){
	iniz();
	pthread_t threads[N];
	int *taskids[N];

	for (int i=0; i < N; i++){
		taskids[i] = (int *)malloc(sizeof(int));
		*taskids[i] = i;
		pthread_create(&threads[i], NULL,seek, (void *)taskids[i]);
	};

	pthread_cond_signal(&cseek); //signal kids can seek
	pthread_cond_wait(&cond, &cmut);
	for (int i=0; i < N; i ++){
		pthread_cancel(threads[i]);
		free(taskids[i]);
	}
	if (x > -1){
		printf("Element found %c, at (%d,%d)\n",c,x,y);
		printf("Matrix[x][y] = %c\n",matrix[x][y]);
	}else{
		printf("Element not found\n");
	}


	exit(0);
}
