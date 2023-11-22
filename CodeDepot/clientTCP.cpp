/// Old school C-style code
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int sockfd, portNum, n;
	struct sockaddr_in serverAddress;
	struct hostent *server;

	char buffer[256];
	if(argc < 3) {
		std::cerr << "usage " << argv[0] << " hostname port" << std::endl;
		exit(1);
	}
	portNum = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Opening socket");
		exit(1);
	}
	server = gethostbyname(argv[1]);
	if(server == NULL) {
		perror("Client:gethostbyname");
		exit(1);
	}

	bzero((char *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
	serverAddress.sin_port = htons(portNum);

	/// Attempt to connect to the server
	if(connect(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
		perror("Client:connect");
		exit(1);
	}

	std::cout << "Please enter the message:";
	bzero(buffer, sizeof(buffer));
	fgets(buffer, sizeof(buffer)-1, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if(n < 0){
		perror("Client:write");
		exit(1);
	}
	for(;;){
		bzero(buffer, sizeof(buffer));
		n = read(sockfd, buffer, sizeof(buffer)-1 );
		if(n < 0){
			perror("Client:read");
			exit(1);
		}
		std::cout << buffer << std::endl;
		usleep(10000);
	}
	close(sockfd);
	return 0;
}

