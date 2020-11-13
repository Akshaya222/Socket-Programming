// Server side
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main() 
{ 
	int server_fd, new_socket, valueread,number,cube,square; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	int buffer[1024] = {0}; 
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))  
												
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)  
								
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valueread = read( new_socket , buffer, 1024); 
	printf("Server:Number received from client is %d",buffer[0]);
	number=buffer[0];
	square=number*number;
	cube=square*number;
	buffer[0]=square;
	buffer[1]=cube;
	send(new_socket , buffer ,sizeof(buffer), 0 ); 
	printf("\nServer:Square and cube values sent to client\n"); 
	return 0; 
} 

