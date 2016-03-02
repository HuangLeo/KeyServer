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
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <errno.h>

#define ETH_NAME        "eth0" 


void get_ip_addr(char ip[254])
{
        int sock;
        struct sockaddr_in sin;
        struct ifreq ifr;
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        if (sock == -1){
                perror("socket");
                exit(0);
        }

        //get ipaddr
        strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
        ifr.ifr_name[IFNAMSIZ - 1] = 0;

        if (ioctl(sock, SIOCGIFADDR, &ifr) < 0){
                perror("ioctl");
                exit(0);
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

	sprintf(ip,"%s.%s.%s.%s",e,f,g,h);

	printf("The ip_addr :%s\n", ip);
}
