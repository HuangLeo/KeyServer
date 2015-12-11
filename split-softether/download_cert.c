#include <stdio.h>
#include <string.h>

FILE * fp;
void download_cert(char ip[254])
{
	//打开文件
	if((fp=fopen("greensky-server.ovpn","r"))==NULL)
	{
		printf("-----cannot open this file on the download_cert------");
		//exit(0);
		char filename[254];
		sprintf(filename,"cd /work/softether/ && vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD OpenVpnMakeConfig file.zip",ip);
		system(filename);

		char filename1[254];
		sprintf(filename1,"cd /work/softether/ && chmod 777 file.zip && unzip file.zip && mv greensky*l3.ovpn greensky-server.ovpn");
		system(filename1);

		char filename2[254];
		sprintf(filename2,"cd /work/softether/ && rm readme.* && rm file.zip && rm greensky*l2.ovpn");
		system(filename2);
	}else{
		printf("--------open this file on the download_cert-------");
	}
//	fclose(fp);
	printf("exit download_cert");
}
