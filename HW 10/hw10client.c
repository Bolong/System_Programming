#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define my_fgets(buf, size)		do {            \
			fgets(buf, size, stdin);            \
			if (buf[strlen(buf) - 1] == '\n')   \
				buf[strlen(buf) - 1] = '\0';    \
			else                                \
			{                                   \
				while (getchar() != '\n')       \
					;                           \
			}                                   \
	} while (0)

int main(void)
{
	int sockfd;
	int len;
	struct sockaddr_un addr;
	int ret, cmd_len;
	char cmd[1024], output[4096];

	/* Create a socket for the client. */
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

	/* Name the socket, as agreed with the server. */
	addr.sun_family = AF_LOCAL;
	strcpy(addr.sun_path, "/tmp/server_socket");
	len = sizeof(addr);

	/* Now connect our socket to the server's socket. */
	ret = connect(sockfd, (struct sockaddr *)&addr, len);
	if (-1 == ret)
	{
		perror("oops: client1");	
		exit(1);
	}

	printf("pls input an command u want(the server will execute it): ");
	my_fgets(cmd, 1024);
	cmd_len = strlen(cmd);

	/* We can now read / write via sockfd */
	write(sockfd, cmd, cmd_len + 1);

	/* wait the response from server */
	read(sockfd, output, sizeof(output));
	printf("The command output is:\n");
	puts(output);

	close(sockfd);

	return 0;
}
