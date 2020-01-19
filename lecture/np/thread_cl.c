#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
	int  sockfd, n; 
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct servent *se;
	struct sockaddr_in their_addr;

	if(argc != 3)
	{	fprintf(stderr, "usage : %s hostname servicename\n", argv[0]);
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL)
	{	fprintf(stderr, "gethostbyname() failed !!!\n");
		exit(1);
	}

	if ((se=getservbyname(argv[2], "tcp")) == NULL)
	{	fprintf(stderr, "getservbyname() failed !!!\n");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = se->s_port;
	their_addr.sin_addr = *(struct in_addr *)he->h_addr;
	memset(their_addr.sin_zero, 0, 8);

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{	perror("connect");
		exit(1);
	}


	while ((n=read(0, buf, MAXDATASIZE)) > 0)
	{	write(sockfd, buf,n);
		n = read(sockfd, buf, MAXDATASIZE);
		write(1, buf, n);
	}

	close(sockfd);
}
