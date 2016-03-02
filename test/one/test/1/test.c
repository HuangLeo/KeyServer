#include<stdio.h>
int main()  
{  
       int  a=10;  
       int  *q;  
       q=&a;  
       printf("%d\n",*q);  
       fun(q);  
       printf("%d\n",*q);  
       return  0;  
}  
