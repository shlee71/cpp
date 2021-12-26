/*** rwlock.c  ***/

#include <pthread.h>
#include <stdio.h>

pthread_rwlock_t rwlock;

void *pthread1(void *dummy)
{	sleep(2);
	pthread_rwlock_rdlock(&rwlock);
	printf("Hello... I'm pthread1\n");
	pthread_rwlock_unlock(&rwlock);
	printf("Unlocked ...(1)\n");
}

void *pthread2(void *dummy)
{	sleep(1);
	pthread_rwlock_rdlock(&rwlock);
	printf("Hello... I'm pthread2. I'll reset 3 second.\n");
	sleep(3);
	pthread_rwlock_unlock(&rwlock);
	printf("Unlocked ...(2)\n");
}

void *pthread3(void *dummy)
{	printf("I'm pthread3. before rwlock_wrlock. wait 3 seconds.\n");
	sleep(3);
	pthread_rwlock_wrlock(&rwlock);
	printf("Hello... I'm pthread3.\n");
	sleep(3);
	pthread_rwlock_unlock(&rwlock);
	printf("Unlocked ...(3)\n");
}


int main()
{
	pthread_t tid1, tid2, tid3;

	pthread_rwlock_init(&rwlock, NULL);
	
	pthread_create(&tid1, NULL, pthread1, NULL);
	pthread_create(&tid2, NULL, pthread2, NULL);
	pthread_create(&tid3, NULL, pthread3, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	return 0;
}