#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>


using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
		
public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
};

#endif

