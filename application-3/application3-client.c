// Client side 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <netdb.h> 
#include <stdlib.h> 
#define PORT 8080 

int main() 
{ 
	int sock = 0, valread,a; 
	struct sockaddr_in serv_addr; 
	char str[20],str2[20];
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
	do
	{
	printf("\nclient msg:");
	scanf("%s",str);
	send(sock , str , sizeof(str) , 0 ); 
	listen(sock,1); 
	valread = read( sock , str2, sizeof(str)); 
	printf("\nserver msg:%s",str2);
	if (strncmp("bye", str2, 3) == 0) { 
            printf("Client Exit...\n"); 
	    send(sock , str2 , sizeof(str2) , 0 ); 
            break; 
        }
	}
	while(strncmp("bye", str2, 3) != 0||strncmp("bye", str, 3) != 0);
	return 0; 
} 

