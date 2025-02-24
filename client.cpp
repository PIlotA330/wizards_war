#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char * argv[]) {
	int clientfd;
	const int serverPort = 8080;
	
	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;
	int addrLength = sizeof(server_addr);
	
	const int domain = AF_INET; // IPv4
	const int type = SOCK_STREAM; // TCP
	const int protocol = 0; // IP
	
	// create socket
	clientfd = socket(domain, type, protocol);
	
	if(clientfd < 0) {
		printf("%s\n", "socket creation failed");
		return -1;
	}
	
	server_addr.sin_family = domain; // IPv4
	inet_pton(domain, "3.142.172.167", &(server_addr.sin_addr));
	server_addr.sin_port = htons(serverPort); 
	
	int res = connect(clientfd, (struct sockaddr *)&server_addr, addrLength);
	if(res < 0) {
		printf("%s\n", "connection error");
	}
	
	// create and zero buffer for sending/receiving messages
	char buffer[256];
	int connected = 1;
	while(connected) {
		memset(buffer, 0, 256);

		// grab message from user via standard in
		printf("enter a message:\n");
		fgets(buffer, 255, stdin);

		// write to the socket
		int n = write(clientfd, buffer, strlen(buffer));
		if(n < 0 ) {
			printf("write failed\n");
			return -1;
		}

		// zero buffer to receive response and read response
		memset(buffer, 0, 256);
		n = read(clientfd, buffer, 255);
		if(n < 0) {
			printf("read error\n");
			connected = 0;
		}
		// print response
		printf("Server's reponse: %s\n", buffer);
	}
	close(clientfd);
}

