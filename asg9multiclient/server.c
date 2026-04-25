#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4560

int main(){
	struct sockaddr_in client, server;
	int nsd, sd, clen=sizeof(client);
	char msg[512];
	bzero((char *)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(SERVER_PORT);
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd, (struct sockaddr*)&server, sizeof(server));
	listen(sd,5);
	while(1){
		nsd=accept(sd,(struct sockaddr*)&client, &clen);
		int pid=fork();
		if(pid==0){
			do{
				memset(msg,0x0,512);
				recv(nsd,msg,512,0);
				send(nsd,msg,strlen(msg)+1,0);
			}while(strcmp(msg,"stop"));
		}
		else if(pid>0)
			close(nsd);
		else
			printf("ERROR n fork");
	}
	close(sd);
}

