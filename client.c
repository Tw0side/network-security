#include<sys/socket.h>
#include <netdb.h>
#include <string.h> 
#include <stdlib.h>
#include netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>
void main()
{
  int sd ,addrlen ,num =1;
time_t start time, rt, current time; struct
sockaddr in servaddr, cliaddr; 
sd=socket(AF_INET, SOCK_DGRAM,0);
servaddr.sin family=AF_INET;
servaddr.sin addr.s_addr=htonl(INADDR_ANY);
servaddr.sin _port-=htons(43454); 
cliaddr.sin family=AF_INET;
cliaddr.sin_addr.s_addr=htonl(INADDR_ANY);
cliaddr.sin_port=htons(43455);
bind(sd,(struct sockadddr *)&cliaddr,sizeof(cliaddr));
printf("Client is running......................"\n);
start_time=time(NULL);
sendto(sd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
addrlen=sizeof(cliaddr);
recvfrom(sd,&current_time,sizeof(current_time),0,(struct sockaddr*) & cliaddr *) &cliaddr ,&addrlen);
rtt = time(NULL)-start_time;
current_time +=rtt/2;
printf("Servers Time :%s\n,",ctime(&current_time));
}
