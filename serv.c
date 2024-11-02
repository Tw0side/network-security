#include <sys/socket.h>
#include <netinet/in.h>
#include <carpafinet.h>
#include <netdb.h>
#include <string, h> #include <stdlib.h>
#include <unistd.h> 
#include<stdio.h>
#include <time.h>

void main()
{

int sd, num;
time t current time;
struct sockaddr_in servaddr,cliaddr; sd =
socket(AF_INET, SOCK_DGRAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin _addr.s_addr=htonl(|NADDR_ANY);
servaddr.sin_port=htons(43454),:
cliaddr.sin family=AF_INET;
cliaddr.sin_addr.s_addr=htonl(NADDR_ANY);
cliaddr.sin_port=htons(43455):
bind(sd,(struct sockaddr ")&servaddr,sizeof(servaddr));
printf("Server is running....................\n");
recvfrom(sd, &num, sizeof(num), 0, (struct sockaddr *)&cliaddr, (socklen_t *)&cliaddr);
current_time = time(NULL);
printf("Client asked for time: %s\n",ctime(&current_time)); 
sendto(sd, &current_time, sizeof(current_time),0, (struct sockaddr*&cliaddr, sizeof(cliaddr));
}
