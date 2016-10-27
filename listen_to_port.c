#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_PORT "3490"

int main(int argc, char *argv[])
{
	int status;
	char *port;
	struct addrinfo hints;
	struct addrinfo *result_info;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: ./listen <port_number>\nPort set to %s\n", DEFAULT_PORT);
		port = DEFAULT_PORT;
	} 
	else
	{
		port = argv[1];
	}

	/*	fill source addrinfo struct with nils to make sure it's empty	*/
	memset(&hints, 0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC;	/*	can work with IPv4 and IPv6 now	*/
	hints.ai_socktype = SOCK_STREAM;	/*	use TCP stream sockets	*/
	hints.ai_flags = AI_PASSIVE;	/*	 assign the address of my host to the socket structures	*/

	/*	try to get linked list of addrinfo structures	*/
	if((status = getaddrinfo(NULL, port, &hints, &result_info)) != 0)
	{
		fprintf(stderr, "error: %s\n", gai_strerror(status));
		return -1;
	}
	else
	{
		fprintf(stdout, "addrinfo struct received succesfully\n");
	}

	/*
		some manipulations with addrinfo structs, if we got it
	*/
	
	freeaddrinfo(result_info);
	
	return 1;
}
