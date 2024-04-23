#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in server;
    int cs;
    socklen_t server_len = sizeof(server);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0)
    {
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    int n;
    printf("Enter the number for factorial : ");
    scanf("%d", &n);

    sendto(cs, &n, sizeof(int), 0, (struct sockaddr *)&server, server_len);

    int fact;
    
    recvfrom(cs, &fact, sizeof(int), 0, (struct sockaddr *)&server, &server_len);

    printf("The factorial is %d", fact);

    close(cs);
    return 0;
}