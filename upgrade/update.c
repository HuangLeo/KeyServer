#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/time.h>
#define MAX 1  
pthread_t thread[3];
pthread_mutex_t mut;
int number=0, i;
FILE * fp;
char localip[254];

#define ETH_NAME        "eth0"  
#define MYPORT  8887
#define MYPORT1  8886
#define MYPORT2  8885
#define MYPORT3  8884
#define QUEUE   20
#define BUFFER_SIZE 1024

int sock_cli;
int sock_cli1;
int sock_cli2;
char sendbuf[BUFFER_SIZE];
char recvbuf[BUFFER_SIZE];

char mac[32];

char ver[20];
int lenn;
int k;
int If_cp=1;
char SS[12];
char SE[12];
char Return_String[12]={0};
void get_p_pp_ppp_version();

void *thread1()
{
        printf ("thread1 : I'm thread 1\n");
        for (i = 0; i < MAX; i++)
        {
                printf("thread1 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                number++;
                pthread_mutex_unlock(&mut);
                sleep(2);

		int k1;
		for(k1=0;k1<3;k1++)
		{
			sleep(5);
			///定义sockfd
			sock_cli = socket(AF_INET,SOCK_STREAM, 0);

			struct sockaddr_in servaddr;
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(MYPORT);  ///服务器端口
			servaddr.sin_addr.s_addr = inet_addr(localip);  ///服务器ip

			///连接服务器，成功返回0，错误返回-1
			if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			{
	       			perror("connect");
				printf("************error***********\n");
				if(k1==2){	
					printf("you need change key1!!!!!!!\n");
					char get_softether[254];


					//定义数组存放get_softether
					char acc[4][1000] ;
					char tmp[128];
					sprintf(tmp,"curl http://upd.id2u.cn/?r=softether'&'v=1.0.0.1'&'m=%s -s -o softether",mac);
					printf("ddddddddddddddddddd%s\n",tmp);
					system(tmp);

					//打开文件，读取服务器返回信息
					if((fp=fopen("softether","a+"))==NULL)
					{
						printf("-----cannot open this file on the out------\n");
						//exit(0);
					}else{
						printf("--------open this file on the out-------\n");
					}

					//
					int ik1=0;
					if(fgets(acc[ik1],1000,fp)!=NULL)
					{
						printf("read softether file---%s\n",acc[ik1]);
						strcpy(get_softether,acc[ik1]);
						printf("-----------get_softether=%s\n",get_softether);
					}
					fclose(fp);

			                char nn1[8];
                			nn1[7]='\0';
                			strncpy(nn1,get_softether,7);
                			printf("nnnnnnnnnnnnnnn=%s\n",nn1);
                			if(strncmp(nn1,"http://",7)==0){
                        			printf("You need to update\n");
				        	char tmp1[254];
				        	sprintf(tmp1,"cd ./k1 && wget %s",get_softether);
				        	system(tmp1);
				        	char tmp2[54];
				        	sprintf(tmp2,"cd ./k1/ && tar -zxvf ./* && cd ./patch/ && sh upgrade.sh");
				        	system(tmp2);
				        	char tmp3[54];
				        	sprintf(tmp3,"cd ./k1/ && rm ./*.tar.gz && rm -rf ./patch");
				        	system(tmp3);

			                }else{
                        			printf("***************error******************\n");
                        			printf("Don't need to be updated\n");
                        			char tmp4[24];
                        			sprintf(tmp4,"sleep 60");
                        			system(tmp4);
                			}
				}
				continue;
	       			//exit(1);
			}

			//key1 is ok ?
			char key1[] = "key1\n";
			send(sock_cli, key1, strlen(key1),0); ///发送
			pthread_mutex_lock(&mut);
			recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
			fputs(recvbuf, stdout);

		        char n1[7];
		        n1[6]='\0';
		        strncpy(n1,recvbuf,6);
			pthread_mutex_unlock(&mut);
		        printf("nnnnnnnnnnnnnnn=%s\n",n1);

			if(strncmp(n1,"key1ok",6)==0)
			{
				printf("key1 is ok\n");
				printf("you don't change key1\n");	

				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli);
	
				break;
			}else{
		
				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli);
				sleep(2);
			}
			/*if(k1==2){	
				printf("kkkkkkxxxxx111111=%d\n",k1);
				printf("you need change key1\n");

			}*/
		}
		sleep(1);

		int k2;
		for(k2=0;k2<3;k2++)
		{
			sleep(5);
			///定义sockfd
			sock_cli1 = socket(AF_INET,SOCK_STREAM, 0);

			struct sockaddr_in servaddr;
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(MYPORT1);  ///服务器端口
			servaddr.sin_addr.s_addr = inet_addr(localip);  ///服务器ip

			///连接服务器，成功返回0，错误返回-1
			if (connect(sock_cli1, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			{
	       			perror("connect");
				printf("************error***********\n");
				if(k2==2){	
					printf("you need change key2!!!!!!!\n");
					char get_strongswan[254];

					//定义数组存放get_strongswan
					char acc[4][1000] ;
					char tmp[128];
					sprintf(tmp,"curl http://upd.id2u.cn/?r=strongswan'&'v=1.0.0.1'&'m=%s -s -o strongswan",mac);
					printf("ddddddddddddddddddd%s\n",tmp);
					system(tmp);

					//打开文件，读取服务器返回信息
					if((fp=fopen("strongswan","a+"))==NULL)
					{
						printf("-----cannot open this file on the out------\n");
						//exit(0);
					}else{
						printf("--------open this file on the out-------\n");
					}

					//
					int ik2=0;
					if(fgets(acc[ik2],1000,fp)!=NULL)
					{
						printf("read strongswan file---%s\n",acc[ik2]);
						strcpy(get_strongswan,acc[ik2]);
						printf("-----------get_strongswan=%s\n",get_strongswan);
					}
					fclose(fp);

                                        char nn2[8];
                                        nn2[7]='\0';
                                        strncpy(nn2,get_strongswan,7);
                                        printf("nnnnnnnnnnnnnnn=%s\n",nn2);
                                        if(strncmp(nn2,"http://",7)==0){
                                                printf("You need to update\n");
                                                char tmp1[254];
                                                sprintf(tmp1,"cd ./k2 && wget %s",get_strongswan);
                                                system(tmp1);
                                                char tmp2[54];
                                                sprintf(tmp2,"cd ./k2/ && tar -zxvf ./* && cd ./patch/ && sh upgrade.sh");
                                                system(tmp2);
                                                char tmp3[54];
                                                sprintf(tmp3,"cd ./k2/ && rm ./*.tar.gz && rm -rf ./patch");
                                                system(tmp3);

                                        }else{
                                                printf("***************error******************\n");
                                                printf("Don't need to be updated\n");
                                                char tmp4[24];
                                                sprintf(tmp4,"sleep 60");
                                                system(tmp4);
                                        }

				}
				continue;
	       			//exit(1);
			}

			//key2 is ok ?
			char key2[] = "key2\n";
			send(sock_cli1, key2, strlen(key2),0); ///发送
			pthread_mutex_lock(&mut);
			recv(sock_cli1, recvbuf, sizeof(recvbuf),0); ///接收
			fputs(recvbuf, stdout);

		        char n2[7];
		        n2[6]='\0';
		        strncpy(n2,recvbuf,6);
			pthread_mutex_unlock(&mut);
		        printf("nnnn2222nnnnnnn=%s\n",n2);

			if(strncmp(n2,"key2ok",6)==0)
			{
				printf("key2 is ok\n");	
				printf("you don't change key2\n");

				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli1);
	
				break;
			}else{
		
				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli1);
				sleep(2);
			}
			/*if(k2==2){	
				printf("kkkkkxxxxx22222=%d\n",k2);
				printf("you need change key2\n");

			}*/
		}
		sleep(1);

		int u2;
		for(u2=0;u2<3;u2++)
		{
			sleep(5);
			///定义sockfd
			sock_cli2 = socket(AF_INET,SOCK_STREAM, 0);

			struct sockaddr_in servaddr;
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(MYPORT2);  ///服务器端口
			servaddr.sin_addr.s_addr = inet_addr(localip);  ///服务器ip

			///连接服务器，成功返回0，错误返回-1
			if (connect(sock_cli2, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			{
	       			perror("connect");
				printf("************error***********\n");
				if(u2==2){	
					printf("you need change up2!!!!!!!\n");
					char get_update2[254];

					//定义数组存放get_update2
					char acc[4][1000] ;
					char tmp[128];
					sprintf(tmp,"curl http://upd.id2u.cn/?r=up2'&'v=1.0.0.1'&'m=%s -s -o Mupdate",mac);
					printf("ddddddddddddddddddd%s\n",tmp);
					system(tmp);

					//打开文件，读取服务器返回信息
					if((fp=fopen("Mupdate","a+"))==NULL)
					{
						printf("-----cannot open this file on the out------\n");
						//exit(0);
					}else{
						printf("--------open this file on the out-------\n");
					}

					//
					int iu2=0;
					if(fgets(acc[iu2],1000,fp)!=NULL)
					{
						printf("read Mupdate file---%s\n",acc[iu2]);
						strcpy(get_update2,acc[iu2]);
						printf("-----------get_update2=%s\n",get_update2);
					}
					fclose(fp);

                                        char nn3[8];
                                        nn3[7]='\0';
                                        strncpy(nn3,get_update2,7);
                                        printf("nnnnnnnnnnnnnnn=%s\n",nn3);
                                        if(strncmp(nn3,"http://",7)==0){
                                                printf("You need to update\n");
                                                char tmp1[254];
                                                sprintf(tmp1,"cd ./u2 && wget %s",get_update2);
                                                system(tmp1);
                                                char tmp2[54];
                                                sprintf(tmp2,"cd ./u2/ && tar -zxvf ./* && cd ./patch/ && sh upgrade.sh");
                                                system(tmp2);
                                                char tmp3[54];
                                                sprintf(tmp3,"cd ./u2/ && rm ./*.tar.gz && rm -rf ./patch");
                                                system(tmp3);

                                        }else{
                                                printf("***************error******************\n");
                                                printf("Don't need to be updated\n");
                                                char tmp4[24];
                                                sprintf(tmp4,"sleep 60");
                                                system(tmp4);
                                        }

				}
				continue;
	       			//exit(1);
			}

			//up2 is ok ?
			char up2[] = "up2\n";
			send(sock_cli2, up2, strlen(up2),0); ///发送
			pthread_mutex_lock(&mut);
			recv(sock_cli2, recvbuf, sizeof(recvbuf),0); ///接收
			fputs(recvbuf, stdout);

		        char n3[6];
		        n3[5]='\0';
		        strncpy(n3,recvbuf,5);
			pthread_mutex_unlock(&mut);
		        printf("nnnnnn33333nnnnnn=%s\n",n3);

			printf("uuuuuuu2222222=%d\n",u2);

			if(strncmp(n3,"up2ok",5)==0){
				printf("up2 is ok\n");
				printf("you don't change up2\n");	

				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli2);
	
				break;
			}else{
		
				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
				close(sock_cli2);
				sleep(2);
			}
			/*if(u2==2){	
				printf("uuuuxxxxx22222=%d\n",u2);
				printf("you need change up2\n");

			}*/
		}
        }
        printf("thread1 :主函数在等我完成任务吗？\n");
        pthread_exit(NULL);

}

