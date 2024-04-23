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

    cs = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8080);

    if(connect(cs, (struct sockaddr *) &client, sizeof(client)) < 0){
        perror("connection failed");
        return EXIT_FAILURE;
    }
    
    printf("Enter the sizeof the array : ");
    int n;
    scanf("%d", &n);

    send(cs, &n, sizeof(int), 0);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    send(cs, arr, sizeof(arr), 0);

    int sortedArray[n];

    recv(cs, sortedArray, sizeof(sortedArray), 0);

    for (int i = 0; i < n; i++)
    {
        printf("%d\t", sortedArray[i]);
    }

    close(cs);
    return 0;
}