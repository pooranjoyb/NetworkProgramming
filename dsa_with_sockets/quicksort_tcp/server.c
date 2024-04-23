#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i+1);
}

void quicksort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi+1, high);
    }
}

int main()
{
    struct sockaddr_in server, client;
    int ls, cs;
    socklen_t cleint_len = sizeof(client);

    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls < 0)
    {
        perror("Socket failed");
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(ls, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        cs = socket(AF_INET, SOCK_STREAM, 0);
    }

    listen(ls, 1);
    cs = accept(ls, (struct sockaddr *) &client, &cleint_len);
    if(cs < 0){
        perror("connection failed");
        return EXIT_FAILURE;
    }

    int n;
    recv(cs, &n, sizeof(int), 0);

    int arr[n];

    recv(cs, arr, sizeof(arr), 0);
    
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }

    quicksort(arr, 0, n-1);

    send(cs, arr, sizeof(arr), 0);

    close(ls);
    close(cs);
    return 0;
}