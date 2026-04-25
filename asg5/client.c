#include <stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include <netinet/in.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
	struct sockaddr_in server;
	char msg[512];
	int sd;
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr= inet_addr(SERVER_IP);
	server.sin_port = htons(SERVER_PORT);
	sd = socket(AF_INET, SOCK_STREAM ,0);
	connect(sd, (struct sockaddr *)&server , sizeof(server));
	do {
		printf("Enter a mssg: ");
		//scanf("%s" , msg);
		fgets(msg, sizeof(msg), stdin);
		msg[strcspn(msg , "\n")]=0;
		send(sd,msg,strlen(msg)+1,0);
		memset(msg,0x0,512);
		recv(sd,msg,512,0);
		printf("\nMessage recieved: %s\n", msg);
		}
	while(strcmp(msg,"stop"));
close(sd);
}
