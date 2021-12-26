#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAINERR 1
#define SHMSIZE 2048  

int myshmid ;
char *shmptr;

struct shmid_ds shmid_ds_buf;

main()
{
   // 644   group  other read auth.
    if ((myshmid = shmget(IPC_PRIVATE, SHMSIZE, 0644)) == -1) {
		perror ("shmget failed");
		exit (MAINERR);
    }
    else printf ("myshmid = %d \n", myshmid);

    if ((int) (shmptr = shmat (myshmid,0,0)) == -1) {
        perror("shmat failed");
		exit (MAINERR);
    }
    else printf("shmptr address = %x\n", shmptr);
  
    if (fork() == 0)
	{
		write_shm();
		exit(0);
	}

    sleep(1);
    read_shm();

    if (shmdt (shmptr) == -1) {
        perror ("shmdt failed");
		exit (MAINERR);
    }
/*
    if (shmctl (myshmid, IPC_RMID, 0) == -1) {
        perror ("shmctl IPC_RMID failed");
		exit (MAINERR);
    }
*/
    printf ("the end \n");
}

char *s = "my_test_string";
write_shm()
{
    printf("[CHILD]s => %s \n", s);
    strcpy (shmptr, s);
}

read_shm()
{
    printf("[PARENT] shmptr => %s\n",shmptr);
}
