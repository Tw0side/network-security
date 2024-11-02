#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // for close()

int main() {
    int sd, addrlen, num = 1;
    time_t start_time, rt, current_time; 
    struct sockaddr_in servaddr, cliaddr; 

    // Create socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(43454); 

    // Set up client address
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(43455);

    // Bind the socket
    if (bind(sd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0) {
        perror("Bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    printf("Client is running......................\n");

    // Get the start time
    start_time = time(NULL);

    // Send a request to the server
    sendto(sd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    addrlen = sizeof(cliaddr);

    // Receive the current time from the server
    if (recvfrom(sd, &current_time, sizeof(current_time), 0, (struct sockaddr *) &cliaddr, &addrlen) < 0) {
        perror("recvfrom failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // Calculate round-trip time and adjust current time
    rt = time(NULL) - start_time;
    current_time += rt / 2;

    printf("Server's Time: %s\n", ctime(&current_time));

    // Close the socket
    close(sd);
    return 0;
}
