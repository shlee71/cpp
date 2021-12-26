#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char *argv[])
{	struct hostent *host;
	struct in_addr inaddr;
	int i;
	unsigned char myaddr[4];
	char *buf;

	if (argc < 2)
	{	printf("Usage : %s hostname\n", argv[0]);
		exit(1);
	}

	host = gethostbyname(argv[1]);
	if (host == NULL)
	{	printf("gethostbyname fail\n");
		exit(0);
	}
	printf("size of host->s_addr [%d]", sizeof(int));
	printf("호스트명 : %s\n", host->h_name);
	printf("호스트주소타입번호 : %d\n", host->h_addrtype);
	printf("호스트주소의길이 : %d 바이트\n", host->h_length);
	for (i=0; host->h_addr_list[i]; i++)
	{
		printf("IP주소(%d번째) : %s\n", i+1, 
			inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
		memcpy(myaddr+0,host->h_addr_list[i],1);
		memcpy(myaddr+1,host->h_addr_list[i]+1,1);
        memcpy(myaddr+2,host->h_addr_list[i]+2,1);
		memcpy(myaddr+3,host->h_addr_list[i]+3,1);

        printf("Before IP Change HEX [%2X,%2X,%2X,%2X]\n",myaddr[0],myaddr[1],myaddr[2],myaddr[3]);
		printf("Before IP Change ADR [%x]\n", (struct in_addr *)host->h_addr_list[i]);
    }
	for (i=0; host->h_aliases[i]; i++)
		printf("호스트별명(%d번째) : %s\n", i+1, host->h_aliases[i]);
	return 0;
}

