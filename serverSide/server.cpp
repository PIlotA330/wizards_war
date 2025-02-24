#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char * argv[]) {
	// port number to listen on
	const int portNo = 8080;
	
	// listening socket
	int serverfd;
	// socket for active connection
	int clientfd;
	
	struct sockaddr_in serv_addr;   // server address info
	socklen_t addrLength = sizeof(serv_addr);
	char serv_ip[32]; // buffer for storing ip address as a string
	
	struct sockaddr_in client_addr; // client address info
	char client_ip[32]; // buffer for storing ip address as a string
	
	const int domain = AF_INET; // IPv4
	const int type = SOCK_STREAM; // TCP
	const int protocol = 0; // IP
	
	char buffer[256]; // message buffer
	
	// create socket
	serverfd = socket(domain, type, protocol);
	if(serverfd < 0) {
		printf("%s\n", "socket creation failed");
		return -1;
	}
	
	// zero memory in server/client address struct
	memset(&serv_addr, 0, addrLength);
	memset(&client_addr, 0, addrLength);
	
	// server address struct setup
	serv_addr.sin_family = domain; // IPv4
	serv_addr.sin_addr.s_addr = INADDR_ANY;  // any input address
	serv_addr.sin_port = htons(portNo);  
	
	// bind server program to socket
	int res = bind(serverfd, (struct sockaddr*)&serv_addr, addrLength);
	if(res < 0) {
		printf("%s\n","bind failed");
		return -2;
	}
	
	inet_ntop(domain, &(serv_addr.sin_addr), serv_ip, 32);
	printf("Binding done with IP: %s, port: %d\n", serv_ip, ntohs(serv_addr.sin_port));
	
	int queue_length = 3; // buffer up to 3 incoming connection requests
	
	// listen 
	res = listen(serverfd, queue_length);
	if(res < 0) {
		printf("%s\n","listen failure");
		return -3;
	}
	
	// block until incoming client request is received
	clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &addrLength);
	if(clientfd < 0) {
		printf("%s\n","accept failed");
		return -4;
	}
	
	
	inet_ntop(domain, &(serv_addr.sin_addr), serv_ip, 32);	
	printf("connection accepted: server with IP: %s, port: %d\n", serv_ip, ntohs(serv_addr.sin_port));

	// grab IP/port from client, convert IP to a string to print
	inet_ntop(domain, &(client_addr.sin_addr), client_ip, 32);
	printf("connection to client: client IP: %s, port: %d\n", client_ip, ntohs(client_addr.sin_port));

    int connected = 1;

    while (connected) {
    	memset(buffer,0,256); // zero message buffer
    	int n = read(clientfd, buffer, 255); // read message from open connection
    	if(n < 0) {
    		printf("error reading from socket\n");
    		break;
    	}

    	printf("message is: %s\n", buffer);

    	n = write(clientfd, "i got your message", 18);

    	if(n < 0){
    		printf("write fail\n");
    		break;
    	}
    }
	close(clientfd);
	close(serverfd);
}
