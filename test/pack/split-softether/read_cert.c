#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;
void read_cert(char AllString[204800])
{
	//get cert to AllString char;
	char cert[250][254]={0};
	//打开文件
	if((fp=fopen("greensky-server.ovpn","a+"))==NULL)
	{
	        printf("-----cannot open this file on the greensky-server.ovpn------\n");
	        //exit(0);
	}else{
	        printf("--------open this file on the greensky-server.ovpn-------\n");
	}

	//判断文件是否含有<a> and </ca>
	int i=0;
	while(fgets(cert[i],254,fp)!=NULL)
	{
	        char cert1[2];
	        cert1[1]='\0';
	        strncpy(cert1,cert[i],1);
	        if((strcmp(cert1,"#")!=0) && (strcmp(cert1,";")!=0) && (strcmp(cert1,"\r")!=0))
	        {
	                printf("read dada file---%s\n",cert[i]);
			strcat(AllString,cert[i]);
	        }
	        i++;
	}
	fclose(fp);
}
