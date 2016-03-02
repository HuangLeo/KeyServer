#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <time.h>

#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024
 
int sum = 0;

//定义数组存放用户的帐号
char acc[254254][10];
char buf[254];
char s[254];
char account[9];
char miwen[64];
FILE * fp;
void establish_socket_connect(char ip[254],char AllString[204800])
{
	///定义sockfd
	int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
	//AF_INET是针对Internet的,因而可以允许在远程主机之间通信
	//SOCK_STREAM表明我们用的是TCP协议,这样会提供按顺序的,可靠,双向,面向连接的比特流.

     
	///定义sockaddr_in
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(MYPORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	//int bind(int sockfd, struct sockaddr *my_addr, int addrlen)
	//sockfd:是由server_sockfd调用返回的文件描述符.
	//addrlen:是sockaddr结构的长度.
	//my_addr:是一个指向sockaddr的指针. 在中有 sockaddr的定义
	//struct sockaddr{
	//unisgned short as_family;
	//char sa_data[14];
	//};
	//使用另外一个结构(struct server_sockaddr) 来代替


	///bind，成功返回0，出错返回-1
	if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}
 
	///listen，成功返回0，出错返回-1
	if(listen(server_sockfd,QUEUE) == -1)
	{
        	perror("listen");
        	exit(1);
	}
	
	//定义时间并初始化，用作前一天的用户清理
	int shijian;
	long int record_time;

	time_t timep;
	struct tm *p;
	time(&timep);
	p =localtime(&timep);

	shijian  = p->tm_hour;
	printf("now hours is---conn-----%d\n",p->tm_hour);
	printf("now min is---conn-----%d\n",p->tm_min);

	//定义计算用户帐号的数量 
	int conn;
	
	///客户端套接字
	char buffer[BUFFER_SIZE];
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);


	while(1)
	{	
		//输出当前时间
		printf("now shijian is--------%d\n",shijian);


		///成功返回非负描述字，出错返回-1
		conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
		if(conn<0)
		{
        		perror("connect");
        		exit(1);
		}	

		//初始化本地时间
		time_t timep;
		struct tm *p;
		time(&timep);
		p =localtime(&timep);

		//shijian  = p->tm_hour;
		printf("now hours is---conn-----%d\n",p->tm_hour);
		printf("now min is---conn-----%d\n",p->tm_min);


        	memset(buffer,0,sizeof(buffer));
        	int len = recv(conn, buffer, sizeof(buffer),0);
        	/*if(strcmp(buffer,"exit\n")==0)
        		break;*/

		if(strcmp(buffer,"user\n")==0 || strcmp(buffer,"user")==0)
		{

			printf("now hours is----user----%d\n",p->tm_hour);
			printf("now min is----user----%d\n",p->tm_min);
			//判断时间是否为当天的时间，若是，不做处理；若不是，清除之前的帐号
			if(shijian == p->tm_hour)
			{
				printf("time is same\n");
			}else{
				printf("time is diffrent\n");
				shijian = p->tm_hour;
				int y;
				for(y=0; y<sum; y++)
				{
	                		char pp[254];
                			sprintf(pp,"vpncmd /SERVER %s /adminhub:DEFAULT /PASSWORD:server /CMD UserDelete %s",ip,acc[y]);
                			system(pp);
        	        		printf("=======time=======\n");
				}
				sum = 0;
				
			}
			add_account_and_password(ip,s,account);
			strcpy(acc[sum] , account);
			encrypted_account_password(s,miwen);


			//打开存储用户账户的文档
			if((fp=fopen("data","a+"))==NULL)
			{
				printf("-----cannot open this file on the in------");
				exit(0);
			}else{
				printf("--------open this file on the in-------");
			}

			fputs(acc[sum],fp);
			fputs("\n",fp);
			fclose(fp);
			
			printf("-------acc[sum]=%s\n",acc[sum]);

         		send(conn, miwen, 64, 0);
			fputs(buf, stdout);
			sum++;
			printf("-------sum=%d\n",sum);
		
		}else if(strcmp(buffer,"key1\n")==0  ||  strcmp(buffer,"key1")==0){//softether is ok ?
                        char l[]="key1ok\n";
                        send(conn, l, 50, 0);
                        fputs(l, stdout);
		}else if(strcmp(buffer,"listen\n")==0 || strcmp(buffer,"listen")==0){//client listen
                        //定义时间并初始化，判断是否有用户连接
                        time_t timep;
                        struct tm *p;
                        time(&timep);
                        //p =localtime(&timep);
                        //shijian  = p->tm_min;
                        //printf("now min is---listen-----%d\n",p->tm_min);
			record_time = timep;
                        printf("now record_time is---listen-----%ld\n",record_time);
			char ll[]="ok\n";
			send(conn, ll, 50, 0);
			fputs(ll, stdout);
		}else if(strcmp(buffer,"setime\n")==0 || strcmp(buffer,"setime")==0){//client is  connecting ?
                        //初始化本地时间
                        time_t timep;
                        struct tm *p;
                        time(&timep);
                        //p =localtime(&timep);
			
                        //shijian  = p->tm_hour;
                        printf("now timep is---time-----%ld\n",timep);
                        if(timep >= record_time + 300)
                        {
                                char lll[]="setimeok\n";
                                send(conn, lll, 10, 0);
                                fputs(lll, stdout);
                        }else{
                                char llll[]="setimenook\n";
                                send(conn, llll, 12, 0);
                                fputs(llll, stdout);

                        }

                }else if(strcmp(buffer,"cert\n")==0 || strcmp(buffer,"cert")==0){//send cert
			char strkey[]="</key>";
			if(strstr(AllString,strkey)==NULL){
				printf("Get Certificate Again\n");
				memset(AllString,0,sizeof(AllString));
		        	read_cert(AllString);
			}else{
				printf("AllString is complete\n");
                        	send(conn, AllString, 20480, 0);
				printf("%s\n",AllString);
                        	//fputs(acc1, stdout);
				
			}

                }else{
                        char lerror[]="error\n";
                        send(conn, lerror, 50, 0);
                        fputs(lerror, stdout);
                }


	}
	close(conn);
        close(server_sockfd);
}

