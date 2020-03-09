#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void* fun(void* arg){
	int c = (int)arg;
	FILE  *f;
	char recvbuff[128] = {0};
	while(1){
		int n = recv(c,recvbuff,127,0);
		if(n<=0){
			printf("client quit!\n");
			close(c);
			break;
		}
		f=fopen("/home/du/recv.ads","a+");
        fputs(recvbuff,f);
        fclose(f);
		/*printf("%d : %s",c,buff);*/

	}
	
}


int main(int argc,const char *argv[]){
int rec;
FILE *f;
int servfd=-1,connfd=-1;
char recvmasg[100]={0};
struct sockaddr_in servaddr;
struct sockaddr_in connaddr;

//creat socket descriptor
servfd=socket(PF_INET,SOCK_STREAM,0);
  if(servfd==-1){

  perror("socket error");
  return -1;
  }

printf("socket ok\r\n");
//init socketaddr_in
servaddr.sin_family=PF_INET;
servaddr.sin_port=htons(29463);
servaddr.sin_addr.s_addr=inet_addr("192.168.134.128");
//bind port
rec=bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  if(rec==-1){
  perror("bind error");
  close(servfd);
  return -1;
  }
printf("bind ok\r\n");
//listen
rec=listen(servfd,10);
if(rec==-1){

  perror("listen error");
  close(servfd);
  return -1;
  }
printf("listen ok\r\n");
connaddr.sin_family=PF_INET;
connaddr.sin_port=htons(29463);
connaddr.sin_addr.s_addr=inet_addr("192.168.134.134");

//accept
 while(1){
 int addlen=sizeof(connaddr);
 connfd=accept(servfd,(struct sockaddr_in*)&connaddr,&addlen);
  if(connfd==-1){

   perror("accept error");
   continue;//run next cycle
   }
   int pid = fork();
     if(0==pid){
     fun((void*)connfd);

     }
     else if(pid>0){
     fun((void*)connfd);
      sleep(20)
     }

  }


/*receive
rec=recv(connfd,recvmasg,sizeof(recvmasg),0);
if(rec==-1){

  perror("recv error");
  close(connfd);
  close(servfd);
  return -1;
  }
printf("recvok\r\n");
printf("get /s",recvmasg);
f=fopen("/home/du/recv.ads","w+");
if(NULL==f){
printf("fopen error");
}

rec=fputs(recvmasg,f);


fclose(f);*/

//close descriptor
close(connfd);
close(servfd);


return 0;


}
