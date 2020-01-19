#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define MAXDATASIZE 256
void process_request(int);

int main(int argc, char *argv[])
{
	int  sockfd; 
	char name[20];
	struct hostent *he;
	struct sockaddr_in their_addr;

   	if(argc != 2)
	{
		fprintf(stderr, "usage : %s hostname \n", argv[0]);
		exit(1);
   	}

	if ((he=gethostbyname(argv[1])) == NULL)
	{	perror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(30000);
	their_addr.sin_addr = *(struct in_addr *)he->h_addr;
	memset(&(their_addr.sin_zero), '\0', 8);

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{	perror("connect");
		exit(1);
	}

	process_request(sockfd);
	close(sockfd);
	return 0;
}


void process_request(int sockfd)
{
	fd_set mask, read_fds;
	int n, i;
	char ch;
	char buf[MAXDATASIZE], buf1[MAXDATASIZE];
	char name[20];

	printf(" 이름 : ");
	fgets(name, 20, stdin);
	name[strlen(name)-1]='\0';

	FD_ZERO(&mask);
	FD_ZERO(&read_fds);
	FD_SET(sockfd, &mask);
	FD_SET(0, &mask);
	
	while(1)	
	{
		read_fds = mask;
		select(sockfd+1, &read_fds, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &read_fds))
		{
			n = recv(sockfd, buf, MAXDATASIZE-1, 0);
			buf[n] = '\0';
			if (!strcmp(buf, ""))
				break;
			printf("%s\n", buf);
		}
		else
		if(FD_ISSET(0, &read_fds))
		{
			i=0;
			do
			{
				read(0, &ch, 1);
				if (ch == '\n')
					buf[i]='\0';
				else
					buf[i++]=ch;
			} while (ch != '\n');

			sprintf(buf1, "[%s} %s", name, buf);
			send(sockfd, buf1, strlen(buf1), 0);

			if (strncmp(buf, "quit", 4) == 0)
				break;
		}
		else
		{
			printf("Unexpected event\n");
			break;
		}
	} /* while */
}
