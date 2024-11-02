#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <unistd.h> // for close()

int main(int argc, char *argv[]) {
    int s, t, cp;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    time_t ct;

    if (argc != 2) {
        printf("\nUsage: client <port>\n");
        exit(0);
    }

    // Create socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    // Set up server address
    bzero((char*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons((short)atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to any address

    // Bind the socket
    if (bind(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind error");
        close(s);
        exit(1);
    }

    t = sizeof(cliaddr);
    
    while (1) {
        // Receive a message from a client
        if (recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &t) < 0) {
            perror("Error in recvfrom");
            close(s);
            exit(1);
        }

        // Get the current time
        ct = time(NULL);
        snprintf(buffer, sizeof(buffer), "%s", ctime(&ct)); // Format the time as a string

        // Fork a new process
        if ((cp = fork()) == 0) {
            // Child process
            if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr)) < 0) {
                perror("Error in sendto");
                exit(1);
            }
            exit(0); // Exit child process after sending the time
        } else if (cp < 0) {
            perror("Fork error");
            close(s);
            exit(1);
        }
        
        // Parent process continues to listen for more messages
    }

    // Close the socket
    close(s);
    return 0;
}
