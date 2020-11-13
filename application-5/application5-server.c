// Server side 
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
 	int s, sock; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len,n,flag; 

	len = sizeof(cliaddr); //len is value/resuslt 
	for (;;) { 
	n = recvfrom(sockfd, (int *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	// whenever a request from a client came. 
        // It will be processed here. 
        printf("\nServer: The number received from client is:%ls\n", buffer); 
      	int num=*buffer;
	// True if num is perfectly divisible by 2
    	if(num % 2 == 0)
        flag=1;
    	else
       	flag=0;
	sendto(sockfd,&flag, sizeof(int), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	break;
}
	return 0; 
}

