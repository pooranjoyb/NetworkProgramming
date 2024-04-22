#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    struct sockaddr_in server, client;
    int ls, cs;
    socklen_t client_len = sizeof(client);
    char str[20] = {0};

    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9145);

    if (bind(ls, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(ls);
        return EXIT_FAILURE;
    }

    listen(ls, 5);
    cs = accept(ls, (struct sockaddr *)&client, &client_len);
    if (cs < 0) {
        perror("Accept failed");
        close(ls);
        return EXIT_FAILURE;
    }

    recv(cs, str, sizeof(str), 0);
    printf("The message is: %s\n", str);
    close(cs);
    close(ls);
    return 0;
}
