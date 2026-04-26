#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 5600
#define CLIENT_PORT 56001
#define MAX 100

int main() {
    int sd, a[MAX], size;
    struct sockaddr_in server, client;
    int slen = sizeof(server);

    // Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Setup client address
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = INADDR_ANY;

    // Create socket and bind
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sd, (struct sockaddr*)&client, sizeof(client));

    // Input array
    printf("Enter size: ");
    scanf("%d", &size);
    printf("Enter array: ");
    for (int i = 0; i < size; i++) scanf("%d", &a[i]);

    // Send to server
    sendto(sd, &size, sizeof(int), 0, (struct sockaddr*)&server, slen);
    sendto(sd, a, sizeof(int) * size, 0, (struct sockaddr*)&server, slen);

    // Receive sorted array
    recvfrom(sd, a, sizeof(int) * size, 0, (struct sockaddr*)&server, &slen);

    printf("\nSorted: ");
    for (int i = 0; i < size; i++) printf("%d ", a[i]);

    close(sd);
    return 0;
}
