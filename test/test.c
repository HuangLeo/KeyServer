#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#define ETH_NAME        "eth0"
#define MYPORT  8887
#define MYPORT1  8886
#define BUFFER_SIZE 1024
int sock_cli;
char sendbuf[BUFFER_SIZE];
char recvbuf[BUFFER_SIZE];

FILE * fp;
char ver[20];
int lenn;
int k;
int If_cp=1;
char SS[12];
char SE[12];
char Return_String[12]={0};
int main()
{
	void get_p_pp_ppp_version();

        int sock;
        struct sockaddr_in sin;
        struct ifreq ifr;
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        if (sock == -1){
                perror("socket");
                return -1;
        }
        //get mac
        strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
        ifr.ifr_name[IFNAMSIZ - 1] = 0;

        if (ioctl(sock,SIOCGIFHWADDR, &ifr) < 0){
                perror("ioctl");
                return -1;
        }

        memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
//      fprintf(stdout, "%s\n", inet_ntoa(sin.sin_addr));
	char mac[32];
	sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",
	(unsigned char) ifr.ifr_hwaddr.sa_data[0],
	(unsigned char) ifr.ifr_hwaddr.sa_data[1],
	(unsigned char) ifr.ifr_hwaddr.sa_data[2],
	(unsigned char) ifr.ifr_hwaddr.sa_data[3],
	(unsigned char) ifr.ifr_hwaddr.sa_data[4],
	(unsigned char) ifr.ifr_hwaddr.sa_data[5]);
	printf("Mac:%s\n",mac);


	char name[254];
	while(1)
	{

	       	//打开version文件,读取版本信息
	       	if((fp=fopen("version","a+"))==NULL){
	               	printf("-----cannot open this file on the version------\n");
	               	//exit(0);
	       	}else{
	               	printf("--------open this file on the version-------\n");
	       	}
		//
	        char kc[1][1000] ;
		int a,b;
		k=0;
	        if(fgets(kc[k],20,fp)!=NULL){
		        printf("read version file---%s\n",kc[k]);
			a=strlen(kc[k]);
                        printf("lenlenlen=%d\n",a);
	        	strcpy(ver,kc[k]);
	        	printf("-----------ver=%s\n",ver);
			b=strlen(ver);
                        printf("len22222lenlen=%d\n",b);
	        }
		ver[b-1]='\0';
		printf("------bbbbb-----ver=%s\n",ver);
	        fclose(fp);
		lenn=strlen(ver);
		printf("oooverooooolen=%d\n",lenn);
		if(lenn<16 && lenn>6 && strpbrk(ver,"\n")==0 && If_cp==1){
			printf("you need copy version to preversion\n");
			char tmp3[254];
			sprintf(tmp3,"echo %s > preversion && echo %s > ppversion && echo %s > pppversion",ver,ver,ver);
			system(tmp3);
			If_cp--;
		}
		if(lenn>15 || lenn<7){
			printf("!!!!!error!!!!!!ver is error\n");
			//strcpy(ver,"20121028");
			//printf("!!!!!!!!!!!ver=%s\n",ver);
			get_p_pp_ppp_version();
		}
		if(lenn<16 && lenn>6 && strpbrk(ver,"\n")!=0){
                        printf("***error***ver have enter!!\n");
                        //strcpy(ver,"1.0.0.0");
                        //printf("!!!!!!!!!!!ver=%s\n",ver);
			get_p_pp_ppp_version();
                }
		int huang=1;
		if(huang==1){
			printf("you need to update\n");
			while(1)
			{
				void client_connect_server(int port, char sendstring[],char Return_String[12]);
				int one;
				for(one=0;one<1;one++)
				{
					char setime[] = "setime\n";
					client_connect_server(MYPORT,setime,Return_String);
					int lense;
					lense=strlen(Return_String);
					strncpy(SE,Return_String,lense-1);
					SE[lense-1]='\0';
				}

				int two;
				for(two=0;two<1;two++)
				{
					char sstime[] = "sstime\n";
					client_connect_server(MYPORT1,sstime,Return_String);
					int lenss;
					lenss=strlen(Return_String);
					strncpy(SS,Return_String,lenss-1);
					SS[lenss-1]='\0';
				}

				printf("in while--------huang=%d\n",huang);
				printf("in while--------se=%s\n",SE);
				printf("in while--------ss=%s\n",SS);
				if(strcmp(SE,"setimeok")==0 && strcmp(SS,"sstimeok")==0){
					printf("starting upgrade\n");
					char listen[] = "listen\n";
					client_connect_server(MYPORT,listen,Return_String);
					printf("listen--------SE=%s",Return_String);
					client_connect_server(MYPORT1,listen,Return_String);
					printf("listen--------SS=%s",Return_String);
					break;
				}else{
					printf("waiting update\n");
					char pause[24];
                			sprintf(pause,"sleep 1");
                			system(pause);
					huang++;
				}
			}
		}

		//定义数组存放用户的帐号
        	/*char acc[4][1000] ;
		char tmp[254];
		//sprintf(tmp,"curl http://upd.id2u.cn/?r=test&m=%s -s -o data",mac);
		sprintf(tmp,"curl http://upd.id2u.cn/?r=update'&'v=%s'&'m=%s -s -o data",ver,mac);
		printf("ddddddddddddddddddd%s\n",tmp);
		system(tmp);

        	//打开文件，读取服务器返回信息
        	if((fp=fopen("data","a+"))==NULL)
        	{
                	printf("-----cannot open this file on the out------\n");
                	//exit(0);
        	}else{
                	printf("--------open this file on the out-------\n");
        	}

	        //
	        int i=0;
	        if(fgets(acc[i],1000,fp)!=NULL)
	        {
	                printf("read dada file---%s\n",acc[i]);
			strcpy(name,acc[i]);
			printf("-----------name=%s\n",name);
	        }
	        fclose(fp);

		char nn[7];
		nn[6]='\0';
		strncpy(nn,name,7);
		printf("nnnnnnnnnnnnnnn=%s\n",nn);
		if(strncmp(nn,"http://",7)==0){
			printf("You need to update\n");
			int j=15;
			int ii=0;
			char version[9];
			char ss[10];
			ss[9]='\0';
			version[8]='\0';
			while(name[j]!='\0')
			{
				if(name[j]>='0'&&name[j]<='9') //如果数组元素是数字. 就输出这个元素.
				{
					//printf("*********%c",name[j]);
					sprintf(ss,"%c",name[j]);
					version[ii] = *ss;
					ii++;
				}
				j++;
			}
			printf("-22222222222222----------name=%s\n",name);
			printf("-22222222222222----------version=%s\n",version);
	
			char tmp3[254];
			sprintf(tmp3,"echo %s > version",version);
			system(tmp3);

			char tmp6[254];
			sprintf(tmp6,"cd ./new && wget %s",name);
			system(tmp6);
			char tmp5[54];
			sprintf(tmp5,"cd ./new/ && tar -zxvf ./* && cd ./patch/ && sh upgrade.sh");
			system(tmp5);
			char tmp7[54];
			sprintf(tmp7,"cd ./new/ && rm ./*.tar.gz && rm -rf ./patch");
			system(tmp7);
			
		}else{
			printf("***************error******************\n");
			printf("Don't need to be updated\n");
			char tmp4[24];
                	sprintf(tmp4,"sleep 60");
                	system(tmp4);
		}*/

		char tmp2[24];
		sprintf(tmp2,"sleep 5");
		system(tmp2);
	}
	return 0;

}

