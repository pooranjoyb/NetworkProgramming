#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in client;
    int cs;
    socklen_t client_len = sizeof(client);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0)
    {
        perror("socket fail");
        return EXIT_FAILURE;
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8080);

    int n;

    printf("Enter the number : ");
    scanf("%d", &n);

    sendto(cs, &n, sizeof(int), 0, (struct sockaddr *)&client, client_len);

    int arr[n];

    recvfrom(cs, arr, sizeof(arr), 0, NULL, NULL);

    for (int  i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    

    close(cs);
    return 0;
}