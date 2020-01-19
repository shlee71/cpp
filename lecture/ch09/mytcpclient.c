#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;

	if (argc != 2)
	{	fprintf(stderr, "usage :client hostname\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL)
	{	fprintf(stderr, "gethostbyname() failed !!!\n");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(30000);
	their_addr.sin_addr = *(struct in_addr *)he->h_addr;
//  theri_addr.sin_addr.s_addr = *(unsigned long *)he->h_addr_list[0];
	memset(their_addr.sin_zero, 0, 8);

	printf("[%s]-[%d] \n", inet_ntoa(their_addr.sin_addr),sizeof(struct sockaddr));
	
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{	perror("connect");
		exit(1);
	}

	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
	{	perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("Received : %s", buf);
	sleep(3600);
	close(sockfd);
	return 0;
}
