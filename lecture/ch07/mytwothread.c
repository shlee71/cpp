#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>

#define LOOP_MAX 20

int commonCounter = 0;

void *thread_function(void *);

int main(void)
{
	pthread_t tID_1;
	pthread_t tID_2;

	if (pthread_create(&tID_1, NULL, thread_function, NULL) ||
		pthread_create(&tID_2, NULL, thread_function, NULL)) 
	{ 	perror("pthread_create");
		exit(errno);
	}

	pthread_join(tID_1, (void **)NULL);
	pthread_join(tID_2, (void **)NULL);
}


void *thread_function(void *arg)
{
	int loopCount;
	int temp;
	char buffer[80];
	int i;

	for (loopCount=0; loopCount<LOOP_MAX; loopCount++)
	{	sprintf(buffer, "Common counter : from %d to ", commonCounter);
		write(1, buffer, strlen(buffer));

		temp = commonCounter;
		for (i=0; i<500000; i++);
		commonCounter = temp + 1;

		sprintf(buffer, "%d\n", commonCounter);
		write(1, buffer, strlen(buffer));

		for (i=0; i<500000; i++);
	}
}
	

