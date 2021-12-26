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
#include <sys/wait.h>

#define BACKLOG  10

int main(void)
{
	int sockfd, new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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

	if (listen(sockfd, BACKLOG) == -1)
	{ 	perror("listen");
		exit(1);
	}

	while (1)
	{	sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{	perror("accept");
			continue;
		}

		printf("server : got connection from %s\n", inet_ntoa(their_addr.sin_addr));
	
		if (!fork())
		{	close(sockfd);
			if (send(new_fd, "Hello, world\n", 14, 0) == -1)
				perror("send");
			sleep(3600);
			close(new_fd);
			exit(0);
		}
		close(new_fd);

		while (waitpid(-1, NULL, WNOHANG) > 0);
	}
	return 0;
}
