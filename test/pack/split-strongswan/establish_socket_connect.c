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

#define MYPORT  8886
#define QUEUE   20
#define BUFFER_SIZE 1024

FILE * fp;
//定义数组存放用户的帐号
char miwen[64];
char acc[100000][32];
int account_number=0;
void establish_socket_connect()
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

	//判断是否连接成功
	int conn;
	
	///客户端套接字
	char buffer[BUFFER_SIZE];
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	while(1)
	{	
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
				encrypt_account_and_password(acc,miwen,account_number);
				send(conn, miwen, 64, 0);//通过sochet向客户端发送密文
				//fputs(buf, stdout);

        			account_number++;//逐渐提取用户密码预共享密钥
        			if(account_number == 10)
        			{
        			        account_number=0;
        			}

			}else{
				printf("time is diffrent\n");
				shijian = p->tm_hour;//重新定义时间

				recopy_empty_file();
				add_account_and_password(acc);

				account_number=0;
				encrypt_account_and_password(acc,miwen,account_number);
				send(conn, miwen, 64, 0);//通过sochet向客户端发送密文
				//fputs(buf, stdout);

			}

		
		}else if(strcmp(buffer,"key2\n")==0  ||  strcmp(buffer,"key2")==0)
                {
                        char l[]="key2ok\n";
                        send(conn, l, 50, 0);
                        fputs(l, stdout);

		}else if(strcmp(buffer,"listen\n")==0 || strcmp(buffer,"listen")==0){
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
		}else if(strcmp(buffer,"sstime\n")==0 || strcmp(buffer,"sstime")==0){
                        //初始化本地时间
                        time_t timep;
                        struct tm *p;
                        time(&timep);
                        //p =localtime(&timep);

                        //shijian  = p->tm_hour;
                        printf("now timep is---time-----%ld\n",timep);
                        if(timep >= record_time + 300)
                        {
                                char lll[]="sstimeok\n";
                                send(conn, lll, 10, 0);
                                fputs(lll, stdout);
                        }else{
                                char llll[]="sstimenook\n";
                                send(conn, llll, 12, 0);
                                fputs(llll, stdout);

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

