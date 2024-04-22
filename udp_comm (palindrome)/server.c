#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    struct sockaddr_in client, server;
    int cs;
    socklen_t client_len = sizeof(client);

    cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0)
    {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(bind(cs, (struct sockaddr *)&server, sizeof(server)) < 0){
        perror("Binding failed");
        return EXIT_FAILURE;
    }

    char buffer[20];

    recvfrom(cs, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &client_len);

    printf("String received : %s", buffer);

    int flag;
    if(strlen(buffer) == 1){
        flag = 1;
    }else {
        int left = 0;
        int right = strlen(buffer)-1;
        flag = 1;

        while (left < right) {
            if (buffer[left] != buffer[right]) {
                flag = 0;
                break;
            }
            left++;
            right--;
        }
    }

    sendto(cs, &flag, sizeof(int), 0, (struct sockaddr *)&client, client_len);

    close(cs);
    return 0;
    
}