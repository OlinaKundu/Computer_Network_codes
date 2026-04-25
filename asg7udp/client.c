//echo server using udp socket means that the server will echo back what tihe client sent
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4560

int main(){
	struct sockaddr_in server,client;
	int sd,slen=sizeof(server);
	char msg[512], msg1[512];
	bzero((char*)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	sd=socket(AF_INET,SOCK_DGRAM,0);
	do{
		printf("Enter a message: ");
		fgets(msg,sizeof(msg),stdin);
		msg[strcspn(msg, "\n")]=0;
		sendto(sd,msg,strlen(msg)+1,0, (struct  sockaddr*)&server, slen);
		memset(msg1,0x0,512);
		recvfrom(sd,msg1,512,0,(struct sockaddr*)&server, &slen);
		printf("Echoed message: %s", msg1);
	}while(strcmp(msg,"stop"));
	close(sd);
}
