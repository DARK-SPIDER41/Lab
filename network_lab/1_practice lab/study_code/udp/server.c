#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
void main() {
int sockfd;
char buffer[MAXLINE]={0};
char *hello = "Hello from server";
struct sockaddr_in servaddr, cliaddr;
// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
// Filling server information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind the socket with the server address
if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
{
perror("bind failed");
exit(EXIT_FAILURE);
}
int len, n;
len = sizeof(cliaddr); //len is value/result
n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr*) &cliaddr,&len);
printf("Client : %s\n", buffer);
sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr*) &cliaddr,len);
printf("Hello message sent.\n");
}