void *thread2()
{
        printf("thread2 : I'm thread 2\n");
        for (i = 0; i < MAX; i++)
        {
                printf("thread2 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                number++;
                pthread_mutex_unlock(&mut);
                sleep(1);

		///定义sockfd
		int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
	 
		///定义sockaddr_in
		struct sockaddr_in server_sockaddr;
		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_port = htons(MYPORT3);
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

		        if(strcmp(buffer,"up1\n")==0  ||  strcmp(buffer,"up1")==0)
		        {
		                char l[]="up1ok\n";
		                send(conn, l, 50, 0);
		                fputs(l, stdout);
				break;
		        }else if(strcmp(buffer,"listen\n")==0 || strcmp(buffer,"listen")==0){
		                char ll[]="ok\n";
		                send(conn, ll, 50, 0);
		                fputs(ll, stdout);
		        }

		}
		close(conn);
		close(server_sockfd);

        }
        printf("thread2 :主函数在等我完成任务吗？\n");
        pthread_exit(NULL);
}

void *thread3()
{
        printf("thread3 : I'm thread 3\n");
	char link_name[254];
	while(1)
	{

	       	//打开文件,读取版本信息
	       	if((fp=fopen("version","a+"))==NULL)
	       	{
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
		int lenn;
		lenn=strlen(ver);
		printf("oooooooolen=%d\n",lenn);
		if(lenn<16 && lenn>6 && strpbrk(ver,"\n")==0 && If_cp==1){
			printf("you need copy version to preversion\n");
			char v_p[254];
			sprintf(v_p,"echo %s > preversion && echo %s > ppversion && echo %s > pppversion",ver,ver,ver);
			system(v_p);
			If_cp--;
		}
		if(lenn>15 || lenn<7)
		{
			printf("!!!!!!!!!!!ver is empty\n");
			//strcpy(ver,"1.0.0.0");
			//printf("!!!!!!!!!!!ver=%s\n",ver);
			get_p_pp_ppp_version();
		}
		if(lenn<16 && lenn>6 && strpbrk(ver,"\n")!=0){
                        printf("************error******!!!!!!!!!!!!\n");
                        //strcpy(ver,"20121028");
                        //printf("!!!!!!!!!!!ver=%s\n",ver);
			get_p_pp_ppp_version();
                }

		//定义数组存放用户的帐号
        	char acc[4][1000] ;
		char tmp[254];
		//sprintf(tmp,"curl http://update.greenskylimited.com/?r=test&m=%s -s -o data",mac);
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
	        int ij=0;
	        if(fgets(acc[ij],1000,fp)!=NULL)
	        {
	                printf("read dada file---%s\n",acc[ij]);
			strcpy(link_name,acc[ij]);
			printf("-----------link_name=%s\n",link_name);
	        }
	        fclose(fp);

		char nn[8];
		nn[7]='\0';
		strncpy(nn,link_name,7);
		printf("nnnnnnnnnnnnnnn=%s\n",nn);
		if(strncmp(nn,"http://",7)==0){
			printf("You need to update\n");
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

				printf("in while--------se=%s\n",SE);
				printf("in while--------ss=%s\n",SS);
				if(strcmp(SE,"setimeok")==0 && strcmp(SS,"sstimeok")==0){
					printf("starting upgrade\n");
					char listen[] = "listen\n";
					client_connect_server(MYPORT,listen,Return_String);
					printf("listen--------SE=%s",Return_String);
					client_connect_server(MYPORT1,listen,Return_String);
					printf("listen--------SS=%s",Return_String);

					//upgrade command line
					char tmp6[254];
					sprintf(tmp6,"cd ./new && wget %s",link_name);
					system(tmp6);
					If_cp++;
					char tmp5[54];
					sprintf(tmp5,"cd ./new/ && tar -zxvf ./* && cd ./patch/ && sh upgrade.sh");
					system(tmp5);
					char tmp7[54];
					sprintf(tmp7,"rm -rf /work/upgrade/new/*");
					system(tmp7);
					break;
				}else{
                                        printf("waiting update\n");
                                        char pause[24];
                                        sprintf(pause,"sleep 1");
                                        system(pause);
                                }
			}	
		}else{
			printf("***************error******************\n");
			printf("Don't need to be updated\n");
			char tmp4[24];
                	sprintf(tmp4,"sleep 60");
                	system(tmp4);
		}

		char tmp2[24];
		sprintf(tmp2,"sleep 60");
		system(tmp2);
	}
        printf("thread3 :主函数在等我完成任务吗？\n");
        pthread_exit(NULL);
}

