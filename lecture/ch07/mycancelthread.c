#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

int main(void)
{
	int status;
	pthread_t a_thread;
	void *thread_result;
	
	status = pthread_create(&a_thread, NULL, thread_function, (void *)NULL);
	if (status != 0)
	{	perror("pthread_create");
		exit(1);
	}
	sleep(3);
	printf("pthread_cancel() called\n");
	if (pthread_cancel(a_thread) != 0)
	{	perror("pthread_cancel");
		exit(1);
	}

	status = pthread_join(a_thread, &thread_result);
	if (status != 0)
	{ 	perror("pthread_join");
		exit(1);
	}
	return 0;
}


void *thread_function(void *arg)
{
	int i;

	printf("this is thread_function \n");
	/*
	if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0)
	{	perror("pthread_setcancelstate");
		exit(1);
	}

	*/
	printf("I'm thread, Running ....\n");
	sleep(10);
	printf("thread_function ended\n");
	pthread_exit(NULL);
}
