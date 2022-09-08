#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	
}

Scene1::~Scene1(){
	
}

bool Scene1::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	

	IMG_Init(IMG_INIT_PNG);
	
	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	
}

void Scene1::Render() {
	Vec3 screenCoords;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));

	

	SDL_UpdateWindowSurface(window);
}