void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));
        /*创建线程*/
        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)        
                printf("线程1创建失败!\n");
        else
                printf("线程1被创建\n");
        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
                printf("线程2创建失败");
        else
                printf("线程2被创建\n");
        if((temp = pthread_create(&thread[2], NULL, thread3, NULL)) != 0)
                printf("线程3创建失败");
        else
                printf("线程3被创建\n");
}

void thread_wait(void)
{
        /*等待线程结束*/
        if(thread[0] !=0) {
                pthread_join(thread[0],NULL);
                printf("线程1已经结束\n");
        }
        if(thread[1] !=0) {
                pthread_join(thread[1],NULL);
                printf("线程2已经结束\n");
        }
        if(thread[2] !=0) {
                pthread_join(thread[2],NULL);
                printf("线程3已经结束\n");
        }
}

void get_ip_addr()
{
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock == -1){
	        perror("socket");
		exit(1);
	        //return -1;
	}

	//get ipaddr
	strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0){
	        perror("ioctl");
		exit(1);
	        //return -1;
	}

	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
//      fprintf(stdout, "%s\n", inet_ntoa(sin.sin_addr));
	printf("ipaddr:%s\n", inet_ntoa(sin.sin_addr));

	char*e;
	char*f;
	char*g;
	char*h;
	//one
	e=strtok(inet_ntoa(sin.sin_addr),".");
	if(e)
	{
		printf("%s\n",e);
	}
		/*Asecond call to strtok using a NULL
		as the first parameter returns a pointer
		to the character following the token*/
	//two
	f=strtok(NULL,".");
	if(f)
 	        printf("%s\n",f);

	//three
	g=strtok(NULL,".");
	if(g)
		printf("%s\n",g);

	//four
	h=strtok(NULL,".");
	if(h)
		printf("%s\n",h);

	sprintf(localip,"%s.%s.%s.%s",e,f,g,h);

	printf("The ip_addr :%s\n", localip);
}

