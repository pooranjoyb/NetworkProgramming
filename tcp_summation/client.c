#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in client;
    int cs;

    cs = socket(AF_INET, SOCK_STREAM, 0);
    if (cs < 0)
    {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8080);

    if (connect(cs, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        perror("connection failed");
        return EXIT_FAILURE;
    }

    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    send(cs, &n, sizeof(int), 0);

    int array[n];

    printf("Enter the elems of the array : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    int sum; 
    send(cs, array, sizeof(array), 0);
    recv(cs, &sum, sizeof(int), 0);

    printf("summation received from server : %d\n", sum);

    close(cs);
    return 0;
}