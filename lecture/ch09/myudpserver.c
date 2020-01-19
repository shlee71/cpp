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

#define MAXBUFLEN 100

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int addr_len, numbytes;
	char buf[MAXBUFLEN];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(30000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(my_addr.sin_zero, 0, 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{	perror("bind");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	do 
	{	if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN-1, 0, 
				(struct sockaddr *)&their_addr, &addr_len)) == -1)
		{	perror("recvfrom");
			exit(1);
		}

		printf("\ngot packet from %s\n", inet_ntoa(their_addr.sin_addr));
		printf("packet is %d bytes long\n", numbytes);
		buf[numbytes] ='\0';
		printf("packet contains \"%s\"\n", buf);
	} while (strncmp(buf, "quit", 4));

	close(sockfd);
	return 0;
}
