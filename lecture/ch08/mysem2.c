#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(int argc, char **argv)
{	void *shmaddr;
	struct shmid_ds shm_stat;
	int i, j;
	int shmid, semid;
	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	} sem_ctrl;
	struct sembuf sem_ops;

	if (argc != 2)
	{	fprintf(stderr, "Usage : mysem2 shmkey\n");
		exit(1);
	}

	printf("mysem2 is started ....\n");
	if ((shmid = shmget((key_t)atoi(argv[1]), 128, IPC_CREAT|0666)) == -1)
	{ 	perror("shmget failed !!");
		exit(1);
	}
	if ((semid=semget((key_t)1234, 1, IPC_CREAT|0666)) == -1)
	{
		perror("semget failed !!");
		exit(1);
	}

	if ((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
	{	perror("shmat failed !!");
		exit(1);
	}

	for (i=0; i<500; i++)
	{	sem_ops.sem_num = 0;
		sem_ops.sem_op = -1;	
		sem_ops.sem_flg = SEM_UNDO;
		semop(semid, &sem_ops, 1);
//		sleep(1);

		sprintf((char *)shmaddr, "%d", getpid());
		for (j=0; j<50000000; j++);
		if (getpid() == atoi(shmaddr))
			putchar('O');
		else
			putchar('X');
		fflush(stdout);
	 	sem_ops.sem_num = 0;
		sem_ops.sem_op = 1;	
		sem_ops.sem_flg = SEM_UNDO;
		semop(semid, &sem_ops, 1);
		sleep(1);
	}

	if (shmdt(shmaddr) == -1)
	{	perror("shmdt failed !!");
		exit(1);
	}
	exit(0);
} 
