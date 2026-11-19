#include <iostream>
#include <string.h>
#include <sstream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_net.h>
#include <Vector.h>
#include <Quaternion.h>
using namespace MATH;

void Client(); /// Prototyping 


struct Actor {
	Vec3 pos;
	Quaternion orientation;
	uint32_t ID;
};

int main(int argc, char*argv[]){
	Client();
	return 0;
}

void Client(){
	
	/// Create an Actor object and populate it with data
	Actor bob;
	bob.ID = 22;
	bob.pos.set(1, 2, 3);
	bob.orientation.set(4, Vec3(5, 6, 7));


	NET_DatagramSocket *sd;
	NET_Address *srvadd;
	NET_Datagram * packet =nullptr;

	bool isRunning;
	
	/// Initialize SDL_net subsystem
	if (NET_Init() == false) {
		std::cerr << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	/// Open a socket and bind the port to the OS
	if(!(sd = NET_CreateDatagramSocket(NULL, 0x1A2B))) {
		std::cerr << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	
 
	/// Resolve server name 
	srvadd = NET_ResolveHostname("127.0.0.1");
	if (srvadd == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	///Make space for the packet
	packet = new NET_Datagram{};

	///Main loop
	isRunning = true;
	while (isRunning){
		std::cout << "Hit Enter to send data: ";
		std::getchar();  /// This will block execution until "Enter"
		
		///  Get the address of "bob"
		Actor* bobsAddress = &bob;

		packet->addr = srvadd;	/// Set the destination host
		packet->port = 0x1A2B;	/// and destination port 

		/// It's all just bytes. Convert the address to an Uint8 pointer
		packet->buf = reinterpret_cast<Uint8*>(bobsAddress);
		/// Get the number of bytes for the Actor struct
		packet->buflen = sizeof(Actor);

		NET_SendDatagram(sd, srvadd, packet->port, packet->buf, packet->buflen);
	}
 

	NET_DestroyDatagram(packet);
	NET_Quit();
 
	return;
}


