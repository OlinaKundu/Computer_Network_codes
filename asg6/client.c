#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
	struct sockaddr_in server;
	char msg[512];
	int sd;
	bzero((char*)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_port= htons(SERVER_PORT);
	sd= socket(AF_INET,SOCK_STREAM,0);
	connect(sd, (struct sockaddr*)&server,sizeof(server));
	do{
		printf("Enter a message: ");
		scanf("%s", msg);
		send(sd,msg,strlen(msg)+1,0);
		if(strcmp(msg,"stop")==0) break;
		memset(msg,0x0,512);
		recv(sd,msg,512,0);
		printf("message recieved:%s\n ", msg);
	}while(1);
close(sd);
}
