#include<stdio.h>
//#include<string.h>

void add(int *c,int *d/*char str[254],*/)
{
	//int f;
	//char str2[]="huangweijun";
	//f=a+b;
	*c=111;
	//int g = 1000;
	//strcpy(str,str2);
	printf("a+b=%d\n",*c);
	*d=100;
	printf("cccccca+b=%d\n",*c);
	printf("dddddda+b=%d\n",*d);
}
