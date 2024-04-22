#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in server, client;
    int ls, cs, n;
    socklen_t client_len = sizeof(client);

    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls < 0)
    {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    printf("Server listening on port 8080...\n");
    if (bind(ls, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Binding failed");
        return EXIT_FAILURE;
    }

    listen(ls, 1);

    cs = accept(ls, (struct sockaddr *)&client, &client_len);
    if (cs < 0)
    {
        perror("Connection creation failed");
        return EXIT_FAILURE;
    }

    recv(cs, &n, sizeof(int), 0);

    int arr[n];

    recv(cs, arr, sizeof(arr), 0);

    printf("Received sizeof array : %d\n", n);

    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    send(cs, arr, sizeof(arr), 0);

    close(cs);
    close(ls);
    return 0;
}