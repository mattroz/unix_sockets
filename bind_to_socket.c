#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_PORT "3490"

int main(int argc, char *argv[])
{
	struct addrinfo hints, *result;
	int socket_fd;
	char *port;
	
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof hints);
	port = argv[1];
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	/*	set filter for needed socket address	*/
	getaddrinfo(NULL, port, &hints, &result);
	
	/*	get socket file descriptor	*/
	socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);	
	
	/*	bind socket to specified port	*/
	bind(socket_fd, result->ai_addr, result->ai_addrlen);

	return 1;
}
