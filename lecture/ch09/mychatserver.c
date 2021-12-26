#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define MAXDATASIZE 256
#define BACKLOG 10
void process_request(int);

int main(int argc, char *argv[])
{
	int sockfd, new_fd, sin_size, yes = 1;
	struct sockaddr_in my_addr, their_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	perror("soket");
		exit(1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{	perror("setsockopt");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(30000);
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

	sin_size = sizeof(struct sockaddr_in);
	if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) < 0)
	{	perror("accept");
		exit(1);
	}
	printf("server : got connection from %s \n", inet_ntoa(their_addr.sin_addr));

	process_request(new_fd);
	close(new_fd);
	close(sockfd);
	return 0;
}


void process_request(int sockfd)
{
	fd_set mask, read_fds;
	int  n, i;
	char ch, buf[MAXDATASIZE];

   	FD_ZERO(&mask);
   	FD_ZERO(&read_fds);
   	FD_SET(0, &mask);
   	FD_SET(sockfd, &mask);
   
  	while(1)
   	{
		read_fds = mask;
  	 	select(sockfd+1, &read_fds, NULL, NULL, NULL);

	   	if(FD_ISSET(sockfd, &read_fds))
		{
			n=recv(sockfd, buf, MAXDATASIZE, 0);
			buf[n]='\0';
			if (!strcmp(buf, ""))
				break;
			printf("%s\n", buf);
		}
		else
		if (FD_ISSET(0, &read_fds))
		{
			i=0;
			do
			{
				read(0, &ch, 1);
				if (ch == '\n')
					buf[i] = '\0';
				else
					buf[i++] =ch;
			} while (ch != '\n');

			send(sockfd, buf, strlen(buf), 0);

			if (strncmp(buf, "quit", 4) == 0)
				break;
		}
		else
		{	printf("Unexpected event\n");
			break;
		}
	}
}
