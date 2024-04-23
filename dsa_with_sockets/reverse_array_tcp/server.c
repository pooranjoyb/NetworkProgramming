#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server, client;
    int ls, cs;
    socklen_t client_len = sizeof(client);

    ls = socket(AF_INET, SOCK_STREAM, 0);
    if(ls < 0){
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if(bind(ls, (struct sockaddr *)&server, sizeof(server)) < 0){
        perror("connection failed");
        return EXIT_FAILURE;
    }

    listen(ls, 1);

    cs = accept(ls, (struct sockaddr *)&client, &client_len);

    int arr[5];

    recv(cs, arr, sizeof(arr), 0);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", arr[i]);
    }

    int newArr[5];
    int counter = 4;
    for (int i = 0; i < 5; i++)
    {
        newArr[i] = arr[counter];
        counter--;
    }

    printf("Reversed Array : ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", newArr[i]);
    }
    
    send(cs, newArr, sizeof(newArr), 0);

    close(ls);
    close(cs);
    return 0;
}