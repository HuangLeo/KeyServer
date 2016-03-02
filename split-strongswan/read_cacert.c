#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * fp;
void read_cacert(char AllString[204800])
{
        //get cert to AllString char;
        char cacert[250][254]={0};
        //打开文件
        if((fp=fopen("cacert.pem","a+"))==NULL)
        {
                printf("-----cannot open this file on the cacert.pem------\n");
                //exit(0);
        }else{
                printf("--------open this file on the cacert.pem-------\n");
        }

        //判断文件是否含有<a> and </ca>
        int i=0;
        while(fgets(cacert[i],254,fp)!=NULL)
        {
                char cacert1[2];
                cacert1[1]='\0';
                strncpy(cacert1,cacert[i],1);
                if((strcmp(cacert1,"#")!=0) && (strcmp(cacert1,";")!=0) && (strcmp(cacert1,"\r")!=0))
                {
                        printf("read dada file---%s\n",cacert[i]);
                        strcat(AllString,cacert[i]);
                }
                i++;
        }
        fclose(fp);
}

