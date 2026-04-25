#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<time.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
	struct sockaddr_in server,client;
	char msg[512],msg2[]="Invalid Request", *ptr;
	int sd, nsd, clen=sizeof(client);
	time_t ti;
	bzero((char*)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	sd= socket(AF_INET, SOCK_STREAM, 0);
	bind(sd,(struct sockaddr *)&server, sizeof(server));
	listen(sd,5);
	while(1){
		nsd=accept(sd, (struct sockaddr *)&client, &clen);
		do{
		memset(msg,0x0,512);
		recv(nsd, msg, 512,0);
		if(strcmp(msg,"time")==0){
			ti=time(NULL);
			ptr=ctime(&ti);
			send(nsd,ptr,strlen(ptr)+1,0);
		}
		else
			send(nsd,msg2,strlen(msg2)+1,0);
		}while(strcmp(msg,"stop"));
	close(nsd);
	}
close(sd);
}
