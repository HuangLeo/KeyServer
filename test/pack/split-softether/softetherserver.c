#include <stdio.h>

char AllString[204800]={0};
char ip[254];
int main()
{
	get_ip_addr(ip);
	printf("The ip_addr in softether.c:%s\n", ip);

	download_cert(ip);
	printf("Download cert is complete\n");

	read_cert(AllString);
	printf("The following is a certificate:\n%s\n",AllString);

	delete_account_in_data(ip);

	establish_socket_connect(ip,AllString);

	return 0;
}

