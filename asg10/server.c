int main(){
        struct sockaddr_in client, server;
        int sd, nsd, n, count = 0, clen = sizeof(client);
        char msg[512], msg1[512], ack[] = "acknowledgement recieved";

        bzero((char *)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        server.sin_port = htons(SERVER_PORT);

        sd = socket(AF_INET, SOCK_STREAM, 0);
        bind(sd, (struct sockaddr *)&server, sizeof(server));
        listen(sd, 5);

        while(1){
                nsd = accept(sd, (struct sockaddr *)&client, &clen);
                do{
                        memset(msg, 0x0, 512);
                        recv(nsd, msg, 512, 0);
                        printf("recieved message: %s\n", msg);
                        send(nsd, ack, strlen(ack)+1, 0);
                }while(strcmp(msg, "stop"));
        }
}
