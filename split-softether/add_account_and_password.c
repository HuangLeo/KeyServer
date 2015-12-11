#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_account_and_password(char ip[254],char s[254],char account[9])
{
	//生成账户密码
	char pool[]={
	'0','1','2','3','4','5','6','7','8','9',
	'a','b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s','t',
	'u','v','w','x','y','z','A','B','C','D',
	'E','F','G','H','I','J','K','L','M','N',
	'O','P','Q','R','S','T','U','V','W','X',
	'Y','Z'
	};//随机池
	srand(time(0));
	//char account[9];
	char pwd[9];
	account[8]='\0';//方便作为字符串输出处理
	pwd[8]='\0';//方便作为字符串输出处理

	int j=0;
	while(j!=8)
	{
		account[j++]=pool[rand()%sizeof(pool)];
	}
	printf("帐号:%s\n",account);

	int i=0;
	while(i!=8)
	{
		pwd[i++]=pool[rand()%sizeof(pool)];
	}
	printf("密码:%s\n",pwd);
	//执行linux命令，创建随机用户并为之创建密码
	char tmp[254];
	sprintf(tmp,"vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD UserCreate %s /GROUP:none /REALNAME:none /NOTE:vpncmd",ip,account);
	system(tmp);

	char tmp2[254];
	sprintf(tmp2,"vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD UserPasswordSet %s /PASSWORD:%s",ip,account,pwd);
	system(tmp2);
	char buf[254];
	char prsec[10] = {"cl123456"};
	sprintf(buf,"%s,%s",account,pwd);
	sprintf(s,"%s,%s",buf,prsec);

}
