#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_function(void *arg);
char greeting[80] = "Hello, thread !!";
int thread_endflag = 0;

int main(void)
{
	int status;
	pthread_t a_thread;
	void *thread_result;

	if (pthread_create(&a_thread, NULL, thread_function, (void *)NULL) != 0)
	{	perror("pthread_create");
		exit(1);
	}

	while (!thread_endflag)
	{	printf("Waiting for thread end \n");
		sleep(2);
	}
	printf("On Main, greeting : %s\n", greeting);
	return 0;
}

void *thread_function(void *arg)
{
	pthread_detach(pthread_self());
	printf("this is thread_function\n");
	printf("On Thread, greeting : %s\n", greeting);
	sleep(4);
	strcpy(greeting, "Hello Main!!");
	thread_endflag = 1;
	pthread_exit(NULL);
}

