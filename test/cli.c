#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#define MYPORT  8886
#define BUFFER_SIZE 1024
 
int main()
{
	int sock_cli;
	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		///定义sockaddr_in
		struct sockaddr_in servaddr;
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(MYPORT);  ///服务器端口
		servaddr.sin_addr.s_addr = inet_addr("192.168.199.140");  ///服务器ip
 
		///定义sockfd
		sock_cli = socket(AF_INET,SOCK_STREAM, 0);
 
		///连接服务器，成功返回0，错误返回-1
		if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
			perror("connect");
			exit(1);
		}
 
	//	char key1[] = "key1\n";
		send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
		/*if(strcmp(sendbuf,"exit\n")==0)
			break;*/
		recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
		fputs(recvbuf, stdout);
 
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
		close(sock_cli);
	}

	return 0;
}
