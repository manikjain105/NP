#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Creating socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Clear and configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message from client
        int recv_len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len < 0) {
            perror("Receive failed");
            continue;
        }

        printf("Received message: %s\n", buffer);

        // Echo message back to client
        sendto(server_fd, buffer, recv_len, 0, (struct sockaddr *)&client_addr, client_addr_len);
    }

    close(server_fd);
    return 0;
}















































// #include <iostream>
// #include <cstring>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>

// #define PORT 8080
// #define BUFFER_SIZE 1024

// int main() {
//     int server_fd;
//     char buffer[BUFFER_SIZE];
//     struct sockaddr_in server_addr, client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);

//     // Creating socket
//     if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//         std::cerr << "Socket creation failed" << std::endl;
//         return -1;
//     }

//     // Clear and configure server address
//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = INADDR_ANY;
//     server_addr.sin_port = htons(PORT);

//     // Bind the socket to the port
//     if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
//         std::cerr << "Bind failed" << std::endl;
//         close(server_fd);
//         return -1;
//     }

//     while (true) {
//         memset(buffer, 0, BUFFER_SIZE);

//         // Receive message from client
//         int recv_len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);
//         if (recv_len < 0) {
//             std::cerr << "Receive failed" << std::endl;
//             continue;
//         }

//         std::cout << "Received message: " << buffer << std::endl;

//         // Echo message back to client
//         sendto(server_fd, buffer, recv_len, 0, (struct sockaddr*)&client_addr, client_addr_len);
//     }

//     close(server_fd);
//     return 0;
// }
