#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAXDATASIZE 128
#define BACKLOG  10

void *my_thread(void *new_fd)
{
	char buf[MAXDATASIZE];
	int conn_fd = (int)new_fd;
	int n;

	pthread_detach(pthread_self());

	while ((n=read(conn_fd, buf, MAXDATASIZE)) > 0)
		write(conn_fd, buf,n);

	close(conn_fd);
}


int main(int argc, char *argv[])
{
	pthread_t tid1;
	int sockfd, new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	struct servent *se;
	int sin_size;

	if (argc != 2)
	{
		fprintf(stderr, "Usage : %s servicename\n", argv[0]);
		exit(1);
	}

	if ((se=getservbyname(argv[1], "tcp")) == NULL)
	{	fprintf(stderr, "getservbyname() failed !!!\n");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = se->s_port;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(my_addr.sin_zero, 0, 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{	perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1)
	{ 	perror("listen");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);

	while(1)
	{	if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{	perror("accept");
			continue;
		}

		printf("server : got connection from %s \n", inet_ntoa(their_addr.sin_addr));
		pthread_create(&tid1, NULL, my_thread, (void *)new_fd);
	}
}

