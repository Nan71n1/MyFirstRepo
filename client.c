// client side process that sends data to server and  receives the output

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

    printf("Enter an operator: ");
    scanf("%c", &Q.operator);

    printf("Enter any two numbers: ");
    scanf("%d %d", &Q.num1, &Q.num2);
  
    struct sockaddr_in servaddr;
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }


    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    int len, ans;
    sendto(sockfd, &Q, sizeof(Q), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    
    recvfrom(sockfd, &ans, sizeof(int), 0, (struct sockaddr *) &servaddr, &len);

    if(ans == INT_MAX) {
        printf("Invalid Input\n");
    }
    else {
        printf("%d %c %d = %d\n", Q.num1, Q.operator, Q.num2, ans);
    }
    
    close(sockfd);  
    return 0;
}
