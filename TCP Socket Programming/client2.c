
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_SIZE 1020000

int main(int argc, char const *argv[])
{
    struct sockaddr_in server_address;
    int socket_fd = 0, valread;
    struct sockaddr_in server_addr;
    char *hello = "Hello from client";
    char buffer[MAX_SIZE] = {0};

   
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&server_addr, '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Welcome to the client!\n");

    
    while (1)
    {
        printf(">>");
        char user_input[MAX_SIZE];
        char command[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            user_input[i] = '\0';
        }

        int len = 0;
        char c;
        scanf("%c", &c);
        user_input[len++] = c;
        while (c != '\n')
        {
            scanf("%c", &c);
            user_input[len++] = c;
        }
        user_input[len - 1] = '\0';

        for (int i = 0; i < MAX_SIZE; ++i)
        {
            command[i] = '\0';
        }

        for (int i = 0; i < len; ++i)
        {
            command[i] = user_input[i];
        }

        send(socket_fd, user_input, strlen(user_input), 0);

        for (int i = 0; i < MAX_SIZE; ++i)
        {
            user_input[i] = '\0';
        }

        valread = read(socket_fd, user_input, MAX_SIZE);

       
        if (strcmp(user_input, "Closing Connection.....Exiting....!") == 0)
        {
            printf("%s\n", user_input);
            break;
        }
        if (strcmp(user_input, "What file do you want from the server??") == 0)
        {
            printf("%s\n", user_input);
            continue;
        }
        if (strcmp(user_input, "File Not Found!") == 0)
        {
            printf("%s\n", user_input);
            continue;
        }

        char *token = strtok(command, " ");
        if (strcmp(token, "send") == 0)
        {
            token = strtok(NULL, " ");
            FILE *file = fopen("output.txt", "w");
            fprintf(file, "%s", user_input);
            fclose(file);
            printf("File downloaded successfully!\n");
            continue;
        }
        printf("%s\n", user_input); 
    }
    return 0;
}
