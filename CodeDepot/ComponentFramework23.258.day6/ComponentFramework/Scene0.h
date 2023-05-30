#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
class CameraActor;
class LightActor;

class Scene0 : public Scene {
private:
	Actor* mario;
	CameraActor* camera;
	LightActor* light;
public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event &sdlEvent);
};


#endif // SCENE0_H