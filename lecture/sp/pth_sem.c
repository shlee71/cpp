/*** pth_sem.c ***/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *pthread1(void *dummy)
{	printf("I'm pthread1. before sem_wait.  wait 1 second.\n");
	sleep(1);
	sem_wait(&sem);
	printf("Hello... I'm pthread1 in sem.\n");
	sleep(5);
	sem_post(&sem);
	printf("I release semaphore1\n");
}

void *pthread2(void *dummy)
{	printf("I'm pthread2. before sem_wait.  wait 2 seconds.\n");
	sleep(2);
	sem_wait(&sem);
	printf("Hello... I'm pthread2 in sem.\n");
	sleep(5);
	sem_post(&sem);
	printf("I release semaphore2\n");
}


void *pthread3(void *dummy)
{	printf("I'm pthread3. before sem_wait.  wait 3 seconds.\n");
	sleep(3);
	sem_wait(&sem);
	printf("Hello... I'm pthread3 in sem.\n");
	sleep(5);
	sem_post(&sem);
	printf("I release semaphore3\n");
}


int main()
{
	pthread_t tid1, tid2, tid3;

	sem_init(&sem, 0, 2);

	pthread_create(&tid1, NULL, pthread1, NULL);
	pthread_create(&tid2, NULL, pthread2, NULL);
	pthread_create(&tid3, NULL, pthread3, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	
	return 0;
}