#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <wait.h>

#define MAXDATASIZE 128
#define BACKLOG  10
void sighandler(int);

int main (int argc, char *argv[]) 
{ 
	int sockfd, newfd, sin_size;
	int yes = 1;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	struct servent *se;

	if(argc != 2)
	{
		fprintf(stderr, "usage : %s servicename\n", argv[0]);
		exit(1);
	}

	if ((se=getservbyname(argv[1], "tcp")) == NULL)
	{
		perror("getservbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{	perror("setsockopt");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = se->s_port;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(my_addr.sin_zero), '\0', 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{	perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1)
	{ 	perror("listen");
		exit(1);
	}


	init_daemon();

    	sin_size = sizeof(struct sockaddr_in);
	sigset(SIGCHLD, sighandler);

    	while (1) 
	{ 
        	if((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			perror("accept");
			continue;
		}

		if(fork() == 0)
		{
			close(sockfd);
			process_request(newfd);
    			close(newfd);
			exit(0);
		}
		close(newfd);

	} /* while */
}


init_daemon()
{
	if (fork() > 0)  exit(0);  /* parent */

	setsid();
	chdir("/");
	umask(0);
}


process_request(int connfd)
{
	time_t tloc;
	char buf[MAXDATASIZE];
	
	time(&tloc);
	strcpy(buf, ctime(&tloc));
	write(connfd, buf, strlen(buf));

}


void sighandler(int signo)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}
