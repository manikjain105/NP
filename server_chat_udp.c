#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int n;
    socklen_t len = sizeof(cliaddr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Receive message from client
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);

        // Exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exited the chat.\n");
            break;
        }

        // Get server's message
        printf("Server: ");
        fgets(buffer, MAXLINE, stdin);

        // Send the message to client
        sendto(sockfd, buffer, strlen(buffer), 0,
               (const struct sockaddr *) &cliaddr, len);

        // Exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server exited the chat.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}