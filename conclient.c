#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h> // for close()

int main(int argc, char *argv[]) {
    int n, s, t;
    struct sockaddr_in servaddr, local;
    char buffer[1024];

    if (argc < 3) {
        printf("Usage: client <server-addr> <port>\n");
        exit(0);
    }

    // Create socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Set up local address
    bzero((char *)&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(6677); // Change this if needed
    local.sin_addr.s_addr = htonl(INADDR_ANY); // Use any available interface

    // Bind the socket
    if (bind(s, (struct sockaddr *)&local, sizeof(local)) == -1) {
        perror("Bind error");
        close(s);
        exit(1);
    }

    // Set up server address
    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons((short)atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    // Send "TIME" message to server
    strcpy(buffer, "TIME");
    if (sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Error in sendto");
        close(s);
        exit(1);
    }

    t = sizeof(servaddr);
    printf("The current time is: ");
    if ((n = recvfrom(s, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&servaddr, &t)) > 0) {
        buffer[n] = '\0';
        fputs(buffer, stdout);
    } else {
        if (n < 0) {
            perror("Error in read from");
        } else {
            printf("Server closed connection\n");
        }
        close(s);
        exit(1);
    }

    // Close the socket
    close(s);
    return 0;
}
