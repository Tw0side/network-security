#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

int main() {
    int sd, num;
    time_t current_time; // Correct type declaration
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr); // Variable to hold the size of client address

    // Create socket
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(43454);

    // Bind the socket
    if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running....................\n");

    // Receive a request from the client
    if (recvfrom(sd, &num, sizeof(num), 0, (struct sockaddr *)&cliaddr, &cliaddr_len) < 0) {
        perror("recvfrom failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // Get the current time
    current_time = time(NULL);
    printf("Client asked for time: %s\n", ctime(&current_time));

    // Send the current time back to the client
    if (sendto(sd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&cliaddr, cliaddr_len) < 0) {
        perror("sendto failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(sd);
    return 0;
}
