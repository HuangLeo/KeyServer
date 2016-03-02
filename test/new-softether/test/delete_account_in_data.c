#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;
void delete_account_in_data(char ip[254])
{
	//打开文件
	if((fp=fopen("data","a+"))==NULL)
	{
		printf("-----cannot open this file on the out------");
		exit(0);
	}else{
		printf("--------open this file on the out-------");
	}

	//判断文件里面是否有账户，并删除用户
	char acc[254254][10];
	int ii=0;
	while(fgets(acc[ii],10,fp)!=NULL)
	{
		char tmp0[254];
		sprintf(tmp0,"vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD UserDelete %s",ip,acc[ii]);
		system(tmp0);

		printf("read dada file---%s",acc[ii]);
		ii++;
	}
	fclose(fp);
	//删除用户后重新拷贝空文件
	char tmp4[254];
	sprintf(tmp4,"cp ./cp/data  ./data");
	system(tmp4);
}
