#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // Creating socket
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Clear and configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost IP

    socklen_t server_addr_len = sizeof(server_addr);

    // Enter message to send
    printf("Enter message to send to server: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Send message to the echo server
    sendto(client_fd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, server_addr_len);

    printf("Message sent to server, waiting for echo...\n");

    // Receive echoed message from the server
    int recv_len = recvfrom(client_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
    if (recv_len < 0) {
        perror("Receive failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received string
    buffer[recv_len] = '\0';
    printf("Echo from server: %s\n", buffer);

    close(client_fd);
    return 0;
}