void get_mac_addr()
{
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock == -1){
		perror("socket");
		exit(1);
		//return -1;
	}
	//get mac
	strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

	if (ioctl(sock,SIOCGIFHWADDR, &ifr) < 0){
		perror("ioctl");
		exit(1);
		//return -1;
	}

	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	
	sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",
	(unsigned char) ifr.ifr_hwaddr.sa_data[0],
	(unsigned char) ifr.ifr_hwaddr.sa_data[1],
	(unsigned char) ifr.ifr_hwaddr.sa_data[2],
	(unsigned char) ifr.ifr_hwaddr.sa_data[3],
	(unsigned char) ifr.ifr_hwaddr.sa_data[4],
	(unsigned char) ifr.ifr_hwaddr.sa_data[5]);
	printf("Mac:%s\n",mac);
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
	servaddr.sin_addr.s_addr = inet_addr(localip);  ///服务器ip

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
	pthread_mutex_lock(&mut);
	recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
	fputs(recvbuf, stdout);
	//int lenss;
	//lenss=strlen(recvbuf);
	//strncpy(Return_String,recvbuf,lenss-1);
	//Return_String[lenss-1]='\0';
	strcpy(Return_String,recvbuf);
	pthread_mutex_unlock(&mut);
	printf("nnnnnnnnReturn_Stringnnnnnnn=%s\n",Return_String);


	//memset(sendbuf, 0, sizeof(sendbuf));
	memset(recvbuf, 0, sizeof(recvbuf));
	close(sock_cli);
}

int main()
{
	get_ip_addr();
	get_mac_addr();	

        /*用默认属性初始化互斥锁*/
        pthread_mutex_init(&mut,NULL);
        printf("我是主函数哦，我正在创建线程，呵呵\n");
        thread_create();
        printf("我是主函数哦，我正在等待线程完成任务阿，呵呵\n");
        thread_wait();
        printf("两个线程已经结束\n");
        sleep(5);
        printf("结束\n");
        return 0;
}

