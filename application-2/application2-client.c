// Client side
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

int main() 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr;
	int buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	printf("Enter the number : ");
	scanf("%d",&buffer[0]);
	send(sock , buffer , sizeof(buffer) , 0 ); 
	printf("\nClient: Number sent to server\n"); 
	valread = read( sock , buffer, 1024); 
	printf("\nsquare of the number is %d",buffer[0]);
	printf("\ncube of the number is %d",buffer[1]);
	return 0; 
} 