void get_p_pp_ppp_version()
{
	memset(ver,0,sizeof(ver));//clean ver
	//打开preversion文件,读取版本信息
       	if((fp=fopen("preversion","a+"))==NULL)
       	{
	       	printf("-----cannot open this file on the preversion------\n");
	       	//exit(0);
       	}else{
	       	printf("--------open this file on the preversion-------\n");
       	}
	//
	char pre[1][1000] ;
	int c,d;
	k=0;
	if(fgets(pre[k],20,fp)!=NULL)
	{
		printf("read preversion file---%s\n",pre[k]);
		c=strlen(pre[k]);
                printf("lenprelenlen=%d\n",c);
		strcpy(ver,pre[k]);
		printf("-------pre----ver=%s\n",ver);
		d=strlen(ver);
                printf("len222pre22lenlen=%d\n",d);
	}
	ver[d-1]='\0';
	printf("------dddpreddd-----ver=%s\n",ver);
	fclose(fp);
	lenn=strlen(ver);
	printf("ooopreooooolen=%d\n",lenn);
	if(lenn<16 && lenn>6 && strpbrk(ver,"\n")==0){
		printf("you need copy preversion to version\n");
		char pre_v[254];
		sprintf(pre_v,"echo %s > version",ver);
		system(pre_v);
	}
	if(lenn>15 || lenn<7){
		memset(ver,0,sizeof(ver));//clean ver
		printf("!!!!!error!!!!!!pre is error\n");
		//打开ppversion文件,读取版本信息
	       	if((fp=fopen("ppversion","a+"))==NULL)
	       	{
		       	printf("-----cannot open this file on the ppversion------\n");
		       	//exit(0);
	       	}else{
		       	printf("--------open this file on the ppversion-------\n");
	       	}
		//
		char pp[1][1000] ;
		int e,f;
		k=0;
		if(fgets(pp[k],20,fp)!=NULL)
		{
			printf("read ppversion file---%s\n",pp[k]);
			e=strlen(pp[k]);
		        printf("lenpplenlen=%d\n",e);
			strcpy(ver,pp[k]);
			printf("-------pp----ver=%s\n",ver);
			f=strlen(ver);
		        printf("len222pp22lenlen=%d\n",f);
		}
		ver[f-1]='\0';
		printf("------dddppddd-----ver=%s\n",ver);
		fclose(fp);
		lenn=strlen(ver);
		printf("oooppooooolen=%d\n",lenn);
		if(lenn<16 && lenn>6 && strpbrk(ver,"\n")==0){
			printf("you need copy ppversion to version\n");
			char pp_v[254];
			sprintf(pp_v,"echo %s > version && echo %s > preversion",ver,ver);
			system(pp_v);
		}
		if(lenn>15 || lenn<7){
			memset(ver,0,sizeof(ver));//clean ver
			printf("!!!!!error!!!!!!pp is error\n");
			//打开pppversion文件,读取版本信息
		       	if((fp=fopen("pppversion","a+"))==NULL)
		       	{
			       	printf("-----cannot open this file on the pppversion------\n");
			       	//exit(0);
		       	}else{
			       	printf("--------open this file on the pppversion-------\n");
		       	}
			//
			char ppp[1][1000] ;
			int g,h;
			k=0;
			if(fgets(ppp[k],20,fp)!=NULL)
			{
				printf("read pppversion file---%s\n",ppp[k]);
				g=strlen(ppp[k]);
				printf("lenppplenlen=%d\n",g);
				strcpy(ver,ppp[k]);
				printf("-------ppp----ver=%s\n",ver);
				h=strlen(ver);
				printf("len222ppp22lenlen=%d\n",h);
			}
			ver[h-1]='\0';
			printf("------dddpppddd-----ver=%s\n",ver);
			fclose(fp);
			lenn=strlen(ver);
			printf("ooopppooooolen=%d\n",lenn);
			if(lenn<16 && lenn>6 && strpbrk(ver,"\n")==0){
				printf("you need copy pppversion to version\n");
				char ppp_v[254];
				sprintf(ppp_v,"echo %s > version && echo %s > preversion && echo %s > ppversion",ver,ver,ver);
				system(ppp_v);
			}
			if(lenn>15 || lenn<7){
				printf("!!!!!error!!!!!!ppp is error\n");
				exit(0);
			}
		}		
	}
}

void client_connect_server(int port, char sendstring[],char Return_String[12])
{
	///定义sockaddr_in
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);  ///服务器端口
	servaddr.sin_addr.s_addr = inet_addr("192.168.199.140");  ///服务器ip

	///定义sockect ss
	sock_cli = socket(AF_INET,SOCK_STREAM, 0);

	///连接服务器，成功返回0，错误返回-1
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	send(sock_cli, sendstring, strlen(sendstring),0); ///发送
	/*if(strcmp(sendbuf,"exit\n")==0)
		break;*/
	recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
	fputs(recvbuf, stdout);
	//int lenss;
	//lenss=strlen(recvbuf);
	//strncpy(Return_String,recvbuf,lenss-1);
	//Return_String[lenss-1]='\0';
	strcpy(Return_String,recvbuf);
	printf("nnnnnnnnReturn_Stringnnnnnnn=%s\n",Return_String);


	//memset(sendbuf, 0, sizeof(sendbuf));
	memset(recvbuf, 0, sizeof(recvbuf));
	close(sock_cli);
}


