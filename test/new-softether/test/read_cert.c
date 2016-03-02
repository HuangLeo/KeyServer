#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;
void read_cert(char AllString[204800])
{
	//get cert to AllString char;
	char acc1[250][254]={0};
	//打开文件
	if((fp=fopen("greensky-server.ovpn","a+"))==NULL)
	{
	        printf("-----cannot open this file on the out------\n");
	        exit(0);
	}else{
	        printf("--------open this file on the out-------\n");
	}

	//判断文件是否含有<a> and </ca>
	int iiii=0;
	while(fgets(acc1[iiii],254,fp)!=NULL)
	{
	        char acc2[2];
	        acc2[1]='\0';
	        strncpy(acc2,acc1[iiii],1);
	        if((strcmp(acc2,"#")!=0) && (strcmp(acc2,";")!=0) && (strcmp(acc2,"\r")!=0))
	        {
	                printf("read dada file---%s\n",acc1[iiii]);
			strcat(AllString,acc1[iiii]);
	        }
	        iiii++;
	}
	fclose(fp);
}
