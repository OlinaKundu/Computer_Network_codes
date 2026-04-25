#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6555

int main(){
	struct sockaddr_in server;
	int sd,counter=0,w=2,ack,i;
	char msg[]= "HELLOGUYS";
	int total = strlen(msg);
	bzero((char *)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	server.sin_port=htons(SERVER_PORT);

	sd= socket(AF_INET,SOCK_STREAM,0);
	connect(sd,(struct sockaddr*)&server, sizeof(server));
	while(counter<total){
		int frames_in_window = 0;
	//send window
		for(i=counter;i<w+counter && i<total; i++){
			printf("Sending frame: %c\n",msg[i]);
			send(sd,&msg[i],sizeof(char),0);
			frames_in_window++;
		}

	//receive acks for the frames sent in this window
		for(i=0;i<frames_in_window;i++){
			recv(sd,&ack, sizeof(int),0);
			printf("Reciever Ack: %d\n",ack);
			// the last ack recieved tells us the new base
			counter =ack;
		}
		printf("---Window slid to index:%d---\n",counter);
	}
	close(sd);
	return 0;
}
