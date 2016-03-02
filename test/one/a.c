#include<stdio.h>
#include<string.h>

int main()
{
	char str[100];
	printf("starting\n");
	printf("----str=%s\n",str);
	gets(str);
	printf("str=%s\n",str);
	int len;
	len = strlen(str);
	printf("strlen=%d\n",len);
	return 0;
}
