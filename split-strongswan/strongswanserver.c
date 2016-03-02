#include <stdio.h>

char ip[254];
char AllString[204800]={0};
char acc[100000][30];
int main()
{
	get_ip_addr(ip);
        printf("The ip_addr in strongswan.c:%s\n", ip);

	//重新拷贝空文件
	recopy_empty_file();
	//添加用户名、密码、预共享密钥
	add_account_and_password(acc);

        read_cacert(AllString);
        printf("The following is a certificate:\n%s\n",AllString);
	
	establish_socket_connect(AllString);

	return 0;
}

