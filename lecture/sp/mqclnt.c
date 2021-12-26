/***  mqclnt.c  ***/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
	if ((msqid=msgget(key, 0666)) < 0)
	{	perror("msgget");
		exit(1);
	}

	mb.mtype=1;
	while ((n=read(0, mb.mtext, MSQSIZE)) > 0)
	{	if (msgsnd(msqid, &mb, n, 0) < 0)
		{	perror("msgsnd");
			exit(1);
		}
	}

	mb.mtype=2;
	memset(mb.mtext, 0 , MSQSIZE);
	if (msgsnd(msqid, &mb, MSQSIZE, 0) < 0)
	{	perror("msgsnd");
		exit(1);
	}

	exit(0);
}
