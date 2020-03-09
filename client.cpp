#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,const char *argv[]){
  int  rec;
  int clifd;
  char sendmasg[100];
  struct sockaddr_in cliaddr;
  struct sockaddr_in servaddr;
  //creat client desciptor
  clifd=socket(PF_INET,SOCK_STREAM,0) ;
  if(clifd==-1){

  perror("clifd error");
  return -1;
  }
printf("socket ok\r\n");
//init socketaddr_in
/*#if 0
servaddr.sin_family=PF_INET;
servaddr.sin_port=htons(29463);
servaddr.sin_addr.s_addr=inet_addr("192.168.134.128");
//bind port
rec=bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  if(rec=-1){
  perror("bind error");
  return -1;
  }
printf("bind ok\r\n");
#endif*/
//connect
cliaddr.sin_family=PF_INET;
cliaddr.sin_port=htons(29463);
cliaddr.sin_addr.s_addr=inet_addr("192.168.134.128");

rec=connect(clifd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

if(rec==-1){
  perror("connect error");
  close(clifd);
  return -1;
  }
printf("connect ok\r\n");
fgets(sendmasg,sizeof(sendmasg),stdin);
rec=send(clifd,sendmasg,sizeof(sendmasg),0);

if(rec==-1){
  perror("send error");
  close(clifd);
  return -1;
  }
printf("send ok\r\n");


close(clifd);
return 0;
}
