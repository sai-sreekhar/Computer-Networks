#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr *)&serv_addr,
                          sizeof(serv_addr))) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Print server address
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    getpeername(client_fd, (struct sockaddr *)&server_addr, &server_addr_len);
    char server_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(server_addr.sin_addr), server_ip, INET_ADDRSTRLEN);
    printf("Connected to server: %s:%d\n", server_ip, ntohs(server_addr.sin_port));

    while (true)
    {
        char *toSendFromClient;
        printf("Enter message to send to server: ");
        scanf("%s", toSendFromClient);

        if(strcmp(toSendFromClient, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        send(client_fd, toSendFromClient, strlen(toSendFromClient), 0);
        valread = read(client_fd, buffer, 1024);
        printf("%s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    // closing the connected socket
    close(client_fd);
    return 0;
}
