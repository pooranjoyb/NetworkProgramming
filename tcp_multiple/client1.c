
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    struct sockaddr_in client;
    int cs;
    char s[20];

    printf("Enter the message: ");
    gets(s);

    cs = socket(AF_INET, SOCK_STREAM, 0);
    if (cs < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(9145);

    if (connect(cs, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("Connection failed");
        close(cs);
        return EXIT_FAILURE;
    }

    send(cs, s, strlen(s), 0);
    close(cs);
    return 0;
}
