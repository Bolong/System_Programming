#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void)
{
	int srv_fd, conn_fd, ret;
	int srv_len, cli_len;
	struct sockaddr_un srv_addr;
	struct sockaddr_un cli_addr;

	/*
	 * 这里实际上假设执行命名的标准输出不超出 4096 个字节
	 * unix 域套接字是可以直接传输文件描述符的, 算了...
	 */
	char cmd[1024], output[4096] = { };
	FILE *fp;

	/* Remove any old socket and create an unnamed socket for the server. */
	unlink("/tmp/server_socket");

	srv_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	/* Name the socket */
	srv_addr.sun_family = AF_LOCAL;
	strcpy(srv_addr.sun_path, "/tmp/server_socket");
	srv_len = sizeof(srv_addr);

	/* 
	 * bind 后创建 "/tmp/server_socket" UNIX 域套接字文件,
	 * ls -l /tmp 可以看到这个文件
	 */
	bind(srv_fd, (struct sockaddr *)&srv_addr, srv_len);

	/* Create a connection queue and wait for clients. */
	listen(srv_fd, 5);
	while (1)
	{
		/* accept a connection */
		conn_fd	= accept(srv_fd, (struct sockaddr *)&cli_addr, &cli_len);
		read(conn_fd, cmd, 1024);
		printf("the cmd is: %s\n", cmd);

		/* 如果客户端输入"quit" 可以结束服务器进程 */
		if (!strcmp("quit", cmd))
			break;

		fp = popen(cmd, "r");
		ret = fread(output, 1, 4096, fp);
		write(conn_fd, output, ret);
		pclose(fp);
	
		close(conn_fd);
	}

	close(srv_fd);

	return 0;
}
