/***  mysem.c  ***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#define  DUMMY  0
#define  COUNT   5

union semun 
{	int val;  
	struct semid_ds *buf; 
	unsigned short int *array; 
};

main(int argc, char *argv[])
{
	key_t	ipckey;
	int   	semid, pid, creator, i;
	struct sembuf lock={0, -1, SEM_UNDO};
	struct sembuf unlock={0, 1, SEM_UNDO};
    //struct sembuf lock={0, -1, 0};
	//struct sembuf unlock={0, 1,  0};

	union semun arg;

	setbuf(stdout, (char *)NULL);
	ipckey=ftok(argv[0], 1);
	
	if ((semid=semget(ipckey, 1, IPC_CREAT|IPC_EXCL|0666)) != -1)
		creator=1;
	else
		if ((semid=semget(ipckey, 1, 0))==-1)
		{	perror("semget failed");
			exit(1);
		}
		else
			creator=0;

	if (creator)
	{	arg.val = 1;
		if (semctl(semid, 0, SETVAL, arg) == -1)
		{	perror("semctl SETVAL failed");
			exit(1);
		}
	}

	pid=getpid();
	for (i=0; i<COUNT; i++)
	{	if (semop(semid, &lock, 1) == -1)
		{	perror("semop lock failed");
			exit(1);
		}
		printf("\t[%d]locking\n", pid);
		sleep(2);
		printf("\t[%d]unlocking\n", pid);
		if (semop(semid, &unlock, 1) == -1)
		{	perror("semop unlocking failed");
			exit(1);
		}
		sleep(1);
	}

	if (creator)
	{	sleep(10);
		if (semctl(semid, DUMMY, IPC_RMID, DUMMY) == -1)
		{	perror("semctl IPC_RMID failed");
			exit(1);
		}
	}
} /* end of main */
