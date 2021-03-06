#include <netdb.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
//typedef enum {false,true}bool;
int main() 
{ 
    bool flag;
    int    sock;
    char **pptr = NULL;
    struct sockaddr_in    destAddr;
    struct hostent    *ptr = NULL;
    char destIP[128];
    char szBuffer[] = {"GET /ip2city.asp HTTP/1.1\r\nHost:www.ip138.com\r\nConnection:Close\r\n\r\n"};
    char res[1024];

    sock = socket(AF_INET,SOCK_STREAM,0);
    if( -1 == sock ){
        perror("creat socket failed");
        exit(0);
    }

    bzero((void *)&destAddr,sizeof(destAddr));
    destAddr.sin_family = AF_INET;        
    destAddr.sin_port = htons(80);

    ptr = gethostbyname("www.ip138.com");
    if(NULL == ptr){
        perror("gethostbyname error");
        exit(0);
    }   

    for(flag=false,pptr=ptr->h_addr_list ; NULL != *pptr ; ++pptr){
        inet_ntop(ptr->h_addrtype,*pptr,destIP,sizeof(destIP));
        printf("addr:%s\n",destIP);
        destAddr.sin_addr.s_addr = inet_addr(destIP);
        if(-1!=connect(sock,(struct sockaddr *)&destAddr,sizeof(struct sockaddr))){
            flag = true;
            break;
        }
    }

    if(false == flag){
        perror("connect failed");
    }

    if(strlen(szBuffer) != send(sock,szBuffer,strlen(szBuffer),0)){
        perror("send error");
        exit(0);
    }

    if(-1 == recv(sock,res,1024,0)){
        perror("recv error");
        exit(0);
    }

    printf("res:\n%s\n",res);    
    return 0;
}
