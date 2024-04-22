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
    char buffer[20];

    cs = socket(AF_INET, SOCK_STREAM, 0);
    if (cs < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(9145);

    if (connect(cs, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("Connection failed");
        close(cs);
        return EXIT_FAILURE;
    }

    printf("Enter the string to check: ");
    scanf("%s", buffer);

    send(cs, buffer, strlen(buffer), 0);

    int flag;
    recv(cs, &flag, sizeof(int), 0);

    if (flag == 1)
        printf("Palindrome\n");
    else
        printf("Not palindrome\n");

    close(cs);
    return 0;
}
