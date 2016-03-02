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
#include <time.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <errno.h>


char ip[254];
char acc[100000][30];
int main()
{
	get_ip_addr(ip);
        printf("The ip_addr in strongswan.c:%s\n", ip);

	//重新拷贝空文件
	recopy_empty_file();
	//添加用户名、密码、预共享密钥
	add_account_and_password(acc);
	
	establish_socket_connect();

	return 0;
}

