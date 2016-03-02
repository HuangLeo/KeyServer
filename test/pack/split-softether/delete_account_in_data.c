#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;
void delete_account_in_data(char ip[254])
{
	//打开文件
	if((fp=fopen("data","a+"))==NULL)
	{
		printf("-----cannot open this file on the data------");
		exit(0);
	}else{
		printf("--------open this file on the data-------");
	}

	//判断文件里面是否有账户，并删除用户
	char acc[254254][10];
	int i=0;
	while(fgets(acc[i],10,fp)!=NULL)
	{
		char tmp0[254];
		sprintf(tmp0,"vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD UserDelete %s",ip,acc[i]);
		system(tmp0);

		printf("read dada file---%s",acc[i]);
		i++;
	}
	fclose(fp);
	//删除用户后重新拷贝空文件
	char tmp[254];
	sprintf(tmp,"cp ./cp/data  ./data");
	system(tmp);
}
