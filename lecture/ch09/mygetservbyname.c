#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct servent *servent;

	if (argc != 3)
	{	fprintf(stderr, "Usage :mygetservbyname <servie_name> <tcp|udp>\n");
		exit(1);
	}

	if ((servent = getservbyname(argv[1], argv[2])) == NULL)
	{	fprintf(stderr, "서비스정보를 얻을 수 없음\n\n");
		exit(1);
	}

	printf("servie name : %s, port no : %d\n", servent->s_name , servent->s_port);
	printf("servie name ntohs: %s, port no : %d\n", servent->s_name , ntohs(servent->s_port));

	return 0;
}
