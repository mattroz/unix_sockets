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

	/*	list IP addresses for given hostname	*/
	fprintf(stdout, "IP addresses for %s:\n", hostname);
	for(iter_addrinfo = result; iter_addrinfo != NULL; iter_addrinfo = iter_addrinfo->ai_next)
	{
		void *address;
		char *ip_version;
		
		if(iter_addrinfo->ai_family == AF_INET)	/*	if IPv4	*/
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)iter_addrinfo->ai_addr;
			address = &(ipv4->sin_addr);
			ip_version = "IPv4";
		}
		else	/*	if IPv6	*/
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)iter_addrinfo->ai_addr;
			address = &(ipv6->sin6_addr);
			ip_version = "IPv6";
		}
	
		/*	print in human-readable format addresses	*/
		inet_ntop(iter_addrinfo->ai_family, address, ip_in_str, sizeof ip_in_str);
		fprintf(stdout, "%s: %s\n", ip_version, ip_in_str);	
	}

	freeaddrinfo(result);

	return 1;
}
