#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
	struct sockaddr_in sa;
	struct sockaddr_in6 sa6;
	char ipv4[INET_ADDRSTRLEN];
	char src_ipv4[INET_ADDRSTRLEN] = "100.100.0.200";

	inet_pton(AF_INET, src_ipv4, &(sa.sin_addr));
	printf("pton: %u\n", sa.sin_addr.s_addr);

	inet_ntop(AF_INET, &(sa.sin_addr), ipv4, INET_ADDRSTRLEN);
	printf("ntop: %s\n", ipv4);
	printf("INET_ADDRSTRLEN: %u\n", INET_ADDRSTRLEN);
	
	return 0;
}
