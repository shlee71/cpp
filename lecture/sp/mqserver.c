/***  mqserver.c  ***/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSQKEY  	ftok("mqserver.c", 1)
#define MSQSIZE	32

struct mymsgbuf {
	long	mtype;
	char	mtext[MSQSIZE];
};

int main(void)
{
	key_t key;
	int n, msqid;
	struct mymsgbuf mb;

	key = MSQKEY;
	if ((msqid=msgget(key, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{	perror("msgget");
		exit(1);
	}

	while ((n=msgrcv(msqid, &mb, MSQSIZE, 0, 0))  > 0)
	{	if (mb.mtype == 1)
			write(1, mb.mtext, n);
		else
			if (mb.mtype == 2)
				break;
	}

	if (msgctl(msqid, IPC_RMID, (struct msqid_ds *)0) < 0)
	{	perror("msqctl");
		exit(1);
	}
	exit(0);
}
