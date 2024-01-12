#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 10024

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[BUFFER_SIZE];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) == 0) {
        std::cout << "Listening..." << std::endl;
    } else {
        perror("Error in listening");
        exit(EXIT_FAILURE);
    }

    addrSize = sizeof(newAddr);
    // Accept connection
    newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addrSize);
    if (newSocket < 0) {
        perror("Error in accepting");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(newSocket, buffer, sizeof(buffer), 0);

        /* if (bytesRead <= 0) {
            std::cerr << "Connection closed by client or error occurred." << std::endl;
            break;
        }

        std::cout << "Received data: " << buffer << std::endl; */
        if (bytesRead == 0) {
        std::cout << "Connection closed by the client." << std::endl;
        break;
    } else if (bytesRead < 0) {
        perror("Error during recv");
        break;
    } else {
        std::cout << "Received data: " << buffer << std::endl;
    }
        usleep(1000000);
    }

    // Close sockets
    close(newSocket);
    close(serverSocket);

    return 0;
}
