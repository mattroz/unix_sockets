#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/*	initialize addrinfo hints and result	*/
	struct addrinfo hints, &result;
	char *hostname, *port;
	int socket_fd, ai_status;
	

	memset(&hints, 0, sizeof hints);
	
	if(argc != 3)
	{
		fprintf(stderr, "Usage: connect_to <hostname> <port>\n");
		exit(EXIT_FAILURE);
	}
	

	return 1;
}
