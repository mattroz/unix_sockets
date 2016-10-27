#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int status;
	char *hostname;
	struct addrinfo hints, *result, *iter_addrinfo;
	char ip_in_str[INET6_ADDRSTRLEN];
	
	if(argc != 2)
	{
		fprintf(stderr, "Usage: showip <hostname>\n");
		return 1;
	}

	/*	initializing section	*/
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hostname = argv[1];
	
	status = getaddrinfo(hostname, NULL, &hints, &result);
	if(status != 0)
	{
		fprintf(stderr, "Error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stdout, "Connection established, hostname: %s\n", hostname);
	}
	
	
	freeaddrinfo(result);

	return 1;
}
