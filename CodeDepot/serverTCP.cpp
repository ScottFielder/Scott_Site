#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	int serverSockfd, incomingSockfd, portNum;
	char buffer[0xFF];
	socklen_t clientLength;
	struct sockaddr_in serverAddress, clientAddress;
	int len;

	if(argc < 2) {
		std::cerr << "ERROR, no port provided" << std::endl;
		exit(1);
	}
	/// Create a TCP socket
	serverSockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSockfd < 0){
		std::cerr << "ERROR, opening the socket" << std::endl;
		exit(1);
	}

	bzero((char *)&serverAddress, sizeof(serverAddress));
	portNum = atoi(argv[1]);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNum); /// Convert to big endian

	/// Bind the server's address and the port number with the OS
	if(bind(serverSockfd, (struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0){
		std::cerr << "ERROR, binding socket" << std::endl;
		exit(1);
	}
	/// Listen for incoming connections, the second arg "5" is the max number of 
	/// waiting connections - I think it is the UNIX limit
	listen(serverSockfd, 5);

	clientLength = sizeof(clientAddress);
	std::cout << "about to call accept" << std::endl;
	incomingSockfd = accept(serverSockfd,(struct sockaddr *) &clientAddress,&clientLength);
	std::cout << "accept returned" << std::endl;

	/// (Weird stuff, you need to send the clientLength address because this 
	/// function will place the address length of the returned address - don't
	/// ask unless you're a super geek)

	if(incomingSockfd < 0){
		std::cerr << "ERROR on accept" << std::endl;
		exit(1);
	}

	bzero(buffer, sizeof(buffer));
	len = read(incomingSockfd, buffer, sizeof(buffer)-1);
	if(len < 0){
		std::cerr << "ERROR on read" << std::endl;
		exit(1);
	}

	std::cout << "=>" << buffer << std::endl;
	char msg[] = "Received your message";
	len = write(incomingSockfd, msg, sizeof(msg));
	if(len < 0) {
		std::cerr << "ERROR writing to the socket" << std::endl;
		exit(1);
	}

	close(incomingSockfd);
	close(serverSockfd);
	return 0;
}

