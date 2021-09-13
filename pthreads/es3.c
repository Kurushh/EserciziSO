//Un lettore, uno scrittore, un buffer in C con POSIX

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

void *producer(void *arg);
void *consumer(void *arg);

struct {
	int N;
	pthread_t tid_c;
	pthread_t tid_p;
	sem_t *empty;
	sem_t *full;
	int buf;
} s;

int main(){
	srand(time(0));
	s.N = rand()%20+1;

	sem_unlink("empty");
	sem_unlink("full");
	s.empty = sem_open("empty", O_CREAT | O_EXCL, 666, 1);
	s.full = sem_open("full", O_CREAT | O_EXCL, 666, 0);

	pthread_create(&s.tid_p, NULL, producer, NULL);
	pthread_create(&s.tid_c, NULL, consumer, NULL);

	pthread_join(s.tid_p, NULL);
	pthread_join(s.tid_c, NULL);
	sem_close(s.empty);
	sem_close(s.full);
	sem_unlink("empty");
	sem_unlink("full");
	exit(0);
}

void *producer(void *arg){
	int off = s.tid_p;
	for(int i=0; i<s.N; i++){
		sem_wait(s.empty);
		s.buf = (off/2) + rand()%off;
		printf("Wrote: %d\n", s.buf);
		sem_post(s.full);
	}
}

void *consumer(void *arg){
	int off = s.tid_c;
	int read = -1;
	for (int i=0; i<s.N; i++){
		sem_wait(s.full);
		read = s.buf;
		printf("Read: %d\n", read);
		sem_post(s.empty);
	}
}
