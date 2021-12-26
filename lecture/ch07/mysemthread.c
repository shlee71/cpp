#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
sem_t semid;

char common_area[1024];

int main(void)
{
	int res;
	pthread_t t_id;
	void *thread_result;

	res = sem_init(&semid, 0, 0);
	if (res != 0)
	{	perror("sem_init");
		exit(1);
	}

	if (pthread_create(&t_id, NULL, thread_function, NULL) != 0)
	{	perror("pthread_create");
		exit(1);
	}

	while (strncmp("end", common_area, 3) != 0)
	{	sleep(1);
		printf("input> ");
		fgets(common_area, 1024, stdin);
		sem_post(&semid);
	}

	if (pthread_join(t_id, &thread_result)!= 0)
	{	perror("pthread_join");
		exit(1);
	}
	sem_destroy(&semid);
	exit(0);
}


void *thread_function(void *arg)
{
	sem_wait(&semid);
	while(strncmp("end", common_area, 3) != 0)
	{	printf("length :%d\n", strlen(common_area)-1);
		sem_wait(&semid);
	}
	pthread_exit(NULL);
}
