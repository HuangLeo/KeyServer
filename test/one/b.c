#include<stdio.h>

int main()
{
int *c;
int *d;
int a=11;
c=&a;
d=&a;
//char str[245];
        //int a=11,b=15;
        //printf("input a and b:");
        //scanf("%d,%d",&a,&b);
	printf("d =%d\n",*d);
	printf("sum is =%d\n",*c);
	add(c,d);
	
	/*char tmp[25];
	sprintf(tmp,"sleep 2");
	system(tmp);*/

	printf("sum is =%d\n",*c);
//	printf("str =%s\n",str);
	//add(d);
	printf("d =%d\n",*d);

	return 0;
}
