// Client side 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	int buffer[MAXLINE]; 
	struct sockaddr_in  servaddr; 
	int n, len,flag;
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	
 	for (;;) { 
        printf("\nEnter a number to check even or odd: "); 
        scanf("%ls", buffer); 
  
        printf("\nNumber sent from Client is: %ls", buffer); 
       
  	sendto(sockfd, (const int *)buffer, sizeof(buffer), 
		 MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	n = recvfrom(sockfd,&flag, sizeof(int),
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
        if (flag == 1) { 
            printf("\nServer: The number is even\n"); 
            break; 
        } 
        else { 
            printf("\nServer:The number is odd\n"); 
            break; 
        } 
    } 
  
	close(sockfd); 
	return 0; 
} 

