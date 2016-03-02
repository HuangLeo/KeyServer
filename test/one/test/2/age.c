#include<stdio.h>

int main()
{
	int age(int c);
	int num;
	printf("input age:");
	scanf("%d",&num);
	printf("NO.5 number is %d\n",age(num));
	return 0;
}

int age(int c)
{
	int number;
	if(c==1){
		number=10;
	}else{
		number = age(c-1) + 2;
	}
	return number;
}
