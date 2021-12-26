/**********   select.c   *************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

#define NTTYS   3
#define TIMEOUT 10

int fds[NTTYS];
char *filenames[NTTYS];

int openfiles(char **);
void readfiles(fd_set *);

int main(int argc, char **argv)
{
        fd_set readfds;
        int i, n, maxfd;
        struct timeval tv;

        if (argc != (NTTYS+1))
        {       fprintf(stderr, "You must supply %d tty names.\n", NTTYS);
                exit(1);
        }

        maxfd = openfiles(++argv);

        for (;;)
        {
                FD_ZERO(&readfds);
                for (i=0; i<NTTYS; i++)
		FD_SET(fds[i], &readfds);

                tv.tv_sec = TIMEOUT;
                tv.tv_usec = 0;

                n = select(maxfd+1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &tv);

                switch(n)
                {
                case -1 : perror("select");
                               exit(1);
                case 0  : printf("\nTimeout expired.  Type something\n");
                               break;
                default : readfiles(&readfds);
                               break;
                }
        }
}

int openfiles(char **files)
{
        int i, maxfd;

        maxfd=0;

        for (i=0; i<NTTYS; i++)
        {       if ((fds[i]=open(*files, O_RDONLY)) < 0)
                {       perror(*files);
                        exit(1);
                }

                if (!isatty(fds[i]))
                {       fprintf(stderr, "All files must be tty devices.\n");
                         exit(1);
                }

                filenames[i] = *files++;
                if (fds[i] > maxfd)
                        maxfd = fds[i];
        }
        return(maxfd);
}

void readfiles(fd_set *readfds)
{
        int i, n;
        char buf[BUFSIZ];

        for (i=0; i<NTTYS; i++)
        {
                if (FD_ISSET(fds[i], readfds))
                {       n =read(fds[i], buf, sizeof(buf));
                        buf[n]='\0';

                        printf("\n Read %d bytes from %s :", n, filenames[i]);
                        printf(" %s\n", buf);

                        if (!strncmp(buf, "E-N-D",  5))
                                exit(0);
                }
        }
}
