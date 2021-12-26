/***  mutex.c  ***/

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *pthread1(void *dummy)
{	sleep(2);
	pthread_mutex_lock(&mutex);
	printf("Hello... I'm pthread1\n");
	sleep(2);
	pthread_mutex_unlock(&mutex);
	printf("Unlocked ...(1)\n");
}

void *pthread2(void *dummy)
{	sleep(1);
	pthread_mutex_lock(&mutex);
	printf("Hello... I'm pthread2. I'll reset 3 second.\n");
	sleep(3);
	pthread_mutex_unlock(&mutex);
	printf("Unlocked ...(2)\n");
}

int main()
{
	pthread_t tid1, tid2;
	
	pthread_create(&tid1, NULL, pthread1, NULL);
	pthread_create(&tid2, NULL, pthread2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

