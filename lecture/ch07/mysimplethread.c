#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

int main(void)
{
	int status;
	pthread_t a_thread;
	void * thread_result;

	status = pthread_create(&a_thread, NULL, thread_function, (void *)NULL);
	if (status != 0)
	{	perror("pthread_create");
		exit(1);
	}

	status = pthread_join(a_thread, &thread_result);
	if (status != 0)
	{	perror("pthread_join");
		exit(1);
	}
	printf("Thread joined, it returned %s\n", (char *)thread_result);
	return 0;
}


void *thread_function(void *arg)
{
	printf("this is thread_function\n");
	sleep(2);
	pthread_exit("Good Bye from thread");
}

