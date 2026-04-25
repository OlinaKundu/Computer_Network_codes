
    #include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6555

int main() {
    struct sockaddr_in client, server;
    int sd, nsd, clen = sizeof(client);
    int next_expected = 0; // This will be our ACK
    char frame;

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr*)&server, sizeof(server));
    listen(sd, 5);

    printf("Server listening...\n");
    nsd = accept(sd, (struct sockaddr*)&client, &clen);

    while (1) {
        // Use nsd, not sd
        int res = recv(nsd, &frame, sizeof(char), 0);
        if (res <= 0) break; // Client disconnected

        printf("Received frame: %c\n", frame);
        
        // Logic: Send the index of the NEXT frame we want
        next_expected++; 
        send(nsd, &next_expected, sizeof(int), 0);
        printf("Sent ACK: %d\n", next_expected);
    }

    close(nsd);
    close(sd);
    return 0;
}
