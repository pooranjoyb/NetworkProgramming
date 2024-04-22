#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    struct sockaddr_in server;
    int cs;
    char buffer[20];

    socklen_t server_len = sizeof(server);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    printf("Enter the string: ");
    gets(buffer);

    sendto(cs, buffer, strlen(buffer), 0, (struct sockaddr *)&server, server_len);

    close(cs);

    return 0;
}
