#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int fibonacci(int n){
    if(n == 0) return 0;
    else if(n == 1) return 1;
    return (fibonacci(n-1) + fibonacci(n-2));
}

int main(){
    struct sockaddr_in server, client;
    int cs;
    socklen_t client_len = sizeof(client);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if(cs < 0){
        perror("socket fail");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if(bind(cs, (struct sockaddr *)&server, sizeof(server)) < 0){
        perror("bind fail");
        return EXIT_FAILURE;
    }

    int n;
    recvfrom(cs, &n, sizeof(int), 0, (struct sockaddr *)&client, &client_len);

    printf("RECEIVED : %d", n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = fibonacci(i);
    }

    sendto(cs, arr, sizeof(arr), 0, (struct sockaddr *)&client, client_len);
    
    

    close(cs);
    return 0;
}