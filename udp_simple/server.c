#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    struct sockaddr_in server, client;
    int cs;
    char buffer[20];

    socklen_t client_len = sizeof(client);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(cs, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Binding failed");
        close(cs);
        return EXIT_FAILURE;
    }

    if (recvfrom(cs, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &client_len) < 0) {
        perror("Receive failed");
        close(cs);
        return EXIT_FAILURE;
    }

    printf("The string received is: %s\n", buffer);

    close(cs);

    return 0;
}
