#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1020000

void *clientThread(void *arg)
{
   
    int bytesRead;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char *response = "Hello World!\n";
    int clientSocket = *((int *)arg);

    
    while (1)
    {
        for (int i = 0; i < MAX_BUFFER_SIZE; ++i)
        {
            buffer[i] = '\0';
        }
        bytesRead = read(clientSocket, buffer, MAX_BUFFER_SIZE); 

       
        char command[MAX_BUFFER_SIZE] = {0};
        int index = 0;
        while (buffer[index] != ' ' && buffer[index] != '\0')
        {
            command[index] = buffer[index];
            index++;
        }
        command[index] = '\0';
        /*******************************************************************************************/

        if (strcmp(buffer, "listall") == 0)
        {
            
            char fileList[MAX_BUFFER_SIZE];
            int count = 0;
            DIR *dir;
            struct dirent *entry; 
            dir = opendir(".");   
            if (dir)
            {
               
                while ((entry = readdir(dir)) != NULL)
                {
                    for (int j = 0; j < strlen(entry->d_name); ++j)
                    {
                        fileList[count++] = entry->d_name[j];
                    }
                    fileList[count++] = '\n';
                }
                fileList[count - 1] = '\0';
                closedir(dir); 
            }
            response = &fileList[0];
        }
        else if (strcmp(buffer, "exit") == 0)
        {
           
            response = "Closing Connection.....Exiting....!";
            send(clientSocket, response, strlen(response), 0); 
            printf("Response sent to client!\n");
            break; 
        }
        else if (strcmp(command, "send") == 0)
        {
           
            char *token = strtok(buffer, " ");
            token = strtok(NULL, " ");
           
            if (token == NULL)
            {
                response = "What file do you want from the server??";
            }
            else
            {
               
                DIR *dir;
                struct dirent *entry;
                dir = opendir(".");
                int found = 0;
                if (dir)
                {
                    while ((entry = readdir(dir)) != NULL)
                    {
                        if (strcmp(entry->d_name, token) == 0)
                        {
                            found = 1;
                        }
                    }
                    closedir(dir);
                }
                /*****************************************************************/
                if (found)
                {
                    
                    FILE *file;
                    file = fopen(token, "r"); 
                    char responseData[MAX_BUFFER_SIZE];
                   
                    for (int i = 0; i < MAX_BUFFER_SIZE; ++i)
                    {
                        responseData[i] = '\0';
                    }
                    char ch;
                    int index = 0;
                    while ((ch = fgetc(file)) != EOF && index < (MAX_BUFFER_SIZE - 1))
                    {
                        responseData[index++] = ch;
                    }
                    /************************************************************/

                    response = &responseData[0]; 
                }
                else
                {
                    
                    response = "File Not Found!";
                }
            }
        }
        else
        {
            
            response = "Invalid Command!";
        }
        send(clientSocket, response, strlen(response), 0); 
        printf("Response sent to client!\n");
    }
    pthread_exit(NULL); 
}

int main(int argc, char const *argv[])
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress; 
    int opt = 1;
    int addressLength = sizeof(serverAddress);

    
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    serverAddress.sin_family = AF_INET;         
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    serverAddress.sin_port = htons(PORT);       

    
    if (bind(serverSocket, (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(serverSocket, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[105];
    int threadCount = 0;
    while (1)
    {
        
        clientSocket = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t *)&addressLength);
        if (clientSocket < 0)
        {
            perror("accept");
            continue;
        }
        
        int result = pthread_create(&threads[threadCount++], NULL, clientThread, &clientSocket);
        if (result != 0)
        {
            perror("Failed to create thread");
            continue;
        }
    }
    return 0;
}
