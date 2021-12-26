#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	int sockfd;
	struct hostent *he;
	struct servent *se;
	struct sockaddr_in their_addr;
	int numbytes;
	char buf[80];

	if (argc != 2)
	{	fprintf(stderr, "usage : myudpclient hostname\n");
		exit(1);
	}

	if ((he = gethostbyname(argv[1])) == NULL)
	{	fprintf(stderr, "gethostbyname() failed !!!\n");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(30000);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero, 0, 8);

	do
	{
		printf("\nsend string? ");
		fgets(buf, 79, stdin);
		if ((numbytes = sendto(sockfd, buf, strlen(buf)-1, 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
		{	perror("sendto");
			exit(1);
		}

		printf("sent %d bytes to %s\n", 
			numbytes, inet_ntoa(their_addr.sin_addr));
	} while (strncmp(buf, "quit", 4));

	close(sockfd);
	return 0;
}
