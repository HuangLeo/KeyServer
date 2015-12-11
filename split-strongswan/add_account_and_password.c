#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;

//添加用户名、密码、预共享密钥
void add_account_and_password(char acc[100000][30])
{
	char pool[]=
	{
		'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j',
		'k','l','m','n','o','p','q','r','s','t',
		'u','v','w','x','y','z','A','B','C','D',
		'E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X',
		'Y','Z'
    	};//随机池
	srand(time(0));
    	char account[9];
	char pwd[9];
	account[8]='\0';//方便作为字符串输出处理
	pwd[8]='\0';//方便作为字符串输出处理

	int sum0;   	
	for(sum0=0;sum0<10;sum0++)
	{
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

		char tmp2[254];
		sprintf(tmp2,"%s \%%any : XAUTH \\\"%s\\\"",account,pwd);
		printf("----------%s\n",tmp2);

		char tmp3[254];
		sprintf(tmp3,"echo %s >> ipsec.secrets",tmp2);
		system(tmp3);

		char tmp4[254];
		sprintf(tmp4,"cp ipsec.secrets /etc");
		system(tmp4);

	        char buf[254];
		char s[100000];
	        char prsec[10] = {"cl123456"};
	        sprintf(buf,"%s,%s",account,pwd);
		sprintf(s,"%s,%s",buf,prsec);
		strcpy(acc[sum0] , s);

		//打开存储用户账户的文档
		if((fp=fopen("data","a+"))==NULL)
		{
			printf("-----cannot open this file on the in------\n");
			exit(0);
		}else{
			printf("--------open this file on the in-------");
		}

		fputs(acc[sum0],fp);
		fputs("\n",fp);
		fclose(fp);

		printf("-------用户名、密码、预共享密钥=%s\n",acc[sum0]);

	}
	char tmp[254];
	sprintf(tmp,"ipsec restart");
	system(tmp);
}

