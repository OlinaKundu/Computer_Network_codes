#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 5671
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670
void main()
{
struct sockaddr_in client, server;
int sd;
char msg[512];
bzero((char *)&server, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(SERVER_PORT);
server.sin_addr.s_addr = inet_addr(SERVER_IP);
  
sd = socket(AF_INET, SOCK_STREAM, 0);
connect(sd, (struct sockaddr *)&server, sizeof(server));
do
{
printf("Enter a Message: ");
scanf("%s", msg);
send(sd, msg, strlen(msg) + 1, 0);
} while (strcmp(msg, "stop"));
close(sd);
}
