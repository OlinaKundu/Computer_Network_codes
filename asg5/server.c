#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
	struct sockaddr_in server,client;
	char msg[512];
	int sd, nsd,clen=sizeof(client);
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_port = htons(SERVER_PORT);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr *)&server, sizeof(server));
	listen(sd,5);
	while(1){
		nsd = accept(sd, (struct sockaddr *)&client,&clen);
		do{
		memset(msg,0x0,512);
		recv(nsd,msg,512,0);
		send(nsd,msg,strlen(msg)+1,0);
		}while(strcmp(msg,"stop"));
	close(nsd);
	}
	close(sd);
}
