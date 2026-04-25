#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670
void main()
{
struct sockaddr_in client, server;
int sd, nsd, clen = sizeof(client);
char msg[512];
bzero((char *)&server, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(SERVER_PORT);
server.sin_addr.s_addr = inet_addr(SERVER_IP);
sd = socket(AF_INET, SOCK_STREAM, 0);
bind(sd, (struct sockaddr *)&server, sizeof(server));
listen(sd, 5);
while (1)
{
nsd = accept(sd, (struct sockaddr *)&client, &clen);
do
{
memset(msg, 0x0, 512);
recv(nsd, msg, 512, 0);
printf("\nMessage received from Client: %s, Client IP: %s, Client Port: %u\n", msg,inet_ntoa(client.sin_addr), ntohs(client.sin_port));
} while (strcmp(msg, "stop"));
close(nsd);
}
}
