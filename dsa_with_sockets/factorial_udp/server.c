#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int factorial(int n){
    if (n >= 1)
        return n*factorial(n-1);
    else return 1;
} 

int main()
{

    struct sockaddr_in server, client;
    int cs;
    socklen_t client_len = sizeof(client);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0)
    {
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(cs, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed");
        return EXIT_FAILURE;
    }

    int n;

    recvfrom(cs, &n, sizeof(int), 0, (struct sockaddr *)&client, &client_len);

    printf("RECEIVED : %d", n);

    int fact = factorial(n);

    sendto(cs, &fact, sizeof(int), 0, (struct sockaddr *)&client, client_len);

    close(cs);
    return 0;
}