#include <stdio.h>
#include <string.h>

char s[100000];//存放用户名、密码、预共享密钥
//发送一个密文
void encrypt_account_and_password(char acc[100000][32],char miwen[64],int account_number)
{
	sprintf(s,"%s",acc[account_number]);
	//把字符串拆分成每个都是8位的字符串
	int jjj;
	jjj = strlen(s);
	printf("printff-------acc[account_number]=%s\n",acc[account_number]);
	printf("printff-------sssssssss=%s\n",s);
	printf("printff-------fdddddf%d\n",jjj);
	//char s[50]="userName,Password";
		char s1[9];
		char s2[9];
		char s3[9];
		char s4[8];
		char sn[8];
		char ss[9];
	
		s1[8]='\0';
		s2[8]='\0';
		s3[8]='\0';
		s4[7]='\0';
		sn[7]='\0';
		ss[8]='\0';
		int i;
		for(i=0;i<8;i++)//one
		{		
			if(i<strlen(s))
			{
				printf("%c",s[i]);
				sprintf(ss,"%c",s[i]);
				s1[i] = *ss;
			}
			else printf("%c",' ');
		}
		printf("\n");


		for(i=0;i<8;i++)//two
		{
			if(i+8<strlen(s))
			{

				printf("%c",s[i+8]);
				sprintf(ss,"%c",s[i+8]);
				s2[i] = *ss;
			}
			else printf("%c",' ');
		}
		printf("\n");

		for(i=0;i<8;i++)//three
		{
			if(i+16<strlen(s))
			{

				printf("%c",s[i+16]);
				sprintf(ss,"%c",s[i+16]);
				s3[i] = *ss;
			}
			else printf("%c",' ');
		}
		printf("\n");

		for(i=0;i<8;i++)//four
		{
			if(i+24<strlen(s))
			{

				printf("%c",s[i+24]);
				sprintf(ss,"%c",s[i+24]);
				s4[i] = *ss;
			}
			else printf("%c",' ');
		}
		printf("\n");


	for(i=0;i<7;i++)
	{
		sprintf(ss,"%c",s4[i]);
		sn[i] = *ss;

	}

	int s11;s11 = strlen(s1);
	printf("-----%s-----%d\n",s1,s11);
	int s21;s21 = strlen(s2);
	printf("-----%s-----%d\n",s2,s21);
	int s31;s31 = strlen(s3);
	printf("-----%s-----%d\n",s3,s31);
	int s41;s41 = strlen(s4);
	printf("-----%s-----%d\n",s4,s41);


	int eee=0;

	//char MyMessage[16]={"as1df345"};
	char dddd[48]={0}; 
	char dddd1[48]={0}; 
	char dddd2[48]={0};
	char dddd3[48]={0};
	//main1(MyMessage,MesHex);
	main1(s1,dddd);
	//printf("Encrypted!----buf-----:%s\n",buf);

	printf("Your Message is Encrypted!:\n");  // 信息已加密one
	printf("Encrypted!:%s\n",dddd);
	for(eee=0;eee<64;eee++)           
	{
		printf("%c",dddd[eee]);
	}
	printf("\n");
	printf("\n");

	main1(s2,dddd1);
	printf("Your Message2222222 is Encrypted!:\n");  // 信息已加密two
	printf("Encrypted22222222!:%s\n",dddd1);
	for(eee=0;eee<64;eee++)           
	{
		printf("%c",dddd1[eee]);
	}
	printf("\n");
	printf("\n");

	main1(s3,dddd2);
	printf("Your Message2222222 is Encrypted!:\n");  // 信息已加密three
	printf("Encrypted22222222!:%s\n",dddd2);
	for(eee=0;eee<64;eee++)           
	{
		printf("%c",dddd2[eee]);
	}
	printf("\n");
	printf("\n");

	main1(sn,dddd3);
	printf("Your Message2222222 is Encrypted!:\n");  // 信息已加密four
	printf("Encrypted22222222!:%s\n",dddd3);
	for(eee=0;eee<64;eee++)           
	{
		printf("%c",dddd3[eee]);
	}
	printf("\n");
	printf("\n");
	sprintf(miwen,"%s%s%s%s",dddd,dddd1,dddd2,dddd3);//发送密文
	printf("*****miwen*****%s\n",miwen); 
}
