#include <iostream>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_net.h>
#include <SDL_endian.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Vector.h>
#include <Quaternion.h>
using namespace MATH;

void Server(); /// Prototyping

struct Actor {
	Vec3 pos;
	Quaternion orientation;
	uint32_t ID;
};


int main(int argc, char*argv[]){
	Server();
	return 0;
}




void Server(){
	NET_DatagramSocket *sd; /// Socket descriptor 
	NET_Datagram * packet; /// Pointer to packet memory 
	packet = nullptr;
	bool isRunning;
 
	/// Initialize SDL_net
	if (NET_Init() == false) {
		std::cerr << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	/// Open a socket and bind the port to the OS
	if (!(sd = NET_CreateDatagramSocket(NULL,0x1A2B))) {
		std::cerr << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	///Allocate space for the packet
	packet = new NET_Datagram{};

	/// Since I know how many bytes are going makeup the object, I will just allocate that memory with malloc
	Uint8* actorData = reinterpret_cast<Uint8*> (malloc(sizeof(Actor))); /// Don't forget to free it 
	packet->buf = actorData;
	
	/// Main loop
	isRunning = true;
	std::cout << "Listening: " << std::endl;
	
	while (isRunning) {
		if (NET_ReceiveDatagram(sd, &packet) == true){ /// This always returns true unless failure
			if (packet == nullptr) { /// No data have been received
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); /// sleep a bit 
				continue; /// loop around and try again
			}

			const char* s = NET_GetAddressString(packet->addr);
			std::cout << "UDP Packet incoming" << std::endl;
			std::cout << "Data: " << packet->buf << std::endl;
			std::cout << "Len: " << std::dec << packet->buflen << std::endl;
			std::cout << "Net address: " << s << std::endl;

			/// Take the buffer data pointer and convert it to an Actor pointer 
			Actor* bob = reinterpret_cast<Actor*>(packet->buf);

			/// Now treat it like an Actor because it is! It's just bytes
			printf("Actor ID = %d\n", bob->ID);
			bob->pos.print("pos");
			bob->orientation.print("orientation");	
		}
		
	}
	
	if (packet) {
		NET_DestroyDatagram(packet);
		free(actorData);

	}

	/// Clean up and exit the program 
	NET_Quit();
	return;
}