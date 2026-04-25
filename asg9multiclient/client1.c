#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include<string.h>
#define CLIENT_IP "127.0.0.2"
#define CLIENT_PORT 5981
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4560

int main(){
	struct sockaddr_in server, client;
	int sd;
	char  msg[512],msg1[512];
	bzero((char*)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	bzero((char*)&client, sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(CLIENT_PORT);
	client.sin_addr.s_addr=inet_addr(CLIENT_IP);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd, (struct sockaddr*)&client, sizeof(client));
	connect(sd,(struct sockaddr*)&server,sizeof(server));
	do{
		printf("Enter a message: ");
		scanf("%s", msg);
		send(sd,msg,strlen(msg)+1,0);
		memset(msg1,0x0,512);
		recv(sd,msg1,512,0);
		printf("\nMessage received from server: %s\n", msg1);
	}while(strcmp(msg,"stop"));
close(sd);
}
