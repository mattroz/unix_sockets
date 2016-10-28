#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
	/*	initialize addrinfo hints and result	*/
	struct addrinfo hints, *result;
	char *hostname, *port;
	int socket_fd, ai_status, connect_status;
	

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	
	if(argc != 3)
	{
		fprintf(stderr, "Usage: connect_to <hostname> <port>\n");
		exit(EXIT_FAILURE);
	}

	hostname = argv[1];
	port = argv[2];
	ai_status = getaddrinfo(hostname, port, &hints, &result);
	
	if(ai_status != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ai_status));
		exit(EXIT_FAILURE);
	}
	
	/*	get socket file descriptor with given addrinfo	specification	*/
	socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	fprintf(stdout, "socketfd: %d\n", socket_fd);

	/*	connect to host with given socket file desciptor and hostname	*/
	connect_status = connect(socket_fd, result->ai_addr, result->ai_addrlen);	
	if(connect_status != 0)
	{
		perror("connection error: ");
		exit(EXIT_FAILURE);
	}	
	fprintf(stdout, "connection established succesfully\n");	

	freeaddrinfo(result);	

	return 1;
}
