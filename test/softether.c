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
#include <ctype.h>
 
#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024
 
int main()
{
	/*char sss[]="bviavbidfv<key>";
	char ss[]="</key>";
	printf("ss=key?-------%s\n",ss);
	if(strstr(sss,ss)==NULL)
	{
		printf("yes\n");
	}else{
		printf("dddddddd----%s\n",strstr(sss,ss));
	}	

	unsigned long long num;
	char str[]="201511151515";
	printf("str=%s\n",str);
	num=strtoull(str,NULL,10);
	printf("num=%lld\n",num);

	unsigned long long ssss;
	ssss=201511151515;
	printf("ssss=%lld\n",ssss);*/
	///定义sockfd
	int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
 
	///定义sockaddr_in
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(MYPORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
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

	///客户端套接字
	char buffer[BUFFER_SIZE];
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	int conn;
       	int shijian=0;

	while(1)
	{
		///成功返回非负描述字，出错返回-1
		conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
		if(conn<0)
		{
			perror("connect");
			exit(1);
		}
		memset(buffer,0,sizeof(buffer));
		int len = recv(conn, buffer, sizeof(buffer),0);

                if(strcmp(buffer,"key1\n")==0  ||  strcmp(buffer,"key1")==0)
                {
                        char l[]="key1ok\n";
                        send(conn, l, 50, 0);
                        fputs(l, stdout);
                }else if(strcmp(buffer,"listen\n")==0 || strcmp(buffer,"listen")==0){
        		//定义时间并初始化，用作前一天的用户清理
        		time_t timep;
        		struct tm *p;
        		time(&timep);
        		p =localtime(&timep);
        		shijian  = p->tm_min;
        		printf("now min is---conn-----%d\n",p->tm_min);
                        char ll[]="ok\n";
                        send(conn, ll, 50, 0);
                        fputs(ll, stdout);
                }else if(strcmp(buffer,"setime\n")==0 || strcmp(buffer,"setime")==0){
        	        //初始化本地时间
        	        time_t timep;
        	        struct tm *p;
        	        time(&timep);
        	        p =localtime(&timep);
	
        	        //shijian  = p->tm_hour;
	                printf("now min is---time-----%d\n",p->tm_min);
	                printf("now min is---shijian-----%d\n",shijian);
			if(p->tm_min >= shijian + 1)
			{
                        	char lll[]="setimeok\n";
                        	send(conn, lll, 50, 0);
                        	fputs(lll, stdout);
			}else{
			        char llll[]="setimenook\n";
                                send(conn, llll, 50, 0);
                                fputs(llll, stdout);

			}

                }else{
                        send(conn, buffer, 50, 0);
                        fputs(buffer, stdout);
                }


	}
	close(conn);
	close(server_sockfd);
	return 0;
}
