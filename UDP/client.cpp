#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    std::string message;

    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (message == "exit")
            break;

        auto start = std::chrono::steady_clock::now(); // Start measuring time

        sendto(sockfd, message.c_str(), message.length(), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

        int n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, nullptr, nullptr);
        buffer[n] = '\0';

        auto end = std::chrono::steady_clock::now(); // Stop measuring time
        auto diff = end - start;
        double rtt = std::chrono::duration<double, std::milli>(diff).count();

        std::cout << "Server: " << buffer << std::endl;
        std::cout << "Round-trip time: " << rtt << " ms" << std::endl;
    }

    close(sockfd);
    return 0;
}
