int main(){
        struct sockaddr_in client, server;
        int sd, n, count=0;
        char msg[512], msg1[512], ack[512];

        bzero((char *)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        server.sin_port = htons(SERVER_PORT);

        sd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sd, (struct sockaddr *)&server, sizeof(server));

        do{
                printf("\nenter a message:");
                scanf("%s", msg);
                printf("\nenter wndow size:");
                scanf("%d", &n);

                int i, j = 0;
                for(i = 0; i < strlen(msg); i++){
                        if(j < n){
                                msg1[j++] = msg[i];
                        }

                        if(j == n || i == strlen(msg) - 1){
                                msg1[j] = '\0';
                                send(sd, msg1, strlen(msg1)+1, 0);
                                memset(ack, 0x0, 512);
                                recv(sd, ack, 512, 0);
                                count++;
                                printf("\n%s %d\n", ack, count);
                                j = 0;
                        }
                }
        }while(strcmp(msg, "stop"));
        return 0;
}
