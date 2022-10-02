// Program to create a server side process to receive data and send the result to the client

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

struct Query {
    int num1;
    int num2;
    char operator;
};
 

int main()
{
    
    int sockfd;
    struct Query Q;
    struct sockaddr_in servaddr, cliaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind Failed\n");
        exit(EXIT_FAILURE);
    }

    int len, size;

    len = sizeof(cliaddr);
    size = sizeof(Q);
    recvfrom(sockfd, &Q, size, 0, (struct sockaddr *) &cliaddr, &len);

    int ans;
    switch(Q.operator) {
        case '+':
        ans = Q.num1 + Q.num2;
        break;

        case '-':
        ans = Q.num1 - Q.num2;
        break;

        case '*':
        ans = Q.num1 * Q.num2;
        break;

        case '/':
        ans = Q.num1 / Q.num2;
        break;

        case '%':
        ans = Q.num1 % Q.num2;
        break;

        default:
        ans = INT_MAX;

    }

    sendto(sockfd, &ans, sizeof(int), 0, (const struct sockaddr *) &cliaddr, len);
    
    close(sockfd);
    return 0;
}
