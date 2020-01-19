/***  shmproduce.c  ***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define MSG_SIZE 30
#define MAX 10
int main(void)
{
	key_t key;
	struct sembuf wait_consumed = { 1, -1, 0};
	struct sembuf signal_produced = { 0, 1, 0};
	int semid, shmid;
	char *message;
	int i;

	if ((key=ftok(getenv("HOME"), 'u')) == -1)
	{	fprintf(stderr, "ftok key formation error\n");
		exit(1);
	}

	if ((semid=semget(key, 2, IPC_CREAT|0666)) < 0)
	{	perror("producer semget");
		exit(1);
	}

	if ((shmid=shmget(key, MSG_SIZE, IPC_CREAT|0666)) < 0)
	{	perror("producer shmget");
		exit(1);
	}

	message = shmat(shmid, 0, 0);

	for (i=1; i<MAX; i++)
	{	if (i>1)  semop(semid, &wait_consumed, 1);
		sprintf(message, "message %d", i);
		sleep(1);
		semop(semid, &signal_produced, 1);
	}

	shmdt(message);

	sleep(5);
	shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
	semctl(semid, 0, IPC_RMID, 0);
}
