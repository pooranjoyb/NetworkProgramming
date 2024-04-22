#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in client;
    int cs;

    cs = socket(AF_INET, SOCK_STREAM, 0);
    if(cs < 0){
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8080);

    if(connect(cs, (struct sockaddr *)&client, sizeof(client)) < 0){
        perror("connection failed");
        return EXIT_FAILURE;
    }

    int arr[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }

    send(cs, arr, sizeof(arr), 0);

    int revArr[5];

    recv(cs, revArr, sizeof(revArr), 0);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", revArr[i]);
    }
    
    close(cs);
    return 0;
}