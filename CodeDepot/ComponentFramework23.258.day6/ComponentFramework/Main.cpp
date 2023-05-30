#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include <string>
#include "SceneManager.h"
#include "Debug.h"

  
int main(int argc, char* args[]) {
	
	/// Comment out the line below if you really want to make a 64-bit build
	static_assert(sizeof(void*) == 4, "Are you ready for 64-bit build?");

	Debug::DebugInit("GameEngineLog.txt");
	
	SceneManager* gsm = new SceneManager();
	if (gsm->Initialize("Game Engine", 1280, 720) ==  true) {
		gsm->Run();
	} 
	delete gsm;
	exit(0);
}