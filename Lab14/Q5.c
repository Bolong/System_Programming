/* Make the necessary includes and set up the variables. */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';

/* Create a socket for the client. */

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

/* Name the socket, as agreed with the server. */

	address.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.60.130", &address.sin_addr);
	len = sizeof(address);
	address.sin_port = htons(9734);

/* Now connect our socket to the server's socket. */
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1) {
		perror("oops: client1");
		exit(1);
	}

/* We can now read/write via sockfd. */

	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);
	close(sockfd);
	exit(0);
}
