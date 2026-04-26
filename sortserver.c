#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5600
#define MAX 100

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

int main() {
    int sd, a[MAX], size;
    struct sockaddr_in server, client;
    int clen = sizeof(client);

    // Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Create socket and bind
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sd, (struct sockaddr*)&server, sizeof(server));

    // Receive size and array from client
    recvfrom(sd, &size, sizeof(int), 0, (struct sockaddr*)&client, &clen);
    recvfrom(sd, a, sizeof(int) * size, 0, (struct sockaddr*)&client, &clen);

    // Print and sort
    printf("Received: ");
    for (int i = 0; i < size; i++) printf("%d ", a[i]);

    bubbleSort(a, size);

    // Send sorted array back
    sendto(sd, a, sizeof(int) * size, 0, (struct sockaddr*)&client, clen);

    close(sd);
    return 0;
}
