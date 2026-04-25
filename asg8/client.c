#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6540

int main(){
	struct sockaddr_in server,client;
	int sd,slen=sizeof(server);
	char msg[512], msg1[512];
	bzero((char*)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	sd=socket(AF_INET,SOCK_DGRAM,0);
	do{
		printf("Enter a message: ");
		scanf("%s",msg);
		sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr *)&server, slen);
		if(strcmp(msg,"stop")==0) break;
		memset(msg1,0x0,512);
		recvfrom(sd,msg1,512,0,(struct sockaddr*)&server,&slen);
		printf("Echoed message: %s\n", msg1);
	}while(1);
	close(sd);
}
